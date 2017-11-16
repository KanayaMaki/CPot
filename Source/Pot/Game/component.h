//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

//�^�𒲂ׂ�
#pragma region Type

using Type = HashString<28>;

//���N���X�Ő錾����
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


//�h���N���X�Ő錾����
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


//���d�p�����Ă���N���X�Ő錾����
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

	//����������
	#pragma region Init
public:
	//�R���X�g���N�^
	Component();

	void Init(GameObject* aGameObject);

	#pragma endregion


	//�I��
	#pragma region Final
public:
	//���z�R���X�g���N�^
	virtual ~Component() {}

	#pragma endregion


	//GameObject�Ɋւ���
	#pragma region GameObject

private:
	GameObject* mGameObject;

public:
	GameObject* GetGameObject() const {
		return mGameObject;
	}

	#pragma region Function

public:
	//GameObject�̊֐����AComponent�ł��g����悤��
	template <typename T>
	T* GetComponent();
	template <typename T>
	u32 GetComponentNum();
	Transform& GetTransform();

	#pragma endregion

	#pragma endregion


	//���
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


	//�R���|�[�l���g�̖��O
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


	//�R���|�[�l���g���Ƃ̃��j�[�N�Ȕԍ�
	#pragma region Unique

	u32 mUnique;
	u32 GetUnique() const {
		return mUnique;
	}

	#pragma endregion
};

}


#include "./Pot/Game/gameObject.h"

