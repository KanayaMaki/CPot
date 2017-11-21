//
//	content	:	XAudio�ɂ�����f�o�C�X�ł�Clip�̎���
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

		//���̃N���b�v���g�p���Ă��邷�ׂẴ{�C�X�̍폜
		mVoices.Release();
		
		//�T�E���h�f�[�^�̍폜
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