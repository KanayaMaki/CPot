//
//	content	:	XAudio�ɂ�����f�o�C�X�ł�Clip�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

#include "./Audio/XAudio/Device/deviceXAudioDevice.h"


namespace cpot {

namespace xaudio {

namespace device {

class Voice;

class Clip {

	friend class Voice;
	HashString<64> mFileName;
	BOOL mIsLoop;
	f32 mVolume;

	WAVEFORMATEXTENSIBLE	mWfx;			// WAV�t�H�[�}�b�g
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

		//!���̃N���b�v���g�p���Ă���S�Ẵ{�C�X��Release���Ă����K�v������
		delete[] mDataBuffer;

		Reset();
	}


	BOOL IsLoaded() const {
		return mDataBuffer != nullptr;
	}

};


}

}

}