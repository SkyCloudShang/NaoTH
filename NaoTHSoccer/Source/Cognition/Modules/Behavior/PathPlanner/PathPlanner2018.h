/**
* @file PathPlanner2018.h
*
* @author <a href="mailto:akcayyig@hu-berlin.de">Yigit Can Akcay</a>
* Definition of class PathPlanner2018
*/

#ifndef _PathPlanner2018_H_
#define _PathPlanner2018_H_

#include <ModuleFramework/Module.h>

#include "Tools/Math/Geometry.h"

// debug
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugModify.h"
#include "Tools/Debug/DebugParameterList.h"

// representations
#include "Representations/Infrastructure/FieldInfo.h"
#include "Representations/Motion/Request/HeadMotionRequest.h"
#include "Representations/Motion/Request/MotionRequest.h"
#include "Representations/Motion/MotionStatus.h"
#include "Representations/Perception/BallPercept.h"
#include "Representations/Perception/MultiBallPercept.h"
#include "Representations/Modeling/BallModel.h"
#include "Representations/Modeling/PathModel.h"
#include "Representations/Debug/Stopwatch.h"


BEGIN_DECLARE_MODULE(PathPlanner2018)
PROVIDE(DebugRequest)
PROVIDE(DebugModify)
PROVIDE(DebugParameterList)

REQUIRE(FieldInfo)
REQUIRE(BallPercept)
REQUIRE(MultiBallPercept)
REQUIRE(MotionStatus)
REQUIRE(BallModel)

PROVIDE(PathModel)
PROVIDE(MotionRequest)
PROVIDE(HeadMotionRequest)
PROVIDE(StopwatchManager)
END_DECLARE_MODULE(PathPlanner2018)



class PathPlanner2018 : public PathPlanner2018Base
{
public:
  PathPlanner2018();
  ~PathPlanner2018();

  virtual void execute();

private:
  class Parameters : public ParameterList
  {
  public:
    Parameters() : ParameterList("PathPlanner2018")
    {
      PARAMETER_REGISTER(acquire_ball_control_x_threshold) = 170;
      PARAMETER_REGISTER(acquire_ball_control_y_threshold) = 40;

      /*PARAMETER_REGISTER(sidekick_scale) = 1.0;
      PARAMETER_REGISTER(short_kick_time) = 300;
      PARAMETER_REGISTER(long_kick_time) = 300;
      PARAMETER_REGISTER(sidekick_time) = 300;

      PARAMETER_REGISTER(approach_ball_adapt_control) = true;
      PARAMETER_REGISTER(approach_ball_adapt_threshold) = 10;
      PARAMETER_REGISTER(approach_ball_slow_distance) = 50;*/

      syncWithConfig();
    }
    virtual ~Parameters(){}

    double acquire_ball_control_x_threshold;
    double acquire_ball_control_y_threshold;
    /*double sidekick_scale;
    int short_kick_time;
    int long_kick_time;
    int sidekick_time;
    bool approach_ball_adapt_control;
    int approach_ball_adapt_threshold;
    int approach_ball_slow_distance;*/
  } params;

  // NONE means hip
  enum Foot
  {
    RIGHT,
    LEFT,
    NONE
  };
  typedef WalkRequest::StepControlRequest::StepType StepType;

  bool acquire_ball_control();
  bool execute_action();

  void short_kick(const Foot foot);

  // Stepcontrol
  struct Step_Buffer_Element {
    Pose2D pose;
    double speedDirection;
    StepType type;
    int time;
    double character;
    double scale;
    Foot foot;
    WalkRequest::Coordinate coordinate;
    WalkRequest::StepControlRequest::RestrictionMode restriction;
    bool isProtected;
  };
  std::vector<Step_Buffer_Element> step_buffer;

  // Used to alternate between left and right foot
  // or to specify which foot to use
  Foot foot_to_use;

  // Used to synchronize stepIDs of WalkEngine to take control
  unsigned int last_stepRequestID;

  void add_step(Pose2D &pose,
    const StepType &type,
    const WalkRequest::Coordinate &coordinate,
    const double character,
    const Foot foot,
    const double scale,
    const double speedDirection,
    const WalkRequest::StepControlRequest::RestrictionMode restriction,
    const bool isProtected,
    int kick_time);
  void update_step(Pose2D &pose);
  void manage_step_buffer();
  void execute_step_buffer();


private:
  bool kick_planned;
  bool steps_planned;
};

#endif // _PathPlanner2018_H_
