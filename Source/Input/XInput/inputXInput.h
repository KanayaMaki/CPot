///////////////////////////////////////
//
//	ファイル名	:	inputJoystick.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/03/18
//	更新日時	:	2017/03/18
//	内容		:	キーボードの入力クラス
//
///////////////////////////////////////

#pragma once

#include "./Atom/atom.h"
#include "./Inter/singleton.h"

#include <dinput.h>

namespace cyc {

namespace pot {

namespace xinput {


//仮想のJoystickコントローラーのボタンを定義
class JoystickCode {
public:
	enum {
		cLStickLeft,
		cLStickRight,
		cLStickUp,
		cLStickDown,
		cRStickLeft,
		cRStickRight,
		cRStickUp,
		cRStickDown,
		cLButtonLeft,
		cLButtonRight,
		cLButtonUp,
		cLButtonDown,
		cRButtonLeft,
		cRButtonRight,
		cRButtonUp,
		cRButtonDown,
		cLButton1,
		cLButton2,
		cLButton3,
		cRButton1,
		cRButton2,
		cRButton3,
		cNull,
		cMax,
	};
};


//実際のデバイスのボタンを定義
class JoystickButton {
public:
	enum {
		cStickAxis1Plus,
		cStickAxis1Minus,
		cStickAxis2Plus,
		cStickAxis2Minus,
		cStickAxis3Plus,
		cStickAxis3Minus,
		cStickAxis4Plus,
		cStickAxis4Minus,
		cStickAxis5Plus,
		cStickAxis5Minus,
		cStickAxis6Plus,
		cStickAxis6Minus,
		cPOV1XPlus,
		cPOV1XMinus,
		cPOV1YPlus,
		cPOV1YMinus,
		cPOV2XPlus,
		cPOV2XMinus,
		cPOV2YPlus,
		cPOV2YMinus,
		cPOV3XPlus,
		cPOV3XMinus,
		cPOV3YPlus,
		cPOV3YMinus,
		cPOV4XPlus,
		cPOV4XMinus,
		cPOV4YPlus,
		cPOV4YMinus,
		cButton1,
		cButton2,
		cButton3,
		cButton4,
		cButton5,
		cButton6,
		cButton7,
		cButton8,
		cButton9,
		cButton10,
		cButton11,
		cButton12,
		cButton13,
		cButton14,
		cButton15,
		cButton16,
		cButton17,
		cButton18,
		cButton19,
		cButton20,
		cNull,
		cMax,
	};
};


//仮想のJoystickコントローラーのコードをデバイスごとのボタンに変換する
struct Translater {
public:
	Translater() {
		for (u32 i = 0; i < JoystickCode::cMax; i++) {
			//初期値は全て空入力
			mTranse[i] = JoystickButton::cNull;
		}
	}

public:
	//変換する対応付けを設定する
	void SetButton(u32 aCode, u32 aButton) {
		//範囲チェック
		CYC_POT_ASSERT(aCode < JoystickCode::cMax);
		CYC_POT_ASSERT(aButton < JoystickButton::cMax);
		mTranse[aCode] = aButton;
	}

	//変換後のボタンを取得する
	u32 GetButton(u32 aCode) const {
		CYC_POT_ASSERT(aCode < JoystickCode::cMax);
		return mTranse[aCode];
	}

	u32 mTranse[JoystickCode::cMax];


public:
	static Translater PS4() {
		Translater res;
		res.SetButton(JoystickCode::cLStickLeft, JoystickButton::cStickAxis1Minus);
		return res;
	}
};


class JoystickInstance {
public:
	BOOL mAleradyAcquire;
	IDirectInputDevice8A* mJoystick;
	GUID mInstanceGUID;

public:
	JoystickInstance() {
		mJoystick == nullptr;
		mAleradyAcquire = false;
	}

	BOOL Valid() {
		return mJoystick != nullptr;
	}

	void Release();


public:
	f32 GetValue(u32 aCode) const {
		CYC_POT_ASSERT(aCode < JoystickCode::cMax);
		return mValue[mTrans.GetButton(aCode)];
	}

	f32 mValue[JoystickButton::cMax];
	Translater mTrans;
};


class Joystick : public Singleton<Joystick> {
	friend Singleton<Joystick>;

private:
	IDirectInput8A* mInput;
	static constexpr s32 cJoystickMaxNum = 4;
	JoystickInstance mJoystick[cJoystickMaxNum];
	HWND mHwnd;
	HINSTANCE mHInstance;

private:
	Joystick() {
		mInput = nullptr;
		for (s32 i = 0; i < cJoystickMaxNum; i++) {
			mJoystick[i].mJoystick = nullptr;
		}
	}
	~Joystick();

public:
	void Init(HINSTANCE aHInstance, HWND aHwnd);
	void Reset();


private:
	//デバイスの接続に使用する
	friend ::BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCEA*, VOID*);
	BOOL IsAlreadyUse(GUID aInstanceGUID);
	JoystickInstance* GetEmptyJoystickInstance();


public:
	//入力の更新
	void Update();

	//値の取得
	f32 Value(u32 aCount, u32 aCode) const {
		CYC_POT_ASSERT(aCode < JoystickCode::cMax);
		CYC_POT_ASSERT(aCount < cJoystickMaxNum);
		return mJoystick[aCount].GetValue(aCode);
	}

	BOOL Valid(u32 aCount) {
		CYC_POT_ASSERT(aCount < cJoystickMaxNum);
		return mJoystick[aCount].Valid();
	}
};



}

}

}