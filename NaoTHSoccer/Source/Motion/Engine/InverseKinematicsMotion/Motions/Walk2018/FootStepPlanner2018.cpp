/**
* @file FootStepPlanner.cpp
*
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
* plan the foot step according to motion request
*/

#include "FootStepPlanner2018.h"

using namespace InverseKinematic;
using namespace std;

FootStepPlanner2018::FootStepPlanner2018()
:
  theMaxTurnInner(0.0),
  theMaxStepTurn(0.0),
  theMaxStepLength(0.0),
  theMaxStepLengthBack(0.0),
  theMaxStepWidth(0.0),
  theFootOffsetY(0.0),
  theMaxChangeTurn(0.0),
  theMaxChangeX(0.0),
  theMaxChangeY(0.0),

  theMaxCtrlTurn(0.0),
  theMaxCtrlLength(0.0),
  theMaxCtrlWidth(0.0),
  emergencyCounter(0)
{
}

void FootStepPlanner2018::updateParameters(const IKParameters& parameters)
{
  theMaxTurnInner = Math::fromDegrees(parameters.walk.limits.maxTurnInner);
  theMaxStepTurn = Math::fromDegrees(parameters.walk.limits.maxStepTurn);
  theMaxStepLength = parameters.walk.limits.maxStepLength;
  theMaxStepLengthBack = parameters.walk.limits.maxStepLengthBack;
  theMaxStepWidth = parameters.walk.limits.maxStepWidth;
  
  // step control
  theMaxCtrlTurn = parameters.walk.limits.maxCtrlTurn;
  theMaxCtrlLength = parameters.walk.limits.maxCtrlLength;
  theMaxCtrlWidth = parameters.walk.limits.maxCtrlWidth;


  theFootOffsetY = NaoInfo::HipOffsetY + parameters.footOffsetY;
  
  theMaxChangeTurn = theMaxStepTurn * parameters.walk.limits.maxStepChange;
  theMaxChangeX = theMaxStepLength * parameters.walk.limits.maxStepChange;
  theMaxChangeY = theMaxStepWidth * parameters.walk.limits.maxStepChange;
}

void FootStepPlanner2018::execute(){
    // add the initial step
    // NOTE: zmp for this step it already completely planed,
    //       so we add the actual first step right after
    if(getStepBuffer().empty())
    {
      std::cout << "walk start" << std::endl;

      // use the current com pose as a basis for start
      CoMFeetPose currentCOMFeetPose = getInverseKinematicsMotionEngineService().getEngine().getCurrentCoMFeetPose();
      currentCOMFeetPose.localInLeftFoot();

      Vector3d startZMPTarget(currentCOMFeetPose.com.translation);
      startZMPTarget.z = getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.hip.comHeight;

      // new step (don't move the feet)
      Step& initialStep = getStepBuffer().add();
      initialStep.footStep = FootStep(currentCOMFeetPose.feet, FootStep::NONE);

      // initialize the zmp buffer with the current com pose
      initialStep.numberOfCycles = getInverseKinematicsMotionEngineService().getEngine().zmpControl.init(currentCOMFeetPose.com.translation, startZMPTarget);
      initialStep.planningCycle = initialStep.numberOfCycles;
    }

    // current step has been executed, remove
    if ( getStepBuffer().first().isExecuted() ) {
      getStepBuffer().pop();
    }

    // add a new step
    if(getStepBuffer().last().isPlanned()) {
      const Step& lastStep = getStepBuffer().last();
      Step& step = getStepBuffer().add();
      calculateNewStep(lastStep, step, getMotionRequest().walkRequest);
    }
}

void FootStepPlanner2018::calculateNewStep(const Step& lastStep, Step& newStep, const WalkRequest& walkRequest) //const
{
  // update the parameters in case they have changed
  updateParameters(getInverseKinematicsMotionEngineService().getEngine().getParameters());

  newStep.walkRequest = walkRequest;

  // STABILIZATION
  bool do_emergency_stop = getCoMErrors().absolute2.isFull() && getCoMErrors().absolute2.getAverage() > getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.stabilization.emergencyStopError;

  if ( getMotionRequest().id != motion::walk2018 /*getId()*/ || (do_emergency_stop && !walkRequest.stepControl.isProtected))
  {
    // TODO: find reason for deadlock
    // current fix: force leaving emergency_stop after some cycles
    if(do_emergency_stop) {
      emergencyCounter++;
    }

    PLOT("Walk:emergencyCounter",emergencyCounter);

    if(emergencyCounter > getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.stabilization.maxEmergencyCounter){
        emergencyCounter = 0;
        getCoMErrors().absolute2.clear();
    }

    // try to make a last step to align the feet if it is required
    if ( getMotionRequest().standardStand ) {
      newStep.footStep = finalStep(lastStep.footStep, walkRequest);
    } else {
      newStep.footStep = zeroStep(lastStep.footStep);
    }

    newStep.numberOfCycles = (newStep.footStep.liftingFoot() == FootStep::NONE)?1:getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.step.duration/getRobotInfo().basicTimeStep;
    newStep.type = Step::STEP_WALK;

    // print it only once
    if(newStep.footStep.liftingFoot() == FootStep::NONE && lastStep.footStep.liftingFoot() != FootStep::NONE) {
      std::cout << "walk stopping ..." << std::endl;
    }
    return;
  } else {
      // reset emergencyCounter if the stop was succesful (no deadlock case)
      emergencyCounter = 0;
  }

  if (walkRequest.stepControl.stepRequestID == getMotionStatus().stepControl.stepRequestID + 1)
  {
    // return the accepted stepRequestID
    getMotionStatus().stepControl.stepRequestID += 1;

    switch (walkRequest.stepControl.type)
    {
    case WalkRequest::StepControlRequest::ZEROSTEP:
      newStep.footStep = zeroStep(lastStep.footStep);
      newStep.numberOfCycles = walkRequest.stepControl.time / getRobotInfo().basicTimeStep;
      newStep.type = Step::STEP_CONTROL;
      break;
    case WalkRequest::StepControlRequest::KICKSTEP:
      newStep.footStep = controlStep(lastStep.footStep, walkRequest);
      newStep.numberOfCycles = walkRequest.stepControl.time / getRobotInfo().basicTimeStep;
      newStep.type = Step::STEP_CONTROL;
      break;
    case WalkRequest::StepControlRequest::WALKSTEP:
    {
      newStep.footStep = controlStep(lastStep.footStep, walkRequest);

      int duration = getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.step.duration;

      if(getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.step.dynamicDuration)
      {
        if(walkRequest.character <= 0.3) {
          duration = 300;
        } else if(walkRequest.character <= 0.7) {
          duration = 280;
        } else {// if(walkRequest.character == 1) {
          duration = 260;
        }
      }

      //newStep.numberOfCycles = parameters().step.duration / getRobotInfo().basicTimeStep;
      newStep.numberOfCycles = duration / getRobotInfo().basicTimeStep;
      newStep.type = Step::STEP_CONTROL;

      PLOT("Walk:after_adaptStepSize_x", newStep.footStep.footEnd().translation.x);
      PLOT("Walk:after_adaptStepSize_y", newStep.footStep.footEnd().translation.y);
      break;
    }
    default:
      ASSERT(false);
    }

    // STABILIZATION
    if (getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.stabilization.dynamicStepsize && !walkRequest.stepControl.isProtected) {
      adaptStepSize(newStep.footStep);
      getCoMErrors().e.clear();
    }

  }
  else // regular walk
  {
    newStep.footStep = nextStep(lastStep.footStep, walkRequest);
    newStep.numberOfCycles = getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.step.duration / getRobotInfo().basicTimeStep;
    newStep.type = Step::STEP_WALK;

    // STABILIZATION
    if (getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.stabilization.dynamicStepsize) {
      adaptStepSize(newStep.footStep);
      getCoMErrors().e.clear();
    }

    PLOT("Walk:XABSL_after_adaptStepSize_x", newStep.footStep.footEnd().translation.x);
    PLOT("Walk:XABSL_after_adaptStepSize_y", newStep.footStep.footEnd().translation.y);
  }
}

void FootStepPlanner2018::adaptStepSize(FootStep& step) const
{
  // only do something when the buffer is not empty
  if(getCoMErrors().e.size() > 0)
  {
    Vector3d errorCoM = getCoMErrors().e.getAverage();
    static Vector3d lastCoMError = errorCoM;

    Vector3d comCorrection = errorCoM*getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.stabilization.dynamicStepsizeP +
                          (errorCoM - lastCoMError)*getInverseKinematicsMotionEngineService().getEngine().getParameters().walk.stabilization.dynamicStepsizeD;

    Vector3d stepCorrection = step.supFoot().rotation * comCorrection;
    step.footEnd().translation.x += stepCorrection.x;
    step.footEnd().translation.y += stepCorrection.y;

    lastCoMError = errorCoM;
  }
}//end adaptStepSize

FootStep FootStepPlanner2018::finalStep(const FootStep& lastStep, const WalkRequest& /*req*/)
{
  // don't move the feet if they stoped moving once
  if(lastStep.liftingFoot() == FootStep::NONE) {
    return zeroStep(lastStep);
  }

  // TODO: check if an actual step is necessary based on the last step
  //       => calculate an actual step only if necessary

  // try to plan a real last step with an empty walk request
  FootStep footStep = nextStep(lastStep, WalkRequest());
  // how much did the foot move in this step
  Pose3D diff = footStep.footBegin().invert() * footStep.footEnd();

  // planed step almost didn't move the foot, i.e., is was almost a zero step
  if(diff.translation.abs2() < 1 && diff.rotation.getZAngle() < Math::fromDegrees(1)) {
    return zeroStep(lastStep);
  } else {
    return footStep;
  }
}

FootStep FootStepPlanner2018::nextStep(const FootStep& lastStep, const WalkRequest& req)
{
  if ( lastStep.liftingFoot() == FootStep::NONE ) {
    return firstStep(lastStep.end(), lastStep.offset(), lastStep.stepRequest(), req);
  } else {
    FootStep::Foot liftingFoot = (lastStep.liftingFoot()==FootStep::LEFT)?FootStep::RIGHT:FootStep::LEFT;
    return calculateNextWalkStep(lastStep.end(), lastStep.offset(), lastStep.stepRequest(), liftingFoot, req, false);
  }
}


FootStep FootStepPlanner2018::controlStep(const FootStep& lastStep, const WalkRequest& req)
{
  WalkRequest myReq = req;
  myReq.target = req.stepControl.target;//HACK

  FootStep::Foot liftingFoot = req.stepControl.moveLeftFoot?FootStep::LEFT:FootStep::RIGHT;
  return calculateNextWalkStep(lastStep.end(), lastStep.offset(), lastStep.stepRequest(), liftingFoot, myReq, true);
}

FootStep FootStepPlanner2018::zeroStep(const FootStep& lastStep) const
{
  return FootStep(lastStep.end(), FootStep::NONE);
}

FootStep FootStepPlanner2018::firstStep(const InverseKinematic::FeetPose& pose, const Pose2D& offset, const Pose2D& lastStepRequest, const WalkRequest& req)
{
  FootStep firstStepLeft = calculateNextWalkStep(pose, offset, lastStepRequest, FootStep::LEFT, req);
  FootStep firstStepRight = calculateNextWalkStep(pose, offset, lastStepRequest, FootStep::RIGHT, req);
  
  Pose3D leftMove = firstStepLeft.footBegin().invert() * firstStepLeft.footEnd();
  Pose3D rightMove = firstStepRight.footBegin().invert() * firstStepRight.footEnd();

  if ( fabs(req.target.rotation) > theMaxTurnInner )
  {
    // choose foot by rotation
    double leftTurn = leftMove.rotation.getZAngle();
    double rightTurn = rightMove.rotation.getZAngle();
    if ( fabs(leftTurn) > fabs(rightTurn) ) {
      return firstStepLeft;
    } else {
      return firstStepRight;
    }
  }
  else
  {
    // choose foot by distance
    if ( leftMove.translation.abs2() > rightMove.translation.abs2() ) {
      return firstStepLeft;
    } else {
      return firstStepRight;
    }
  }
}//end firstStep

// TODO: parameter for the foot to move
FootStep FootStepPlanner2018::calculateNextWalkStep(const InverseKinematic::FeetPose& pose, const Pose2D& offset, const Pose2D& lastStepRequest, FootStep::Foot movingFoot, const WalkRequest& req, bool stepControl)
{
  // TODO: how to deal with zero steps properly
  ASSERT(movingFoot != FootStep::NONE);

  // transform between the foot coordinates and the corresponding origin
  const Pose2D supportOriginOffset = offset * Pose2D(0, theFootOffsetY);
  const Pose2D targetOriginOffset = req.offset * Pose2D(0, theFootOffsetY);

  // transform between the global odometry coordinates and the origin of the support foot
  const Pose2D supportOrigin = (movingFoot == FootStep::RIGHT)?
    pose.left.projectXY() * supportOriginOffset.invert() :
    pose.right.projectXY() * supportOriginOffset;

  // transform the request in the coordinates of the support origin
  Pose2D stepRequest = req.target;
  if (req.coordinate == WalkRequest::LFoot) {
    stepRequest = supportOrigin.invert() * pose.left.projectXY() * stepRequest * targetOriginOffset.invert();
  } else if(req.coordinate == WalkRequest::RFoot) {
    stepRequest = supportOrigin.invert() * pose.right.projectXY() * stepRequest * targetOriginOffset;
  }

  // apply restriction mode
  if (stepControl && req.stepControl.restriction == WalkRequest::StepControlRequest::RestrictionMode::SOFT)
  {
    restrictStepSizeControlStep(stepRequest, req.character);
  } 
  else if (stepControl && req.stepControl.restriction == WalkRequest::StepControlRequest::RestrictionMode::HARD)
  {
    restrictStepSize(stepRequest, req.character);
    restrictStepChange(stepRequest, lastStepRequest);
  }
  else
  {
    restrictStepSize(stepRequest, req.character);
    restrictStepChange(stepRequest, lastStepRequest);
  }

  // create a new step
  FootStep newStep(pose, movingFoot);
  newStep.offset() = req.offset;
  newStep.stepRequest() = stepRequest; // HACK: save the step request before geometrical restrictions


  // apply geometric restrictions to the step request
  if(movingFoot == FootStep::RIGHT) {
    stepRequest = Pose2D(min(theMaxTurnInner, stepRequest.rotation), stepRequest.translation.x, min(0.0, stepRequest.translation.y));
  } else {
    stepRequest = Pose2D(max(-theMaxTurnInner, stepRequest.rotation), stepRequest.translation.x, max(0.0, stepRequest.translation.y));
  }

  // apply the planed motion and calculate the coordinates of the moving foot
  Pose2D footStepTarget = supportOrigin * stepRequest * ((movingFoot == FootStep::RIGHT) ? targetOriginOffset.invert() : targetOriginOffset);

  newStep.footEnd() = Pose3D::embedXY(footStepTarget);

  return newStep;
}//end calculateNextWalkStep


void FootStepPlanner2018::restrictStepSize(Pose2D& step, double character) const
{
  // scale the character: [0, 1] --> [0.5, 1]
  character = 0.5*character + 0.5;


  double maxTurn = theMaxStepTurn * character;
  
  /*double maxLen = sqrt(theMaxStepLength * theMaxStepLength + theMaxStepWidth * theMaxStepWidth) * character;

  if (maxLen > 1)
  {
    Pose3D lastHip = lastStep.supFoot();
    lastHip.translate(0, static_cast<int>(lastStep.liftingFoot())*theFootOffsetY*2, 0);
    double lastStepLen = (lastStep.footEnd().translation - lastHip.translation).abs();
    maxTurn *= Math::clamp(1 - lastStepLen / maxLen, 0.5, 1.0);
  }*/

  // limit the rotation
  step.rotation = Math::clamp(step.rotation, -maxTurn, maxTurn);

  double maxStepLength = theMaxStepLength * character;
  double maxStepLengthBack = theMaxStepLengthBack * character;
  double maxStepWidth = theMaxStepWidth * character;
  if ( step.translation.x < 0 )
  {
    maxStepLength = maxStepLengthBack;
  }


  if ( maxStepLength > 0.5  && maxStepWidth > 0.5 )
  {
    // restrict the step size in an ellipse
    double alpha = step.translation.angle();
    double cosa = cos(alpha);
    double sina = sin(alpha);

    const double maxStepLength2 = Math::sqr(maxStepLength);
    const double maxStepWidth2 = Math::sqr(maxStepWidth);
    double length = sqrt((maxStepLength2 * maxStepWidth2) / (maxStepLength2 * Math::sqr(sina) + maxStepWidth2 * Math::sqr(cosa)));
    if (step.translation.abs2() > Math::sqr(length))
    {
      step.translation.x = length * cosa;
      step.translation.y = length * sina;
    }

    ASSERT( step.translation.x > -maxStepLengthBack - 1e-5 );
    ASSERT( step.translation.x < maxStepLength + 1e-5 );
    ASSERT( fabs(step.translation.y) < maxStepWidth + 1e-5 );
  }
  else
  {
    if (step.translation.x < -maxStepLengthBack) {
      step.translation.x = -maxStepLengthBack;
    } else if (step.translation.x > maxStepLength ) {
      step.translation.x = maxStepLength;
    }
    
    if (theMaxStepWidth > numeric_limits<double>::epsilon()) {
      step.translation.y = Math::clamp(step.translation.y, -maxStepWidth, maxStepWidth);
    } else {
      step.translation.y = 0;
    }

    ASSERT( fabs(step.translation.x) <= maxStepLength );
    ASSERT( fabs(step.translation.y) <= maxStepWidth );
  }

  if ( maxTurn > Math::fromDegrees(1.0) ) {
    step.translation *= cos( step.rotation/maxTurn * Math::pi / 2);
  }
}//end restrictStepSize


void FootStepPlanner2018::restrictStepSizeControlStep(Pose2D& step, double character) const
{
  character = 0.5*character + 0.5;

  double maxTurn =  theMaxCtrlTurn * character;
  double maxStepLength = theMaxCtrlLength * character;
  double maxStepWidth = theMaxCtrlWidth * character;

  // limit the rotation
  step.rotation = Math::clamp(step.rotation, -maxTurn, maxTurn);

  // limit translation
  if ( maxStepLength > 0.5  && maxStepWidth > 0.5 )
  {
    // restrict the step size in an ellipse
    double alpha = step.translation.angle();
    double cosa = cos(alpha);
    double sina = sin(alpha);

    const double maxStepLength2 = Math::sqr(maxStepLength);
    const double maxStepWidth2 = Math::sqr(maxStepWidth);
    double length = sqrt((maxStepLength2 * maxStepWidth2) / (maxStepLength2 * Math::sqr(sina) + maxStepWidth2 * Math::sqr(cosa)));
    if (step.translation.abs2() > Math::sqr(length))
    {
      step.translation.x = length * cosa;
      step.translation.y = length * sina;
    }

    //ASSERT( step.translation.x > -maxStepLengthBack - 1e-5 );
    ASSERT( step.translation.x < maxStepLength + 1e-5 );
    ASSERT( fabs(step.translation.y) < maxStepWidth + 1e-5 );
  }
}//end restrictStepSizeControlStep


void FootStepPlanner2018::restrictStepChange(Pose2D& step, const Pose2D& lastStep) const
{
  Pose2D change;
  change.translation = step.translation - lastStep.translation;
  change.rotation = Math::normalize(step.rotation - lastStep.rotation);
  double maxX = theMaxChangeX;
  double maxY = theMaxChangeY;
  double maxT = theMaxChangeTurn;

  change.translation.x = Math::clamp(change.translation.x, -maxX, maxX);
  change.translation.y = Math::clamp(change.translation.y, -maxY, maxY);
  change.rotation = Math::clamp(change.rotation, -maxT, maxT);

  step.translation = lastStep.translation + change.translation;
  step.rotation = Math::normalize(lastStep.rotation + change.rotation);
}
