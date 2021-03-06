/**
 * @file InverseKinematicsMotionEngine.h
 *
 * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
 * Declaration of class Inverse Kinematics Motion Engine
 */

#ifndef _INVERSE_KINEMATCS_MOTION_ENGINE_
#define _INVERSE_KINEMATCS_MOTION_ENGINE_

#include "Motions/IKPose.h"
#include "Motions/IKParameters.h"

#include <ModuleFramework/Module.h>

// representations
#include <Representations/Infrastructure/JointData.h>
#include "Representations/Modeling/KinematicChain.h"


#include <Representations/Infrastructure/GyrometerData.h>
#include <Representations/Infrastructure/InertialSensorData.h>
#include "Representations/Modeling/GroundContactModel.h"
#include "Representations/Modeling/InertialModel.h"
#include "Representations/Modeling/IMUData.h"
#include <Representations/Infrastructure/RobotInfo.h>
#include <Representations/Infrastructure/FrameInfo.h>
#include "Representations/Motion/MotionStatus.h"

// debug
#include "Tools/Debug/DebugParameterList.h"
#include "Tools/Debug/DebugModify.h"
#include "Tools/Debug/DebugPlot.h"
#include "Tools/Debug/DebugRequest.h"

BEGIN_DECLARE_MODULE(InverseKinematicsMotionEngine)
  PROVIDE(DebugParameterList)
  PROVIDE(DebugModify)
  PROVIDE(DebugPlot)
  PROVIDE(DebugRequest)

  REQUIRE(FrameInfo)
  REQUIRE(KinematicChainSensor)
  REQUIRE(KinematicChainMotor)
  REQUIRE(SensorJointData)
END_DECLARE_MODULE(InverseKinematicsMotionEngine)

class InverseKinematicsMotionEngine: private InverseKinematicsMotionEngineBase
{
private:

  InverseKinematic::HipFeetPose getHipFeetPoseFromKinematicChain(const KinematicChain& kc) const;
  
  InverseKinematic::CoMFeetPose getCoMFeetPoseFromKinematicChain(const KinematicChain& kc) const;
  
  Pose3D getLeftFootFromKinematicChain(const KinematicChain& kc) const;
  
  Pose3D getRightFootFromKinematicChain(const KinematicChain& kc) const;

public:

  InverseKinematicsMotionEngine();

  virtual ~InverseKinematicsMotionEngine()
  {
      getDebugParameterList().remove(&theParameters);
  }

  virtual void execute(){} // dummy

  
  InverseKinematic::HipFeetPose getHipFeetPoseBasedOnSensor() const;
  InverseKinematic::CoMFeetPose getCoMFeetPoseBasedOnSensor() const;

  InverseKinematic::HipFeetPose getHipFeetPoseBasedOnModel() const;
  InverseKinematic::CoMFeetPose getCoMFeetPoseBasedOnModel() const;

  InverseKinematic::HipFeetPose getCurrentHipFeetPose() const;
  InverseKinematic::CoMFeetPose getCurrentCoMFeetPose() const;
  InverseKinematic::ZMPFeetPose getPlannedZMPFeetPose() const;

  const InverseKinematic::CoMFeetPose& getlastControlledCoMFeetPose() const {
    return lastCoMFeetControlPose;
  }

  template<typename T>
  T interpolate(const T& sp, const T& tp, double t) const 
  {
    T p;
    p.body() = Pose3D::interpolate(sp.body(), tp.body(), t);
    p.feet.left = Pose3D::interpolate(sp.feet.left, tp.feet.left, t);
    p.feet.right = Pose3D::interpolate(sp.feet.right, tp.feet.right, t);
    return p;
  }


  template<typename T>
  T interpolateArms(const T& sp, const T& tp, double t) const 
  {
    T p;
    p.body() = Pose3D::interpolate(sp.body(), tp.body(), t);
    p.arms.left = Pose3D::interpolate(sp.arms.left, tp.arms.left, t);
    p.arms.right = Pose3D::interpolate(sp.arms.right, tp.arms.right, t);
    return p;
  }


  InverseKinematic::HipFeetPose controlCenterOfMass(
    const naoth::MotorJointData& theMotorJointData,
    const InverseKinematic::CoMFeetPose& p, 
    bool& solved, 
    bool fix_height/*=false*/);

  void controlCenterOfMassCool(
    const MotorJointData& theMotorJointData,
    const InverseKinematic::CoMFeetPose& target,
    InverseKinematic::HipFeetPose& result,
    bool leftFootSupport,
    bool& sloved,
    bool fix_height);

  void solveHipFeetIK(const InverseKinematic::HipFeetPose& p);
  
  bool rotationStabilizeRC16(
    const Vector2d& inertial,
    const GyrometerData& theGyrometerData,
    const double timeDelta,
    const Vector2d&  rotationP,
    const Vector2d&  rotationVelocityP,
    const Vector2d&  rotationD,
    InverseKinematic::HipFeetPose& p);

  bool rotationStabilize(
    const InertialModel& theInertialModel,
    const GyrometerData& theGyrometerData,
    const double timeDelta,
    const Vector2d&  rotationP,
    const Vector2d&  rotationVelocityP,
    const Vector2d&  rotationD,
    InverseKinematic::HipFeetPose& p);

  /*
  bool rotationStabilize(
    const InertialModel& theInertialModel,
    const GyrometerData& theGyrometerData,
    Pose3D& hip);
  */
  /**
   * @return if stabilizer is working
   */
  /*
  bool rotationStabilize(
    const naoth::RobotInfo& theRobotInfo,
    const GroundContactModel& theGroundContactModel,
    const naoth::InertialSensorData& theInertialSensorData,
    Pose3D& hip);
  */

  void copyLegJoints(double (&position)[naoth::JointData::numOfJoint]) const;
  
  const IKParameters& getParameters() const { return theParameters; }
  
  /**
   * Solves the inverse kinematic for the hands
   * @return squared sum error for the estimated joint positions
   */
  double solveHandsIK(
    const Pose3D& chest,
    const Pose3D& leftHand,
    const Pose3D& rightHand,
    double (&position)[naoth::JointData::numOfJoint]);

  Vector3<double> sensorCoMIn(
    const KinematicChainSensor& theKinematicChain,
    KinematicChain::LinkID link) const;

  Vector3<double> balanceCoM(
    const naoth::FrameInfo& theFrameInfo,
    const KinematicChainSensor& theKinematicChain,
    const Vector3d& lastReqCoM, KinematicChain::LinkID link) const;

  void armsBasedOnInertialModel(
    const InertialModel& theInertialModel,
    double (&position)[naoth::JointData::numOfJoint]);

  void armsSynchronisedWithWalk(
    const naoth::RobotInfo& theRobotInfo,
    const InverseKinematic::CoMFeetPose& feet, 
    naoth::JointData& jointData);

  void armsOnBack(
    const RobotInfo& theRobotInfo,
    const InverseKinematic::HipFeetPose& pose, 
    double (&position)[naoth::JointData::numOfJoint]);

private:
  IKParameters theParameters;

  Kinematics::InverseKinematics theInverseKinematics;
  
  Vector3d theCoMControlResult; // save CoM control result to be reused
  InverseKinematic::CoMFeetPose lastCoMFeetControlPose;
  FrameInfo lastCoMFeetControlFrameInfo;

  double rotationStabilizeFactor; // [0, 1] disable ~ enable
};

/**
* a representation providing access to a instance of InverseKinematicsMotionEngine
*/
class InverseKinematicsMotionEngineService
{
public:
  InverseKinematicsMotionEngineService() : theEngine(NULL) {}

  virtual ~InverseKinematicsMotionEngineService() 
  {
  }

  InverseKinematicsMotionEngine& getEngine() const
  {
    assert(theEngine != NULL);
    return *theEngine;
  }

  void setEngine(InverseKinematicsMotionEngine* ref)
  {
    theEngine = ref;
  }

private:
  InverseKinematicsMotionEngine* theEngine;
};//end InverseKinematicsMotionEngineService

#endif // _INVERSE_KINEMATCS_MOTION_ENGINE_
