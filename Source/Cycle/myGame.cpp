//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"

#include "./Pot/Input/input.h"

namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}

}


namespace myspc {

//ゲームの更新
void MyGame::Update() {
	static cpot::u32 i = 0;
	i++;
	CPOT_LOG("Update! : ", i);

	if (cpot::Input::GetButtonUp(cpot::windows::c0)) {
		cpot::Config::S().SetGameEnd();
	}
}

}