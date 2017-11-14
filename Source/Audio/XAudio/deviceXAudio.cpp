#include "./device.h"

namespace cyc {

namespace pot {

namespace xaudio {


void Device::Init() {

	HRESULT      hr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	/**** Create XAudio2 ****/
	hr = XAudio2Create(&(mXAudio2), 0/* , XAUDIO2_DEFAULT_PROCESSOR*/);
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