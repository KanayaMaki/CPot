//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Out/out.h"
#include "./Pot/Game/game.h"
#include "./Pot/Config/config.h"

namespace myspc {

//Gameの処理を行う基底クラス
class MyGame : public cpot::GameBase {

public:
	//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
	void Setting() override {
		cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
		cpot::Config::S().SetTitle("MyGame!");
	}

	//ゲームの初期化
	void Init() override {
		CPOT_LOG("Init!");
	}

	//ゲームの更新
	void Update() override;

	//ゲームの描画
	void Render() override {}
};


}
