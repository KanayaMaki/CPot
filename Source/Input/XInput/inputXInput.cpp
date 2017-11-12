#include "./Input/XInput/inputXInput.h"

#ifdef CPOT_VALID_XINPUT

#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

namespace cpot {

namespace xInput {

void Input::Update() {
	
	//コントローラーの数繰り返す
	for (u32 i = 0; i < cControllerMaxNum; i++) {

		//前回のデータの保存
		mInputData[i].mBeforeData = mInputData[i].mData;

		//新しいデータの取得
		XINPUT_STATE tState;
		DWORD tErr = XInputGetState(i, &(tState));

		//コントローラが未接続なら
		if (tErr == ERROR_DEVICE_NOT_CONNECTED) {
			Reset(i);	//コントローラの入力値のリセット
		}
		else {
			mInputData[i].mIsValid = true;

			mInputData[i].mData.mLeftStickX = (tState.Gamepad.sThumbLX);
			mInputData[i].mData.mLeftStickY = (tState.Gamepad.sThumbLY);

			mInputData[i].mData.mRightStickX = (tState.Gamepad.sThumbRX);
			mInputData[i].mData.mRightStickY = (tState.Gamepad.sThumbRY);

			mInputData[i].mData.mLeftTrigger = (tState.Gamepad.bLeftTrigger);
			mInputData[i].mData.mRightTrigger = (tState.Gamepad.bRightTrigger);
		}
	}
}

//値の取得
f32 Input::GetValue(u32 aControllerNum, CInputCode aCode) const {
	return 0.0f;
}
f32 Input::GetValueBefore(u32 aControllerNum, CInputCode aCode) const {
	return 0.0f;
}


}

}

#endif