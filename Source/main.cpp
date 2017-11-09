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

	windows::OutputConsoleDevice::S().Init(lWindow->GetHwnd());

	windows::OutputConsole o;
	o.Load();
	Log::S().Set(&o);

	standard::Rand r;
	r.SetSeed(1000);

	for (u32 i = 0; i < 1000; i++) {
		CPOT_LOG_NO_ENDL(r.Nextf(2.0f), ",");
	}
  

	Window::MessageLoop();

	Window::Destroy(lWindow);

	return 0;
}