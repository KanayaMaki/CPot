//
//	content	:	�G���g���[�|�C���g
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

	//�f�t�H���g�̐ݒ�
	Config::S().SetScreenSize(Vector2(960.0f, 540.0f));
	Config::S().SetTitle("CPotGame!");
	Config::S().SetFps(60.0f);


	//�Q�[���̐ݒ�ŏ㏑��
	GameMain::Setting();

	//�E�B���h�E�̍쐬
	windows::Window::S().Load(hInstance, Config::S().GetScreenSize(), Config::S().GetTitle());

	//�Q�[���X���b�h�̊J�n
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


	//�Q�[���X���b�h�̍�����҂�
	t.Join();

	return 0;
}