/**
* @file Walk.h
*
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
*
*/

#ifndef _IK_MOTION_H_
#define _IK_MOTION_H_

#include "IKMotion.h"
#include "Walk/FootStep.h"
#include "Walk/FootStepPlanner.h"
#include <list>

class Walk: public IKMotion
{
public:
  Walk();
  
  virtual void execute(const MotionRequest& motionRequest, MotionStatus& motionStatus);
  
private:
  struct Step {

    Step():planningCycle(0),executingCycle(0){}

    int planningCycle;
    int executingCycle;
    FootStep footStep;
    // parameters
    // calcualted parameters of walk
    double bodyPitchOffset;
    int samplesDoubleSupport;
    int samplesSingleSupport;
    int numberOfCyclePerFootStep;
  };

  bool FSRProtection();
  
  bool waitLanding();
  
  void plan(const MotionRequest& motionRequest);
  
  void walk(const WalkRequest& req);
  
  void stopWalking();
  
  bool canStop() const;
  
  FootStep firstStep(const WalkRequest& req);
  
  void updateParameters(Step& step) const;

  void calculateError();

  void manageSteps(const WalkRequest& req);

  void planStep();

  InverseKinematic::CoMFeetPose executeStep();
  
private:
  const IKParameters::Walk& theWalkParameters;
  
  InverseKinematic::CoMFeetPose theCoMFeetPose;
  
  int theWaitLandingCount;
  int theUnsupportedCount;
  
  bool isStopping;
  bool stoppingStepFinished;
  WalkRequest stoppingRequest;
  
  std::list<Step> stepBuffer;
  
  FootStepPlanner theFootStepPlanner;

  Vector3d theCoMErr;
};

#endif // _IK_MOTION_H_
