/**
 * @file NaoController.cpp
 *
 * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu Yuan</a>
 * @breief Interface for the real robot for cognition
 *
 */

#include "NaoController.h"
#include <PlatformInterface/Platform.h>

using namespace naoth;

NaoController::NaoController()
:playerCfgLoaded(false),
theSoundHandler(NULL),
theTeamComm(NULL)
{
  naothDataWriting = naothData.writing();
  
  // register input
  registerInput<AccelerometerData>(*this);
  registerInput<FrameInfo>(*this);
  registerInput<SensorJointData>(*this);
  registerInput<Image>(*this);
  registerInput<FSRData>(*this);
  registerInput<GyrometerData>(*this);
  registerInput<InertialSensorData>(*this);
  registerInput<IRReceiveData>(*this);
  registerInput<CurrentCameraSettings>(*this);
  registerInput<ButtonData>(*this);
  registerInput<BatteryData>(*this);
  registerInput<UltraSoundReceiveData>(*this);
  registerInput<MotorJointData>(*this);

  // register output
  registerOutput<const CameraSettingsRequest>(*this);
  registerOutput<const LEDData>(*this);
  registerOutput<const IRSendData>(*this);
  registerOutput<const UltraSoundSendData>(*this);
  registerOutput<const SoundPlayData>(*this);
  
  cout<<"Init Platform"<<endl;
  Platform::getInstance().init(this);
  
  std::cout << "Init CameraHandler" << endl;
  theCameraHandler.init("/dev/video");
  
  std::cout << "Init SoundHandler" <<endl;
  theSoundHandler = new SoundControl();

  std:cout<< "Init TeamComm"<<endl;
  theTeamComm = new TeamCommunicator();
}

NaoController::~NaoController()
{
  if (theSoundHandler!=NULL)
  {
    delete theSoundHandler;
  }

  if ( theTeamComm != NULL)
  {
    delete theTeamComm;
  }
}

void NaoController::get(Image& data)
{
  theCameraHandler.get(data);
}

void NaoController::set(const CameraSettingsRequest& data)
{
  theCameraHandler.setCameraSettings(data, data.queryCameraSettings);
}

void NaoController::get(CurrentCameraSettings& data)
{
  theCameraHandler.getCameraSettings(data);
}

void NaoController::set(const SoundPlayData& data)
{
  theSoundHandler->setSoundData(data);
}

void NaoController::getCognitionInput()
{
  if ( libNaothData.swapReading() )
  {
    libNaothDataReading = libNaothData.reading();
  }
  else
  {
    // didn't get new sensor data
    libNaothDataReading = NULL;
  }
  
  NaoControllerBase<NaoController>::getCognitionInput();
}
  
void NaoController::setCognitionOutput()
{
  NaoControllerBase<NaoController>::setCognitionOutput();
  
  naothData.swapWriting();
  naothDataWriting = naothData.writing();
}

void NaoController::get(TeamMessageData& data)
{
  data.data.clear();
  theTeamComm->receive(data.data);
}

void NaoController::set(const RobotMessageData& data)
{
  theTeamComm->send(data.data);
}

void NaoController::get(GameData& data)
{
  if (!playerCfgLoaded)
  {
    playerCfgLoaded = true;
    data.loadFromCfg( naoth::Platform::getInstance().theConfiguration );
  }
}
