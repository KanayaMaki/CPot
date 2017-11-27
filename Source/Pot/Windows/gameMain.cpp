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

#include "./Pot/Audio/XAudio/Platform/deviceXAudioPlatform.h"
#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

#include "./Pot/Config/config.h"

#include "./Pot/Fps/fps.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Usefull/resourceUpdaterList.h"

namespace cpot {


GameBase* GameMain::mGame;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
	mGame->Setting();
}

void* GameMain::GameLoop(void* aDummy) {

	//�v���b�g�t�H�[���̏�����
	#pragma region PlatformInit

	windows::Window& tW = windows::Window::S();

	xaudio::platform::Device::S().Init();
	directX11::platform::Device::S().Init(tW.GetHwnd(), tW.GetSize());

	//�E�B���h�E�Y�̓��͂̏�����
	windows::Input::S().Init(tW.GetHInstance(), tW.GetHwnd());

	//���O�̏o�͐�̏�����
	#ifdef CPOT_VALID_LOG
	windows::OutConsoleDevice::S().Init(tW.GetHwnd());

	auto o = new windows::OutConsole;
	o->Load();
	Log::S().Set(o);
	#endif


	//Fps�̍쐬
	Fps::S().Init(new Time, new Sleep, Config::S().GetFps());
	#pragma endregion


	//�Q�[���̏�����
	mGame->Init();

	//�Q�[�����[�v
	while (true) {

		//���͂̎擾
		xInput::Input::S().Update();
		windows::Input::S().Update();

		//���[�_�̃A�b�v�f�[�g
		LoaderManager::S().Update();
		
		//���\�[�X�̃A�b�v�f�[�g
		ResourceUpdaterList::S().Update();

		//�Q�[���̍X�V
		mGame->Update();

		//�Q�[���̕`��
		mGame->Render();

		//�Q�[���̏I��
		if (Config::S().GetApplicationEnd() || Config::S().GetGameEnd()) {
			LoaderManager::S().Join();
			break;
		}
		

		//FPS����
		Fps::S().Update();
	}

	return nullptr;
}


}