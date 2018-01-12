//
//	content	:	Resource�̃��X�g���쐬����
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/List/vector.h"
#include "./Pot/Usefull/resourceUpdaterList.h"

namespace cpot {

template<typename T>
class ResourceListUpdater : public ResourceUpdater {
public:
	void Update() override;
};

//NamedResource���p�����Ă���K�v������
template <typename T>
class ResourceList : public Singleton<ResourceList<T>> {
	friend class Singleton<ResourceList<T>>;
	friend class ResourceListUpdater<T>;

private:
	ResourceList() {
		ResourceUpdaterList::S().Regist(&mResourceListUpdater);
	}
	
	static ResourceListUpdater<T> mResourceListUpdater;

public:
	BOOL Exist(const HashTableKey& aUnionName) {
		for (u32 i = 0; i < mResourceList.GetSize(); i++) {
			auto lT = mResourceList[i];
			if (lT->GetName() == aUnionName) {
				return true;
			}
		}
		return false;
	}

	std::shared_ptr<T> Find(const HashTableKey& aUnionName) {
		for (u32 i = 0; i < mResourceList.GetSize(); i++) {
			auto lT = mResourceList[i];
			if (lT->GetName() == aUnionName) {
				return lT;
			}
		}
		std::shared_ptr<T> lT(new T);
		lT->Load(aUnionName);
		//�ǂݍ��݂Ɏ��s���Ă�����
		if (lT->IsLoad() == false) {
			//null��Ԃ��BlT�͉�������
			return std::shared_ptr<T>(nullptr);
		}
		lT->SetName(aUnionName);
		mResourceList.PushBack(lT);
		return lT;
	}

public:
	void Regist(std::shared_ptr<T> aResource) {
		mResourceList.PushBack(aResource);
	}
	void Remove(const std::shared_ptr<T>& aResource) {
		mResourceList.Remove(aResource);
	}
	void Remove(const HashTableKey& aUnionName) {
		for (u32 i = 0; i < mResourceList.GetSize(); i++) {
			auto& lT = mResourceList[i];
			if (lT->GetName() == aUnionName) {
				mResourceList.Remove(lT);
			}
		}
	}

private:
	Vector<std::shared_ptr<T>> mResourceList;
};


template<typename T>
void ResourceListUpdater<T>::Update() {
	for (u32 i = 0; i < ResourceList<T>::S().mResourceList.GetSize(); i++) {
		auto& lT = ResourceList<T>::S().mResourceList[i];
		if (lT.use_count() == 1) {
			ResourceList<T>::S().mResourceList.Remove(lT);
		}
	}
}

template<typename T>
ResourceListUpdater<T> ResourceList<T>::mResourceListUpdater;

}
