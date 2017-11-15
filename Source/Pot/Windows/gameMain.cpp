//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Pot/Windows/gameMain.h"
#include "./Pot/Game/game.h"

#include "./Pot/Window/Windows/windowWindows.h"
#include "./Pot/Input/Windows/inputWindows.h"
#include "./Pot/Input/XInput/inputXInput.h"

namespace cpot {


GameBase* GameMain::mGame;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
}

void GameMain::GameLoop() {

	//ゲームの初期化
	mGame->Init();

	//ゲームループ
	while (true) {

		//入力の取得
		xInput::Input::S().Update();
		windows::Input::S().Update();

		//ゲームの更新
		mGame->Update();

		//ゲームの描画
		mGame->Render();

		/*
		if (mGameEnd) {
			break;
		}

		//FPS制御
		Fps::S().Wait();
		*/
	}
}

}