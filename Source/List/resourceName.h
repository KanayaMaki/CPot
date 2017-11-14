//
//	content	:	���O�ɓo�^���Ă�������������A�L�[����擾����
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./List/hashTable.h"

namespace cpot {

class ResourceName {

public:
	//���\�[�X�̖��O�̌^�̒�`
	using Name = String<64>;

	//�o�^
	#pragma region Regist

public:
	void Regist(const HashTableKey& aKey, const CHAR* aName) {
		mNameList.Add(aKey, Name(aName));
	}
	void Regist(const CHAR* aKey, const CHAR* aName) {
		Regist(HashTableKey(aKey), aName);	//�Ϗ�
	}

	#pragma endregion


	//�擾
	#pragma region Get

public:
	const Name& Get(const HashTableKey& aKey) {
		if (mNameList.Exist(aKey)) {
			return mNameList.Find(aKey);
		}
		return mNameNull;
	}
	const Name& Get(const CHAR* aKey) {
		return Get(aKey);	//�Ϗ�
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	HashTable<Name> mNameList;	//�L�[�Ɩ��O�̃Z�b�g
	Name mNameNull;	//������Ȃ������Ƃ��ɕԂ����

	#pragma endregion
};

}