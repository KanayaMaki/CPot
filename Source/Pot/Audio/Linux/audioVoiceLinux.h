//
//	content	:	AudioVoice��XAudio�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceList.h"

#include "./Pot/Audio/audioVoice.h"

#include "./Pot/Audio/Linux/audioClipLinux.h"

namespace cpot {

namespace linux {

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
		SetName(aClip->GetName());
	}

	#pragma endregion

public:
	void Release() CPOT_OR {
	}


	//����
	#pragma region Operate

public:
	//�Đ�
	void Play() CPOT_OR {
	}

	//��~
	void Stop() CPOT_OR {
	}

	//�{�����[����ݒ�
	void SetVolume(f32 aVolume) CPOT_OR {
	}
	//�{�����[����ݒ�i���݂̃{�����[�����瑊�ΓI�Ɂj
	void SetVolumeRel(f32 aRelative) CPOT_OR {
	}

	#pragma endregion


public:
	//�{�����[�����擾
	f32 GetVolume() CPOT_OR {
		return 0.0f;
	}

	BOOL IsLoad() const CPOT_OR {
		return false;
	}


	//�t�B�[���h
	#pragma region Field

public:
	std::shared_ptr<AudioClip> mClip;

	#pragma endregion

};

}

using AudioVoice = linux::AudioVoice;

}