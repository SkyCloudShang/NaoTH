/**
* @file PotentialActionSimulator.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Declaration of class PotentialActionSimulator
*/

#ifndef _PotentialActionSimulator_h_
#define _PotentialActionSimulator_h_

#include <ModuleFramework/Module.h>

// Representations
#include "Representations/Infrastructure/FrameInfo.h"

#include "Representations/Modeling/PlayersModel.h"
#include "Representations/Modeling/BallModel.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/GoalModel.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/SoccerStrategy.h"
#include "Representations/Modeling/RawAttackDirection.h"
#include "Representations/Modeling/CompassDirection.h"
#include "Representations/Modeling/ActionModel.h"
#include "Representations/Motion/MotionStatus.h"

// Tools
#include <Tools/DataStructures/ParameterList.h>
#include <Tools/Debug/DebugParameterList.h>

// Debug
#include "Tools/Debug/DebugModify.h"
#include <Tools/Debug/DebugRequest.h>

#include "Tools/DataStructures/RingBufferWithSum.h"

//////////////////// BEGIN MODULE INTERFACE DECLARATION ////////////////////

BEGIN_DECLARE_MODULE(PotentialActionSimulator)
  PROVIDE(DebugRequest)
  PROVIDE(DebugDrawings)
  PROVIDE(DebugModify)
  PROVIDE(DebugParameterList)
  REQUIRE(FrameInfo)
  REQUIRE(FieldInfo)  
  REQUIRE(PlayerInfo)

  REQUIRE(RobotPose)
  REQUIRE(BallModel)
  REQUIRE(SelfLocGoalModel)
  REQUIRE(LocalGoalModel)
  REQUIRE(CompassDirection)
  REQUIRE(PlayersModel)
  REQUIRE(MotionStatus)
  
  //PROVIDE(RawAttackDirection)
  PROVIDE(ActionModel)
END_DECLARE_MODULE(PotentialActionSimulator)

//////////////////// END MODULE INTERFACE DECLARATION //////////////////////

class PotentialActionSimulator : public PotentialActionSimulatorBase
{
public:

  PotentialActionSimulator();
  virtual ~PotentialActionSimulator(){}

  virtual void execute();

  /** parameters for the module */
  class Parameters: public ParameterList
  {
  public:
	
    Parameters() : ParameterList("PotentialActionParameters")
    {
      PARAMETER_REGISTER(goal_attractor_strength) = -0.001;
      PARAMETER_REGISTER(goal_post_offset) = 200.0;
      PARAMETER_REGISTER(goal_line_offset_front) = 100.0;
      PARAMETER_REGISTER(goal_line_offset_back) = 100.0;

      PARAMETER_REGISTER(player_repeller_radius) = 2000;
      PARAMETER_REGISTER(player_repeller_strenth) = 1500;

      PARAMETER_REGISTER(action_sidekick_distance) = 310;
      PARAMETER_REGISTER(action_short_kick_distance) = 2200;
      PARAMETER_REGISTER(action_long_kick_distance) = 2750;

      syncWithConfig();
      //DebugParameterList::getInstance().add(this);
    }

    /*virtual ~Parameters() {
      DebugParameterList::getInstance().remove(this);
    }*/

    // 
    double goal_attractor_strength;
    double goal_post_offset;
    double goal_line_offset_front;
    double goal_line_offset_back;

    //
    double player_repeller_radius;
    double player_repeller_strenth;
    
    double action_sidekick_distance;
    double action_short_kick_distance;
    double action_long_kick_distance;

  } theParameters;


  class Action
  {
  private:
    ActionModel::ActionId _id;
    Vector2d actionVector;

  public:
    Action(ActionModel::ActionId _id, const Vector2d& actionVector) : 
		  _id(_id), 
      actionVector(actionVector), 
		  potential(-1),
		  goodness(0)
	  {}
	
	  Vector2d predict(const Vector2d& ball, double distance, double angle) const;
    ActionModel::ActionId id() { return _id; }

    Vector2d target;
    double potential;
    double goodness;
  };

private:
 
  /**
    * Calculate the target point between the goal posts to shoot at.
    * @param point The relative point for which the target point should be calculated.
    * @param oppGoalModel Relative coordinates of the opponent goal.
    * @return Target point.
    */
  Vector2d getGoalTarget(const Vector2d& point, const Vector2d& leftPost, const Vector2d& rightPost) const;

  double calculatePotential(const Vector2d& point, const Vector2d& targetPoint) const;

  double globalAttractorPotential(const Vector2d& p, const Vector2d& x) const;
  double compactRepellerPotential(const Vector2d& p, const Vector2d& x) const;

  void calculateAction(GoalModel::Goal &oppGoalModel, std::vector<RingBufferWithSum<double, 30> > &buffer) const;
  Vector2d outsideField(const Vector2d& relativePoint) const;

  std::vector<RingBufferWithSum<double, 30> > actionRingBuffer;//name scheisse
};

#endif //_PotentialFieldProvider_h_
