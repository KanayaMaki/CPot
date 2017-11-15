//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

//型を調べる
#pragma region Type

using Type = HashString<28>;

//基底クラスで宣言する
#pragma region Base

#define CYC_POT_TYPE_BASE(THIS)									\
public:															\
	static const Type& SGetTypeName() {							\
		static Type t(CPOT_NAME_EXTEND(THIS));					\
		return t;												\
	}															\
	virtual BOOL CanCast(const Type& aTypeName) const {			\
		return THIS::SEqualType(aTypeName);						\
	}															\
	virtual BOOL EqualType(const Type& aTypeName) const {		\
		return THIS::SEqualType(aTypeName);						\
	}															\
	virtual const Type& GetTypeName() const {					\
		return SGetTypeName();									\
	}															\
																\
protected:														\
	static BOOL SEqualType(const Type& aTypeName) {				\
		return	STypeName() == aTypeName;						\
	}

#pragma endregion


//派生クラスで宣言する
#pragma region Extend


#define CYC_POT_TYPE(THIS, SUPER)								\
public:															\
	static const Type& SGetTypeName() {							\
		static Type t(CPOT_NAME_EXTEND(THIS));					\
		return t;												\
	}															\
	BOOL CanCast(const Type& aTypeName) const override {		\
		if (THIS::SEqualType(aTypeName)) return true;			\
		return SUPER::SEqualType(aTypeName);					\
	}															\
	BOOL EqualType(const Type& aTypeName) const override {		\
		return THIS::SEqualType(aTypeName);						\
	}															\
	const Type& GetTypeName() const override {					\
		return SGetTypeName();									\
	}															\
																\
protected:														\
	static BOOL SEqualType(const Type& aTypeName) {				\
		return	STypeName() == aTypeName;						\
	}

#pragma endregion


//多重継承しているクラスで宣言する
#pragma region Double


#define CYC_POT_TYPE_DOUBLE(THIS, SUPER1, SUPER2)				\
public:															\
	static const Type& SGetTypeName() {							\
		static Type t(CPOT_NAME_EXTEND(THIS));					\
		return t;												\
	}															\
	BOOL CanCast(const Type& aTypeName) const override {		\
		if (THIS::SEqualType(aTypeName)) return true;			\
		if (SUPER1::SEqualType(aTypeName)) return true;			\
		return SUPER2::SEqualType(aTypeName);					\
	}															\
	BOOL EqualType(const Type& aTypeName) const override {		\
		return THIS::SEqualType(aTypeName);						\
	}															\
	const Type& GetTypeName() const override {					\
		return SGetTypeName();									\
	}															\
																\
protected:														\
	static BOOL SEqualType(const Type& aTypeName) {				\
		return	STypeName() == aTypeName;						\
	}

#pragma endregion

#pragma endregion





}
