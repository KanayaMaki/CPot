//
//	content	:	XAudioのデバイスを管理する
//	author	:	SaitoYoshiki
//

#include "./Pot/Atom/atom.h"

#include "./Pot/Audio/XAudio/Device/deviceXAudioDevice.h"

#pragma comment(lib, "XAudio2.lib")

namespace cpot {

namespace xaudio {

namespace device {


void Device::Init() {

	HRESULT      hr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	/**** Create XAudio2 ****/
	UINT32 lCreateFlag = 0;
	#ifdef CPOT_ON_DEBUG
	//lCreateFlag += XAUDIO2_DEBUG_ENGINE;
	#endif

	hr = XAudio2Create(&(mXAudio2), lCreateFlag/* , XAUDIO2_DEFAULT_PROCESSOR*/);
	if (FAILED(hr)) {
		CoUninitialize();
		abort();
	}
	/**** Create Mastering Voice ****/
	hr = mXAudio2->CreateMasteringVoice(&(mMasteringVoice)/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/);
	if (FAILED(hr)) {
		if (mXAudio2) {
			mXAudio2->Release();
		}
		CoUninitialize();
		abort();
	}
}
void Device::Final() {
	mMasteringVoice->DestroyVoice();
	if (mXAudio2) {
		mXAudio2->Release();
	}
	CoUninitialize();
}


}

}

}