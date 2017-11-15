//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Out/out.h"
#include "./Pot/Game/game.h"

namespace myspc {

//Gameの処理を行う基底クラス
class MyGame : public cpot::GameBase {

public:
	//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
	void Setting() override {
		CPOT_LOG("Setting!");
	}

	//ゲームの初期化
	void Init() override {
		CPOT_LOG("Init!");
	}

	//ゲームの更新
	void Update() override {
		static cpot::u32 i = 0;
		i++;
		CPOT_LOG("Update! : ", i);
	}

	//ゲームの描画
	void Render() override {
	}
};


}
