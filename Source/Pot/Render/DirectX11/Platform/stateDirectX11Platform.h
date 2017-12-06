#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


template <typename StateType>
class State {

	//������
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


	//�I������
	#pragma region Final

public:
	~State() {
		Release();
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//�ǂݍ��܂�Ă��Ȃ��Ȃ�A���������Ȃ�
		}
		CPOT_SAFE_RELEASE(mState);
		Clear();
	}
	#pragma endregion


	//�擾
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mState != nullptr;
	}

	StateType* GetState() const {
		return mState;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

protected:
	StateType* mState;

	#pragma endregion

};


}

}

}
