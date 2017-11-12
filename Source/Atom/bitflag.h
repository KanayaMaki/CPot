//	�t�@�C����	:	Atom/string.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/06
//	�X�V����	:	2017/11/06
//	���e		:	������n�̃N���X��֐����`

#pragma once


#include "defines.h"
#include "typedef.h"

#include "function.h"

#include "string.h"


namespace cpot {

//32bit�̃r�b�g�t���O
class BitFlag {

	//�R���X�g���N�^
	#pragma region Constructor

public:
	BitFlag() {
		DownAll();
	}

	#pragma endregion


	//�t���O���擾����
	#pragma region Getter

public:
	//�C���f�b�N�X�Ŏ擾
	BOOL operator[](u32 aIndex) {
		return IsStand(aIndex);
	}

	//�w�肳�ꂽ�r�b�g�������Ă��邩
	BOOL IsStand(u32 aIndex) const {
		return mVal & BitStand(aIndex);
	}
	BOOL IsDown(u32 aIndex) const {
		return !IsStand(aIndex);
	}

	//�S�Ẵr�b�g�������Ă��邩
	BOOL IsStandAll() const {
		return mVal == AllBitStand();
	}
	BOOL IsDownAll() const {
		return mVal == AllBitDown();
	}

	//�����ꂩ�̃r�b�g�������Ă��邩
	BOOL IsStandAny() const {
		return !IsDownAll();
	}
	BOOL IsDownAny() const {
		return !IsStandAll();
	}

	#pragma endregion


	//�t���O��ݒ肷��
	#pragma region Setter

public:

	//�r�b�g�𗧂Ă�
	#pragma region Stand

	BitFlag& Stand(u32 aIndex) {
		mVal |= BitStand(aIndex);
		return *this;
	}
	BitFlag& StandAll() {
		mVal = AllBitStand();
		return *this;
	}
	BitFlag& StandRange(u32 aStartIndex, u32 aEndIndex) {
		mVal |= BitStandRange(aStartIndex, aEndIndex);
		return *this;
	}

	#pragma endregion

	//�r�b�g�����낷
	#pragma region Down

	BitFlag& Down(u32 aIndex) {
		mVal &= ~(BitStand(aIndex));
		return *this;
	}
	BitFlag& DownAll() {
		mVal = AllBitDown();
		return *this;
	}
	BitFlag& DownRange(u32 aStartIndex, u32 aEndIndex) {
		mVal &= ~(BitStandRange(aStartIndex, aEndIndex));
		return *this;
	}

	#pragma endregion

	//�r�b�g�𔽓]������
	#pragma region Flip

	BitFlag& Flip(u32 aIndex) {
		mVal ^= BitStand(aIndex);
		return *this;
	}
	BitFlag& FlipAll() {
		mVal ^= AllBitStand();
		return *this;
	}
	BitFlag& FlipRange(u32 aStartIndex, u32 aEndIndex) {
		mVal ^= BitStandRange(aStartIndex, aEndIndex);
		return *this;
	}

	#pragma endregion

	//�^�U�ɂ���āA���Ă邩���낷�����߂�
	#pragma region Flag

	BitFlag& Flag(u32 aIndex, BOOL aIsStand) {
		if (aIsStand) {
			Stand(aIndex);
		}
		else {
			Down(aIndex);
		}
		return *this;
	}
	BitFlag& FlagRange(u32 aStartIndex, u32 aEndIndex, BOOL aIsStand) {
		if (aIsStand) {
			StandRange(aStartIndex, aEndIndex);
		}
		else {
			DownRange(aStartIndex, aEndIndex);
		}
		return *this;
	}

	#pragma endregion

	#pragma endregion


	//�����o
	#pragma region Member

private:
	u32 mVal;	//�r�b�g�̏�Ԃ��i�[����

	#pragma endregion


	//�r�b�g�̕��т𕶎���ɂ���
	#pragma region ToString

public:
	using BitString = String<33>;

	BitString ToString() const {
		BitString lRes;
		for (u32 i = 0; i < 32; i++) {
			lRes += IsStand(31 - i) ? "1" : "0";
		}
		return lRes;
	}

	#pragma endregion


	//�ÓI�Ȋ֐�
	#pragma region static

public:

	//�w�肳�ꂽ�C���f�b�N�X�̃r�b�g�����������Ă����Ԃ�Ԃ�
	static u32 BitStand(u32 aIndex) {
		//aIndex��0�`31
		CPOT_ASSERT(aIndex < sizeof(u32) * 8);
		return 1U << aIndex;
	}

	//�w�肳�ꂽ�C���f�b�N�X�͈̔͂̃r�b�g�����������Ă����Ԃ�Ԃ�
	static u32 BitStandRange(u32 aStartIndex, u32 aEndIndex) {
		//aIndex��0�`31
		u32 lRes = 0UL;
		for (u32 i = aStartIndex; i <= aEndIndex; i++) {
			lRes += BitStand(i);
		}
		return lRes;
	}

	//�S�Ẵr�b�g�������Ă����Ԃ�Ԃ�
	static u32 AllBitStand() {
		return 0xffffffffU;
	}

	//�S�Ẵr�b�g������Ă����Ԃ�Ԃ�
	static u32 AllBitDown() {
		return 0U;
	}

	#pragma endregion

};


//���傫���r�b�g�t���O�̃N���X
template <u32 cBitNum>
class BitFlagLarge {

	//�R���X�g���N�^
	#pragma region Constructor

public:
	BitFlagLarge() {
		DownAll();
	}

	#pragma endregion


	//�t���O���擾����
	#pragma region Getter

public:
	//�C���f�b�N�X�Ŏ擾
	BOOL operator[](u32 aIndex) {
		return IsStand(aIndex);
	}

	//�w�肳�ꂽ�r�b�g�������Ă��邩
	BOOL IsStand(u32 aIndex) const {
		return GetBitFlag(aIndex).IsStand(GetIndex(aIndex));
	}
	BOOL IsDown(u32 aIndex) const {
		return GetBitFlag(aIndex).IsDown(GetIndex(aIndex));
	}

	//�S�Ẵr�b�g�������Ă��邩
	BOOL IsStandAll() const {
		for (u32 i = 0; i < GetBitFlagNum(); i++) {
			if (!GetBitFlag(i).IsStandAll()) {
				return false;
			}
		}
		return true;
	}
	BOOL IsDownAll() const {
		for (u32 i = 0; i < GetBitFlagNum(); i++) {
			if (!GetBitFlag(i).IsDownAll()) {
				return false;
			}
		}
		return true;
	}

	//�����ꂩ�̃r�b�g�������Ă��邩
	BOOL IsStandAny() const {
		return !IsDownAll();
	}
	BOOL IsDownAny() const {
		return !IsStandAll();
	}


	//�C���f�b�N�X�̃r�b�g���܂܂��BitFlag��Ԃ�
	const BitFlag& GetBitFlag(u32 aIndex) const {
		return mBitFlag[aIndex / 32];
	}
	BitFlag& GetBitFlag(u32 aIndex) {
		return mBitFlag[aIndex / 32];
	}
	//BitFlag���̃C���f�b�N�X��Ԃ�
	u32 GetIndex(u32 aIndex) const {
		return aIndex % 32;
	}
	//�g�p����BitFlag�̐���Ԃ�
	u32 GetBitFlagNum() const {
		return (cBitNum + 31) / 32;
	}
	#pragma endregion


	//�t���O��ݒ肷��
	#pragma region Setter

public:

	//�r�b�g�𗧂Ă�
	#pragma region Stand

	BitFlagLarge& Stand(u32 aIndex) {
		GetBitFlag(aIndex).Stand(GetIndex(aIndex));
		return *this;
	}
	BitFlagLarge& StandAll() {
		for (u32 i = 0; i < GetBitFlagNum(); i++) {
			GetBitFlag(i).StandAll();
		}
		return *this;
	}
	BitFlagLarge& StandRange(u32 aStartIndex, u32 aEndIndex) {
		//TODO ����
		return *this;
	}

	#pragma endregion

	//�r�b�g�����낷
	#pragma region Down

	BitFlagLarge& Down(u32 aIndex) {
		GetBitFlag(aIndex).Down(GetIndex(aIndex));
		return *this;
	}
	BitFlagLarge& DownAll() {
		for (u32 i = 0; i < GetBitFlagNum(); i++) {
			GetBitFlag(i).DownAll();
		}
		return *this;
	}
	BitFlagLarge& DownRange(u32 aStartIndex, u32 aEndIndex) {
		//TODO ����
		return *this;
	}

	#pragma endregion

	//�r�b�g�𔽓]������
	#pragma region Flip

	BitFlagLarge& Flip(u32 aIndex) {
		GetBitFlag(aIndex).Flip(GetIndex(aIndex));
		return *this;
	}
	BitFlagLarge& FlipAll() {
		for (u32 i = 0; i < GetBitFlagNum(); i++) {
			GetBitFlag(i).FlipAll();
		}
		return *this;
	}
	BitFlagLarge& FlipRange(u32 aStartIndex, u32 aEndIndex) {
		//TODO ����
		return *this;
	}

	#pragma endregion

	//�^�U�ɂ���āA���Ă邩���낷�����߂�
	#pragma region Flag

	BitFlagLarge& Flag(u32 aIndex, BOOL aIsStand) {
		if (aIsStand) {
			Stand(aIndex);
		}
		else {
			Down(aIndex);
		}
		return *this;
	}
	BitFlagLarge& FlagRange(u32 aStartIndex, u32 aEndIndex, BOOL aIsStand) {
		if (aIsStand) {
			StandRange(aStartIndex, aEndIndex);
		}
		else {
			DownRange(aStartIndex, aEndIndex);
		}
		return *this;
	}

	#pragma endregion

	#pragma endregion


	//�����o
	#pragma region Member

private:
	BitFlag mBitFlag[(cBitNum + 31) / 32];	//�r�b�g�̏�Ԃ��i�[����

	#pragma endregion


	//�r�b�g�̕��т𕶎���ɂ���
	#pragma region ToString

public:
	using BitString = String<((cBitNum + 31) / 32) * 32 + 1>;

	BitString ToString() const {
		BitString lRes;
		for (u32 i = 0; i < GetBitFlagNum(); i++) {
			lRes += GetBitFlag(i).ToString();
		}
		return lRes;
	}

	#pragma endregion

};

}