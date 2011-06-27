/* 
 * File:   Debug.h
 * Author: thomas
 *
 * Created on 11. November 2010, 18:32
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include <ModuleFramework/Module.h>
#include <DebugCommunication/DebugCommandExecutor.h>


#include "Representations/Infrastructure/FieldInfo.h"
#include <Representations/Infrastructure/GyrometerData.h>
#include <Representations/Infrastructure/FrameInfo.h>
#include <Representations/Infrastructure/Image.h>
#include <Representations/Infrastructure/JointData.h>
#include <Representations/Infrastructure/InertialSensorData.h>
#include <Representations/Infrastructure/AccelerometerData.h>
#include <Representations/Infrastructure/FSRData.h>

#include "Representations/Infrastructure/ColorTable64.h"
#include "Representations/Motion/Request/MotionRequest.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/KinematicChain.h"
#include "Representations/Modeling/BallModel.h"

#include "Tools/Debug/Logger.h"

using namespace naoth;

BEGIN_DECLARE_MODULE(Debug)
  REQUIRE(GyrometerData)
  REQUIRE(FrameInfo)
  REQUIRE(FieldInfo)
  REQUIRE(Image)
  REQUIRE(SensorJointData)
  REQUIRE(InertialSensorData)
  REQUIRE(AccelerometerData)
  REQUIRE(FSRData)
  REQUIRE(RobotPose)
  REQUIRE(KinematicChain)
  REQUIRE(BallModel)
  
  PROVIDE(ColorTable64)
  PROVIDE(MotionRequest)
END_DECLARE_MODULE(Debug)

class Debug : public DebugBase, public DebugCommandExecutor
{
public:
  Debug();
  virtual ~Debug();

  virtual void execute();

  virtual void executeDebugCommand(
    const std::string& command, const std::map<std::string,std::string>& arguments,
    std::ostream &outstream);

private:
  Logger cognitionLogger;

  void draw3D();
  void drawRobot3D(const Pose3D& robotPose);
};

#endif	/* DEBUG_H */

