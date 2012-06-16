/*
   Copyright 2011 Thomas Krause
   
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
   
       http://www.apache.org/licenses/LICENSE-2.0
       
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef RAWATTACKDIRECTION_H
#define RAWATTACKDIRECTION_H

#include <Tools/Math/Vector2.h>
#include <Tools/DataStructures/Printable.h>

class RawAttackDirection : public naoth::Printable
{
public:
  RawAttackDirection();

  Vector2<double> attackDirection;

  // some possible support information
  double deviationLeft;
  double deviationRight;
  double distanceToTarget;

  // strategic meaning
  bool pointingToGoal;

  virtual void print(ostream &stream) const;
};

#endif // RAWATTACKDIRECTION_H
