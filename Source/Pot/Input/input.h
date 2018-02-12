//
//	content	:	入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Config/config.h"

#include "./Pot/Input/Windows/inputWindows.h"
#include "./Pot/Input/XInput/inputXInput.h"
#include "./Pot/Input/Android/inputAndroid.h"
#include "./Pot/Input/GLUT/inputGLUT.h"


namespace cpot {

enum CKeyCode {
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
	cLeft,
	cUp,
	cRight,
	cDown,
	cSpace,
};

inline windows::CInputCode ConvertKeyCodeToWindowsInputCode(CKeyCode aCode) {
	if (CKeyCode::c0 <= aCode && aCode <= CKeyCode::c9) {
		return (windows::CInputCode)(aCode - CKeyCode::c0 + windows::CInputCode::c0);
	}
	if (CKeyCode::cA <= aCode && aCode <= CKeyCode::cZ) {
		return (windows::CInputCode)(aCode - CKeyCode::cA + windows::CInputCode::cA);
	}
	if (CKeyCode::cF1 <= aCode && aCode <= CKeyCode::cF12) {
		return (windows::CInputCode)(aCode - CKeyCode::cF1 + windows::CInputCode::cF1);
	}
	switch (aCode) {
		case CKeyCode::cLeft:
			return windows::CInputCode::cLeft;
		case CKeyCode::cUp:
			return windows::CInputCode::cUp;
		case CKeyCode::cRight:
			return windows::CInputCode::cRight;
		case CKeyCode::cDown:
			return windows::CInputCode::cDown;
		case CKeyCode::cSpace:
			return windows::CInputCode::cSpace;
	}


	return windows::cNull;
}
inline glut::CInputCode ConvertKeyCodeToGLUTInputCode(CKeyCode aCode) {
	if (CKeyCode::c0 <= aCode && aCode <= CKeyCode::c9) {
		return (glut::CInputCode)(aCode - CKeyCode::c0 + glut::CInputCode::c0);
	}
	if (CKeyCode::cA <= aCode && aCode <= CKeyCode::cZ) {
		return (glut::CInputCode)(aCode - CKeyCode::cA + glut::CInputCode::cA);
	}
	if (CKeyCode::cF1 <= aCode && aCode <= CKeyCode::cF12) {
		return (glut::CInputCode)(aCode - CKeyCode::cF1 + glut::CInputCode::cF1);
	}
	switch (aCode) {
		case CKeyCode::cLeft:
			return glut::CInputCode::cLeft;
		case CKeyCode::cUp:
			return glut::CInputCode::cUp;
		case CKeyCode::cRight:
			return glut::CInputCode::cRight;
		case CKeyCode::cDown:
			return glut::CInputCode::cDown;
		case CKeyCode::cSpace:
			return glut::CInputCode::cSpace;
	}

	return glut::cNull;
}


class Input {

	//Windowsの入力を担当する
	#pragma region Windows
	
	//Windowsの入力が有効なら
	#ifdef CPOT_VALID_INPUT_WINDOWS

public:
	static f32 GetValue(windows::CInputCode aCode) {
		return windows::Input::S().GetValue(aCode);
	}
	static BOOL GetButton(windows::CInputCode aCode) {
		return windows::Input::S().GetButton(aCode);
	}
	static BOOL GetButtonDown(windows::CInputCode aCode) {
		return windows::Input::S().GetButtonDown(aCode);
	}
	static BOOL GetButtonUp(windows::CInputCode aCode) {
		return windows::Input::S().GetButtonUp(aCode);
	}
	static f32 GetAxis(windows::CInputAxisCode aCode) {
		return windows::Input::S().GetAxis(aCode);
	}

	//Windowsの入力が無効なら、入力無し
	#else

public:
	static f32 GetValue(windows::CInputCode aCode) {
		return 0.0f;
}
	static BOOL GetButton(windows::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(windows::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(windows::CInputCode aCode) {
		return false;
	}
	static f32 GetAxis(windows::CInputAxisCode aCode) {
		return 0.0f;
	}

	#endif

	#pragma endregion


	//XInputの入力を担当する
	#pragma region XInput

public:
	//１番目のプレイヤーのコントローラを使用
	static f32 GetValue(xInput::CInputCode aCode) {
		return GetValue(0, aCode);
	}
	static BOOL GetButton(xInput::CInputCode aCode) {
		return GetButton(0, aCode);
	}
	static BOOL GetButtonDown(xInput::CInputCode aCode) {
		return GetButtonDown(0, aCode);
	}
	static BOOL GetButtonUp(xInput::CInputCode aCode) {
		return GetButtonUp(0, aCode);
	}
	static f32 GetAxis(xInput::CInputAxisCode aCode) {
		return GetAxis(0, aCode);
	}

	//XInputが有効な時
	#ifdef CPOT_VALID_XINPUT

public:
	static f32 GetValue(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetValue(aControllerNum, aCode);
	}
	static BOOL GetButton(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetButton(aControllerNum, aCode);
	}
	static BOOL GetButtonDown(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetButtonDown(aControllerNum, aCode);
	}
	static BOOL GetButtonUp(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetButtonUp(aControllerNum, aCode);
	}
	static f32 GetAxis(u32 aControllerNum, xInput::CInputAxisCode aCode) {
		return xInput::Input::S().GetAxis(aControllerNum, aCode);
	}

	//XInputが無効な時
	#else

public:
	//入力無しの状態の値を返す
	static f32 GetValue(u32 aControllerNum, xInput::CInputCode aCode) {
		return 0.0f;
	}
	static BOOL GetButton(u32 aControllerNum, xInput::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(u32 aControllerNum, xInput::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(u32 aControllerNum, xInput::CInputCode aCode) {
		return false;
	}
	static f32 GetAxis(u32 aControllerNum, xInput::CInputAxisCode aCode) {
		return 0.0f;
	}

	#endif

	#pragma endregion


	//GLUTの入力を担当する
	#pragma region GLUT

	//Windowsの入力が有効なら
	#ifdef CPOT_VALID_INPUT_GLUT

public:
	static f32 GetValue(glut::CInputCode aCode) {
		return glut::Input::S().GetValue(aCode);
	}
	static BOOL GetButton(glut::CInputCode aCode) {
		return glut::Input::S().GetButton(aCode);
	}
	static BOOL GetButtonDown(glut::CInputCode aCode) {
		return glut::Input::S().GetButtonDown(aCode);
	}
	static BOOL GetButtonUp(glut::CInputCode aCode) {
		return glut::Input::S().GetButtonUp(aCode);
	}
	static f32 GetAxis(glut::CInputAxisCode aCode) {
		return glut::Input::S().GetAxis(aCode);
	}

	//GLUTの入力が無効なら、入力無し
	#else

public:
	static f32 GetValue(glut::CInputCode aCode) {
		return 0.0f;
	}
	static BOOL GetButton(glut::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(glut::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(glut::CInputCode aCode) {
		return false;
	}
	static f32 GetAxis(glut::CInputAxisCode aCode) {
		return 0.0f;
	}

	#endif

	#pragma endregion


	//キーボードの入力を担当する
	#pragma region Keyboard

public:
	static f32 GetValue(CKeyCode aCode) {
		#ifdef CPOT_VALID_INPUT_WINDOWS
		return GetValue(ConvertKeyCodeToWindowsInputCode(aCode));
		#elif defined CPOT_VALID_INPUT_GLUT
		return GetValue(ConvertKeyCodeToGLUTInputCode(aCode));
		#endif
		return 0.0f;
	}
	static BOOL GetButton(CKeyCode aCode) {
		#ifdef CPOT_VALID_INPUT_WINDOWS
		return GetButton(ConvertKeyCodeToWindowsInputCode(aCode));
		#elif defined CPOT_VALID_INPUT_GLUT
		return GetButton(ConvertKeyCodeToGLUTInputCode(aCode));
		#endif
		return false;
	}
	static BOOL GetButtonDown(CKeyCode aCode) {
		#ifdef CPOT_VALID_INPUT_WINDOWS
		return GetButtonDown(ConvertKeyCodeToWindowsInputCode(aCode));
		#elif defined CPOT_VALID_INPUT_GLUT
		return GetButtonDown(ConvertKeyCodeToGLUTInputCode(aCode));
		#endif
		return false;
	}
	static BOOL GetButtonUp(CKeyCode aCode) {
		#ifdef CPOT_VALID_INPUT_WINDOWS
		return GetButtonUp(ConvertKeyCodeToWindowsInputCode(aCode));
		#elif defined CPOT_VALID_INPUT_GLUT
		return GetButtonUp(ConvertKeyCodeToGLUTInputCode(aCode));
		#endif
		return false;
	}

	#pragma endregion


	//Androidの入力を担当する
	#pragma region Android

	//Windowsの入力が有効なら
	#ifdef CPOT_VALID_INPUT_ANDROID

public:
	static f32 GetValue(android::CInputCode aCode) {
		return android::Input::S().GetValue(aCode);
	}
	static BOOL GetButton(android::CInputCode aCode) {
		return android::Input::S().GetButton(aCode);
	}
	static BOOL GetButtonDown(android::CInputCode aCode) {
		return android::Input::S().GetButtonDown(aCode);
	}
	static BOOL GetButtonUp(android::CInputCode aCode) {
		return android::Input::S().GetButtonUp(aCode);
	}

	//Windowsの入力が無効なら、入力無し
	#else

public:
	static f32 GetValue(android::CInputCode aCode) {
		return 0.0f;
	}
	static BOOL GetButton(android::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(android::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(android::CInputCode aCode) {
		return false;
	}
	#endif

	#pragma endregion
};

}
