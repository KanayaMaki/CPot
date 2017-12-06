//
//	content	:	AudioClip��XAudio�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceList.h"
#include "./Pot/Usefull/resourceLoadList.h"

#include "./Pot/Audio/audioClip.h"
#include "./Pot/Audio/Android/Device/audioClipAndroidDevice.h"


namespace cpot {

namespace android {


class AudioLoadData : public ResourceLoadList<AudioLoadData, String<64>> {

};

class AudioClip : public AudioClipBase {
	friend class ResourceList<AudioClip>;

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mClip.Load(AudioLoadData::S().Get(aUnionName).Get());
		SetName(aUnionName);
	};

	//�v���b�g�t�H�[������̓ǂݍ���
	void LoadPlatform(const CHAR* aFileName) {
		mClip.Load(aFileName);
		SetName(aFileName);
	};

public:
	void Release() CPOT_OR {
		mClip.Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mClip.IsLoaded();
	};


	//�t�B�[���h
	#pragma region Field

public:
	device::AudioClip mClip;

	#pragma endregion
};

}

using AudioClip = android::AudioClip;

}