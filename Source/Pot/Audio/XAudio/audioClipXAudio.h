//
//	content	:	AudioClip��XAudio�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Usefull/resourceList.h"

#include "./Pot/Audio/audioClip.h"
#include "./Pot/Audio/XAudio/Platform/clipXAudioPlatform.h"


namespace cpot {

namespace xaudio {


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
	platform::Clip mClip;

	#pragma endregion
};

}

using AudioClip = xaudio::AudioClip;

}