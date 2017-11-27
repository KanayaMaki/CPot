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

#include "./Pot/Audio/XAudio/Platform/deviceXAudioPlatform.h"
#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

#include "./Pot/Config/config.h"

#include "./Pot/Fps/fps.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Usefull/resourceUpdaterList.h"

namespace cpot {


GameBase* GameMain::mGame;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
	mGame->Setting();
}

void* GameMain::GameLoop(void* aDummy) {

	//プラットフォームの初期化
	#pragma region PlatformInit

	windows::Window& tW = windows::Window::S();

	xaudio::platform::Device::S().Init();
	directX11::platform::Device::S().Init(tW.GetHwnd(), tW.GetSize());

	//ウィンドウズの入力の初期化
	windows::Input::S().Init(tW.GetHInstance(), tW.GetHwnd());

	//ログの出力先の初期化
	#ifdef CPOT_VALID_LOG
	windows::OutConsoleDevice::S().Init(tW.GetHwnd());

	auto o = new windows::OutConsole;
	o->Load();
	Log::S().Set(o);
	#endif


	//Fpsの作成
	Fps::S().Init(new Time, new Sleep, Config::S().GetFps());
	#pragma endregion


	//ゲームの初期化
	mGame->Init();

	//ゲームループ
	while (true) {

		//入力の取得
		xInput::Input::S().Update();
		windows::Input::S().Update();

		//ローダのアップデート
		LoaderManager::S().Update();
		
		//リソースのアップデート
		ResourceUpdaterList::S().Update();

		//ゲームの更新
		mGame->Update();

		//ゲームの描画
		mGame->Render();

		//ゲームの終了
		if (Config::S().GetApplicationEnd() || Config::S().GetGameEnd()) {
			LoaderManager::S().Join();
			break;
		}
		

		//FPS制御
		Fps::S().Update();
	}

	return nullptr;
}


}