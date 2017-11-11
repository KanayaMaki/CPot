///////////////////////////////////////
//
//	ファイル名	:	inputKeyboard.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/03/18
//	更新日時	:	2017/03/18
//	内容		:	キーボードの入力クラス
//
///////////////////////////////////////

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include <dinput.h>

namespace cpot {

namespace windows {


class CKeyCode {
public:
	enum {
		c0 = DIK_0,
		c1 = DIK_1,
		c2 = DIK_2,
		c3 = DIK_3,
		c4 = DIK_4,
		c5 = DIK_5,
		c6 = DIK_6,
		c7 = DIK_7,
		c8 = DIK_8,
		c9 = DIK_9,
		cA = DIK_A,
		cB = DIK_B,
		cC = DIK_C,
		cD = DIK_D,
		cE = DIK_E,
		cF = DIK_F,
		cG = DIK_G,
		cH = DIK_H,
		cI = DIK_I,
		cJ = DIK_J,
		cK = DIK_K,
		cL = DIK_L,
		cM = DIK_M,
		cN = DIK_N,
		cO = DIK_O,
		cP = DIK_P,
		cQ = DIK_Q,
		cR = DIK_R,
		cS = DIK_S,
		cT = DIK_T,
		cU = DIK_U,
		cV = DIK_V,
		cW = DIK_W,
		cX = DIK_X,
		cY = DIK_Y,
		cZ = DIK_Z,
		cLeft = DIK_LEFT,
		cRight = DIK_RIGHT,
		cUp = DIK_UP,
		cDown = DIK_DOWN,
		cSpace = DIK_SPACE,
		cEnter = 0,
		cLeftCtrl = DIK_LCONTROL,
		cRightCtrl = DIK_RCONTROL,
		cLeftAlt = DIK_LALT,
		cRightAlt = DIK_RALT,
		cLeftShift = DIK_LSHIFT,
		cRightShift = DIK_RSHIFT,
		cEsc = DIK_ESCAPE,
		cF1 = DIK_F1,
		cF2 = DIK_F2,
		cF3 = DIK_F3,
		cF4 = DIK_F4,
		cF5 = DIK_F5,
		cF6 = DIK_F6,
		cF7 = DIK_F7,
		cF8 = DIK_F8,
		cF9 = DIK_F9,
		cF10 = DIK_F10,
		cF11 = DIK_F11,
		cF12 = DIK_F12,
		cMouseCursorX = 256,
		cMouseCursorY,
		cMouseWheelForward,
		cMouseWheelBack,
		cMouseButton1,
		cMouseButton2,
		cMouseButton3,
		cMouseButton4,
		cNull,	//何もないキー
		cMax,
	};
};

class InputDevice : public Singleton<InputDevice> {
	friend Singleton<InputDevice>;

	//初期化
	#pragma region Init

private:
	InputDevice();

public:
	void Init(HINSTANCE aHInstance, HWND aHwnd);

	#pragma endregion


	//終了
	#pragma region Final

public:
	~InputDevice();

	#pragma endregion


	//更新
	#pragma region Update

public:
	//デバイスごとの入力状態を更新
	void Update();

private:
	void UpdateKeyboard();
	void UpdateMouse();

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//入力された値
	f32 GetValue(u32 aKeyCode) const {
		CPOT_ASSERT(aKeyCode < CKeyCode::cMax);
		return mValue[aKeyCode];
	}

	//使用可能かどうか
	BOOL IsValid() const;

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	//入力された値を格納する
	f32 mValue[CKeyCode::cMax];


	//DirectInputを使うのに必要な変数
	#pragma region DirectInput

	IDirectInput8A* mInput;	//DirectInput全体のデバイス
	IDirectInputDevice8A* mMouseDevice;
	IDirectInputDevice8A* mKeyboardDevice;

	HWND mHwnd;
	HINSTANCE mHInstance;

	#pragma endregion

	#pragma endregion
};


}

}