#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

template <typename ViewType>
class View {

	//初期化
	#pragma region Init

public:
	View() {
		Clear();
	}
	View(const View&) = delete;
	const View& operator =(const View&) = delete;

protected:
	void Clear() {
		mView = nullptr;
	}

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	~View() {
		Release();
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		CPOT_SAFE_RELEASE(mView);
		Clear();
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mView != nullptr;
	}

	ViewType* Get() const {
		return mView;
	}

	//所有権を譲る
	ViewType* Free() {
		ViewType* lView = mView;
		Clear();
		return lView;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

protected:
	ViewType* mView;

	#pragma endregion

};


}

}

}