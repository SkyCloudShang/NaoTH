/**
* @file MotionRequestID.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
* Definition of the class MotionID
*/

#ifndef __MotionID_h_
#define __MotionID_h_

#include <string>

namespace motion
{

  /** ids for all motion types */
  enum MotionID {
    
    EMPTY,
    INIT,
    DEAD,
    
    /* inverse kinematic */
    STAND,
    
    WALK,
    KICK,
    DANCE,
    //SIT_STABLE,
    /* motion net */
    STAND_UP_FROM_FRONT,
    STAND_UP_FROM_BACK,
    /*BLOCK_LEFT,
    BLOCK_RIGHT,
    BLOCK_MIDDLE,

    goalie_get_down,
    goalie_sit,
    goalie_get_up,

    goalie_get_fast_down,
    goalie_sit_small,
    goalie_get_fast_up,

    goalie_dive_left,
    goalie_dive_right,

    goalie_dive_left_test,
    goalie_dive_right_test,

    fall_left,
    fall_right,*/

    NUM_OF_MOTION //error value
  };

  /** return a string reprenting the id */
  static std::string getName(MotionID id)
  {
    switch(id)
    {
      case EMPTY: return "empty";
      case INIT: return "init";
      case DEAD: return "dead";
      case STAND: return "stand";

      case WALK: return "walk";
      case KICK: return "kick";
      case DANCE: return "dance";
      
      case STAND_UP_FROM_FRONT: return "stand_up_from_front";
      case STAND_UP_FROM_BACK: return "stand_up_from_back";
      /*case check_reactivity: return "check_reactivity";

//      case pre_grasping:    return "pre_grasping";
      case grasp: return "grasping";

      
      case block_left: return "block_left";
      case block_right: return "block_right";
      case block_middle: return "block_middle";
      case evolution_motion: return "evolution_motion"; //(Martin)

      case goto_pose_directly: return "goto_pose_directly";
      case force_joints: return "force_joints";
      case test: return "test";
      case play_editor_motionnet: return "play_editor_motionnet";
      case knead_mode: return "knead_mode";
      case reachability_grid_experiment: return "reachability_grid_experiment";

      case goalie_get_down: return "goalie_get_down";
      case goalie_sit: return "goalie_sit";
      case goalie_get_up: return "goalie_get_up";

      case goalie_get_fast_down: return "goalie_get_fast_down";
      case goalie_sit_small: return "goalie_sit_small";
      case goalie_get_fast_up: return "goalie_get_fast_up";

      case goalie_dive_left: return "goalie_dive_left";
      case goalie_dive_right: return "goalie_dive_right";

      case goalie_dive_left_test: return "goalie_dive_left_test";
      case goalie_dive_right_test: return "goalie_dive_right_test";

      case fall_left: return "fall_left";
      case fall_right: return "fall_right";

      case sit_stable: return "sit_stable";

      case parallel_dance: return "parallel_dance";
      case parallel_stepper: return "parallel_stepper";
      case sensor_stepper: return "sensor_stepper";

      case neural_walk: return "neural_walk";

      case kick_right: return "kick_right";*/
      case NUM_OF_MOTION: return "num_of_motion";
    }///end switch

    return "unkown";
  }///end getName
} // namespace motion

#endif // __MotionRequestID_h_


