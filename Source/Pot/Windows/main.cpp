//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Pot/Atom/atom.h"

#include "./Pot/Window/Windows/windowWindows.h"

#include "./Pot/Windows/gameMain.h"
#include "./Pot/Thread/thread.h"

#include <Windows.h>

#include "./test.h"

using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	GameMain::Setting();

	windows::Window::S().Load(hInstance, Vector2(960.0f, 540.0f), "Game");

	//ゲームスレッドの開始
	Thread t;
	t.Start(GameMain::GameLoop, nullptr);

	#pragma region Test

	//TestOutput(lWindow->GetHwnd());

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

	return 0;
}