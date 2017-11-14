#pragma once

#include "./Atom/atom.h"

#include "./Audio/XAudio/deviceXAudio.h"


namespace cpot {

namespace xAudio {


class Voice;

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

		//使われているすべてのボイスを削除
		delete[] mDataBuffer;

		Reset();
	}


	BOOL IsLoaded() const {
		return mDataBuffer != nullptr;
	}

};


}

}