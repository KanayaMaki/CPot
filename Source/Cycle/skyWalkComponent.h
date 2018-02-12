//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/componentSystem.h"
#include "./Pot/Input/input.h"
#include "./Pot/Time/time.h"

namespace cpot {


class SkyWalkComponent : public Updater {
	CPOT_TYPE(SkyWalkComponent, Updater)

public:
	SkyWalkComponent() {
		mFastMoveSpeed = 20.0f;
		mNormalMoveSpeed = 10.0f;

		mFastRotateSpeed = 90.0f;
		mNormalRotateSpeed = 45.0f;

		mMoveSpeed = mFastMoveSpeed;
		mRotateSpeed = mNormalRotateSpeed;

		mCanMove = true;
		mCanRotate = true;
	}

	//�Ăяo�����֐�
	#pragma region Event
public:
	//�X�V����
	void OnUpdate() override {
		
		//��]���\�Ȃ�
		if (mCanRotate) {

			//��]���x�̕ύX
			if (Input::GetButton(windows::cRightShift)) {
				mRotateSpeed = mFastRotateSpeed;
			}
			else {
				mRotateSpeed = mNormalRotateSpeed;
			}

			//��]
			if (Input::GetButton(cLeft)) {
				GetTransform().mRotation *= Quaternion::FromAxis(Vector3::Up(), -ToRad(mRotateSpeed * DeltaTime()));
			}
			if (Input::GetButton(cRight)) {
				GetTransform().mRotation *= Quaternion::FromAxis(Vector3::Up(), ToRad(mRotateSpeed * DeltaTime()));
			}
			if (Input::GetButton(cUp)) {
				GetTransform().mRotation *= Quaternion::FromAxis(GetTransform().mRotation.Right(), -ToRad(mRotateSpeed * DeltaTime()));
			}
			if (Input::GetButton(cDown)) {
				GetTransform().mRotation *= Quaternion::FromAxis(GetTransform().mRotation.Right(), ToRad(mRotateSpeed * DeltaTime()));
			}
		}

		//�ړ����\�Ȃ�
		if (mCanMove) {

			//�ړ����x�̕ύX
			if (Input::GetButton(cSpace)) {
				mMoveSpeed = mFastMoveSpeed;
			}
			else {
				mMoveSpeed = mNormalMoveSpeed;
			}

			//�ړ�
			if (Input::GetButton(cA)) {
				GetTransform().mPosition += GetTransform().mRotation.Left() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(cD)) {
				GetTransform().mPosition += GetTransform().mRotation.Right() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(cW)) {
				GetTransform().mPosition += GetTransform().mRotation.Forward() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(cS)) {
				GetTransform().mPosition += GetTransform().mRotation.Back() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(cE)) {
				GetTransform().mPosition += GetTransform().mRotation.Up() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(cQ)) {
				GetTransform().mPosition += GetTransform().mRotation.Down() * mMoveSpeed * DeltaTime();
			}
		}
	}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	s32 GetPriority() override {
		return 0;
	}

	#pragma endregion


	//�v���p�e�B
	#pragma region Property

public:
	BOOL GetCanMove() const {
		return mCanMove;
	}
	void SetCanMove(BOOL aCanMove) {
		mCanMove = aCanMove;
	}

	BOOL GetCanRotate() const {
		return mCanRotate;
	}
	void SetCanRotate(BOOL aCanRotate) {
		mCanRotate = aCanRotate;
	}

	f32 GetFastRotateSpeed() const {
		return mFastRotateSpeed;
	}
	void SetFastRotateSpeed(f32 aFastRotateSpeed) {
		mFastRotateSpeed = aFastRotateSpeed;
	}
	f32 GetNormalRotateSpeed() const {
		return mNormalRotateSpeed;
	}
	void SetNormalRotateSpeed(f32 aNormalRotateSpeed) {
		mNormalRotateSpeed = aNormalRotateSpeed;
	}

	f32 GetFastMoveSpeed() const {
		return mFastMoveSpeed;
	}
	void SetFastMoveSpeed(f32 aFastMoveSpeed) {
		mFastMoveSpeed = aFastMoveSpeed;
	}
	f32 GetNormalMoveSpeed() const {
		return mNormalMoveSpeed;
	}
	void SetNormalMoveSpeed(f32 aNormalMoveSpeed) {
		mNormalMoveSpeed = aNormalMoveSpeed;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field


private:
	f32 mRotateSpeed;
	f32 mMoveSpeed;

	f32 mFastRotateSpeed;
	f32 mNormalRotateSpeed;
	f32 mFastMoveSpeed;
	f32 mNormalMoveSpeed;

	BOOL mCanMove;
	BOOL mCanRotate;

	#pragma endregion

};
CPOT_REGIST_TYPE(SkyWalkComponent);







//����ŃR���|�[�l���g���`
class PresenComponent : public Updater {
	CPOT_TYPE(PresenComponent, Updater)

public:
	void OnUpdate() override {}
};
CPOT_REGIST_TYPE(PresenComponent);


void PresenFunc() {

	GameObject* lObject = new GameObject;
	lObject->SetName("Saito");	//�Q�[���I�u�W�F�N�g�ɖ��O��t����

	lObject->AddComponent<PresenComponent>();	//�R���|�[�l���g��ǉ�
	lObject->GetComponent<PresenComponent>();	//�R���|�[�l���g���擾
	lObject->AddComponent("PresenComponent");	//�����񂩂�ł��R���|�[�l���g��ǉ��ł���
}


	





}