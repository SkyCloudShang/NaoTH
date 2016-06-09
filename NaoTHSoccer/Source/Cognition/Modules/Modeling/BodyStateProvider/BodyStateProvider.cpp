/**
* @file BodyStateProvider.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Implementation of class BodyStateProvider
*/

#include "BodyStateProvider.h"

// Debug
#include "Tools/Debug/DebugModify.h"

BodyStateProvider::BodyStateProvider()
{

}

void BodyStateProvider::execute()
{
  // update the fall down state (written by Heinrich Mellmann at 1 am in Magdeburg)
  updateTheFallDownState();

  // ... :)
  updateTheFootState();
  PLOT("BodyStateProvider:standByLeftFoot", getBodyState().standByLeftFoot);
  PLOT("BodyStateProvider:standByRightFoot", getBodyState().standByRightFoot);
  PLOT("BodyStateProvider:foot_state_time", getFrameInfo().getTimeSince(getBodyState().foot_state_time));

  // 
  updateTheLegTemperature();
  updateIsLiftedUp();
  
}//end execute

void BodyStateProvider::updateTheFootState()
{
  bool old_standByLeftFoot = getBodyState().standByLeftFoot;
  bool old_standByRightFoot = getBodyState().standByRightFoot;

  getBodyState().standByLeftFoot = getFSRData().forceLeft() > theParams.foot_threshold;
  getBodyState().standByRightFoot = getFSRData().forceRight() > theParams.foot_threshold;

  if(old_standByLeftFoot != getBodyState().standByLeftFoot ||
     old_standByRightFoot != getBodyState().standByRightFoot)
  {
    getBodyState().foot_state_time = getFrameInfo().getTime();
  }
}//end updateTheFootState


void BodyStateProvider::updateTheFallDownState()
{
  BodyState::State old_fall_down_state = getBodyState().fall_down_state;

  // buffer the inertial data
  inertialBuffer.add(getInertialSensorData().data);

  Vector2d avg = inertialBuffer.getAverage();
  double inertialXaverage = avg.x;
  double inertialYaverage = avg.y;

  getBodyState().fall_down_state = BodyState::upright;

  if(inertialXaverage < -theParams.getup_threshold) {
    getBodyState().fall_down_state = BodyState::lying_on_left_side;
  } else if(inertialXaverage > theParams.getup_threshold) {
    getBodyState().fall_down_state = BodyState::lying_on_right_side;
  }

  if(inertialYaverage < -theParams.getup_threshold) {
    getBodyState().fall_down_state = BodyState::lying_on_back;
  } else if(inertialYaverage > theParams.getup_threshold) {
    getBodyState().fall_down_state = BodyState::lying_on_front;
  }

  if(old_fall_down_state != getBodyState().fall_down_state) {
    getBodyState().fall_down_state_time = getFrameInfo().getTime();
  }
}//end updateTheFallDownState


void BodyStateProvider::updateTheLegTemperature()
{
  static naoth::JointData::JointID leftLegId[] = 
  {
    naoth::JointData::LHipPitch,
    naoth::JointData::LHipRoll,
    naoth::JointData::LKneePitch,
    naoth::JointData::LAnklePitch,
    naoth::JointData::LAnkleRoll
  };

  static naoth::JointData::JointID rightLegId[] = 
  {
    naoth::JointData::RHipPitch,
    naoth::JointData::RHipRoll,
    naoth::JointData::RKneePitch,
    naoth::JointData::RAnklePitch,
    naoth::JointData::RAnkleRoll
  };

  double tempL(0);
  double tempR(0);

  for(int i = 0; i < 5; i++)
  {
    tempL = std::max(tempL, getSensorJointData().temperature[leftLegId[i]]);
    tempR = std::max(tempR, getSensorJointData().temperature[rightLegId[i]]);
  }

  getBodyState().temperatureLeftLeg = tempL;
  getBodyState().temperatureRightLeg = tempR;
}//end updateTheLegTemperature

void BodyStateProvider::updateIsLiftedUp(){
   getBodyState().isLiftedUp =  getBodyState().fall_down_state == BodyState::upright && 
                      !getBodyState().standByLeftFoot && 
                      !getBodyState().standByRightFoot && // no foot is on the ground
                       getFrameInfo().getTimeSince(getBodyState().foot_state_time) > theParams.maxTimeForLiftUp;

 
}