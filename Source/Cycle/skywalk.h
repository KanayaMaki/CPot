//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/componentSystem.h"
#include "./Pot/Input/input.h"
#include "./Pot/Time/time.h"

namespace cpot {

class SkyWalk : public Updater {
	CPOT_TYPE(SkyWalk, Updater)

	//�Ăяo�����֐�
	#pragma region Event
public:
	//�ŏ��̍X�V�̑O�ɌĂяo�����
	void OnStart() override {
		mMoveSpeed = 10.0f;
		mRotSpeed = 50.0f;
	}

	//�X�V����
	void OnUpdate() override {
		
		if (Input::GetButton(windows::cLeft)) {
			GetTransform().mRotation *= Quaternion::FromAxis(Vector3::Up(), -ToRad(mRotSpeed * DeltaTime()));
		}
		if (Input::GetButton(windows::cRight)) {
			GetTransform().mRotation *= Quaternion::FromAxis(Vector3::Up(), ToRad(mRotSpeed * DeltaTime()));
		}
		if (Input::GetButton(windows::cUp)) {
			GetTransform().mRotation *= Quaternion::FromAxis(GetTransform().mRotation.Right(), -ToRad(mRotSpeed * DeltaTime()));
		}
		if (Input::GetButton(windows::cDown)) {
			GetTransform().mRotation *= Quaternion::FromAxis(GetTransform().mRotation.Right(), ToRad(mRotSpeed * DeltaTime()));
		}


		if (Input::GetButton(windows::cLeftShift)) {
			mMoveSpeed = 20.0f;
		}
		else {
			mMoveSpeed = 10.0f;
		}

		if (Input::GetButton(windows::cA)) {
			GetTransform().mPosition += GetTransform().mRotation.Left() * mMoveSpeed * DeltaTime();
		}
		if (Input::GetButton(windows::cD)) {
			GetTransform().mPosition += GetTransform().mRotation.Right() * mMoveSpeed * DeltaTime();
		}
		if (Input::GetButton(windows::cW)) {
			GetTransform().mPosition += GetTransform().mRotation.Forward() * mMoveSpeed * DeltaTime();
		}
		if (Input::GetButton(windows::cS)) {
			GetTransform().mPosition += GetTransform().mRotation.Back() * mMoveSpeed * DeltaTime();
		}
		if (Input::GetButton(windows::cE)) {
			GetTransform().mPosition += GetTransform().mRotation.Up() * mMoveSpeed * DeltaTime();
		}
		if (Input::GetButton(windows::cQ)) {
			GetTransform().mPosition += GetTransform().mRotation.Down() * mMoveSpeed * DeltaTime();
		}
	}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	u32 GetPriority() override {
		return 0;
	}

	#pragma endregion


private:
	f32 mRotSpeed;
	f32 mMoveSpeed;
};

}