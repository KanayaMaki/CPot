//
//	content	:	AudioVoice��XAudio�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Audio/audioVoice.h"

#include "./Pot/Audio/Android/audioClipAndroid.h"
#include "./Pot/Audio/Android/Device/audioVoiceAndroidDevice.h"

namespace cpot {

namespace android {

class AudioVoice : public AudioVoiceBase {

public:
	void Load(AudioClip& aClip) CPOT_OR {
		mVoice.Load(aClip.mClip);
	}

public:
	void Release() CPOT_OR {
		mVoice.Release();
	}


	//����
	#pragma region Operate

public:
	//�Đ�
	void Play() CPOT_OR {
		mVoice.Play();
	}

	//��~
	void Stop() CPOT_OR {
		mVoice.Stop();
	}

	//�{�����[����ݒ�
	void SetVolume(f32 aVolume) CPOT_OR {
		mVoice.Volume(aVolume);
	}
	//�{�����[����ݒ�i���݂̃{�����[�����瑊�ΓI�Ɂj
	void SetVolumeRel(f32 aRelative) CPOT_OR {
		mVoice.Volume(mVoice.Volume() * aRelative);
	}

	#pragma endregion


public:
	//�{�����[�����擾
	f32 GetVolume() CPOT_OR {
		return mVoice.Volume();
	}

	BOOL IsLoad() const CPOT_OR {
		return mVoice.IsLoaded();
	}


	//�t�B�[���h
	#pragma region Field

public:
	device::AudioVoice mVoice;

	#pragma endregion

};

}

using AudioVoice = android::AudioVoice;

}