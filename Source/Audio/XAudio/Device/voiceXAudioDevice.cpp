//
//	content	:	XAudioにおけるデバイスでのVoiceの実装
//	author	:	SaitoYoshiki
//


#include "./Audio/XAudio/Device/clipXAudioDevice.h"
#include "./Audio/XAudio/Device/voiceXAudioDevice.h"

namespace cpot {

namespace xaudio {

namespace device {


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