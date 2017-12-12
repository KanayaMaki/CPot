//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#include "./Pot/Game/component.h"
#include "./Pot/Game/unique.h"

#include "./Pot/Game/gameObject.h"

namespace cpot {

Component::Component() {
	ComponentManager::S().Regist(this);
}

Component::~Component() {
	ComponentManager::S().Remove(this);
}



void Component::InitComponent(GameObject* aGameObject) {

	//���j�[�N�Ȕԍ��̎擾
	mUnique = UniqueGenerator<Component>::S().Generate();

	//�Q�[���I�u�W�F�N�g�̐ݒ�
	mGameObject = aGameObject;

	//�t���O�̃��Z�b�g
	mFlags.AllBitDown();
	mFlags.Stand(cActive);

	if (mGameObject->GetActive()) {
		mFlags.Stand(cGameObjectActive);
	}
}

}