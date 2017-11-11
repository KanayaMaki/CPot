#include "./Input/Windows/inputWindows.h"

#include <Windows.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace cpot {

namespace windows {


//初期化
#pragma region Init


InputDevice::InputDevice() {

	mHInstance = 0;
	mHwnd = 0;

	mInput = nullptr;
	mKeyboardDevice = nullptr;
	mMouseDevice = nullptr;
}

void InputDevice::Init(HINSTANCE aHInstance, HWND aHwnd) {

	//引数の状態が正常かチェックする
	if (aHInstance == 0) {
		CPOT_ERROR("HINSTANCEが無効です");
		return;
	}
	if (aHwnd == 0) {
		CPOT_ERROR("HWNDが無効です");
		return;
	}

	mHInstance = aHInstance;
	mHwnd = aHwnd;


	HRESULT hr;

	//DirectInputデバイスの作成
	if (!mInput) {
		hr = DirectInput8Create(mHInstance, DIRECTINPUT_VERSION, IID_IDirectInput8A, (void**)&mInput, NULL);
		if (FAILED(hr)) {
			CPOT_ERROR("DirectInputの作成に失敗しました");
		}
	}

	//キーボードデバイスの作成
	if (!mKeyboardDevice) {
		hr = mInput->CreateDevice(GUID_SysKeyboard, &mKeyboardDevice, NULL);
		if (FAILED(hr)) {
			CPOT_ERROR("DirectInputの作成に失敗しました");
			return;
		}

		hr = mKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) {
			CPOT_ERROR("DirectInputの作成に失敗しました");
			return;
		}

		hr = mKeyboardDevice->SetCooperativeLevel(mHwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr)) {
			CPOT_ERROR("DirectInputの作成に失敗しました");
			return;
		}

		mKeyboardDevice->Acquire();
	}

	//マウスデバイスの作成
	if (!mMouseDevice) {
		hr = mInput->CreateDevice(GUID_SysMouse, &mMouseDevice, NULL);
		if (FAILED(hr)) {
			CPOT_ERROR("マウスデバイスの作成に失敗しました");
			return;
		}

		hr = mMouseDevice->SetDataFormat(&c_dfDIMouse);
		if (FAILED(hr)) {
			CPOT_ERROR("マウスデバイスの作成に失敗しました");
			return;
		}

		hr = mMouseDevice->SetCooperativeLevel(mHwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr)) {
			CPOT_ERROR("マウスデバイスの作成に失敗しました");
			return;
		}

		mMouseDevice->Acquire();
	}

	//入力情報の初期化
	for (u32 i = 0; i < CKeyCode::cMax; i++) {
		mValue[i] = 0.0f;
	}
}


#pragma endregion



//終了処理
#pragma region Final

InputDevice::~InputDevice() {
	if (mKeyboardDevice) {
		mKeyboardDevice->Unacquire();
		mKeyboardDevice->Release();
		mKeyboardDevice = nullptr;
	}
	if (mMouseDevice) {
		mMouseDevice->Unacquire();
		mMouseDevice->Release();
		mMouseDevice = nullptr;
	}
	if (mInput) {
		mInput->Release();
		mInput = nullptr;
	}
}


#pragma endregion



//更新
#pragma region Update


void InputDevice::Update() {
	UpdateKeyboard();
	UpdateMouse();
}

void InputDevice::UpdateKeyboard() {
	//キーボード情報の取得
	u8 tValue[256];
	HRESULT  hr;
	hr = mKeyboardDevice->GetDeviceState(sizeof(tValue), (LPVOID)&tValue);

	//取得に失敗したら
	if (FAILED(hr)) {
		//有効にして、もう一度取得
		mKeyboardDevice->Acquire();
		hr = mKeyboardDevice->GetDeviceState(sizeof(tValue), (LPVOID)&tValue);

		//取得に失敗したら
		if (FAILED(hr)) {
			for (u32 i = 0; i < 256; i++) {
				mValue[i] = 0.0f;	//入力無し
			}
			return;
		}
	}

	//取得したデータを、フィールドに格納する
	for (s32 i = 0; i < 256; i++) {
		//入力があったら
		if (tValue[i] & 0x80) {
			mValue[i] = 1.0f;
		}
		else {
			mValue[i] = 0.0f;
		}
	}
}

void InputDevice::UpdateMouse() {
	//マウス座標の取得
	POINT tMouse;
	GetCursorPos(&tMouse);
	ScreenToClient(mHwnd, &tMouse);

	mValue[CKeyCode::cMouseCursorX] = (f32)tMouse.x;
	mValue[CKeyCode::cMouseCursorY] = (f32)tMouse.y;

	mValue[CKeyCode::cNull] = 0.0f;


	//マウス情報の取得
	DIMOUSESTATE tMouseState;
	HRESULT  hr;
	hr = mMouseDevice->GetDeviceState(sizeof(tMouseState), (LPVOID)&tMouseState);

	//もしマウス情報の取得に失敗したら
	if (FAILED(hr)) {
		//有効にして、もう一度取得
		mMouseDevice->Acquire();
		hr = mMouseDevice->GetDeviceState(sizeof(tMouseState), (LPVOID)&tMouseState);

		//もし失敗したなら
		if (FAILED(hr)) {
			for (u32 i = CKeyCode::cMouseWheelForward; i <= CKeyCode::cMouseButton4; i++) {
				mValue[i] = 0.0f; //入力無し
			}
		}
	}

	//ホイール情報の格納
	mValue[CKeyCode::cMouseWheelForward] = tMouseState.lZ > 0 ? 1.0f : 0.0f;
	mValue[CKeyCode::cMouseWheelBack] = tMouseState.lZ < 0 ? 1.0f : 0.0f;

	//マウスのボタン情報の格納
	for (u32 i = 0; i < 4; i++) {
		//入力があれば
		if (tMouseState.rgbButtons[i] & 0x80) {
			mValue[CKeyCode::cMouseButton1 + i] = 1.0f;
		}
		else {
			mValue[CKeyCode::cMouseButton1 + i] = 0.0f;
		}
	}
}

#pragma endregion



BOOL InputDevice::IsValid() const {
	return mInput != nullptr;
}


}

}