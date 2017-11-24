//
//	content	:	AudioVoiceのXAudioでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceList.h"

#include "./Pot/Audio/audioVoice.h"

#include "./Pot/Audio/Android/audioClipAndroid.h"
#include "./Pot/Audio/Android/Device/audioVoiceAndroidDevice.h"

namespace cpot {

namespace android {

class AudioVoice : public AudioVoiceBase {
	friend class ResourceList<AudioVoice>;


	//ロード
	#pragma region Load

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mClip = ResourceList<AudioClip>::S().Find(aUnionName);
		Load(mClip);	//委譲
	}
	void Load(AudioClip* aClip) CPOT_OR {
		mVoice.Load(aClip->mClip);
		SetName(aClip->GetName());
	}

	#pragma endregion

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
	AudioClip* mClip;
	device::AudioVoice mVoice;

	#pragma endregion

};

}

using AudioVoice = android::AudioVoice;

}