//
//	content	:	XAudioにおけるデバイスでのClipの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"


namespace cpot {

namespace android {

namespace device {

class AudioVoice;

class AudioClip {

	friend class AudioVoice;
	HashString<64> mFileName;
	BOOL mIsLoop;
	f32 mVolume;

public:
	AudioClip() {
		Reset();
	}
	~AudioClip() {
		Release();
	}

private:
	void Reset() {
		mIsLoop = true;
		mVolume = 1.0f;
	}

public:
	void Load(const CHAR* aFileName) {
		mFileName = aFileName;
	}
	void Release() {
		if (!IsLoaded()) {
			return;
		}

		
		Reset();
	}


	BOOL IsLoaded() const {
		return false;
	}
};


}

}

}