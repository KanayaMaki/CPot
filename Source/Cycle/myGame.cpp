//
//	content	:	�Q�[��
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"

#include "./Pot/Input/input.h"
#include "./Pot/Audio/audio.h"

namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}

}

using namespace cpot;

namespace myspc {

//�Q�[���̍X�V
void MyGame::Update() {
	static cpot::u32 i = 0;
	i++;
	CPOT_LOG("Update! : ", i);

	//�Q�[���I��
	if (Input::GetButtonUp(windows::c0)) {
		Config::S().SetGameEnd();
	}

	//�T�E���h
	if (Input::GetButtonUp(windows::c1)) {
		auto a = new AudioClip;
		a->Load("./test.wav");

		auto c = new AudioVoice;
		c->Load(*a);

		c->Play();
	}
}

}