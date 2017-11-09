//
//	���e�@:�@VectorBase�N���X�̎���
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


//�ϒ��z��̃N���X
template <typename T>
class VectorBase {

	//�v�f�̒ǉ�
	#pragma region Add

public:
	CPOT_VI void PushBack(T aT) CPOT_ZR;

	#pragma endregion


	//�v�f�̏���
	#pragma region Remove
	
public:
	//�w�肳�ꂽ�l�Ɠ������v�f�̍폜�i�擪����P�����j
	CPOT_VI T Remove(T aT) CPOT_ZR;

	//�������v�f�̍폜�i�S�āj
	CPOT_VI void RemoveAll(T aT) CPOT_ZR;

	//�S�Ă̗v�f���폜
	CPOT_VI void Clear() CPOT_ZR;

	#pragma endregion


	//�v�f�̎擾
	#pragma region Getter

public:
	//�C���f�b�N�X�A�N�Z�X
	CPOT_VI T& operator[](u32 aIndex) CPOT_ZR;

	//�w�肳�ꂽ�l�̗v�f���������邩
	CPOT_VI u32 Count(T aT) CPOT_ZR;

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
	CPOT_VI u32 GetCapacity() CPOT_ZR;

	#pragma endregion

};


}


#ifdef CPOT_ON_WINDOWS
#include "./List/Standard/vector.h"
#endif