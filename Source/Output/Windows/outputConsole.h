//
//	���e	:	Windows�ŁA�R���\�[�����쐬���ĕW���o�͂ŏo�͂���N���X
//


#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include "./Output/output.h"

#include <Windows.h>
#include <cstdio>


namespace cpot {

namespace windows {


//	�R���\�[�����쐬���āA�W���o�͂���N���X
class OutputConsoleDevice : public Singleton<OutputConsoleDevice> {
	friend class Singleton<OutputConsoleDevice>;

private:
	OutputConsoleDevice() {
		Reset();
	}

public:
	//�K�v�ȃf�[�^���Z�b�g����
	void Set(HWND aHwnd) {
		mHwnd = aHwnd;
	}
	void Final();	//�����I�ɏI���������s��

private:
	void Reset() {
		mHwnd = nullptr;
		mUserNum = 0;
		mFp = nullptr;
	}
	void Load();	//�m�ۂ���
	void Release();	//�������

public:
	void Alloc();	//���L�����擾����
	void Free();	//���L�����������

	BOOL IsLoaded() const {
		return mFp != nullptr;
	}

private:
	HWND mHwnd;
	s32 mUserNum;
	std::FILE* mFp;

public:
	void Output(const CHAR* aStr);
};



//	�R���\�[�����쐬���āA�W���o�͂���N���X
class OutputConsole : public OutputBase {
public:
	OutputConsole() { Reset(); }
	~OutputConsole() override;

private:
	void Reset() {
		mIsLoaded = false;
	}
public:
	void Load();
	void Release();

	BOOL IsLoaded() const {
		return mIsLoaded;
	}

private:
	void OutputStr(const CHAR* aStr) override;

	BOOL mIsLoaded;
};


}


}