/**
 * @file AbstractMotion.cpp
 * 
 * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
 */

#include "AbstractMotion.h"

using namespace naoth;

AbstractMotion::AbstractMotion(motion::MotionID id, MotionLock& lock)
: theId(id),
  lock(lock),
  currentState(motion::stopped)
{
  //assert(lock.state == motion::stopped || id == motion::dead);
  // occupy lock
  lock.id = id;
  lock.state = currentState;

  init();
}

bool AbstractMotion::setStiffness(
  naoth::MotorJointData& theMotorJointData,
  const naoth::SensorJointData& theSensorJointData,
  double* stiffness,
  double delta, 
  JointData::JointID begin, JointData::JointID end)
{
  int readyJointNum = 0;
  for (int i = begin; i < end; i++)
  {
    // Achtung: the increase of the stiffness depends on the sensory feedback
    double d = stiffness[i] - theSensorJointData.stiffness[i];
    if (fabs(d) < 1e-2 || 
      // NOTE: those joints are considered not critical
      i == JointData::HeadPitch || i==JointData::HeadYaw || i==JointData::LHand || i==JointData::RHand || i==JointData::LWristYaw || i==JointData::RWristYaw)
    {
      readyJointNum++;
      theMotorJointData.stiffness[i] = stiffness[i];
    } else {
      d = Math::clamp(d, -delta, delta);
      theMotorJointData.stiffness[i] = theSensorJointData.stiffness[i] + d;
    }

    // ensure that we always get a valid stiffness, i.e, -1 or [0,1]
    if (theMotorJointData.stiffness[i] < 0) // -1 is the special case
    {
      theMotorJointData.stiffness[i] = (d > 0)?0:-1;
    } else {
      theMotorJointData.stiffness[i] = std::min(theMotorJointData.stiffness[i],1.0);
    }
  }//end for

  return readyJointNum == (end - begin);
}//end setStiffness
