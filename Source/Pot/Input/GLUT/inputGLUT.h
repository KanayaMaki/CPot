//
//	content	:	GLUTでの入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"


#ifdef CPOT_ON_LINUX

#define CPOT_VALID_INPUT_GLUT

#endif


#pragma region InputCode

namespace cpot {

namespace glut {

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
	cMouseButtonLeft,
	cMouseButtonMiddle,
	cMouseButtonRight,
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
#ifdef CPOT_VALID_INPUT_GLUT

#include <GL/glut.h>
#include "./Pot/Config/config.h"

namespace cpot {

namespace glut {


class Input : public Singleton<Input> {
	friend Singleton<Input>;

	//初期化
	#pragma region Init

private:
	Input() {

	}

public:
	void Init() {
		glutIgnoreKeyRepeat(GL_TRUE);
		glutKeyboardFunc(InputKeyDownCallback);
		glutKeyboardUpFunc(InputKeyUpCallback);

		glutSpecialFunc(InputSpecialKeyDownCallback);
		glutSpecialUpFunc(InputSpecialKeyUpCallback);

		glutMouseFunc(InputMouseCallback);
	}

	#pragma endregion


	//終了
	#pragma region Final

public:
	~Input() {
	}

	#pragma endregion


	//更新
	#pragma region Update

public:
	//デバイスごとの入力状態を更新
	void Update() {
		mBeforeData = mData;
		mData = mTmpData;

		mTmpData.mMouseWheel = 0.0f;
	}

private:

	static void SetMousePositionCallback(int x, int y) {
		Input::S().mTmpData.mMouseX = (f32)x;
		Input::S().mTmpData.mMouseY = (f32)y;
	}

	static void InputMouseCallback(int button, int state, int x, int y) {
		s32 lButtonNum = -1;
		
		switch (button) {
			case GLUT_LEFT_BUTTON:
				lButtonNum = 0;
				break;
			case GLUT_MIDDLE_BUTTON:
				lButtonNum = 1;
				break;
			case GLUT_RIGHT_BUTTON:
				lButtonNum = 2;
				break;
		}

		switch (state) {
			case GLUT_DOWN:
				//ボタンが下がったので、入力されるようになった→フラグは上げる
				Input::S().mTmpData.mMouseButton.Stand(lButtonNum);
				break;
			case GLUT_UP:
				Input::S().mTmpData.mMouseButton.Down(lButtonNum);
				break;
		}

		SetMousePositionCallback(x, y);
	}
	static void InputKeyDownCallback(unsigned char key, int x, int y) {
		CInputCode lCode = ConvertGLUTKeyToInputCode(key);
		if (lCode != CInputCode::cNull) {
			Input::S().mTmpData.mKey.Stand(lCode);
		}
		SetMousePositionCallback(x, y);
	}
	static void InputKeyUpCallback(unsigned char key, int x, int y) {
		CInputCode lCode = ConvertGLUTKeyToInputCode(key);
		if (lCode != CInputCode::cNull) {
			Input::S().mTmpData.mKey.Down(lCode);
		}
		SetMousePositionCallback(x, y);
	}

	static CInputCode ConvertGLUTKeyToInputCode(unsigned char key) {
		switch (key) {
			case ' ':
				return CInputCode::cSpace;
			case 'W':
				return CInputCode::cW;
			case 's':
				return CInputCode::cS;
		}
		return CInputCode::cNull;
	}


	static void InputSpecialKeyDownCallback(int key, int x, int y) {
		CInputCode lCode = ConvertGLUTSpecialKeyToInputCode(key);
		if (lCode != CInputCode::cNull) {
			Input::S().mTmpData.mKey.Stand(lCode);
		}
		SetMousePositionCallback(x, y);
	}
	static void InputSpecialKeyUpCallback(int key, int x, int y) {
		CInputCode lCode = ConvertGLUTSpecialKeyToInputCode(key);
		if (lCode != CInputCode::cNull) {
			Input::S().mTmpData.mKey.Down(lCode);
		}
		SetMousePositionCallback(x, y);
	}
	static CInputCode ConvertGLUTSpecialKeyToInputCode(int key) {
		switch (key) {
			case GLUT_KEY_F1:
				return CInputCode::cF1;
			case GLUT_KEY_F2:
				return CInputCode::cF2;
			case GLUT_KEY_F3:
				return CInputCode::cF3;
			case GLUT_KEY_F4:
				return CInputCode::cF4;
			case GLUT_KEY_F5:
				return CInputCode::cF5;
			case GLUT_KEY_F6:
				return CInputCode::cF6;
			case GLUT_KEY_F7:
				return CInputCode::cF7;
			case GLUT_KEY_F8:
				return CInputCode::cF8;
			case GLUT_KEY_F9:
				return CInputCode::cF9;
			case GLUT_KEY_LEFT:
				return CInputCode::cLeft;
			case GLUT_KEY_UP:
				return CInputCode::cUp;
			case GLUT_KEY_RIGHT:
				return CInputCode::cRight;
			case GLUT_KEY_DOWN:
				return CInputCode::cDown;
		}
		return CInputCode::cNull;
	}



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

	InputData mTmpData;	//コールバックの値がここに入る

	#pragma endregion

};


}

}


#endif
