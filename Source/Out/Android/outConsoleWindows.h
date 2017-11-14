//
//	content	:	Windowsでコンソールを作成して標準出力する
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

//	コンソールを作成して、標準出力するクラス
class OutConsoleDevice : public Singleton<OutConsoleDevice> {
	friend class Singleton<OutConsoleDevice>;

	//初期化
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
	~OutConsoleDevice() {
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
class OutConsole : public OutBase {

	//初期化
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


	//終了
	#pragma region Final

public:
	~OutConsole() override {
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
			OutConsoleDevice::S().Alloc();
		}
	}
	//出力不可能にする
	void Release() {
		if (IsLoaded()) {
			//コンソール出力の許可を返す
			OutConsoleDevice::S().Free();
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
		OutConsoleDevice::S().Output(aStr);
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