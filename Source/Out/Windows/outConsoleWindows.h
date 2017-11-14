//
//	content	:	Windows�ŃR���\�[�����쐬���ĕW���o�͂���
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include "./Out/out.h"

#include <Windows.h>
#include <cstdio>


namespace cpot {

namespace windows {

//	�R���\�[�����쐬���āA�W���o�͂���N���X
class OutConsoleDevice : public Singleton<OutConsoleDevice> {
	friend class Singleton<OutConsoleDevice>;

	//������
	#pragma region Init

private:
	OutConsoleDevice() {
		Reset();
	}

private:
	void Reset() {
		mHwnd = nullptr;
		mUserNum = 0;
		mFp = nullptr;
	}


public:
	//�������B�f�[�^���Z�b�g���Ă���
	void Init(HWND aHwnd) {
		mHwnd = aHwnd;
	}


private:
	//�R���\�[�����m�ۂ���
	void Load();

	#pragma endregion


	//�I������
	#pragma region Final

public:
	~OutConsoleDevice() {
		Final();
	}

public:
	//�����I�ɏI���������s��
	void Final();

private:
	//�R���\�[�����������
	void Release();

	#pragma endregion


	//����
	#pragma region Operate

public:
	void Alloc();	//���L�����擾����
	void Free();	//���L�����������

public:
	//��������o�͂���
	void Output(const CHAR* aStr);

	#pragma endregion


	//�擾
	#pragma region Getter

	BOOL IsLoaded() const {
		return mFp != nullptr;
	}

	#pragma endregion



	//�t�B�[���h
	#pragma region Field

private:
	HWND mHwnd;
	u32 mUserNum;	//�R���\�[�����Q�Ƃ���Ă��鐔
	std::FILE* mFp;	//�R���\�[���E�B���h�E�̃t�@�C���|�C���^

	#pragma endregion

};



//	�R���\�[�����쐬���āA�W���o�͂���N���X
class OutConsole : public OutBase {

	//������
	#pragma region Init

public:
	OutConsole() {
		Reset();
	}

private:
	void Reset() {
		mIsLoaded = false;
	}

	#pragma endregion


	//�I��
	#pragma region Final

public:
	~OutConsole() override {
		Release();
	}

	#pragma endregion


	//����
	#pragma region Operate

public:
	//�o�͉\�ɂ���
	void Load() {
		if (!IsLoaded()) {
			//�R���\�[���o�͂̋������炤
			OutConsoleDevice::S().Alloc();
		}
	}
	//�o�͕s�\�ɂ���
	void Release() {
		if (IsLoaded()) {
			//�R���\�[���o�͂̋���Ԃ�
			OutConsoleDevice::S().Free();
		}
		Reset();
	}

	#pragma endregion


	//�擾
	#pragma region Getter

	BOOL IsLoaded() const {
		return mIsLoaded;
	}

	#pragma endregion


	//���̑�
	#pragma region Other

private:
	//OutBase�̊֐��̃I�[�o�[���C�h�B��������o�͂���
	void OutputStr(const CHAR* aStr) override {
		OutConsoleDevice::S().Output(aStr);
	}

	#pragma endregion



	//�t�B�[���h
	#pragma region Field

private:
	BOOL mIsLoaded;	//���[�h�ς݂��ǂ���

	#pragma endregion

};


}


}