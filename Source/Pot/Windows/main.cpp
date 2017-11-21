//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Pot/Atom/atom.h"

#include "./Pot/Window/Windows/windowWindows.h"

#include "./Pot/Windows/gameMain.h"
#include "./Pot/Thread/thread.h"
#include "./Pot/Config/config.h"

#include <Windows.h>

#include "./test.h"

using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	//デフォルトの設定
	Config::S().SetScreenSize(Vector2(960.0f, 540.0f));
	Config::S().SetTitle("CPotGame!");
	Config::S().SetFps(60.0f);


	//ゲームの設定で上書き
	GameMain::Setting();

	//ウィンドウの作成
	windows::Window::S().Load(hInstance, Config::S().GetScreenSize(), Config::S().GetTitle());

	//ゲームスレッドの開始
	Thread t;
	t.Start(GameMain::GameLoop, nullptr);

	#pragma region Test

	TestDirectX11(windows::Window::S().GetHwnd());


	//TestOutput(windows::Window::S().GetHwnd());
	//TestAnimation();

	//TestAudio();

	//TestLoader();

	//TestThread();

	//TestFileOut();
	//TestFileIn();

	//TestInputWindows(lWindow->GetHInstance(), lWindow->GetHwnd());
	//TestInputDirectInput(lWindow->GetHInstance(), lWindow->GetHwnd());
	//TestInputXInput();

	//TestInputInputWindows(lWindow->GetHInstance(), lWindow->GetHwnd());
	//TestInputInputXInput();

	#pragma endregion

	windows::Window::MessageLoop();


	//ゲームスレッドの合流を待つ
	t.Join();

	return 0;
}