//
//	content	:	�G���g���[�|�C���g
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

	//�v���b�g�t�H�[���̏�����
	#pragma region PlatformInit

	windows::Window* tW = windows::WindowManager::S().Get();

	//�E�B���h�E�Y�̓��͂̏�����
	windows::Input::S().Init(tW->GetHInstance(), tW->GetHwnd());

	//���O�̏o�͐�̏�����
	#ifdef CPOT_VALID_LOG
	windows::OutConsoleDevice::S().Init(tW->GetHwnd());

	auto o = new windows::OutConsole;
	o->Load();
	Log::S().Set(o);
	#endif

	#pragma endregion


	//�Q�[���̏�����
	mGame->Init();

	//�Q�[�����[�v
	while (true) {

		//���͂̎擾
		xInput::Input::S().Update();
		windows::Input::S().Update();

		//�Q�[���̍X�V
		mGame->Update();

		//�Q�[���̕`��
		mGame->Render();

		/*
		if (mGameEnd) {
			break;
		}

		//FPS����
		Fps::S().Wait();
		*/
	}
}


}