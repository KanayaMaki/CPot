//
//	content	:	XAudioにおけるデバイスでのClipの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Audio/XAudio/Platform/deviceXAudioPlatform.h"


namespace cpot {

namespace xaudio {

namespace platform {

class Voice;

class VoiceObservers {
public:
	VoiceObservers() {
		mReleasing = false;
	}

public:
	void Add(Voice* aObserver) {
		mObserver.PushBack(aObserver);
	}
	void Remove(Voice* aObserver) {
		if (!mReleasing) {
			mObserver.Remove(aObserver);
		}
	}
	void Release();


private:
	Vector<Voice*> mObserver;
	BOOL mReleasing;
};


class Clip {

	friend class Voice;
	HashString<64> mFileName;
	BOOL mIsLoop;
	f32 mVolume;

	WAVEFORMATEXTENSIBLE	mWfx;			// WAVフォーマット
	XAUDIO2_BUFFER			mBuffer;
	BYTE*					mDataBuffer;

public:
	Clip() {
		Reset();
	}
	~Clip() {
		Release();
	}

private:
	void Reset() {
		mDataBuffer = nullptr;
		mIsLoop = true;
		mVolume = 1.0f;
	}

public:
	void Load(const CHAR* aFileName);
	void Release() {
		if (!IsLoaded()) {
			return;
		}

		//このクリップを使用しているすべてのボイスの削除
		mVoices.Release();
		
		//サウンドデータの削除
		delete[] mDataBuffer;

		Reset();
	}


	BOOL IsLoaded() const {
		return mDataBuffer != nullptr;
	}

private:
	VoiceObservers mVoices;
};


}

}

}