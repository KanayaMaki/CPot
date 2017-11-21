//
//	content	:	XAudioのデバイスを管理する
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include <xaudio2.h>


namespace cpot {

namespace xaudio {

namespace platform {


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