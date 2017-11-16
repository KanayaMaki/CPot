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

#define CPOT_TYPE_BASE(THIS)									\
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
		return	SGetTypeName() == aTypeName;					\
	}

#pragma endregion


//派生クラスで宣言する
#pragma region Extend


#define CPOT_TYPE(THIS, SUPER)									\
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
		return	SGetTypeName() == aTypeName;					\
	}

#pragma endregion


//多重継承しているクラスで宣言する
#pragma region Double


#define CPOT_TYPE_DOUBLE(THIS, SUPER1, SUPER2)					\
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
		return	SGetTypeName() == aTypeName;					\
	}

#pragma endregion

#pragma endregion


class GameObject;

using ComponentName = HashString<28>;

class Component {
	CPOT_TYPE_BASE(Component);

	//初期化処理
	#pragma region Init
public:
	//コンストラクタ
	Component();

	void Init(GameObject* aGameObject);

	#pragma endregion


	//終了
	#pragma region Final
public:
	//仮想コンストラクタ
	virtual ~Component() {}

	#pragma endregion


	//GameObjectに関する
	#pragma region GameObject

private:
	GameObject* mGameObject;

public:
	GameObject* GetGameObject() const {
		return mGameObject;
	}

	#pragma region Function

public:
	//GameObjectの関数を、Componentでも使えるように
	template <typename T>
	T* GetComponent();
	template <typename T>
	u32 GetComponentNum();
	Transform& GetTransform();

	#pragma endregion

	#pragma endregion


	//状態
	#pragma region Flags

private:
	BitFlag mFlags;
	enum CFlags {
		cDelete,
		cDeleteNow,
		cActive,
		cGameObjectActive
	};

	#pragma region Delete

public:
	BOOL GetDelete() const {
		return mFlags.IsStand(cDelete);
	}
	void SetDelete() {
		mFlags.Stand(cDelete);
	}

	BOOL GetDeleteNow() const {
		return mFlags.IsStand(cDeleteNow);
	}

	#pragma endregion


	#pragma region Active

	BOOL GetActive() const {
		return GetThisActive() && GetGameObjectActive();
	}
	BOOL GetThisActive() const {
		return mFlags.IsStand(cActive);
	}
	BOOL GetGameObjectActive() const {
		return mFlags.IsStand(cGameObjectActive);
	}
	void SetActive(BOOL aIsActive) {
		mFlags.Flag(cActive, aIsActive);
	}

	#pragma endregion

	#pragma endregion


	//コンポーネントの名前
	#pragma region Name

	ComponentName mName;
	const ComponentName& GetName() const {
		return mName;
	}
	void SetName(const CHAR* aName) {
		mName = aName;
	}
	void SetName(const ComponentName& aName) {
		mName = aName;
	}

	#pragma endregion


	//コンポーネントごとのユニークな番号
	#pragma region Unique

	u32 mUnique;
	u32 GetUnique() const {
		return mUnique;
	}

	#pragma endregion
};

}


#include "./Pot/Game/gameObject.h"

