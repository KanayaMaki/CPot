#include "./Input/XInput/inputXInput.h"

#pragma comment(lib, "xinput.lib")

namespace cpot {

namespace xInput {


void Device::Update() {
	
	//コントローラーの数繰り返す
	for (u32 i = 0; i < cJoystickMaxNum; i++) {

		//前回のデータの保存
		mInputData[i].mBeforeData = mInputData[i].mData;

		DWORD tErr = XInputGetState(i, &(mInputData[i].mData));

		//コントローラが未接続なら
		if (tErr == ERROR_DEVICE_NOT_CONNECTED) {
			Reset(i);	//コントローラの入力値のリセット
		}
		else {
			mInputData[i].mIsValid = true;
		}
	}
}

//値の取得
f32 Device::GetValue(u32 aCount, u32 aCode) const {
	return 0.0f;
}

//値の取得
f32 Device::GetAxis(u32 aCount, CAxis aAxis) const {
	return 0.0f;
}

//ボタンが押されているか
BOOL Device::GetButton(u32 aCount, u32 aCode) const {
	return false;
}

//ボタンが押された瞬間か
BOOL Device::GetButtonDown(u32 aCount, u32 aCode) const {
	return false;
}

//ボタンが離された瞬間か
BOOL Device::GetButtonUp(u32 aCount, u32 aCode) const {
	return false;
}
}

}