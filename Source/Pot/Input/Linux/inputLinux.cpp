//
//	content	:	Windowsでの入力
//	author	:	SaitoYoshiki
//

#include "./Pot/Input/Windows/inputLinux.h"

#ifdef CPOT_VALID_INPUT_LINUX

namespace cpot {

namespace linux {


//初期化
#pragma region Init


Input::Input() {

}

void Input::Init() {

	//引数の状態が正常かチェックする
	glfwEnable(GLFW_STICKY_KEYS);
}


#pragma endregion



//終了処理
#pragma region Final

Input::~Input() {
	
}


#pragma endregion



//更新
#pragma region Update


void Input::Update() {

	mBeforeData = mData;

	UpdateKeyboard();
	UpdateMouse();
}

void Input::UpdateKeyboard() {
	//キーボード情報の取得
	int lTransListSize = sizeof(TransList) / sizeof(TransList[0]);
	for (s32 i = 0; i < lTransListSize; i++) {
		mData.mKey.Flag(i, glfwGetKey(lTransList[i]));
	}
}

void Input::UpdateMouse() {
	//マウス座標の取得
	int mx, my;
	glfwGetMousePos(&mx, &my);

	mData.mMouseX = (f32)mx;
	mData.mMouseY = (f32)my;


	//マウス情報の取得
	mData.mMouseButton.Flag(0, glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT));
	

	/*
	//ホイール情報の格納
	if (tMouseState.lZ > 0) {
		mData.mMouseWheel = 1.0f;
	}
	else if (tMouseState.lZ < 0) {
		mData.mMouseWheel = -1.0f;
	}
	else {
		mData.mMouseWheel = 0.0f;
	}

	//*/
}

#pragma endregion



BOOL Input::IsValid() const {
	return true;
}


}

}

#endif