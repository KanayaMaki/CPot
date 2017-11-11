#include "./Input/DirectInput/inputDirectInput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace cpot {

namespace directInput {


void JoystickInstance::Release() {
	if (mJoystick) {
		mJoystick->Unacquire();
		mJoystick->Release();
		mJoystick = nullptr;
		mAleradyAcquire = false;
	}
}


::BOOL CALLBACK JoystickDevice::EnumJoysticksCallback(const DIDEVICEINSTANCEA*
	pdidInstance, VOID* pContext) {
	HRESULT hr;

	if (JoystickDevice::S().IsAlreadyUse(pdidInstance->guidInstance)) {
		return DIENUM_CONTINUE;
	}

	//空いているJoystickを見つける
	JoystickInstance* lJoystick = JoystickDevice::S().FindNoUseJoystickInstance();

	if (lJoystick == nullptr) {
		return DIENUM_CONTINUE;
	}

	// Obtain an interface to the enumerated joystick.
	hr = JoystickDevice::S().mInput->CreateDevice(pdidInstance->guidInstance,
		&(lJoystick->mJoystick), NULL);
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	}

	//return DIENUM_STOP;
	return DIENUM_CONTINUE;
}


BOOL JoystickDevice::IsAlreadyUse(GUID aInstanceGUID) {
	for (s32 i = 0; i < cJoystickMaxNum; i++) {
		if (aInstanceGUID == mJoystick[i].mInstanceGUID && mJoystick[i].mJoystick != nullptr) {
			return true;
		}
	}
	return false;
}

JoystickInstance* JoystickDevice::FindNoUseJoystickInstance() {
	for (s32 i = 0; i < cJoystickMaxNum; i++) {
		if (mJoystick[i].mJoystick == nullptr) {
			return &(mJoystick[i]);
		}
	}
	return nullptr;
}

void JoystickDevice::Init(HINSTANCE aHInstance, HWND aHwnd) {

	mHInstance = aHInstance;
	mHwnd = aHwnd;

	Reset();
}

void JoystickDevice::Reset() {

	HRESULT hr;

	if (!mInput) {
		hr = DirectInput8Create(mHInstance, DIRECTINPUT_VERSION, IID_IDirectInput8A, (void**)&mInput, NULL);
		if (FAILED(hr)) {
			CPOT_ASSERT(0 && "DirectInputの作成に失敗しました");
		}
	}

	mInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
		NULL, DIEDFL_ATTACHEDONLY);

	for (s32 i = 0; i < cJoystickMaxNum; i++) {

		if (mJoystick[i].IsValid()) {

			if (mJoystick[i].mAleradyAcquire == false) {

				if (FAILED(hr = mJoystick[i].mJoystick->SetDataFormat(&c_dfDIJoystick2))) {
					CPOT_ASSERT(0 && "DirectInputのフォーマットの設定に失敗しました");
				}

				if (FAILED(hr = mJoystick[i].mJoystick->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
					CPOT_ASSERT(0 && "DirectInputの協調レベルの設定に失敗しました");
				}

				DIDEVCAPS diDevCaps;
				diDevCaps.dwSize = sizeof(DIDEVCAPS);
				if (FAILED(hr = mJoystick[i].mJoystick->GetCapabilities(&diDevCaps))) {
					CPOT_ASSERT(0 && "DirectInputの設定に失敗しました");
				}

				mJoystick[i].mJoystick->Acquire();
				mJoystick[i].mAleradyAcquire = true;
			}
		}
	}


}

JoystickDevice::~JoystickDevice() {

	for (s32 i = 0; i < cJoystickMaxNum; i++) {
		if (mJoystick[i].IsValid()) {
			mJoystick[i].Release();
		}
	}

	if (mInput) {
		mInput->Release();
		mInput = nullptr;
	}
}



void JoystickDevice::Update() {
	if (mInput == nullptr) {
		return;
	}

	for (s32 i = 0; i < cJoystickMaxNum; i++) {

		if (mJoystick[i].mJoystick == nullptr) continue;

		HRESULT hr;
		hr = mJoystick[i].mJoystick->Poll();
		if (FAILED(hr)) {
			hr = mJoystick[i].mJoystick->Acquire();
		}

		DIJOYSTATE2 js;
		hr = mJoystick[i].mJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &js);
		if (FAILED(hr)) {
			//assert(0 && "DirectInputのデータ取得に失敗しました");
			for (s32 j = 0; j < CJoystickButton::cMax; j++) {
				mJoystick[i].mValue[j] = 0.0f;
			}
			if (hr == HRESULT_FROM_WIN32(ERROR_READ_FAULT)) {
				mJoystick[i].Release();
			}
			return;
		}

		mJoystick[i].mValue[CJoystickButton::cNull] = 0.0f;
		//スティック
		mJoystick[i].mValue[CJoystickButton::cStickAxis1Plus] = Clamp01((f32)(js.lX - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis1Minus] = Clamp01(-(f32)(js.lX - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis2Plus] = Clamp01((f32)(js.lY - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis2Minus] = Clamp01(-(f32)(js.lY - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis3Plus] = Clamp01((f32)(js.lZ - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis3Minus] = Clamp01(-(f32)(js.lZ - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis4Plus] = Clamp01((f32)(js.lRx - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis4Minus] = Clamp01(-(f32)(js.lRx - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis5Plus] = Clamp01((f32)(js.lRy - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis5Minus] = Clamp01(-(f32)(js.lRy - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis6Plus] = Clamp01((f32)(js.lRz - 0x7fff) / 0x7fff);
		mJoystick[i].mValue[CJoystickButton::cStickAxis6Minus] = Clamp01(-(f32)(js.lRz - 0x7fff) / 0x7fff);

		//十字キー
		for (s32 j = 0; j < 4; j++) {
			mJoystick[i].mValue[CJoystickButton::cPOV1XPlus + j * 4] = 0.0f;
			mJoystick[i].mValue[CJoystickButton::cPOV1XMinus + j * 4] = 0.0f;
			mJoystick[i].mValue[CJoystickButton::cPOV1YPlus + j * 4] = 0.0f;
			mJoystick[i].mValue[CJoystickButton::cPOV1YMinus + j * 4] = 0.0f;

			if (js.rgdwPOV[i] == 0) mJoystick[i].mValue[CJoystickButton::cPOV1YMinus + j * 4] = 1.0f;
			else if (js.rgdwPOV[i] == 180L * DI_DEGREES) mJoystick[i].mValue[CJoystickButton::cPOV1YPlus + j * 4] = 1.0f;
			else if (js.rgdwPOV[i] == 90L * DI_DEGREES) mJoystick[i].mValue[CJoystickButton::cPOV1XPlus + j * 4] = 1.0f;
			else if (js.rgdwPOV[i] == 270L * DI_DEGREES) mJoystick[i].mValue[CJoystickButton::cPOV1XMinus + j * 4] = 1.0f;
		}

		//ボタン
		for (s32 j = CJoystickButton::cButton1; j <= CJoystickButton::cButton20; j++) {
			mJoystick[i].mValue[j] = js.rgbButtons[j - CJoystickButton::cButton1] & 0x80;
		}

		for (s32 j = 0; j < CJoystickButton::cMax; j++) {
			if (NotZero(mJoystick[i].mValue[j])) {
				int as = 0;
				as++;
			}
		}
	}
}



}

}