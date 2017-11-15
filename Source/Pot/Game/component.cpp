//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#include "./Pot/Game/component.h"
#include "./Pot/Game/unique.h"

#include "./Pot/Game/gameObject.h"

namespace cpot {

void Component::Init(GameObject* aGameObject) {

	//���j�[�N�Ȕԍ��̎擾
	mUnique = UniqueGenerator<Component>::S().Generate();

	mGameObject = aGameObject;


	//�t���O�̃��Z�b�g
	mFlags.AllBitDown();
	mFlags.Stand(cActive);

	if (mGameObject->GetActive()) {
		mFlags.Stand(cGameObjectActive);
	}


	//�R���|�[�l���g�̃��X�g�ɓo�^����
}

}