/**
* @file StrategyTools.cpp
*
* @author Tobias H�bner</a>
* 
* Implementation of the class StrategyTools
*/

#include "StrategyTools.h"
#include <Tools/Debug/NaoTHAssert.h>
#include <Tools/Math/Common.h>

void StrategyTools::arrangeRobots(
  const std::vector<Vector2d>& robots, 
  const std::vector<Vector2d>& places, 
  std::vector<int>& placesToRobots,
  int numberOfIterations)
{
  size_t numberOfRobots = robots.size();
  size_t numberOfPlaces = places.size();


  // inverse assignement
  std::vector<int> robotsToPlaces(numberOfRobots,-1); // init with invalid places -1

  ASSERT(numberOfPlaces == placesToRobots.size());
  ASSERT(numberOfPlaces <= numberOfRobots);
  
  // TODO: treat the case numberOfPlaces > numberOfRobots
  //initial assignment
  for(size_t i = 0; i < numberOfPlaces; i++)
  {
    //int robotIndex = (int)(Math::random()*(numberOfRobots-1)+0.5);
    robotsToPlaces[placesToRobots[i]] = static_cast<int> (i);

    // place i <= robotIndex
    //placesToRobots[i] = i;
  }//end for


  for(int i = 0; i < numberOfIterations; i++)
  {
    // select place
    int placeIndexOne = (int)(Math::random()*(static_cast<double> (numberOfPlaces)-1.0)+0.5);
    // take the robot assighned to this place
    int robotIndexOne = placesToRobots[placeIndexOne];

    // select another robot
    int robotIndexTwo = (int)(Math::random()*(static_cast<double> (numberOfRobots)-1.0)+0.5);
    // take the place of this robot (!!!could be -1)
    int placeIndexTwo = robotsToPlaces[robotIndexTwo];

    if(robotIndexOne == robotIndexTwo) {
      continue;
    }

    // current distance
    double distOne = (robots[robotIndexOne] - places[placeIndexOne]).abs();
    double distTwo = 0;
    if(placeIndexTwo != -1) {
      distTwo = (robots[robotIndexTwo] - places[placeIndexTwo]).abs();
    }
    double currentDistance = distOne + distTwo;
  
    // alternative distance
    double alternativeDistOne = 0;
    if(placeIndexTwo != -1) {
      alternativeDistOne = (robots[robotIndexOne] - places[placeIndexTwo]).abs();
    }

    double alternativeDistTwo = (robots[robotIndexTwo] - places[placeIndexOne]).abs();
    double alternativeDistance = alternativeDistOne + alternativeDistTwo;

	//current use the minimum sum, maybe better to use the minimum distance of longest way

    // switch
    if(alternativeDistance < currentDistance)
    {
      placesToRobots[placeIndexOne] = robotIndexTwo;
      if(placeIndexTwo != -1) {
        placesToRobots[placeIndexTwo] = robotIndexOne;
      }

      robotsToPlaces[robotIndexOne] = placeIndexTwo;
      robotsToPlaces[robotIndexTwo] = placeIndexOne;
    }//end if
  }//end for

}//end arrangeRobots
