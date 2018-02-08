//
//	content	:	GLFWでの入力
//	author	:	SaitoYoshiki
//

#include "./Pot/Input/GLFW/inputGLFW.h"

#ifdef CPOT_VALID_INPUT_GLFW

namespace cpot {

namespace glfw {


//初期化
#pragma region Init


Input::Input() {

}

void Input::Init(GLFWwindow* aWindow) {

	mWindow = aWindow;

	//そのフレームの間に押されていたら、押されている判定にする
	glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
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
		mData.mKey.Flag(i, glfwGetKey(mWindow, TransList[i]));
	}
}

void Input::UpdateMouse() {
	//マウス座標の取得
	double mx, my;
	glfwGetCursorPos(mWindow, &mx, &my);

	mData.mMouseX = (f32)mx;
	mData.mMouseY = (f32)my;


	//マウス情報の取得
	mData.mMouseButton.Flag(0, glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_LEFT));
	

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