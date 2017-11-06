//	�t�@�C����	:	Atom/hashString.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/06
//	�X�V����	:	2017/11/06
//	���e		:	Hash�Ŕ�r���镶����̃N���X���`

#pragma once

#include "string.h"
#include "hash.h"


namespace cpot {


#pragma region �������ۑ����Ȃ�HashString

template <u32 cSize>
class HashStringNone {
public:
	HashStringNone() {
		Set("");
	}
	HashStringNone(const CHAR* aStr) {
		Set(aString);
	}

public:
	void Set(const CHAR* aStr) {
		mHashCode = Hash(aStr);
	}
	const HashStringNone<cSize>& operator =(const CHAR* aStr) {
		Set(aStr);
		return *this;
	}
	const CHAR* GetString() const {
		return "hashNone";
	}


private:
	HashCode mHashCode;
public:
	HashCode Get() const {
		return mHashCode;
	}


public:
	BOOL operator ==(const HashStringNone<cSize>& aStr) const {
		return mHashCode == aStr.mHashCode;
	}
	BOOL operator !=(const HashStringNone<cSize>& aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(const CHAR* aStr) const {
		return mHashCode == Hash(aStr);
	}
	BOOL operator !=(const CHAR* aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(HashCode aHashCode) const {
		return mHashCode == aHashCode;
	}
	BOOL operator !=(HashCode aHashCode) const {
		return !((*this) == aHashCode);
	}

	static constexpr HashCode Hash(const CHAR* aStr) {
		return Hasher::Hash(aStr);
	}
};

#pragma endregion



#pragma region �������ۑ�����HashString


template <u32 cSize>
class HashStringLeft {
public:
	HashStringLeft() {
		Set("");
	}
	HashStringLeft(const CHAR* aStr) {
		Set(aStr);
	}


public:
	using TString = String<cSize>;
	TString mString;

public:
	void Set(const CHAR* aStr) {
		mHashCode = Hash(aStr);
		mString = aStr;
	}
	const HashStringLeft<cSize>& operator =(const CHAR* aStr) {
		Set(aStr);
		return *this;
	}

	const CHAR* GetString() const {
		return mString.Get();
	}


private:
	HashCode mHashCode;
public:
	HashCode Get() const {
		return mHashCode;
	}


public:
	BOOL operator ==(const HashStringLeft<cSize>& aStr) const {
		return mHashCode == aStr.mHashCode;
	}
	BOOL operator !=(const HashStringLeft<cSize>& aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(const CHAR* aStr) const {
		return mHashCode == Hash(aStr);
	}
	BOOL operator !=(const CHAR* aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(HashCode aHashCode) const {
		return mHashCode == aHashCode;
	}
	BOOL operator !=(HashCode aHashCode) const {
		return !((*this) == aHashCode);
	}

	static constexpr HashCode Hash(const CHAR* aStr) {
		return Hasher::Hash(aStr);
	}
};


#pragma endregion



#pragma region �ǂ����HashString���g�p���邩�̐؂�ւ�


#ifdef CPOT_VALID_HASHSTRING_LEFT

template<s32 cSize>
using HashString = HashStringLeft<cSize>;

#else

template<s32 cSize>
using HashString = HashStringNone<cSize>;

#endif


#pragma endregion



}