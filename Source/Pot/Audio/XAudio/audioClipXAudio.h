//
//	content	:	AudioClipのXAudioでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Audio/audioClip.h"
#include "./Pot/Audio/XAudio/Platform/clipXAudioPlatform.h"


namespace cpot {

namespace xaudio {


class AudioClip : public AudioClipBase {

public:
	void Load(const CHAR* aFileName) CPOT_OR {
		mClip.Load(aFileName);
	};
	void LoadFromKey(const HashTableKey& aFileNameKey) CPOT_OR {
		mClip.Load(AudioName::S().Get(aFileNameKey).Get());
	};
	void LoadFromKey(const CHAR* aFileNameKey) CPOT_OR {
		LoadFromKey(HashTableKey(aFileNameKey));
	};

public:
	void Release() CPOT_OR {
		mClip.Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mClip.IsLoaded();
	};


	//フィールド
	#pragma region Field

public:
	platform::Clip mClip;

	#pragma endregion
};

}

using AudioClip = xaudio::AudioClip;

}