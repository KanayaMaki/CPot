//
//	content	:	�G���g���[�|�C���g
//	author	:	SaitoYoshiki
//

#include "./Pot/Linux/gameMain.h"
#include "./Pot/Game/game.h"

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"
#include "./Pot/Out/Standard/outStandard.h"

#include "./Pot/Config/config.h"

#include "./Pot/Time/time.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Usefull/resourceUpdaterList.h"

namespace cpot {


GameBase* GameMain::mGame;
Time gTime;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
	mGame->Setting();
}

void GameMain::GameInit() {

	//�v���b�g�t�H�[���̏�����
	#pragma region PlatformInit

	openGL::platform::Device::S().Init();


	//�E�B���h�E�Y�̓��͂̏�����
	
	//���O�̏o�͐�̏�����
	#ifdef CPOT_VALID_LOG
	auto o = new standard::OutStandard();
	Log::S().Set(o);
	#endif

	//�Q�[���̏�����
	mGame->Init();
}

void GameMain::GameUpdate() {

	//InputUpdate
	

	//���[�_�̃A�b�v�f�[�g
	LoaderManager::S().Update();
		
	//���\�[�X�̃A�b�v�f�[�g
	ResourceUpdaterList::S().Update();

	//�Q�[���̍X�V
	mGame->Update();

	//�Q�[���̏I��
	if (Config::S().GetApplicationEnd() || Config::S().GetGameEnd()) {
		LoaderManager::S().Join();
	}
}

void GameMain::GameRender() {
	//�Q�[���̕`��
	mGame->Render();
}
void GameMain::GameFinal() {
	openGL::platform::Device::S().Final();
}

}
