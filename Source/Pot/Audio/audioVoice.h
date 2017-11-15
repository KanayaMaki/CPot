//
//	content	:	AudioVoiceのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Audio/audioName.h"
#include "./Pot/Audio/audioClip.h"

namespace cpot {

class AudioVoiceBase {

public:
	CPOT_VI void Load(AudioClip& aClip) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;


	//操作
	#pragma region Operate

public:
	//再生
	CPOT_VI void Play() CPOT_ZR;

	//停止
	CPOT_VI void Stop() CPOT_ZR;

	//ボリュームを設定
	CPOT_VI void SetVolume(f32 aVolume) CPOT_ZR;
	//ボリュームを設定（現在のボリュームから相対的に）
	CPOT_VI void SetVolumeRel(f32 aRelative) CPOT_ZR;

	#pragma endregion


public:
	//ボリュームを取得
	CPOT_VI f32 GetVolume() CPOT_ZR;

	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}

#ifdef CPOT_ON_WINDOWS
#include "./Pot/Audio/XAudio/audioVoiceXAudio.h"
#endif