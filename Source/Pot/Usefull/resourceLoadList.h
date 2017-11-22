//
//	content	:	���O�ɓo�^���Ă�������������A�L�[����擾����
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/hashTable.h"

namespace cpot {

template <typename T, typename DataType>
class ResourceLoadList  : public Singleton<ResourceLoadList<T, DataType>> {
	friend class Singleton<ResourceLoadList<T, DataType>>;

public:
	//�o�^
	#pragma region Regist

public:
	void Regist(const HashTableKey& aKey, const DataType& aData) {
		mDataList.Add(aKey, aData);
	}

	#pragma endregion


	//�擾
	#pragma region Get

public:
	const DataType& Get(const HashTableKey& aKey) {
		if (mDataList.Exist(aKey)) {
			return mDataList[aKey];
		}
		return mNullData;
	}
	const DataType& Get(const CHAR* aKey) {
		return Get(HashTableKey(aKey));	//�Ϗ�
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	HashTable<DataType> mDataList;	//�L�[�Ɩ��O�̃Z�b�g
	static DataType mNullData;

	#pragma endregion
};

template <typename T, typename DataType>
DataType ResourceLoadList<T, DataType>::mNullData;

}