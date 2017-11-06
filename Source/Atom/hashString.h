//	ファイル名	:	Atom/hashString.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/06
//	更新日時	:	2017/11/06
//	内容		:	Hashで比較する文字列のクラスを定義

#pragma once

#include "string.h"
#include "hash.h"


namespace cpot {


#pragma region 文字列を保存しないHashString

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



#pragma region 文字列を保存するHashString


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



#pragma region どちらのHashStringを使用するかの切り替え


#ifdef CPOT_VALID_HASHSTRING_LEFT

template<s32 cSize>
using HashString = HashStringLeft<cSize>;

#else

template<s32 cSize>
using HashString = HashStringNone<cSize>;

#endif


#pragma endregion



}