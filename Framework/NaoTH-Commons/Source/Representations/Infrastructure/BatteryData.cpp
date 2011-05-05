#include "BatteryData.h"

using namespace naoth;

BatteryData::BatteryData():
  charge(0.0)
{
}

void BatteryData::print(ostream& stream) const
{
  stream << "charge: " << charge << endl;
}

BatteryData::~BatteryData()
{ 
}
