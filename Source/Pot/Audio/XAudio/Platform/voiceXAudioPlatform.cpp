//
//	content	:	XAudioにおけるPlatformでのVoiceの実装
//	author	:	SaitoYoshiki
//


#include "./Pot/Audio/XAudio/Platform/clipXAudioPlatform.h"
#include "./Pot/Audio/XAudio/Platform/voiceXAudioPlatform.h"

namespace cpot {

namespace xaudio {

namespace platform {


void Voice::Load(Clip& aAudioClip) {
	if (IsLoaded()) {
		Release();
	}
	Device::S().mXAudio2->CreateSourceVoice(&mSourceVoice, &(aAudioClip.mWfx.Format));
	mSourceVoice->SubmitSourceBuffer(&(aAudioClip.mBuffer));	// ボイスキューに新しいオーディオバッファーを追加

	mClip = &aAudioClip;

	mClip->mVoices.Add(this);
}
void Voice::Release() {
	if (IsLoaded()) {

		Stop();	//ボイスを止める

		//ボイスを削除する
		mSourceVoice->FlushSourceBuffers();
		mSourceVoice->DestroyVoice();			// オーディオグラフからソースボイスを削除

		Init();
	}

	mClip->mVoices.Remove(this);
}


}

}

}