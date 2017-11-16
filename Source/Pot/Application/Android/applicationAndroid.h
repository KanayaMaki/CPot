//
//	content	:	ウィンドウズのウィンドウの実装
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


	//コンストラクタなど
	#pragma region Constructor

private:
	//ユーザからはnewできず、deleteもできない
	Application() {
		mState = nullptr;
	}
	~Application() {
		Release();
	}

	#pragma endregion


	//初期化
	#pragma region Load

public:
	void Load(android_app* aState) {
		mState = aState;
	}

	#pragma endregion


	//終了
	#pragma region Release

private:
	void Release() {}

	#pragma endregion


	//イベントを取得する
	#pragma region Event

public:
	void MessageLoop() {

	}


	#pragma region Handler
private:
	#pragma endregion



	#pragma endregion


	//値を取得する
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
		return NotNull(mState);	//mHwndがnullでないならロード済み
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	android_app* mState;
	Vector2 mSize;
	BOOL mFocus;

	#pragma endregion
};


}

}
