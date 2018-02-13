//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/componentSystem.h"
#include "./Pot/Time/time.h"
#include "./Pot/Animation/animation.h"
#include "./Pot/Game/staticModelRenderer.h"

namespace cpot {

class MorphComponent : public Updater {
	CPOT_TYPE(MorphComponent, Updater)

public:
	MorphComponent() {}

	//�Ăяo�����֐�
	#pragma region Event
public:
	//�X�V����
	void OnUpdate() override {
		mMorphTime.ForwardTime(DeltaTime());

		for (u32 i = 0; i < mNow.GetSize(); i++) {
			f32 t = mMorphTime.Get();
			mNow[i].position = Lerp(mBefore[i].position, mAfter[i].position, t);
			mNow[i].normal = Lerp(mBefore[i].normal, mAfter[i].normal, t).NormalSafe();
		}

		GetComponent<StaticModelRenderer>()->model->mesh.vertex->Write(&mNow[0]);
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
	VectorSimple<StaticMeshVertex> mBefore;
	VectorSimple<StaticMeshVertex> mAfter;
	VectorSimple<StaticMeshVertex> mNow;
	Animation<f32> mMorphTime;
	
};
CPOT_REGIST_TYPE(MorphComponent);

}