/**
* @file KeyFrameMotionEngine.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Implementation of class KeyFrameMotionEngine
*/

#include "KeyFrameMotionEngine.h"

using namespace naoth;

KeyFrameMotionEngine::KeyFrameMotionEngine()
:currentMotion(NULL)
{
  /*REGISTER_DEBUG_COMMAND("reload:motion_net", 
    "reloads a particular motion net. Usage: reload:motion_net file=turn_right", this);
  REGISTER_DEBUG_COMMAND("motion:load_editor_motionnet", 
      "load the temporary editor's motion net.", this);*/
  
  // load motion nets in different folders
  const std::string& dirlocation = Platform::getInstance().theConfigDirectory;
  const std::string& scheme = Platform::getInstance().theScheme;
  const std::string& id = Platform::getInstance().theHardwareIdentity;
  const std::string motionnet = "motionnet/";
  loadAvailableMotionNets(dirlocation + "general/" + motionnet);
  loadAvailableMotionNets(dirlocation + "scheme/" + scheme + "/" + motionnet);
  loadAvailableMotionNets(dirlocation + "robots/" + id + "/" + motionnet);
  loadAvailableMotionNets(dirlocation + "private/" + motionnet);
}

KeyFrameMotionEngine::~KeyFrameMotionEngine()
{
  delete currentMotion;
}

void KeyFrameMotionEngine::loadAvailableMotionNets(std::string dirlocation)
{
  if (!g_str_has_suffix(dirlocation.c_str(), "/"))
  {
    dirlocation = dirlocation + "/";
  }

  GDir* dir = g_dir_open(dirlocation.c_str(), 0, NULL);
  if (dir != NULL)
  {
    const gchar* name;
    while ((name = g_dir_read_name(dir)) != NULL)
    {
      if (g_str_has_suffix(name, ".mef"))
      {
        gchar* group = g_strndup(name, strlen(name) - strlen(".cfg"));
        
        std::string completeFileName = dirlocation + name;
        loadMotionNet(completeFileName, std::string(group));

        g_free(group);
      }
    }//end while

    g_dir_close(dir);
  }//end if
}//end loadAvailableMotionNets


void KeyFrameMotionEngine::loadMotionNetFromFile(const std::string& fileName, MotionNet& motionNet)
{
  ifstream inputFileStream ( fileName.c_str() , ifstream::in );

  if(inputFileStream.fail())
  {
    throw std::string("Could not open MotionNet file.");
  }//end if

  Scanner scanner(inputFileStream);
  MotionNetParser parser(scanner);

  motionNet = parser.parse();

  inputFileStream.close();

  if(motionNet.isEmpty())
  {
    throw std::string("MotionNet file is empty.");
  }//end if
}//end loadMotionNetFromFile


bool KeyFrameMotionEngine::loadMotionNet(const std::string& fileName, const std::string& motionNetName)
{
  try
  {
    MotionNet motionNet;

    cout << "KeyFrameMotionEngine: load " << fileName;
    loadMotionNetFromFile(fileName, motionNet);
    cout << "\tok" << endl;

    // loading successfull: copy to the map
    motionNets[motionNetName] = motionNet;
    return true;
  }
  catch(std::string e)
  {
    // loading failed
    cout << "\tfail" << endl; 
    cout << e << endl;
    return false;
  }
}//end loadMotionNet


AbstractMotion* KeyFrameMotionEngine::createMotion(const MotionRequest& motionRequest)
{
  std::string motionName = motion::getName(motionRequest.id);

  if(motionNets.find(motionName) != motionNets.end())
  {
    delete currentMotion;
    currentMotion = new KeyFrameMotion(motionNets.find(motionName)->second, motionRequest.id);
    return currentMotion;
  }//end if

  return NULL;
}//end createMotion

/*
 * TODO
void KeyFrameMotionEngine::executeDebugCommand(
    const std::string& command, const std::map<std::string,std::string>& arguments,
    std::stringstream &outstream)
{  
  if(command == "reload:motion_net")
  { 
    if(arguments.find("file") != arguments.end())
    {
      string fileName = arguments.find("file")->second;

      outstream << "load " << fileName;

      string filePath = Platform::getInstance().theConfigPathInfo.motionnet + fileName + ".mef";
      if(loadMotionNet(filePath, fileName))
        outstream << " ok\n" << endl;
      else
        outstream << " fail\n" << endl;
    }
    else
      outstream << "Command fail: Usage: reload:motion_net file=turn_right" << endl;
  }
  else if(command == "motion:load_editor_motionnet")
  {
    if(arguments.find("condition") != arguments.end())
    {
      cout << command << endl;
    }
    string filePath = Platform::getInstance().theConfigPathInfo.motionnet + "../" + "play_editor_motionnet.mef";
    outstream << "load motionnet editor file: " << filePath;
    if(loadMotionNet(filePath, string("play_editor_motionnet")))
    {
        outstream << " ok\n" << endl;
    }
    else
        outstream << " fail\n" << endl;
  }//end if
}//end executeDebugCommand
*/
