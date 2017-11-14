#pragma once

#include "./Atom/atom.h"
#include "./Inter/singleton.h"

#include <xaudio2.h>


namespace cyc {

namespace pot {

namespace xaudio {


class Clip;
class Voice;

class Device : public Singleton<Device> {
	friend Singleton<Device>;

private:
	Device() {}


public:
	IXAudio2*				mXAudio2;
	IXAudio2MasteringVoice*	mMasteringVoice;


public:
	void Init();
	void Final();
};


}

}

}