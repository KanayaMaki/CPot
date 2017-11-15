//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#include "./Pot/Game/component.h"
#include "./Pot/Game/unique.h"

#include "./Pot/Game/gameObject.h"

namespace cpot {

void Component::Init(GameObject* aGameObject) {

	//ユニークな番号の取得
	mUnique = UniqueGenerator<Component>::S().Generate();

	mGameObject = aGameObject;


	//フラグのリセット
	mFlags.AllBitDown();
	mFlags.Stand(cActive);

	if (mGameObject->GetActive()) {
		mFlags.Stand(cGameObjectActive);
	}


	//コンポーネントのリストに登録する
}

}