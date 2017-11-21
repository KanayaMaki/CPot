#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


template <typename StateType>
class State {

	//初期化
	#pragma region Init

public:
	State() {
		Clear();
	}

	State(const State&) = delete;
	const State& operator =(const State&) = delete;

private:
	void Clear() {
		mState = nullptr;
	}

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	~State() {
		Release();
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		CPOT_SAFE_RELEASE(mState);
		Clear();
	}
	#pragma endregion


	//取得
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mState != nullptr;
	}

	StateType* GetState() const {
		return mState;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

protected:
	StateType* mState;

	#pragma endregion

};


}

}

}
