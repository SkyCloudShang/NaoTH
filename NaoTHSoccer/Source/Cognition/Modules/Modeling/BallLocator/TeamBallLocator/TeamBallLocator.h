/**
* @file TeamBallLocator.h
*
* Declaration of class TeamBallLocator
*/

#ifndef __TeamBallLocator_h_
#define __TeamBallLocator_h_

#include <ModuleFramework/Module.h>
#include <algorithm>

// Debug
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugDrawings.h"

// Representations
#include "Representations/Modeling/TeamMessage.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/TeamBallModel.h"
#include "Representations/Infrastructure/GameData.h"
#include "Representations/Infrastructure/FrameInfo.h"

// Canopy Clustering
#include "Cognition/Modules/Modeling/SelfLocator/MonteCarloSelfLocator/CanopyClustering.h"
#include "Cognition/Modules/Modeling/SelfLocator/MonteCarloSelfLocator/SampleSet.h"
#include "Cognition/Modules/Modeling/SelfLocator/MonteCarloSelfLocator/Sample.h"

BEGIN_DECLARE_MODULE(TeamBallLocator)
  PROVIDE(DebugRequest)
  PROVIDE(DebugDrawings)
  REQUIRE(TeamMessage)
  REQUIRE(RobotPose)
  REQUIRE(GameData)
  REQUIRE(FrameInfo)

  PROVIDE(TeamBallModel)
END_DECLARE_MODULE(TeamBallLocator)

class TeamBallLocator : protected TeamBallLocatorBase
{
  public:
    // time stamped Vector2d
    class Vector2dTS
    {
      public:
        Vector2dTS() {}
        // this may be implemented the wrong way round
        bool operator< (const Vector2dTS &v2) const
        {
          return this->t < v2.t;
        }
      public:
        Vector2d vec;
        unsigned int t;
    };

  public:
    TeamBallLocator();
    ~TeamBallLocator() {}

    virtual void execute();

  private:
    std::vector<Vector2dTS> ballPosHist;
    std::map<unsigned int, unsigned int> lastMessages;
};

#endif //__TeamBallLocator_h_
