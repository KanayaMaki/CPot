#pragma once

#include "./Atom/atom.h"

#include "./device.h"


namespace cyc {

namespace pot {

namespace xaudio {


class Clip;


class Voice {
	IXAudio2SourceVoice*	mSourceVoice;

public:
	Voice() {
		Init();
	}
	Voice(Clip* aClip) {
		Init();
		Load(aClip);
	}

	void Init() {
		mSourceVoice = nullptr;
	}

	void Load(Clip* aClip);
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
			//’âŽ~‚·‚é
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