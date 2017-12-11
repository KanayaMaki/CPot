//
//	content	:	Standard�ł�HashTable�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/hashTable.h"

#include <map>

namespace cpot {

namespace android {


//�n�b�V���e�[�u���̃N���X
template <typename T>
class HashTable : public HashTableBase<T> {

	//�v�f�̒ǉ�
	#pragma region Add

public:
	// ! �����L�[�����łɂ���ꍇ�A�ǉ����Ȃ�
	void Add(const HashTableKey& aKey, T aValue) CPOT_OR {
		mList.insert(std::make_pair(aKey, aValue));
	}

	#pragma endregion


	//�v�f�̏���
	#pragma region Remove

public:
	//�w�肳�ꂽ�L�[�����v�f�̍폜
	T Remove(const HashTableKey& aKey) CPOT_OR {
		auto it = mList.find(aKey);

		//�v�f�������
		if (it != mList.end()) {
			T tRes = (*it).second;
			mList.erase(it);
			return tRes;
		}
		T lRes;
		return lRes;
	}

	//�w�肳�ꂽ�l�Ɠ������v�f�̍폜
	void Remove(T aT) CPOT_OR {
		//
	}

	//�S�Ă̗v�f���폜
	void Clear() CPOT_OR {
		mList.clear();
	}

	#pragma endregion


	//�v�f�̎擾
	#pragma region Getter

public:
	//�C���f�b�N�X�A�N�Z�X
	// ! �v�f���Ȃ���΁A�쐬����
	T& operator[](const HashTableKey& aKey) CPOT_OR {
		return mList[aKey];
	}

	//���O�Ō���
	// ! �v�f���Ȃ����0��Ԃ�
	T Find(const HashTableKey& aKey) const CPOT_OR {
		auto it = mList.find(aKey);
		if (it != mList.end()) {
			return (*it).second;
		}
		T lRes;
		return lRes;
	}

	//�w�肳�ꂽ�L�[�����v�f�����݂��邩
	BOOL Exist(const HashTableKey& aKey) const CPOT_OR {
		return mList.find(aKey) != mList.end();
	}

	#pragma endregion


	//�v�f�̐ݒ�
	#pragma region Setter

public:
	void Set(const HashTableKey& aKey, const T& aValue) CPOT_OR {
		CPOT_ASSERT(Exist(aKey));	//���łɗv�f�����݂��Ă��Ȃ���΂����Ȃ�
		mList[aKey] = aValue;
	}

	#pragma endregion

	//�z��̗v�f��
	#pragma region Size

public:
	//���݂̗v�f���̎擾
	u32 GetSize() const CPOT_OR {
		return mList.size();
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	std::map<HashTableKey, T> mList;

	#pragma endregion

};

}

template <typename T>
using HashTable = android::HashTable<T>;

}