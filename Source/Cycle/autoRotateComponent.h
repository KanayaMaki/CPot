//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/componentSystem.h"
#include "./Pot/Input/input.h"
#include "./Pot/Time/time.h"

namespace cpot {

class AutoRotateComponent : public Updater {
	CPOT_TYPE(AutoRotateComponent, Updater)

public:
	This() {
		mRotateSpeed = Quaternion::Unit();
	}

	//�Ăяo�����֐�
	#pragma region Event
public:
	//�X�V����
	void OnUpdate() override {
		GetTransform().mRotation *= SLerp(Quaternion::Unit(), mRotateSpeed, DeltaTime());
	}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	s32 GetPriority() override {
		return 0;
	}

	#pragma endregion

public:
	Quaternion GetRotateSpeed() const {
		return mRotateSpeed;
	}
	void SetRotateSpeed(const Quaternion& aRotateSpeed) {
		mRotateSpeed = aRotateSpeed;
	}


private:
	Quaternion mRotateSpeed;
};
CPOT_REGIST_TYPE(AutoRotateComponent);

}