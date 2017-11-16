//
//	content	:	HashTable�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using HashTableKey = HashString<32>;

//�n�b�V���e�[�u���̃N���X
template <typename T>
class HashTableBase {

	//�v�f�̒ǉ�
	#pragma region Add

public:
	// ! �����L�[�����łɂ���ꍇ�A�ǉ����Ȃ�
	CPOT_VI void Add(const HashTableKey& aKey, T aValue) CPOT_ZR;

	#pragma endregion


	//�v�f�̏���
	#pragma region Remove

public:
	//�w�肳�ꂽ�L�[�����v�f�̍폜
	CPOT_VI T Remove(const HashTableKey& aKey) CPOT_ZR;

	//�w�肳�ꂽ�l�Ɠ������v�f�̍폜
	CPOT_VI void Remove(T aT) CPOT_ZR;

	//�S�Ă̗v�f���폜
	CPOT_VI void Clear() CPOT_ZR;

	#pragma endregion


	//�v�f�̎擾
	#pragma region Getter

public:
	//�C���f�b�N�X�A�N�Z�X
	// ! �v�f���Ȃ���΁A�쐬����
	CPOT_VI T& operator[](const HashTableKey& aKey) CPOT_ZR;

	//���O�Ō���
	// ! �v�f���Ȃ����0��Ԃ�
	CPOT_VI T Find(const HashTableKey& aKey) const CPOT_ZR;

	//�w�肳�ꂽ�L�[�����v�f�����݂��邩
	CPOT_VI BOOL Exist(const HashTableKey& aKey) const CPOT_ZR;

	#pragma endregion


	//�v�f�̐ݒ�
	#pragma region Setter

public:
	CPOT_VI void Set(const HashTableKey& aKey, const T& aValue) CPOT_ZR;

	#pragma endregion


	//�z��̗v�f��
	#pragma region Size

public:
	//���݂̗v�f���̎擾
	CPOT_VI u32 GetSize() const CPOT_ZR;

	#pragma endregion
};


}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/List/Standard/hashTableStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/List/Android/hashTableAndroid.h"
#endif