//
//	content	:	AudioClipのXAudioでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

#include "./Audio/audioClip.h"
#include "./Audio/XAudio/Device/clipXAudioDevice.h"


namespace cpot {

namespace xaudio {


class AudioClip : public AudioClipBase {

public:
	void Load(const CHAR* aFileName) CPOT_OR {
		mClip.Load(aFileName);
	};
	void Load(const HashTableKey& aFileNameKey) CPOT_OR {
		mClip.Load(AudioName::S().Get(aFileNameKey).Get());
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
	device::Clip mClip;

	#pragma endregion
};

}

using AudioClip = xaudio::AudioClip;

}