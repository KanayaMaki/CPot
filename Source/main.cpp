#include "./Atom/atom.h"

#include "Window/Windows/window.h"

#include <Windows.h>


using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	Window* lWindow = Window::Create();
	lWindow->Load(hInstance, Vector2(960.0f, 540.0f), "Game");

	Window::MessageLoop();

	Window::Destroy(lWindow);

	return 0;
}