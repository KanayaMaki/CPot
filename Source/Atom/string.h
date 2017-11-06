//	ファイル名	:	Atom/string.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/06
//	更新日時	:	2017/11/06
//	内容		:	文字列系のクラスや関数を定義

#pragma once


#include "defines.h"
#include "typedef.h"

#include "function.h"


namespace cpot {


template <u32 cSize>
class String {

public:
	String() {
		Set("");
	}
	String(const CHAR* aStr) {
		Set(aStr);
	}
	template <u32 cOtherSize>
	String(const String<cOtherSize>& aStr) {
		Set(aStr.Get());
	}


public:
	template <u32 cOtherSize>
	const String& operator =(const String<cOtherSize>& aStr) {
		Set(aStr.Get());
		return (*this);
	}

	String operator +(const CHAR* aStr) {
		String s(*this);
		s += aStr;
		return s;
	}
	const String& operator +=(const CHAR* aStr) {
		Add(aStr);
		return (*this);
	}

	String& operator <<(const CHAR* aStr) {
		*this += aStr;
		return *this;
	}

	const CHAR* Get() const { return mStr; }
	void Set(const CHAR* aStr) {

		u32 lNewLen = Clamp(StringLen(aStr), u32(0), cSize - 1);

		CopyMem(mStr, aStr, lNewLen);
		mLength = lNewLen;
		mStr[mLength] = '\0';
	}
	void Add(const CHAR* aStr) {

		s32 lAddLen = Clamp(StringLen(aStr), u32(0), cSize - Length() - 1);

		CopyMem(&(mStr[Length()]), aStr, lAddLen);
		mLength = Length() + lAddLen;
		mStr[mLength] = '\0';
	}


	const String& Pop(u32 aNum) {
		CPOT_ASSERT(0 <= aNum);
		s32 lNewLen = Length() - aNum;
		CPOT_ASSERT(0 <= lNewLen);
		mStr[lNewLen] = '\0';
		mLength = lNewLen;
		return (*this);
	}

	String SliceToEnd(u32 aStart) const {
		return Slice(aStart, Length());
	}
	String SliceFromStart(u32 aEnd) const {
		return Slice(0, aEnd);
	}
	String Slice(u32 aStart, u32 aEnd) const {
		CPOT_ASSERT(0 <= aStart && aStart <= Length() - 1);
		CPOT_ASSERT(aStart <= aEnd && aEnd <= Length());

		String lRes;
		u32 lNewLen = aEnd - aStart;

		CopyMem(lRes.mStr, &(mStr[aStart]), lNewLen);
		lRes.Length = lNewLen;
		lRes.mStr[lRes.mLength] = '\0';

		return lRes;
	}


	CHAR& operator[](u32 aIndex) {
		CPOT_ASSERT(aIndex <= Length() - 1);
		return mStr[aIndex];
	}
	u32 Length() const {
		return mLength;
	}


public:
	template <u32 cOtherSize>
	BOOL operator ==(const String<cOtherSize>& aStr) const {
		if (Length() != aStr.Length()) {
			return false;
		}
		if (StrSame(Get(), aStr.Get())) {
			return true;
		}
		return false;
	}

	template <u32 cOtherSize>
	BOOL operator !=(const String<cOtherSize>& aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(const CHAR* aStr) {
		if (StrSame(Get(), aStr)) {
			return true;
		}
		return false;
	}

	BOOL operator !=(const CHAR* aStr) {
		return !((*this) == aStr);
	}


private:
	CHAR mStr[cSize];
	u32 mLength;

};



}