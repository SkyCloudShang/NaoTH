/**
 * @file HeadMotionEngine.h
 *
 * @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
 * @author Oliver Welter
 *
 * Created on 27. Januar 2009, 16:43
 */

#ifndef _HeadMotionEngine_H
#define _HeadMotionEngine_H

#include <Tools/Math/Vector2.h>
#include <Tools/Math/Vector3.h>

#include <ModuleFramework/Module.h>

// representations
#include <Representations/Infrastructure/RobotInfo.h>
#include <Representations/Infrastructure/CameraInfo.h>
#include "Representations/Modeling/InertialModel.h"
#include "Representations/Infrastructure/InertialSensorData.h"
#include "Representations/Modeling/KinematicChain.h"
#include "Representations/Motion/Request/HeadMotionRequest.h"
#include <Representations/Infrastructure/JointData.h>
#include <Representations/Perception/CameraMatrix.h>
#include "Representations/Motion/MotionStatus.h"
#include <Representations/Modeling/CameraMatrixOffset.h>

// Debug
#include "Tools/Debug/DebugModify.h"
#include <Tools/Debug/DebugRequest.h>
#include <Tools/Debug/DebugDrawings.h>
#include "Tools/Debug/DebugParameterList.h"

BEGIN_DECLARE_MODULE(HeadMotionEngine)
  PROVIDE(DebugModify)
  PROVIDE(DebugRequest)
  PROVIDE(DebugDrawings)
  PROVIDE(DebugParameterList)


  REQUIRE(RobotInfo)
  REQUIRE(InertialModel)
  REQUIRE(InertialSensorData)
  REQUIRE(KinematicChainSensor)
  REQUIRE(HeadMotionRequest)
  REQUIRE(SensorJointData)
  
  REQUIRE(CameraMatrix)
  REQUIRE(CameraMatrixTop)
  REQUIRE(CameraInfo)
  REQUIRE(CameraInfoTop)
  REQUIRE(CameraMatrixOffset)

  PROVIDE(MotionStatus)
  PROVIDE(MotorJointData)
END_DECLARE_MODULE(HeadMotionEngine)


class HeadMotionEngine: private HeadMotionEngineBase
{
public:
  HeadMotionEngine();
  ~HeadMotionEngine();

  void execute();


private:
  struct Parameters: public ParameterList
  {
    Parameters() : ParameterList("HeadMotionEngine")
    {
      
      PARAMETER_REGISTER(max_velocity_deg_in_second_fast) = 60;
      PARAMETER_REGISTER(max_velocity_deg_in_second_slow) = 90;
      PARAMETER_REGISTER(cutting_velocity) = 40;
      
      syncWithConfig();
    }

	  double max_velocity_deg_in_second_fast;
    double max_velocity_deg_in_second_slow;
    double cutting_velocity;
    
  } params;

private:

  // internal use
  naoth::JointData theJointData;
  KinematicChain theKinematicChain;
  

  bool trajectoryHeadMove(const std::vector<Vector3<double> >& points);
  void gotoPointOnTheGround(const Vector2<double>& target);

  void lookStraightAhead();
  void lookStraightAheadWithStabilization();
  void lookAtPoint();
  void simpleLookAtPoint();

  void hold();
  void search();
  void randomSearch();


  void moveByAngle(const Vector2<double>& target);
  void gotoAngle(const Vector2<double>& target);

  void lookAtWorldPoint(const Vector3<double>& target);
  void lookAtWorldPointSimple(const Vector3<double>& target);

  Vector3<double> g(double yaw, double pitch, const Vector3<double>& pointInWorld);
};

#endif  /* _HeadMotionEngine_H */

