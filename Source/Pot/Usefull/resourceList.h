//
//	content	:	ResourceÇÃÉäÉXÉgÇçÏê¨Ç∑ÇÈ
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {


template <typename T>
class ResourceList : public Singleton<ResourceList<T>>{
	friend class Singleton<ResourceList<T>>;

public:
	std::shared_ptr<T> Find(const HashTableKey& aUnionName) {
		if (mResourceList.Exist(aUnionName)) {
			return mResourceList.Find(aUnionName);
		}
		else {
			std::shared_ptr<T> m(new T);
			m->Load(aUnionName);
			m->SetName(aUnionName);
			Regist(m, aUnionName);
			return m;
		}
	}

public:
	void Regist(const std::shared_ptr<T>& aResource, const HashTableKey& aUnionName) {
		mResourceList.Add(aUnionName, aResource);
	}
	std::shared_ptr<T> Remove(const HashTableKey& aUnionName) {
		mResourceList.Remove(aUnionName);
	}

private:
	HashTable<std::shared_ptr<T>> mResourceList;
};

}