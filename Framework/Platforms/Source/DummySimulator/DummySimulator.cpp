/*
* File:   DummySimulator.cpp
* Author: schlottb[at]informatik.hu-berlin.de
*
* Created on 2017.05.21
*/
#ifdef  WIN32
#include <windows.h>
#include <winbase.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif //WIN32

#include "myconio.h"

#include "DummySimulator.h"
#include "Tools/NaoTime.h"
#include "Tools/Math/Common.h"

#include "PlatformInterface/Platform.h"

using namespace std;
using namespace naoth;

DummySimulator::DummySimulator(bool backendMode, bool realTime, unsigned short port)
  : PlatformInterface("DummySimulator", CYCLE_TIME),
  backendMode(backendMode)
{
  registerInput<FrameInfo>(*this);

  registerInput<DebugMessageInCognition>(*this);
  registerInput<DebugMessageInMotion>(*this);
  registerOutput<DebugMessageOut>(*this);


  theDebugServer.start(port);
  theDebugServer.setTimeOut(0);
}


void DummySimulator::printHelp()
{
  cout << endl;
  cout << "Welcome to the NaoTH DummySimulator" << endl;
  cout << "--------------------------------------------" << endl << endl;

  cout << "p - play " << endl;
  cout << "r - repeat a frame" << endl;
  cout << "q or x - quit/exit" << endl << endl;

  cout << "After a frame was executed you will always get a line showing you the current frame" << endl;
}//end printHelp

char DummySimulator::getInput()
{
  if (backendMode) {
    return static_cast<char>(getchar());
  } else {
    return static_cast<char>(getch());
  }
}

void DummySimulator::main()
{
  printHelp();
  executeFrame();

  char c;
  while ((c = getInput()) && c != 'q' && c != 'x')
  {
    if (c == 'r') {
      executeFrame();
    } else if (c == 'p') {
      play();
    }
  }

  cout << endl << "bye bye!" << endl;
}//end main


void DummySimulator::play()
{
#ifdef WIN32
  //cerr << "Play-Support now yet enabled under Windows" << endl;
#else
  // set terminal to non-blocking...
  const int fd = fileno(stdin);
  const int fcflags = fcntl(fd, F_GETFL);
  if (fcntl(fd, F_SETFL, fcflags | O_NONBLOCK) <0)
  {
    cerr << "Could not set terminal to non-blocking mode" << endl;
    cerr << "\"Play\" capatibility not available on this terminal" << endl;
    return;
  }
#endif //WIN32

  int c = -1;
  while (c != 'p' && c != '\n'&& c != 'q' && c != 'x')
  {
    unsigned int startTime = NaoTime::getNaoTimeInMilliSeconds();
    executeFrame();
    unsigned int calculationTime = NaoTime::getNaoTimeInMilliSeconds() - startTime;
    // wait at least 5ms but max 1s
    unsigned int waitTime = Math::clamp((int)frameExecutionTime - (int)calculationTime, 5, 1000);

#ifdef WIN32
    Sleep(waitTime);
    if (_kbhit()) {
      c = getInput();
    }
#else
    // wait some time
    usleep(waitTime * 1000);
    c = getInput();
#endif

  }//while
}

void DummySimulator::executeFrame()
{
  runCognition();
  runMotion();
}