#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

template <typename ViewType>
class View {

	//������
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


	//�I������
	#pragma region Final

public:
	~View() {
		Release();
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//�ǂݍ��܂�Ă��Ȃ��Ȃ�A���������Ȃ�
		}
		CPOT_SAFE_RELEASE(mView);
		Clear();
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mView != nullptr;
	}

	ViewType* Get() const {
		return mView;
	}

	//���L��������
	ViewType* Free() {
		ViewType* lView = mView;
		Clear();
		return lView;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

protected:
	ViewType* mView;

	#pragma endregion

};


}

}

}