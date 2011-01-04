/**
 * @author <a href="xu:mellmann@informatik.hu-berlin.de">Xu, Yuan</a>
 */

#include "Logger.h"
#include <Tools/DataStructures/Serializer.h>
#include <Representations/Infrastructure/GyrometerData.h>

Logger::Logger(const std::string& cmd) : logfileManager(true),command(cmd)
{
  description = command + " on | off | close |activate=<name> | deactivate=<name>";
  activated = false;
  activatedOnce = false;
}

Logger::~Logger()
{
}

void Logger::executeDebugCommand(
  const std::string& command, const std::map<std::string, std::string>& arguments,
  std::stringstream &outstream)
{
  if (command != this->command) return;
  for(std::map<std::string, std::string>::const_iterator iter=arguments.begin(); iter!=arguments.end(); ++iter)
  {
    handleCommand(iter->first, iter->second, outstream);
  }
}

void Logger::handleCommand(const std::string& argName, const std::string& argValue, std::stringstream& outstream)
{
  if ("open" == argName) {
    logfileManager.openFile(argValue.c_str());
    activeRepresentations.clear();
    activated = false;

    // list all logable representations
    for(std::map<std::string, const naoth::Streamable*>::const_iterator iter=streamables.begin(); iter!=streamables.end(); ++iter){
      outstream << iter->first <<" ";
    }
  }
  else if ("activate" == argName) {
    for(std::map<string, const naoth::Streamable*>::const_iterator iter=streamables.begin(); iter!=streamables.end(); ++iter)
    {
      if ( argValue == iter->first)
      {
        activeRepresentations.insert(argValue);
        outstream << "activated logging for " << argValue;
        break;
      }
    }
  }
  else if ("deactivate" == argName) {
    for(std::set<std::string>::iterator iter=activeRepresentations.begin(); iter!=activeRepresentations.end(); ++iter)
    {
      if ( argValue == *iter )
      {
        activeRepresentations.erase(argValue);
        outstream << "deactivated logging for " << argValue;
        break;
      }
    }
  }
  else if ("on" == argName) {
    activated = true;
    outstream << "logging on";
  }
  else if ("off" == argName) {
    activated = false;
    logfileManager.flush();
    outstream << "logging off";
  }
  else if ("once" == argName) {
    activatedOnce = true;
    outstream << "log once";
  }
  else if ("close" == argName) {
    logfileManager.closeFile();
    activated = false;
    outstream << "logfile closed";
  }
  else{
    outstream << "Logger Error: unsupport argument: "<<argName;
  }
}

void Logger::log(unsigned int frameNum)
{
  if (!activated && !activatedOnce) return;

  activatedOnce = false;
  
  for (std::set<std::string>::const_iterator iter = activeRepresentations.begin();
    iter != activeRepresentations.end(); ++iter) 
  {
    std::map<std::string, const naoth::Streamable*>::iterator itStreamables = streamables.find(*iter);
    
    if(itStreamables != streamables.end() && serializers.find(*iter) != serializers.end())
    { 
      std::stringstream& stream = logfileManager.log(frameNum, itStreamables->first);
      serializers[*iter](*(itStreamables->second), stream);
    }
    
  }

}
