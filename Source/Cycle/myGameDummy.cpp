//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"
#include "./Pot/Config/config.h"
#include "./Pot/Input/input.h"

#include "./Pot/Render/OpenGL/renderOpenGL.h"

namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}

}

using namespace cpot;

namespace myspc {

Texture2D renderTexture;


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
	cpot::Config::S().SetTitle("MyGame!");
}

//ゲームの初期化
void MyGame::Init() {
	renderTexture.LoadPlatform();
}


//ゲームの更新
void MyGame::Update() {

	static Color c = Color::White();
	f32 x = Max(Input::GetValue(android::cTouchPosX), Input::GetValue(windows::cMouseCursorX));
	if (x) {
		c.r = x / Config::S().GetScreenSize().x;
	}
	f32 y = Max(Input::GetValue(android::cTouchPosY), Input::GetValue(windows::cMouseCursorY));
	if (y) {
		c.g = y / Config::S().GetScreenSize().y;
	}

	renderTexture.ClearColor(c);

	Render::S().Present();
}


}