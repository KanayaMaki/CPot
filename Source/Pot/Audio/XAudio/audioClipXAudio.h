//
//	content	:	AudioClip��XAudio�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Audio/audioClip.h"
#include "./Pot/Audio/XAudio/Platform/clipXAudioPlatform.h"


namespace cpot {

namespace xaudio {


class AudioXAudioData : public ResourceLoadList<AudioXAudioData, String<64>> {

};

class AudioClip : public AudioClipBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mClip.Load(AudioXAudioData::S().Get(aUnionName).Get());
	};
	void Load(const CHAR* aUnionName) CPOT_OR {
		Load(HashTableKey(aUnionName));
	};

	//�v���b�g�t�H�[������̓ǂݍ���
	void LoadPlatform(const CHAR* aFileName) {
		mClip.Load(aFileName);
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