//
//	content	:	�E�B���h�E�Y�̃E�B���h�E�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"

#include "./Pot/Config/config.h"
#include "./Pot/Application/Android/android_native_app_glue.h"

#include "./Pot/Out/out.h"


namespace cpot {

namespace android {

class Application : public Singleton<Application> {
	friend class Singleton<Application>;


	//�R���X�g���N�^�Ȃ�
	#pragma region Constructor

private:
	//���[�U�����new�ł����Adelete���ł��Ȃ�
	Application() {
		mState = nullptr;
	}
	~Application() {
		Release();
	}

	#pragma endregion


	//������
	#pragma region Load

public:
	void Load(android_app* aState) {
		mState = aState;
	}

	#pragma endregion


	//�I��
	#pragma region Release

private:
	void Release() {}

	#pragma endregion


	//�C�x���g���擾����
	#pragma region Event

public:
	void MessageLoop() {

	}


	#pragma region Handler
private:
	#pragma endregion



	#pragma endregion


	//�l���擾����
	#pragma region Getter

public:
	f32 GetWidth() const {
		return mSize.x;
	}
	f32 GetHeight() const {
		return mSize.y;
	}
	Vector2 GetSize() const {
		return mSize;
	}
	BOOL GetFocus() const {
		return mFocus;
	}
	android_app* GetState() const {
		return mState;
	}

	BOOL IsLoaded() const {
		return NotNull(mState);	//mHwnd��null�łȂ��Ȃ烍�[�h�ς�
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	android_app* mState;
	Vector2 mSize;
	BOOL mFocus;

	#pragma endregion
};


}

}
