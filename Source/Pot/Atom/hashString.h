//
//	content	:	Hash�l�Ŕ�r���镶����̃N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "string.h"
#include "hash.h"


namespace cpot {


#pragma region �������ۑ����Ȃ�HashString

template <u32 cSize>
class HashStringNone {

	//�R���X�g���N�^�Ȃ�
	#pragma region Init

public:
	HashStringNone() {
		Set("");
	}
	HashStringNone(const CHAR* aStr) {
		Set(aStr);
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	HashCode mHashCode;

	#pragma endregion


	//�ݒ�
	#pragma region Setter

public:
	void Set(const CHAR* aStr) {
		mHashCode = Hash(aStr);
	}
	const HashStringNone<cSize>& operator =(const CHAR* aStr) {
		Set(aStr);
		return *this;
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	HashCode Get() const {
		return mHashCode;
	}
	const CHAR* GetString() const {
		return "";
	}

	#pragma endregion


	//��r
	#pragma region Compare

	//�C�R�[��
	#pragma region Equal

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

	#pragma endregion


	//�召�֌W
	#pragma region Less

public:
	BOOL operator >=(const HashStringNone<cSize>& aStr) const {
		return mHashCode >= aStr.mHashCode;
	}
	BOOL operator <(const HashStringNone<cSize>& aStr) const {
		return !((*this) >= aStr);
	}
	BOOL operator <=(const HashStringNone<cSize>& aStr) const {
		return mHashCode <= aStr.mHashCode;
	}
	BOOL operator >(const HashStringNone<cSize>& aStr) const {
		return !((*this) <= aStr);
	}

	#pragma endregion

	#pragma endregion


	//�n�b�V���l�𓾂�֐�
	#pragma region Hash

	static constexpr HashCode Hash(const CHAR* aStr) {
		return Hasher::Hash(aStr);
	}

	#pragma endregion
};

#pragma endregion



#pragma region �������ۑ�����HashString


template <u32 cSize>
class HashStringLeft {

	//�R���X�g���N�^�Ȃ�
	#pragma region Init

public:
	HashStringLeft() {
		Set("");
	}
	HashStringLeft(const CHAR* aStr) {
		Set(aStr);
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

public:
	using TString = String<cSize>;
	
private:
	TString mString;
	HashCode mHashCode;
	
	#pragma endregion


	//�ݒ�
	#pragma region Setter

public:
	void Set(const CHAR* aStr) {
		mHashCode = Hash(aStr);
		mString = aStr;
	}
	const HashStringLeft<cSize>& operator =(const CHAR* aStr) {
		Set(aStr);
		return *this;
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	HashCode Get() const {
		return mHashCode;
	}
	const CHAR* GetString() const {
		return mString.Get();
	}

	#pragma endregion


	//��r
	#pragma region Compare

	//�C�R�[��
	#pragma region Equal

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

	#pragma endregion


	//�召�֌W
	#pragma region Less

public:
	BOOL operator >=(const HashStringLeft<cSize>& aStr) const {
		return mHashCode >= aStr.mHashCode;
	}
	BOOL operator <(const HashStringLeft<cSize>& aStr) const {
		return !((*this) >= aStr);
	}
	BOOL operator <=(const HashStringLeft<cSize>& aStr) const {
		return mHashCode <= aStr.mHashCode;
	}
	BOOL operator >(const HashStringLeft<cSize>& aStr) const {
		return !((*this) <= aStr);
	}

	#pragma endregion

	#pragma endregion


	//�n�b�V���l�𓾂�֐�
	#pragma region Hash

	static constexpr HashCode Hash(const CHAR* aStr) {
		return Hasher::Hash(aStr);
	}

	#pragma endregion

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