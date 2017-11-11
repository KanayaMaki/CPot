//
//	XInputを使用した入力のクラス
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include <Xinput.h>

namespace cpot {

namespace xInput {


//Joystickコントローラーのボタンを定義
enum class CCode {
	cLStickLeft,
	cLStickRight,
	cLStickUp,
	cLStickDown,
	cRStickLeft,
	cRStickRight,
	cRStickUp,
	cRStickDown,
	cDPadLeft,
	cDPadRight,
	cDPadUp,
	cDPadDown,
	cButtonA,
	cButtonB,
	cButtonX,
	cButtonY,
	cLTrigger,
	cLThumb,
	cLShoulder,
	cRTrigger,
	cRThumb,
	cRShoulder,
	cNull,
	cMax,
};

//コントローラの軸を定義
enum class CAxis {
	cLStickX,
	cLStickY,
	cRStickX,
	cRStickY,
	cDPadX,
	cDPadY,
	cTrigger,
	cNull,
	cMax,
};


class Device : public Singleton<Device> {
	friend Singleton<Device>;

	//初期化
	#pragma region Init

private:
	Device() {
		for (u32 i = 0; i < cJoystickMaxNum; i++) {
			Reset(i);
		}
	}

	void Reset(u32 aCount) {
		for (u32 j = 0; j < CCode::cMax; j++) {
			mInputData[aCount].mData = XINPUT_STATE();
			mInputData[aCount].mBeforeData = mInputData[aCount].mData;
		}
		mInputData[aCount].mIsValid = false;
	}

	#pragma endregion


	//更新
	#pragma region Update

public:
	//入力の更新
	void Update();

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//値の取得
	f32 GetValue(u32 aCount, u32 aCode) const;

	//値の取得
	f32 GetAxis(u32 aCount, CAxis aAxis) const;

	//ボタンが押されているか
	BOOL GetButton(u32 aCount, u32 aCode) const;

	//ボタンが押された瞬間か
	BOOL GetButtonDown(u32 aCount, u32 aCode) const;

	//ボタンが離された瞬間か
	BOOL GetButtonUp(u32 aCount, u32 aCode) const;

	//コントローラが有効か
	BOOL IsValid(u32 aCount) const {
		CPOT_ASSERT(aCount < cJoystickMaxNum);
		return mInputData[aCount].mIsValid;
	}

	#pragma endregion


	//操作
	#pragma region Operator

public:
	//バイブレーションさせる


	#pragma endregion


	//フィールド
	#pragma region Field

private:
	static const u32 cJoystickMaxNum = 4;

	struct ControllerData {
		XINPUT_STATE mData;
		XINPUT_STATE mBeforeData;
		BOOL mIsValid;
	};

	ControllerData mInputData[4];

	#pragma endregion
};


}

}