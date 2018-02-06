//
//	content	:	������n�̃N���X��֐�
//	author	:	SaitoYoshiki
//

#pragma once


#include "defines.h"
#include "typedef.h"

#include "function.h"


namespace cpot {


//�Œ蒷������̃N���X
template <u32 cSize>
class String {

	//�R���X�g���N�^
	#pragma region Constructor

public:
	String() {
		Set("");
	}
	String(const CHAR* aStr) {
		Set(aStr);
	}
	String(CHAR aChar) {
		Set(ToString(aChar).Get());
	}
	template <u32 cOtherSize>
	String(const String<cOtherSize>& aStr) {
		Set(aStr.Get());
	}

	#pragma endregion


	//�l�̎擾
	#pragma region Getter

public:
	//������̎擾
	const CHAR* Get() const {
		return mStr;
	}
	//������̒����̎擾
	u32 GetLength() const {
		return mLength;
	}

	//������̃o�b�t�@�̑傫���̎擾
	const u32 GetSize() const {
		return cSize;
	}

	#pragma endregion


	//�l�̐ݒ�
	#pragma region Setter

public:
	//������̃Z�b�g
	#pragma region Set

	void Set(const CHAR* aStr) {

		u32 lNewLen = Clamp(StringLen(aStr), u32(0), cSize - 1);

		CopyMem(mStr, aStr, lNewLen);
		mLength = lNewLen;
		mStr[mLength] = '\0';
	}

	template <u32 cOtherSize>
	const String& operator =(const String<cOtherSize>& aStr) {
		Set(aStr.Get());
		return (*this);
	}

	#pragma endregion

	
	//������̒ǉ�
	#pragma region Add

	void Add(const CHAR* aStr) {

		s32 lAddLen = Clamp(StringLen(aStr), u32(0), cSize - GetLength() - 1);

		CopyMem(&(mStr[GetLength()]), aStr, lAddLen);
		mLength = GetLength() + lAddLen;
		mStr[mLength] = '\0';
	}

	const String& operator +=(const CHAR* aStr) {
		Add(aStr);
		return (*this);
	}
	String operator +(const CHAR* aStr) {
		String lStr(*this);
		lStr += aStr;
		return lStr;
	}
	String& operator <<(const CHAR* aStr) {
		*this += aStr;
		return *this;
	}


	template <u32 cOtherSize>
	const String& operator +=(const String<cOtherSize>& aStr) {
		Add(aStr.Get());
		return (*this);
	}
	template <u32 cOtherSize>
	String operator +(const String<cOtherSize>& aStr) {
		String lStr(*this);
		lStr += aStr;
		return lStr;
	}

	#pragma endregion


	//�C���f�b�N�X�ŁA�������擾
	CHAR& operator[](u32 aIndex) {
		CPOT_ASSERT(aIndex <= GetLength() - 1);
		return mStr[aIndex];
	}

	#pragma endregion


	//��r
	#pragma region Compare

public:
	template <u32 cOtherSize>
	BOOL operator ==(const String<cOtherSize>& aStr) const {
		if (GetLength() != aStr.GetLength()) {
			return false;
		}
		if (StringSame(Get(), aStr.Get())) {
			return true;
		}
		return false;
	}

	template <u32 cOtherSize>
	BOOL operator !=(const String<cOtherSize>& aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(const CHAR* aStr) {
		if (StringSame(Get(), aStr)) {
			return true;
		}
		return false;
	}

	BOOL operator !=(const CHAR* aStr) {
		return !((*this) == aStr);
	}

	#pragma endregion


	//����
	#pragma region Operator

public:
	const String& Pop(u32 aNum) {
		CPOT_ASSERT(0 <= aNum);
		s32 lNewLen = (s32)GetLength() - aNum;
		lNewLen = Clamp(lNewLen, (s32)0, lNewLen);
		mStr[lNewLen] = '\0';
		mLength = lNewLen;
		return (*this);
	}

	/*
	String SliceToEnd(u32 aStart) const {
		return Slice(aStart, GetLength());
	}
	String SliceFromStart(u32 aEnd) const {
		return Slice(0, aEnd);
	}
	String Slice(u32 aStart, u32 aEnd) const {
		CPOT_ASSERT(0 <= aStart && aStart <= GetLength() - 1);
		CPOT_ASSERT(aStart <= aEnd && aEnd <= GetLength());

		String lRes;
		u32 lNewLen = aEnd - aStart;

		CopyMem(lRes.mStr, &(mStr[aStart]), lNewLen);
		lRes.Length = lNewLen;
		lRes.mStr[lRes.mLength] = '\0';

		return lRes;
	}
	*/
	//�w�肳�ꂽ�����ɂȂ�܂ŁA�w�肳�ꂽ�����Ŗ��߂�
	String Padding(CHAR aC, u32 aLength) {
		String lRes = *this;
		
		u32 lNowLength = GetLength();
		for (u32 i = lNowLength; i < aLength; i++) {
			lRes += ToString(aC);
		}

		return lRes;
	}

	//�w�肳�ꂽ�����ɂȂ�܂ŁA�w�肳�ꂽ�����Ŗ��߂�i�������j
	String PaddingLeft(CHAR aC, u32 aLength) {
		String lRes;

		u32 lNowLength = GetLength();
		for (u32 i = lNowLength; i < aLength; i++) {
			lRes += ToString(aC);
		}

		lRes += *this;

		return lRes;
	}

	BOOL Exist(const CHAR* aStr) const {

		//���艟���ōs��
		for (u32 i = 0; i < GetLength(); i++) {
			if (StringSame(&(mStr[i]), aStr) == true) {
				return true;
			}
		}
		return false;
	}

private:
	static String ToString(CHAR aC) {
		String lRes("0");
		lRes.mStr[0] = aC;
		return lRes;
	}
		
	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	CHAR mStr[cSize];	//������
	u32 mLength;	//������̒���

	#pragma endregion

};



//�����𕶎���ɂ���
#pragma region ToString

class ToStringBase {

public:
	static String<15> Do(s32 aVal);
	static String<15> Do(u32 aVal);
	static String<31> Do(s64 aVal);
	static String<31> Do(u64 aVal);
	static String<15> Do(f32 aVal);
	static String<31> Do(f64 aVal);
	static String<7> Do(BOOL aVal);
};

#pragma endregion

}

//	�����Ƃ̃t�@�C���̃C���N���[�h
#ifdef CPOT_ON_WINDOWS
#include "Standard/toStringStandard.h"
#elif defined CPOT_ON_ANDROID
#include "Standard/toStringStandard.h"
#elif defined CPOT_ON_LINUX
#include "Standard/toStringStandard.h"
#endif