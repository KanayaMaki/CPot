#include "./Atom/atom.h"

#include "Window/Windows/window.h"

#include "./Output/output.h"
#include "./Output/Windows/outputDebugWindow.h"
#include "./Output/Windows/outputConsole.h"

#include <Windows.h>

#include "Rand/rand.h"

#include "Sleep/sleep.h"


using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	Window* lWindow = Window::Create();
	lWindow->Load(hInstance, Vector2(960.0f, 540.0f), "Game");

	standard::Rand r;
	r.SetSeed(100);

	for (u32 i = 0; i < 100; i++) {
		r.Next();
	}
  
	cpot::Sleep sleep;
	sleep.SleepSecond(5.0f);
  
	windows::OutputConsoleDevice::S().Init(lWindow->GetHwnd());


	Window::MessageLoop();

	Window::Destroy(lWindow);

	return 0;
}