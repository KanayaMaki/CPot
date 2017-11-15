//
//	content	:	�G���g���[�|�C���g
//	author	:	SaitoYoshiki
//

#include "./Pot/Windows/gameMain.h"
#include "./Pot/Game/game.h"

#include "./Pot/Window/Windows/windowWindows.h"
#include "./Pot/Input/Windows/inputWindows.h"
#include "./Pot/Input/XInput/inputXInput.h"

namespace cpot {


GameBase* GameMain::mGame;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
}

void GameMain::GameLoop() {

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