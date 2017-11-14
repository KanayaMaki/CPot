//
//	content	:	AudioVoiceのXAudioでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

#include "./Audio/audioVoice.h"
#include "./Audio/XAudio/audioClipXAudio.h"

#include "./Audio/XAudio/Device/voiceXAudioDevice.h"

namespace cpot {

namespace xaudio {

class AudioVoice : public AudioVoiceBase {

public:
	void Load(AudioClip& aClip) CPOT_OR {
		mVoice.Load(aClip.mClip);
	}

public:
	void Release() CPOT_OR {
		mVoice.Release();
	}


	//操作
	#pragma region Operate

public:
	//再生
	void Play() CPOT_OR {
		mVoice.Play();
	}

	//停止
	void Stop() CPOT_OR {
		mVoice.Stop();
	}

	//ボリュームを設定
	void SetVolume(f32 aVolume) CPOT_OR {
		mVoice.Volume(aVolume);
	}
	//ボリュームを設定（現在のボリュームから相対的に）
	void SetVolumeRel(f32 aRelative) CPOT_OR {
		mVoice.Volume(mVoice.Volume() * aRelative);
	}

	#pragma endregion


public:
	//ボリュームを取得
	f32 GetVolume() CPOT_OR {
		return mVoice.Volume();
	}

	BOOL IsLoad() const CPOT_OR {
		return mVoice.IsLoaded();
	}


	//フィールド
	#pragma region Field

public:
	device::Voice mVoice;

	#pragma endregion

};

}

using AudioVoice = xaudio::AudioVoice;

}