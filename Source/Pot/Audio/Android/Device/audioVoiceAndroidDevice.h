//
//	content	:	XAudioにおけるデバイスでのVoiceの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

namespace android {

namespace device {


class AudioClip;

class AudioVoice {
	AudioClip* mClip;

public:
	AudioVoice() {
		Init();
	}
	AudioVoice(AudioClip& aClip) {
		Init();
		Load(aClip);
	}

	void Init() {
		
	}

	void Load(AudioClip& aClip) {

	}
	void Release() {

	}

	~AudioVoice() {
		Release();
	}

	BOOL IsLoaded() const {
		return false;
	}

public:
	void Play() {
		if (!IsLoaded()) return;
		
	}
	void Stop() {
		if (!IsLoaded()) return;

	}
	void Volume(f32 aVolume) {
		
	}
	f32 Volume() {
		f32 lVolume;
		lVolume = 1.0f;
		return lVolume;
	}
};


}

}

}