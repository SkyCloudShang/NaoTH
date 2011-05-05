/**
 * @file ParameterList.cpp
 *
 * @author <a href="mailto:aschulz@informatik.hu-berlin.de">Alexander Schulz</a>
 * @author <a href="mailto:krause@informatik.hu-berlin.de">Thomas Krause</a>
 *
 */

#include <string>

#include <PlatformInterface/Platform.h>
#include <Tools/Debug/NaoTHAssert.h>
#include "ParameterList.h"

ParameterList::ParameterList(const std::string& parentClassName)
{
  this->parentClassName = parentClassName;
  
}//end constructor ParameterList

void ParameterList::initParams()
{
  // first load values from configuration
  loadFromConfig();
  // now store them, this will create an entry for all parameters that are
  // unknown in the configuration
  saveToConfig();
}

unsigned int& ParameterList::registerParameter(const std::string& name, unsigned int& parameter)
{
  ASSERT(unsignedIntParameterReferences.find(name) == unsignedIntParameterReferences.end());
  unsignedIntParameterReferences[name] = &parameter;
  return parameter;
}//end registerParameter

int& ParameterList::registerParameter(const std::string& name, int& parameter)
{
  ASSERT(intParameterReferences.find(name) == intParameterReferences.end());
  intParameterReferences[name] = &parameter;
  return parameter;
}//end registerParameter

double& ParameterList::registerParameter(const std::string& name, double& parameter)
{
  ASSERT(doubleParameterReferences.find(name) == doubleParameterReferences.end());
  doubleParameterReferences[name] = &parameter;

  return parameter;
}//end registerParameter

std::string& ParameterList::registerParameter(const std::string& name, std::string& parameter)
{
  ASSERT(stringParameterReferences.find(name) == stringParameterReferences.end());
  stringParameterReferences[name] = &parameter;
  return parameter;
}//end registerParameter

bool& ParameterList::registerParameter(const std::string& name, bool& parameter)
{
  ASSERT(boolParameterReferences.find(name) == boolParameterReferences.end());
  boolParameterReferences[name] = &parameter;
  return parameter;
}

void ParameterList::loadFromConfig()
{
  naoth::Configuration& config =  naoth::Platform::getInstance().theConfiguration;

  // unsigned int
  for (std::map<std::string, unsigned int*>::const_iterator iter = unsignedIntParameterReferences.begin(); iter != unsignedIntParameterReferences.end(); iter++)
  {
    if (config.hasKey(parentClassName, iter->first))
    {
      *(iter->second) = config.getInt(parentClassName, iter->first);
    }
  }//end for

  // int
  for (std::map<std::string, int*>::const_iterator iter = intParameterReferences.begin(); iter != intParameterReferences.end(); iter++)
  {
    if (config.hasKey(parentClassName, iter->first))
    {
      *(iter->second) = config.getInt(parentClassName, iter->first);
    }
  }//end for

  // double
  for (std::map<std::string, double*>::const_iterator iter = doubleParameterReferences.begin(); iter != doubleParameterReferences.end(); iter++)
  {
    if (config.hasKey(parentClassName, iter->first))
    {
      *(iter->second) = config.getDouble(parentClassName, iter->first);
    }
  }//end for

  // string
  for (std::map<std::string, std::string*>::const_iterator iter = stringParameterReferences.begin(); iter != stringParameterReferences.end(); iter++)
  {
    if (config.hasKey(parentClassName, iter->first))
    {
      *(iter->second) = config.getString(parentClassName, iter->first);
    }
  }//end for

  // bool
  for (std::map<std::string, bool*>::const_iterator iter = boolParameterReferences.begin(); iter != boolParameterReferences.end(); iter++)
  {
    if (config.hasKey(parentClassName, iter->first))
    {
      *(iter->second) = config.getBool(parentClassName, iter->first);
    }
  }//end for

}

void ParameterList::saveToConfig()
{
  naoth::Configuration& config =  naoth::Platform::getInstance().theConfiguration;

  for(std::map<std::string, unsigned int*>::iterator iter = unsignedIntParameterReferences.begin(); iter != unsignedIntParameterReferences.end(); iter++)
  {
    config.setInt(parentClassName, iter->first, *(iter->second));
  }//end for

  for(std::map<std::string, int*>::iterator iter = intParameterReferences.begin(); iter != intParameterReferences.end(); iter++)
  {
    config.setInt(parentClassName, iter->first, *(iter->second));
  }//end for

  for(std::map<std::string, double*>::iterator iter = doubleParameterReferences.begin(); iter != doubleParameterReferences.end(); iter++)
  {
    config.setDouble(parentClassName, iter->first, *(iter->second));
  }//end for

  for(std::map<std::string, std::string*>::iterator iter = stringParameterReferences.begin(); iter != stringParameterReferences.end(); iter++)
  {
    config.setString(parentClassName, iter->first, *(iter->second));
  }//end for

  for(std::map<std::string, bool*>::iterator iter = boolParameterReferences.begin(); iter != boolParameterReferences.end(); iter++)
  {
    config.setBool(parentClassName, iter->first, *(iter->second));
  }//end for

}