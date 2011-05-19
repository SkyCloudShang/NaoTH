/**
 * @file Motion.cpp
 *
  * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
 *
 */

#include "Motion.h"
#include <glib.h>

#include "MorphologyProcessor/ForwardKinematics.h"
#include "CameraMatrixCalculator/CameraMatrixCalculator.h"


Motion::Motion():theBlackBoard(MotionBlackBoard::getInstance())
{
  theSupportPolygonGenerator.init(theBlackBoard.theFSRData.force,
    theBlackBoard.theFSRPos,
    theBlackBoard.theKinematicChain.theLinks);
}

Motion::~Motion()
{
}

void Motion::init(naoth::PlatformDataInterface& platformInterface)
{
  theBlackBoard.init();
  theBlackBoard.currentlyExecutedMotion = &theEmptyMotion;
  
  g_message("Motion register begin");
#define REG_INPUT(R)                                                    \
  platformInterface.registerMotionInput(theBlackBoard.the##R)
  
  REG_INPUT(SensorJointData);
  REG_INPUT(FrameInfo);
  REG_INPUT(InertialSensorData);
  REG_INPUT(FSRData);
  REG_INPUT(AccelerometerData);
  REG_INPUT(GyrometerData);
  
#define REG_OUTPUT(R)                                                   \
  platformInterface.registerMotionOutput(theBlackBoard.the##R)

  REG_OUTPUT(MotorJointData);
  g_message("Motion register end");
  
  //theInverseKinematicsMotionFactory.init();
  //theKeyFrameMotionEngine.init();
  //theDebugMotionEngine.init();
}//end init


void Motion::call()
{
  // TODO
  //STOPWATCH_START("MotionExecute");

  // process sensor data
  processSensorData();
  
  // get orders from cognition
  //SwapSpace::getInstance().theCognitionCache.pull(
  //  theBlackBoard.theHeadMotionRequest,
  //  theBlackBoard.theMotionRequest
  //);
  
  // execute head motion firstly
  //theHeadMotionEngine.execute();

  // motion engine execute
  //selectMotion();
  //ASSERT(NULL!=currentlyExecutedMotion);
  //currentlyExecutedMotion->execute(theBlackBoard.theMotionRequest, theBlackBoard.theMotionStatus);

  // HACK: execute the grasping motion
  //if(theBlackBoard.theMotionRequest.id != MotionRequestID::init)
  //{
  //  theInverseKinematicsMotionFactory.theIKArmGrasping.execute(theBlackBoard.theMotionRequest, theBlackBoard.theMotionStatus);
  //}
  // TODO
  //STOPWATCH_STOP("MotionExecute");
  
  postProcess();
}//end call

void Motion::processSensorData()
{
  // check all joint stiffness
  theBlackBoard.theSensorJointData.checkStiffness();
  

  Kinematics::ForwardKinematics::calculateKinematicChainAll(
    theBlackBoard.theAccelerometerData,
    theBlackBoard.theInertialSensorData,
    theBlackBoard.theKinematicChain,
    theBlackBoard.theFSRPos,
    theBlackBoard.theFrameInfo.getBasicTimeStepInSecond());

  cout<<"---------------"<<endl;
  theSupportPolygonGenerator.calcSupportPolygon(theBlackBoard.theSupportPolygon);
  
  CameraMatrixCalculator::calculateCameraMatrix(
    theBlackBoard.theCameraMatrix,
    theBlackBoard.theHeadMotionRequest.cameraID,
    theBlackBoard.theKinematicChain);
    
  theOdometryCalculator.calculateOdometry(
    theBlackBoard.theOdometryData,
    theBlackBoard.theKinematicChain,
    theBlackBoard.theFSRData);
    
    cout<<theBlackBoard.theOdometryData<<endl;
/*
  Kinematics::ForwardKinematics::updateKinematicChainFrom(theBlackBoard.theKinematicChainModel.theLinks);
  theBlackBoard.theKinematicChainModel.updateCoM();*/
}//end processSensorData

void Motion::postProcess()
{
  
}
