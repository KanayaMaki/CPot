//
//	content	:	AudioVoice��XAudio�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceList.h"

#include "./Pot/Audio/audioVoice.h"
#include "./Pot/Audio/XAudio/audioClipXAudio.h"

#include "./Pot/Audio/XAudio/Platform/voiceXAudioPlatform.h"

namespace cpot {

namespace xaudio {


class AudioVoice : public AudioVoiceBase {
	friend class ResourceList<AudioVoice>;


	//���[�h
	#pragma region Load

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mClip = ResourceList<AudioClip>::S().Find(aUnionName);
		Load(mClip);	//�Ϗ�
	}
	void Load(std::shared_ptr<AudioClip> aClip) CPOT_OR {
		mVoice.Load(aClip->mClip);
		SetName(aClip->GetName());
	}

	#pragma endregion


	//�����[�X
	#pragma region Release

public:
	void Release() CPOT_OR {
		mVoice.Release();
		mClip = nullptr;
	}

	#pragma endregion


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


	//�擾
	#pragma region Getter

public:
	//�{�����[�����擾
	f32 GetVolume() CPOT_OR {
		return mVoice.Volume();
	}

	BOOL IsLoad() const CPOT_OR {
		return mVoice.IsLoaded();
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

public:
	std::shared_ptr<AudioClip> mClip;
	platform::Voice mVoice;

	#pragma endregion

};

}

using AudioVoice = xaudio::AudioVoice;

}