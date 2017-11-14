//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Atom/atom.h"

#include "Window/Windows/windowWindows.h"

#include <Windows.h>

#include "./test.h"

using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	windows::Window* lWindow = windows::Window::Create();
	lWindow->Load(hInstance, Vector2(960.0f, 540.0f), "Game");

	TestOutput(lWindow->GetHwnd());

	TestAudio();

	//TestLoader();

	//TestThread();

	//TestFileOut();
	//TestFileIn();

	//TestInputWindows(lWindow->GetHInstance(), lWindow->GetHwnd());
	//TestInputDirectInput(lWindow->GetHInstance(), lWindow->GetHwnd());
	//TestInputXInput();

	//TestInputInputWindows(lWindow->GetHInstance(), lWindow->GetHwnd());
	//TestInputInputXInput();

	windows::Window::MessageLoop();

	windows::Window::Destroy(lWindow);

	return 0;
}