/**
 * @file ParameterList.cpp
 *
 * @author <a href="mailto:aschulz@informatik.hu-berlin.de">Alexander Schulz</a>
 * @author <a href="mailto:krause@informatik.hu-berlin.de">Thomas Krause</a>
 *
 */

#include <string>

#include <PlatformInterface/Platform.h>
#include "ParameterList.h"

void ParameterList::syncWithConfig()
{
  naoth::Configuration& config =  naoth::Platform::getInstance().theConfiguration;

  for (std::list<ConfigParameter*>::iterator iter = parameters.begin(); iter != parameters.end(); ++iter) {
    (*iter)->syncWithConfig(config, name);
  }
}

void ParameterList::saveToConfig()
{
  naoth::Configuration& config =  naoth::Platform::getInstance().theConfiguration;

  for (std::list<ConfigParameter*>::iterator iter = parameters.begin(); iter != parameters.end(); ++iter) {
    (*iter)->writeToConfig(config, name);
  }

  config.save();
}

std::string ParameterList::convertName(std::string name)
{
  for( std::string::iterator i=name.begin(); i!= name.end();  )
  {
    if ( *i == '[' || *i == ']' )
    {
      i = name.erase(i);
    }
    else
    {
      ++i;
    }
  }
  return name;
}//end convertName

