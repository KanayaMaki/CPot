//
//	content	:	�Q�[���̃R���t�B�O�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {


//�t�@�C���o�͂̃x�[�X�N���X
#pragma region ConfigBase

class ConfigBase {

	//���z�f�X�g���N�^
	#pragma region Destructor

public:
	CPOT_VI ~ConfigBase() {}

	#pragma endregion


	//��ʃT�C�Y
	#pragma region ScreenSize

public:
	CPOT_VI void SetScreenSize(const Vector2& aScreenSize) CPOT_ZR;
	CPOT_VI Vector2 GetScreenSize() CPOT_ZR;

	#pragma endregion


	//�A�v���P�[�V�������I�����邩�ǂ���
	#pragma region ApplicationEnd

public:
	CPOT_VI void SetApplicationEnd() CPOT_ZR;
	CPOT_VI BOOL GetApplicationEnd() CPOT_ZR;

	#pragma endregion


	//�Q�[�����I�����邩�ǂ���
	#pragma region GameEnd

	CPOT_VI void SetGameEnd() CPOT_ZR;
	CPOT_VI BOOL GetGameEnd() CPOT_ZR;

	#pragma endregion

	
	//�Q�[���^�C�g���̐ݒ�
	#pragma region Title

	CPOT_VI const CHAR* GetTitle() CPOT_ZR;
	CPOT_VI void SetTitle(const CHAR* aTitle) CPOT_ZR;

	#pragma endregion

	
	//�Q�[�����A�N�e�B�u���ǂ���
	#pragma region Active

	CPOT_VI void SetIsActive(BOOL aIsActive) CPOT_ZR;
	CPOT_VI BOOL GetIsActive() CPOT_ZR;

	#pragma endregion


	//�Q�[����FPS
	#pragma region Fps

	CPOT_VI void SetFps(f32 aFps) CPOT_ZR;
	CPOT_VI f32 GetFps() CPOT_ZR;

	#pragma endregion
	
protected:
	Vector2 mScreenSize;
	String<64> mTitle;
	BOOL mApplicationEnd;
	BOOL mGameEnd;
	BOOL mActive;
	f32 mFps;
};

#pragma endregion


}


#ifdef CPOT_ON_LINUX
#include "./Pot/Config/Linux/configLinux.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Config/Android/configAndroid.h"
#elif defined CPOT_ON_WINDOWS
#include "./Pot/Config/Windows/configWindows.h"
#endif