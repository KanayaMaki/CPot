//
//	content	:	�Q�[��
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


//CPOT������������O�̒i�K�ŌĂ΂��B��ʃT�C�Y�Ȃǂ̐ݒ���s��
void MyGame::Setting() {
	cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
	cpot::Config::S().SetTitle("MyGame!");
}

//�Q�[���̏�����
void MyGame::Init() {
	renderTexture.LoadPlatform();
}


//�Q�[���̍X�V
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