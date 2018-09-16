#ifndef _AudioRecorder_H
#define _AudioRecorder_H
#include <thread>
#include <mutex>
#include <iostream>
#include <pulse/simple.h>

#include "SoundConfig.h"

#include "Representations/Infrastructure/AudioData.h"
#include "Representations/Infrastructure/WhistleControl.h"

namespace naoth
{
	class AudioRecorder
	{
		public:
	  	AudioRecorder();
	  	virtual ~AudioRecorder();

	  	void get(naoth::AudioData& data);
      void set(const naoth::WhistleControl& controlData);

	  	std::vector<short> audioReadBuffer;
	  protected:
  		std::thread audioRecorderThread;
      std::mutex getMutex;
      std::mutex setMutex;
      int command;

      //Audio Control Parameter:
  		std::string activeChannels;
      int numChannels;
      int sampleRate;
      int buffer_size;

      volatile bool running;
      bool recording;
      bool resetting;
      int deinitCyclesCounter;

  		void execute();  		
  		void initAudio();
  		void deinitAudio();

  		pa_simple* paSimple;
	};
}

#endif // _AudioRecorder_H