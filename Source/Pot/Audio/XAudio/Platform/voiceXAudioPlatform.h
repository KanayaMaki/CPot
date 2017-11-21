//
//	content	:	XAudioにおけるデバイスでのVoiceの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Audio/XAudio/Platform/deviceXAudioPlatform.h"


namespace cpot {

namespace xaudio {

namespace platform {


class Clip;

class Voice {
	IXAudio2SourceVoice*	mSourceVoice;
	Clip* mClip;

public:
	Voice() {
		Init();
	}
	Voice(Clip& aClip) {
		Init();
		Load(aClip);
	}

	void Init() {
		mSourceVoice = nullptr;
	}

	void Load(Clip& aClip);
	void Release();

	~Voice() {
		Release();
	}

	BOOL IsLoaded() const {
		return mSourceVoice != nullptr;
	}

public:
	void Play() {
		if (!IsLoaded()) return;
		mSourceVoice->Start();
	}
	void Stop() {
		if (!IsLoaded()) return;

		XAUDIO2_VOICE_STATE xa2state;
		mSourceVoice->GetState(&xa2state);
		if (xa2state.BuffersQueued) {
			//停止する
			mSourceVoice->Stop();
		}
	}
	void Volume(f32 aVolume) {
		mSourceVoice->SetVolume(aVolume);
	}
	f32 Volume() {
		f32 lVolume;
		mSourceVoice->GetVolume(&lVolume);
		return lVolume;
	}
};


}

}

}