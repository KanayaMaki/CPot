#include "./Atom/atom.h"

#include "Window/Windows/window.h"

#include "./Output/output.h"
#include "./Output/Windows/outputDebugWindow.h"
#include "./Output/Windows/outputConsole.h"

#include <Windows.h>

#include "Rand/rand.h"

#include "Sleep/sleep.h"
#include "Time/time.h"


using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	Window* lWindow = Window::Create();
	lWindow->Load(hInstance, Vector2(960.0f, 540.0f), "Game");

	windows::OutputConsoleDevice::S().Init(lWindow->GetHwnd());

	windows::OutputConsole o;
	o.Load();
	Log::S().Set(&o);

	Time lTime;

	f64 lStart = lTime.GetDetail();
	for (u32 i = 0; i < 100000; i++) {
		lTime.GetDetail();
	}
	CPOT_LOG(lTime.GetDetail() - lStart);
 

	Window::MessageLoop();

	Window::Destroy(lWindow);

	return 0;
}