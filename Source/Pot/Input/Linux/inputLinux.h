﻿//
//	content	:	Windowsでの入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"


#ifdef CPOT_ON_LINUX

#define CPOT_VALID_INPUT_LINUX

#endif


#pragma region InputCode

namespace cpot {

namespace linux {

enum CInputCode {
	c0,
	c1,
	c2,
	c3,
	c4,
	c5,
	c6,
	c7,
	c8,
	c9,
	cA,
	cB,
	cC,
	cD,
	cE,
	cF,
	cG,
	cH,
	cI,
	cJ,
	cK,
	cL,
	cM,
	cN,
	cO,
	cP,
	cQ,
	cR,
	cS,
	cT,
	cU,
	cV,
	cW,
	cX,
	cY,
	cZ,
	cLeft,
	cRight,
	cUp,
	cDown,
	cSpace,
	cEnter,
	cLeftCtrl,
	cRightCtrl,
	cLeftAlt,
	cRightAlt,
	cLeftShift,
	cRightShift,
	cEsc,
	cF1,
	cF2,
	cF3,
	cF4,
	cF5,
	cF6,
	cF7,
	cF8,
	cF9,
	cF10,
	cF11,
	cF12,
	cMouseCursorX,
	cMouseCursorY,
	cMouseCursorXDelta,
	cMouseCursorYDelta,
	cMouseWheel,
	cMouseButton1,
	cMouseButton2,
	cMouseButton3,
	cMouseButton4,
	cNull,	//何もないキー
	cMax,
};


enum CInputAxisCode {
	cAD,
	cWS,
	cCrossX,
	cCrossY
};


}

}

#pragma endregion


//Windowsでの入力が有効なら
#ifdef CPOT_VALID_INPUT_LINUX

#include <GL/glfw.h>
#include "./Pot/Config/config.h"

namespace cpot {

namespace linux {


//InputCodeからGLFWのコードに変換する
const GLenum TransList[]{
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',
	GLFW_KEY_LEFT,
	GLFW_KEY_RIGHT,
	GLFW_KEY_UP,
	GLFW_KEY_DOWN,
	GLFW_KEY_SPACE,
	GLFW_KEY_ENTER,
	GLFW_KEY_LCONTROL,
	GLFW_KEY_RCONTROL,
	GLFW_KEY_LALT,
	GLFW_KEY_RALT,
	GLFW_KEY_LSHIFT,
	GLFW_KEY_RSHIFT,
	GLFW_KEY_ESC,
	GLFW_KEY_F1,
	GLFW_KEY_F2,
	GLFW_KEY_F3,
	GLFW_KEY_F4,
	GLFW_KEY_F5,
	GLFW_KEY_F6,
	GLFW_KEY_F7,
	GLFW_KEY_F8,
	GLFW_KEY_F9,
	GLFW_KEY_F10,
	GLFW_KEY_F11,
	GLFW_KEY_F12,
};


class Input : public Singleton<Input> {
	friend Singleton<Input>;

	//初期化
	#pragma region Init

private:
	Input();

public:
	void Init();

	#pragma endregion


	//終了
	#pragma region Final

public:
	~Input();

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
	f32 GetValue(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mData.mKey.IsStand(TransList[aCode]) ? 1.0f : 0.0f;
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return GetMouseLocY();
		}
		else if (aCode == CInputCode::cMouseCursorXDelta) {
			return GetMouseMove().x;
		}
		else if (aCode == CInputCode::cMouseCursorYDelta) {
			return GetMouseMove().y;
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mData.mMouseButton.IsStand(aCode - cMouseButton1) ? 1.0f : 0.0f;
		}
		else {
			return 0.0f;
		}
	}
	f32 GetValueBefore(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mBeforeData.mKey.IsStand(TransList[aCode]) ? 1.0f : 0.0f;
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetBeforeMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return  GetBeforeMouseLocY();
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mBeforeData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mBeforeData.mMouseButton.IsStand(aCode - cMouseButton1) ? 1.0f : 0.0f;
		}
		else {
			return 0.0f;
		}
	}

	BOOL GetButton(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mData.mKey.IsStand(TransList[aCode]);
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return GetMouseLocY();
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mData.mMouseButton.IsStand(aCode - cMouseButton1);
		}
		else {
			return false;
		}
	}
	BOOL GetButtonBefore(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mBeforeData.mKey.IsStand(TransList[aCode]);
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetBeforeMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return GetBeforeMouseLocY();
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mBeforeData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mBeforeData.mMouseButton.IsStand(aCode - cMouseButton1);
		}
		else {
			return false;
		}
	}
	BOOL GetButtonDown(CInputCode aCode) const {
		if (!GetButtonBefore(aCode)) {
			if (GetButton(aCode)) {
				return true;
			}
		}
		return false;
	}
	BOOL GetButtonUp(CInputCode aCode) const {
		if (GetButtonBefore(aCode)) {
			if (!GetButton(aCode)) {
				return true;
			}
		}
		return false;
	}

	f32 GetAxis(CInputCode aMinus, CInputCode aPlus) const {
		return Strong(-GetValue(aMinus), GetValue(aPlus));
	}
	f32 GetAxis(CInputAxisCode aAxis) const {
		switch (aAxis) {
			case CInputAxisCode::cAD:
				return GetAxis(cA, cD);
			case CInputAxisCode::cWS:
				return GetAxis(cS, cW);
			case CInputAxisCode::cCrossX:
				return GetAxis(cLeft, cRight);
			case CInputAxisCode::cCrossY:
				return GetAxis(cDown, cUp);
		}
	}
	

	f32 GetMouseLocX() const {
		return mData.mMouseX;
	}
	f32 GetMouseLocY() const {
		return Config::S().GetScreenSize().y - mData.mMouseY;
	}
	Vector2 GetMouseLoc() const {
		return Vector2(GetMouseLocX(), GetMouseLocY());
	}

	f32 GetBeforeMouseLocX() const {
		return mBeforeData.mMouseX;
	}
	f32 GetBeforeMouseLocY() const {
		return Config::S().GetScreenSize().y - mBeforeData.mMouseY;
	}
	Vector2 GetBeforeMouseLoc() const {
		return Vector2(GetBeforeMouseLocX(), GetBeforeMouseLocY());
	}

	Vector2 GetMouseMove() const {
		return GetMouseLoc() - GetBeforeMouseLoc();
	}
	f32 GetMouseWheel() const {
		return mData.mMouseWheel;
	}

	//使用可能かどうか
	BOOL IsValid() const;

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	struct InputData {
		BitFlagLarge<256> mKey;
		f32 mMouseX, mMouseY;
		f32 mMouseWheel;
		BitFlag mMouseButton;
	};

	//入力された値を格納する
	InputData mData;
	InputData mBeforeData;

	#pragma endregion

};


}

}


#endif
