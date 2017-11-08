//
//	内容	:	Windowsで、コンソールを作成して標準出力で出力するクラス
//


#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include "./Output/output.h"

#include <Windows.h>
#include <cstdio>


namespace cpot {

namespace windows {


//	コンソールを作成して、標準出力するクラス
class OutputConsoleDevice : public Singleton<OutputConsoleDevice> {
	friend class Singleton<OutputConsoleDevice>;

private:
	OutputConsoleDevice() {
		Reset();
	}

public:
	//必要なデータをセットする
	void Set(HWND aHwnd) {
		mHwnd = aHwnd;
	}
	void Final();	//強制的に終了処理を行う

private:
	void Reset() {
		mHwnd = nullptr;
		mUserNum = 0;
		mFp = nullptr;
	}
	void Load();	//確保する
	void Release();	//解放する

public:
	void Alloc();	//所有権を取得する
	void Free();	//所有権を解放する

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



//	コンソールを作成して、標準出力するクラス
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