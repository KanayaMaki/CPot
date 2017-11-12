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
	//引数が適正かのチェック
	CPOT_ASSERT(aControllerNum <= cControllerMaxNum);

	return GetValue(mInputData[aControllerNum].mData, aCode);
}
f32 Input::GetValueBefore(u32 aControllerNum, CInputCode aCode) const {
	//引数が適正かのチェック
	CPOT_ASSERT(aControllerNum <= cControllerMaxNum);

	return GetValue(mInputData[aControllerNum].mBeforeData, aCode);
}

f32 Input::GetValue(const InputData& aData, CInputCode aCode) {

	//ボタンなら
	if (aCode <= cRShoulder) {
		return aData.mButton.IsStand(aCode) ? 1.0f : 0.0f;
	}

	//アナログな値を持つものなら
	switch (aCode) {
		case cLStickLeft:
			return Clamp01(-(f32)aData.mLeftStickX / 0x7fff);
		case cLStickRight:
			return Clamp01((f32)aData.mLeftStickX / 0x7fff);
		case cLStickUp:
			return Clamp01((f32)aData.mLeftStickY / 0x7fff);
		case cLStickDown:
			return Clamp01(-(f32)aData.mLeftStickY / 0x7fff);
		case cRStickLeft:
			return Clamp01(-(f32)aData.mRightStickX / 0x7fff);
		case cRStickRight:
			return Clamp01((f32)aData.mRightStickX / 0x7fff);
		case cRStickUp:
			return Clamp01((f32)aData.mRightStickY / 0x7fff);
		case cRStickDown:
			return Clamp01(-(f32)aData.mRightStickY / 0x7fff);
		case cLTrigger:
			return Clamp01((f32)aData.mLeftTrigger / 0xff);
		case cRTrigger:
			return Clamp01((f32)aData.mRightTrigger / 0xff);
	}
	return 0.0f;
}


}

}

#endif