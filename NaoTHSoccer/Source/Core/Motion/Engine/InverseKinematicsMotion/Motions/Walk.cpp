/**
* @file Walk.cpp
*
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
*
*/

#include "Walk.h"
#include "Walk/ZMPPlanner.h"
#include "Walk/FootTrajectoryGenerator.h"

using namespace InverseKinematic;

Walk::Walk()
:IKMotion(motion::walk),
theWalkParameters(theParameters.walk),
theWaitLandingCount(0),
theUnsupportedCount(0),
isStopping(false),
stoppingStepFinished(false)
{
}
  
void Walk::execute(const MotionRequest& motionRequest, MotionStatus& motionStatus)
{
  //calculateError();

  bool protecting = FSRProtection();
  if ( protecting && canStop() )
  {
    stepBuffer.clear();
    theEngine.controlZMPclear();
    currentState = motion::stopped;
    return;
  }
  else if ( !waitLanding() )
  {
    plan(motionRequest);
    theCoMFeetPose = executeStep();
  }

  HipFeetPose c = theEngine.controlCenterOfMass(theCoMFeetPose);

  theEngine.rotationStabilize(c.hip);

  theEngine.solveHipFeetIK(c);
  theEngine.copyLegJoints(theMotorJointData.position);
  theEngine.autoArms(c, theMotorJointData.position);

  // force the hip joint
  if (theMotorJointData.position[JointData::LHipRoll] < 0)
    theMotorJointData.position[JointData::LHipRoll] *= theWalkParameters.leftHipRollSingleSupFactor;

  if (theMotorJointData.position[JointData::RHipRoll] > 0)
    theMotorJointData.position[JointData::RHipRoll] *= theWalkParameters.rightHipRollSingleSupFactor;
}

bool Walk::FSRProtection()
{
  // no foot on the ground, stop walking
  if ( theWalkParameters.enableFSRProtection &&
    theBlackBoard.theSupportPolygon.mode == SupportPolygon::NONE )
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Walk::waitLanding()
{
  if ( currentState != motion::running
      || theBlackBoard.theSupportPolygon.mode == SupportPolygon::NONE )
  {
    theUnsupportedCount = 0;
    return false;
  }

  double leftH = theCoMFeetPose.feet.left.translation.z;
  double rightH = theCoMFeetPose.feet.right.translation.z;
  bool raiseLeftFoot = leftH > 0.1 && leftH > rightH;
  bool raiseRightFoot = rightH > 0.1 && rightH > leftH;

  // don't raise two feet
  ASSERT( !(raiseLeftFoot && raiseRightFoot) );
  
  bool leftFootSupportable = theBlackBoard.theSupportPolygon.isLeftFootSupportable();
  bool rightFootSupportable = theBlackBoard.theSupportPolygon.isRightFootSupportable();

  bool unSupporting = (raiseLeftFoot && !rightFootSupportable)
                      || (raiseRightFoot && !leftFootSupportable);
                      
  if(unSupporting)
  {
    theUnsupportedCount++;
  }
  else
  {
    theUnsupportedCount = 0;
  }

  if ( theUnsupportedCount > theWalkParameters.maxUnsupportedCount
    && ( theWalkParameters.maxWaitLandingCount < 0 || theWaitLandingCount < theWalkParameters.maxWaitLandingCount) )
  {
    theWaitLandingCount++;
    return true;
  } else
  {
    theWaitLandingCount = 0;
    return false;
  }
}

bool Walk::canStop() const
{
  if (isStopping || stepBuffer.empty() )
    return true;
    
  // wait until full step finished
  const Step& planningStep = stepBuffer.back();
  return planningStep.planningCycle >= planningStep.numberOfCyclePerFootStep;
}

void Walk::plan(const MotionRequest& motionRequest)
{
  WalkRequest walkRequest = motionRequest.walkRequest;
  ASSERT(!Math::isNan(walkRequest.translation.x));
  ASSERT(!Math::isNan(walkRequest.translation.y));
  ASSERT(!Math::isNan(walkRequest.rotation));
  
  if ( motionRequest.id == getId() || !canStop() )
  {
    walk(walkRequest);
    isStopping = false;
    stoppingStepFinished = false;
  }
  else
  {
    if (motionRequest.standardStand) // should end with typical stand
    {
      stopWalking();
    }
    else
    {
      stopWalkingWithoutStand();
    }
  }
}

void Walk::manageSteps(const WalkRequest& req)
{
  if ( stepBuffer.empty() )
  {
    cout<<"walk start"<<endl;
    ZMPFeetPose currentZMP = theEngine.getPlannedZMPFeetPose();
    currentZMP.localInLeftFoot();
    currentZMP.zmp.translation.z = theWalkParameters.comHeight;
    Step zeroStep;
    updateParameters(zeroStep);
    zeroStep.footStep = FootStep(currentZMP.feet, FootStep::NONE);
    int prepareStep = theEngine.controlZMPstart(currentZMP);
    zeroStep.numberOfCyclePerFootStep = prepareStep;
    zeroStep.planningCycle = prepareStep;
    stepBuffer.push_back(zeroStep);
    theFootStepPlanner.updateParameters(theParameters);

    // set the stiffness for walking
    for( int i=JointData::RShoulderRoll; i<JointData::numOfJoint; i++)
    {
      theMotorJointData.stiffness[i] = theWalkParameters.stiffness;
    }
  }

  Step& planningStep = stepBuffer.back();
  if ( planningStep.planningCycle >= planningStep.numberOfCyclePerFootStep )
  {
    // this step is planned completely
    // new foot step
    Step step;
    step.footStep = theFootStepPlanner.nextStep(planningStep.footStep, req);
    theFootStepPlanner.updateParameters(theParameters);
    updateParameters(step);
    stepBuffer.push_back(step);
  }
}

void Walk::planStep()
{
  Step& planningStep = stepBuffer.back();
  ASSERT(planningStep.planningCycle < planningStep.numberOfCyclePerFootStep);
  Vector2d zmp = ZMPPlanner::simplest(planningStep.footStep, theParameters.hipOffsetX, theWalkParameters.ZMPOffsetY);
  // TODO: change the height?
  theEngine.controlZMPpush(Vector3d(zmp.x, zmp.y, theWalkParameters.comHeight));
  planningStep.planningCycle++;
}

CoMFeetPose Walk::executeStep()
{
  Vector3d com;
  if ( !theEngine.controlZMPpop(com) || stepBuffer.empty() )
  {
    return theEngine.getCurrentCoMFeetPose();
  }

  Step& executingStep = stepBuffer.front();
  ASSERT(executingStep.executingCycle < executingStep.planningCycle);

  FootStep& exeFootStep = executingStep.footStep;
  Pose3D* liftFoot = NULL;

  CoMFeetPose result;
  bool footSupporting;
  switch(exeFootStep.liftingFoot())
  {
  case FootStep::LEFT:
  {
    liftFoot = &result.feet.left;
    result.feet.right = exeFootStep.supFoot();
    footSupporting = theBlackBoard.theSupportPolygon.isRightFootSupportable();
    break;
  }
  case FootStep::RIGHT:
  {
    liftFoot = &result.feet.right;
    result.feet.left = exeFootStep.supFoot();
    footSupporting = theBlackBoard.theSupportPolygon.isLeftFootSupportable();
    break;
  }
  case FootStep::NONE:
  {
    result.feet = exeFootStep.begin();
    break;
  }
  default: ASSERT(false);
  }

  if ( liftFoot != NULL )
  {

    // checking on when the foot is lifting
    if ( !executingStep.lifted ) // the foot is on the ground now
    {
      double doubleSupportEnd = executingStep.samplesDoubleSupport / 2 + executingStep.extendDoubleSupport;
      if( executingStep.executingCycle > doubleSupportEnd ) // want to lift the foot
      {
        int maxExtendSamples = static_cast<int>( theWalkParameters.maxExtendDoubleSupportTime / theBlackBoard.theRobotInfo.basicTimeStep );
        if( !footSupporting // but another foot can not support
            && executingStep.extendDoubleSupport < maxExtendSamples ) // allow to extend double support
        {
          executingStep.extendDoubleSupport++;
        }
        else
        {
          executingStep.lifted = true;
          //cout<<"extend "<<executingStep.extendDoubleSupport<<"/"<<maxExtendSamples<<endl;
        }
      }
    }

    *liftFoot = FootTrajectorGenerator::genTrajectory(exeFootStep.footBegin(),
                                                      exeFootStep.footEnd(),
                                                      executingStep.executingCycle,
                                                      executingStep.samplesDoubleSupport,
                                                      executingStep.samplesSingleSupport,
                                                      executingStep.extendDoubleSupport,
                                                      theWalkParameters.stepHeight, 0, 0, 0,
                                                      theWalkParameters.curveFactor);
  }

  result.com.translation = com;
  result.com.rotation = calculateBodyRotation(result.feet ,executingStep.bodyPitchOffset);

  executingStep.executingCycle++;
  if ( executingStep.executingCycle >= executingStep.numberOfCyclePerFootStep )
  {
    ASSERT( stepBuffer.size() > 1);
    // this step is executed
    stepBuffer.pop_front();
    //theCoMErr /= numberOfCyclePerFootStep;
    theCoMErr = Vector3d();
  }

  return result;
}

RotationMatrix Walk::calculateBodyRotation(const FeetPose& feet, double pitch) const
{
  double rAng = feet.left.rotation.getZAngle();
  double lAng = feet.right.rotation.getZAngle();
  double bodyRotation = Math::calculateMeanAngle(rAng, lAng);
  if (abs(Math::normalizeAngle(bodyRotation - lAng)) > Math::pi_2)
  {
    bodyRotation = Math::normalizeAngle(bodyRotation + Math::pi);
  }
  RotationMatrix rot = RotationMatrix::getRotationZ(bodyRotation);
  rot.rotateY(pitch);
  return rot;
}

void Walk::walk(const WalkRequest& req)
{
  manageSteps(req);
  planStep();
  currentState = motion::running;
}

void Walk::stopWalking()
{
  ////////////////////////////////////////////////////////
  // add one step to get stand pose
  ///////////////////////////////////////////////////////

  if ( currentState == motion::stopped )
    return;

  if ( !isStopping ) // remember the stopping foot
  {
    /*
    switch (currentFootStep.liftingFoot()) {
    case FootStep::LEFT:
      stoppingRequest.coordinate = WalkRequest::LFoot;
      break;
    case FootStep::RIGHT:
      stoppingRequest.coordinate = WalkRequest::RFoot;
      break;
    }*/

    stoppingRequest.coordinate = WalkRequest::Hip;
    stoppingRequest.translation.x = 0;
    stoppingRequest.translation.y = 0;
    stoppingRequest.rotation = 0;
  }

  if ( !stoppingStepFinished )
  {
    // make stopping step
    manageSteps(stoppingRequest);

    const Step& planningStep = stepBuffer.back();
    if ( planningStep.planningCycle == 0 )
    {
      Pose3D diff = planningStep.footStep.footBegin().invert() * planningStep.footStep.footEnd();
      if ( diff.translation.abs2() < 1 && diff.rotation.getZAngle() < Math::fromDegrees(1) )
      {
        // don't need to move the foot
        FootStep zeroStep(planningStep.footStep.end(), FootStep::NONE);
        Step& lastStep = stepBuffer.back();
        lastStep.footStep = zeroStep;
        lastStep.numberOfCyclePerFootStep = 0;
        stoppingStepFinished = true;
      }
    }
  }

  if ( !stoppingStepFinished )
  {
    planStep();
  }
  else
  {
    Pose3D finalLeftFoot = stepBuffer.back().footStep.end().left;
    CoMFeetPose standPose = getStandPose(theWalkParameters.comHeight);
    standPose.localInLeftFoot();
    Pose3D finalBody = finalLeftFoot * standPose.com;
    // wait for the com stops
    if ( theEngine.controlZMPstop(finalBody.translation) )
    {
      currentState = motion::stopped;
      stepBuffer.clear();
      cout<<"walk stopped"<<endl;
    }
    else
    {
      Step& lastStep = stepBuffer.back();
      lastStep.planningCycle++;
      lastStep.numberOfCyclePerFootStep = lastStep.planningCycle;
    }
  }

  isStopping = true;
}

void Walk::stopWalkingWithoutStand()
{
  ////////////////////////////////////////////////////////
  // add one step to get stand pose
  ///////////////////////////////////////////////////////

  if ( currentState == motion::stopped )
    return;

  if ( !isStopping ) // remember the stopping foot
  {
    stoppingRequest.coordinate = WalkRequest::Hip;
    stoppingRequest.translation.x = 0;
    stoppingRequest.translation.y = 0;
    stoppingRequest.rotation = 0;
  }

  if ( !stoppingStepFinished )
  {
    // make stopping step
    manageSteps(stoppingRequest);

    const Step& planningStep = stepBuffer.back();
    if ( planningStep.planningCycle == 0 )
    {
      // just modify last planning step
      FootStep zeroStep(planningStep.footStep.begin(), FootStep::NONE);
      Step& lastStep = stepBuffer.back();
      lastStep.footStep = zeroStep;
      lastStep.numberOfCyclePerFootStep = 0;
      stoppingStepFinished = true;
    }
  }

  if ( !stoppingStepFinished )
  {
    planStep();
  }
  else
  {
    const Step& finalStep = stepBuffer.back();
    const FeetPose& finalFeet = finalStep.footStep.end();
    Pose3D finalBody;
    finalBody.rotation = calculateBodyRotation(finalFeet, finalStep.bodyPitchOffset);
    finalBody.translation = (finalFeet.left.translation + finalFeet.right.translation) * 0.5;
    finalBody.translation.z = theWalkParameters.comHeight;
    finalBody.translate(theParameters.hipOffsetX, 0, 0);

    // wait for the com stops
    if ( theEngine.controlZMPstop(finalBody.translation) )
    {
      currentState = motion::stopped;
      stepBuffer.clear();
      cout<<"walk stopped"<<endl;
    }
    else
    {
      Step& lastStep = stepBuffer.back();
      lastStep.planningCycle++;
      lastStep.numberOfCyclePerFootStep = lastStep.planningCycle;
    }
  }

  isStopping = true;
}

void Walk::updateParameters(Step& step) const
{
  const unsigned int basicTimeStep = theBlackBoard.theRobotInfo.basicTimeStep;
  
  step.bodyPitchOffset = Math::fromDegrees(theParameters.bodyPitchOffset);
  step.samplesDoubleSupport = max(0, (int) (theWalkParameters.doubleSupportTime / basicTimeStep));
  step.samplesSingleSupport = max(1, (int) (theWalkParameters.singleSupportTime / basicTimeStep));
  step.numberOfCyclePerFootStep = step.samplesDoubleSupport + step.samplesSingleSupport;
}

void Walk::calculateError()
{
  if ( currentState != motion::running )
    return;

  bool leftFootSupport = theCoMFeetPose.feet.left.translation.z < 0.1;
  bool rightFootSupport = theCoMFeetPose.feet.right.translation.z < 0.1;

  // at least one support foot
  ASSERT( leftFootSupport || rightFootSupport );

  // calculate error of com
  KinematicChain::LinkID supFoot = leftFootSupport ? KinematicChain::LFoot : KinematicChain::RFoot;
  Pose3D footObs = theBlackBoard.theKinematicChain.theLinks[supFoot].M;
  footObs.translate(0, 0, -NaoInfo::FootHeight);
  Vector3d comObs = footObs.rotation * ( footObs.invert() * theBlackBoard.theKinematicChain.CoM );

  const Pose3D& footRef = leftFootSupport ? theCoMFeetPose.feet.left : theCoMFeetPose.feet.right;
  Vector3d comRef = footRef.invert() * theCoMFeetPose.com.translation;
  Vector3d comErr = comObs - comRef;

  theCoMErr += comErr;
}
