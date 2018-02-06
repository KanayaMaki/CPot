//
//	content	:	�Q�[���̃R���t�B�O��Windows��
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Config/config.h"

#include "./Pot/Thread/mutex.h"

#include "./Pot/Window/Linux/windowLinux.h"

namespace cpot {

namespace linux {


#pragma region Config

class Config : public ConfigBase, public Singleton<Config> {
	
	//��ʃT�C�Y
	#pragma region ScreenSize

public:
	void SetScreenSize(const Vector2& aScreenSize) CPOT_OR {
		MutexLocker m(mScreenSizeMutex);
		mScreenSize = aScreenSize;
	}
	Vector2 GetScreenSize() CPOT_OR {
		MutexLocker m(mScreenSizeMutex);
		return mScreenSize;
	}

	#pragma endregion


	//�A�v���P�[�V�������I�����邩�ǂ���
	#pragma region ApplicationEnd

public:
	void SetApplicationEnd() CPOT_OR {
		MutexLocker m(mApplicationEndMutex);
		mApplicationEnd = true;
	}
	BOOL GetApplicationEnd() CPOT_OR {
		MutexLocker m(mApplicationEndMutex);
		return mApplicationEnd;
	}

	#pragma endregion


	//�Q�[�����I�����邩�ǂ���
	#pragma region GameEnd

	void SetGameEnd() CPOT_OR {
		MutexLocker m(mGameEndMutex);
		mGameEnd = true;
	}
	BOOL GetGameEnd() CPOT_OR {
		MutexLocker m(mGameEndMutex);
		return mGameEnd;
	}

	#pragma endregion


	//�Q�[���^�C�g���̐ݒ�
	#pragma region Title

	void SetTitle(const CHAR* aTitle) CPOT_OR;
	const CHAR* GetTitle() CPOT_OR {
		MutexLocker m(mTitleMutex);
		return mTitle.Get();
	}

	#pragma endregion


	//�Q�[�����A�N�e�B�u���ǂ���
	#pragma region Active

	void SetIsActive(BOOL aIsActive) CPOT_OR {
		MutexLocker m(mActiveMutex);
		mActive = aIsActive;
	}
	BOOL GetIsActive() CPOT_OR {
		MutexLocker m(mActiveMutex);
		return mActive;
	}

	#pragma endregion


	//�Q�[����FPS
	#pragma region Fps

	void SetFps(f32 aFps) CPOT_OR {
		MutexLocker m(mFpsMutex);
		mFps = aFps;
	}
	f32 GetFps() CPOT_OR {
		MutexLocker m(mFpsMutex);
		return mFps;
	}

	#pragma endregion


private:
	Mutex mScreenSizeMutex;
	Mutex mTitleMutex;
	Mutex mApplicationEndMutex;
	Mutex mGameEndMutex;
	Mutex mActiveMutex;
	Mutex mFpsMutex;
};

#pragma endregion



}

using Config = linux::Config;

}
