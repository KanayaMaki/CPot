//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Pot/Windows/gameMain.h"
#include "./Pot/Game/game.h"

#include "./Pot/Window/Windows/windowWindows.h"
#include "./Pot/Input/Windows/inputWindows.h"
#include "./Pot/Input/XInput/inputXInput.h"
#include "./Pot/Out/Windows/outConsoleWindows.h"

namespace cpot {


GameBase* GameMain::mGame;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
	mGame->Setting();
}

void GameMain::GameLoop(void* aDummy) {

	//プラットフォームの初期化
	#pragma region PlatformInit

	windows::Window* tW = windows::WindowManager::S().Get();

	//ウィンドウズの入力の初期化
	windows::Input::S().Init(tW->GetHInstance(), tW->GetHwnd());

	//ログの出力先の初期化
	#ifdef CPOT_VALID_LOG
	windows::OutConsoleDevice::S().Init(tW->GetHwnd());

	auto o = new windows::OutConsole;
	o->Load();
	Log::S().Set(o);
	#endif

	#pragma endregion


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