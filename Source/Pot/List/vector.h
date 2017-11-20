//
//	content	:	Vector�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {


//�ϒ��z��̃N���X
template <typename T>
class VectorBase {

	//�v�f�̒ǉ�
	#pragma region Add

public:
	CPOT_VI void PushBack(const T& aT) CPOT_ZR;

	#pragma endregion


	//�v�f�̏���
	#pragma region Remove
	
public:
	//�w�肳�ꂽ�l�Ɠ������v�f�̍폜�i�擪����P�����j
	CPOT_VI T Remove(const T& aT) CPOT_ZR;

	//�������v�f�̍폜�i�S�āj
	CPOT_VI void RemoveAll(const T& aT) CPOT_ZR;

	//�S�Ă̗v�f���폜
	CPOT_VI void Clear() CPOT_ZR;

	//��Ԍ��̗v�f���폜���āA�Ԃ�
	CPOT_VI T PopBack() CPOT_ZR;

	#pragma endregion


	//�v�f�̎擾
	#pragma region Getter

public:
	//�C���f�b�N�X�A�N�Z�X
	CPOT_VI T& operator[](u32 aIndex) CPOT_ZR;

	//�w�肳�ꂽ�l�̗v�f���������邩
	CPOT_VI u32 Count(const T& aT) const CPOT_ZR;

	#pragma endregion


	//����
	#pragma region Operate

public:
	//�\�[�g
	CPOT_VI void Sort() CPOT_ZR;

	#pragma endregion


	//�z��̗v�f��
	#pragma region Size

public:
	//���݂̗v�f���̎擾
	CPOT_VI u32 GetSize() const CPOT_ZR;

	#pragma endregion


	//�m�ۂ��Ă���o�b�t�@�̗v�f��
	#pragma region Capacity

public:
	//�o�b�t�@�̗v�f���𑝂₷
	CPOT_VI void Reserve(u32 aSize) CPOT_ZR;

	//�o�b�t�@�̗v�f�����擾
	CPOT_VI u32 GetCapacity() const CPOT_ZR;

	#pragma endregion

};


}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/List/Standard/vectorStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/List/Android/vectorAndroid.h"
#endif