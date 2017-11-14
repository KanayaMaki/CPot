#include "./voice.h"
#include "./clip.h"

namespace cyc {

namespace pot {

namespace xaudio {


void Voice::Load(Clip* aAudioClip) {
	if (IsLoaded()) {
		Release();
	}
	Device::S().mXAudio2->CreateSourceVoice(&mSourceVoice, &(aAudioClip->mWfx.Format));
	mSourceVoice->SubmitSourceBuffer(&(aAudioClip->mBuffer));	// ボイスキューに新しいオーディオバッファーを追加
}
void Voice::Release() {
	if (IsLoaded()) {

		Stop();	//ボイスを止める

				//ボイスを削除する
		mSourceVoice->FlushSourceBuffers();
		mSourceVoice->DestroyVoice();			// オーディオグラフからソースボイスを削除

		Init();
	}
}


}

}

}