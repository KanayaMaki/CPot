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

	//初期化
	#pragma region Init

private:
	OutputConsoleDevice() {
		Reset();
	}

private:
	void Reset() {
		mHwnd = nullptr;
		mUserNum = 0;
		mFp = nullptr;
	}


public:
	//初期化。データをセットしておく
	void Init(HWND aHwnd) {
		mHwnd = aHwnd;
	}


private:
	//コンソールを確保する
	void Load();

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	~OutputConsoleDevice() {
		Final();
	}

public:
	//強制的に終了処理を行う
	void Final();

private:
	//コンソールを解放する
	void Release();

	#pragma endregion


	//操作
	#pragma region Operate

public:
	void Alloc();	//所有権を取得する
	void Free();	//所有権を解放する

public:
	//文字列を出力する
	void Output(const CHAR* aStr);

	#pragma endregion


	//取得
	#pragma region Getter

	BOOL IsLoaded() const {
		return mFp != nullptr;
	}

	#pragma endregion



	//フィールド
	#pragma region Field

private:
	HWND mHwnd;
	u32 mUserNum;	//コンソールが参照されている数
	std::FILE* mFp;	//コンソールウィンドウのファイルポインタ

	#pragma endregion

};



//	コンソールを作成して、標準出力するクラス
class OutputConsole : public OutputBase {

	//初期化
	#pragma region Init

public:
	OutputConsole() {
		Reset();
	}

private:
	void Reset() {
		mIsLoaded = false;
	}

	#pragma endregion


	//終了
	#pragma region Final

public:
	~OutputConsole() override {
		Release();
	}

	#pragma endregion


	//操作
	#pragma region Operate

public:
	//出力可能にする
	void Load() {
		if (!IsLoaded()) {
			//コンソール出力の許可をもらう
			OutputConsoleDevice::S().Alloc();
		}
	}
	//出力不可能にする
	void Release() {
		if (IsLoaded()) {
			//コンソール出力の許可を返す
			OutputConsoleDevice::S().Free();
		}
		Reset();
	}

	#pragma endregion


	//取得
	#pragma region Getter

	BOOL IsLoaded() const {
		return mIsLoaded;
	}

	#pragma endregion


	//その他
	#pragma region Other

private:
	//OutBaseの関数のオーバーライド。文字列を出力する
	void OutputStr(const CHAR* aStr) override {
		OutputConsoleDevice::S().Output(aStr);
	}

	#pragma endregion



	//フィールド
	#pragma region Field

private:
	BOOL mIsLoaded;	//ロード済みかどうか

	#pragma endregion

};


}


}