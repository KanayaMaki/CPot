//
//	content	:	�Q�[���I�u�W�F�N�g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"
#include "./Pot/Game/component.h"
#include "./Pot/Game/unique.h"

namespace cpot {

using GameObjectName = HashString<32>;

class GameObject {

	//������
	#pragma region Init

public:
	GameObject() {
		Init();
	}
	GameObject(const CHAR* aName) {
		Init(aName);
	}

public:
	void Init(const CHAR* aName) {
		SetName(aName);
		mUnique = UniqueGenerator<GameObject>::S().Generate();

		mFlags.DownAll();
		mFlags.Stand(cActive);
	}
	void Init() {
		Init("GameObject");
	}

	#pragma endregion

	
	//�g�����X�t�H�[��
	#pragma region Transform

public:
	Transform& GetTransform() {
		return mTransform;
	}
private:
	Transform mTransform;

	#pragma endregion


	//�Q�[���I�u�W�F�N�g�̖��O
	#pragma region Name

public:
	const GameObjectName& GetName() const {
		return mName;
	}
	void SetName(const CHAR* aName) {
		mName = aName;
	}
	void SetName(const GameObjectName& aName) {
		mName = aName;
	}

private:
	GameObjectName mName;

	#pragma endregion


	//�R���|�[�l���g
	#pragma region Component

public:
	template <typename T>
	T* GetComponent() {
		for (u32 i = 0; i < GetComponentNum(); i++) {
			Component* lC = mComponents[i];
			if (lC->CanCast(T::SGetTypeName())) {
				return (T*)lC;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* AddComponent() {
		T* lC = new T;
		AddComponent(lC);
		return lC;
	}

	void AddComponent(Component* aComponent) {
		mComponents.PushBack(aComponent);
	}

	void RemoveComponent(Component* aComponent) {
		mComponents.Remove(aComponent);
		aComponent->SetDelete();
	}
	
	u32 GetComponentNum() const {
		return mComponents.GetSize();
	}
	
private:
	Vector<Component*> mComponents;

	#pragma endregion


	//���
	#pragma region Flags

private:
	BitFlag mFlags;
	enum CFlags {
		cDelete,
		cActive,
	};

	//�폜����邩
	#pragma region Delete

public:
	BOOL GetDelete() const {
		return mFlags.IsStand(cDelete);
	}
	void SetDelete() {
		mFlags.Stand(cDelete);
	}

	#pragma endregion

	
	//�L����
	#pragma region Active

public:
	BOOL GetActive() const {
		return mFlags.IsStand(cActive);
	}
	void SetActive(BOOL aIsActive) {
		mFlags.Flag(cActive, aIsActive);
	}

	#pragma endregion


	#pragma endregion


	//�ŗL�̐�
	#pragma region Unique

public:
	u32 GetUnique() const {
		return mUnique;
	}

private:
	u32 mUnique;
	
	#pragma endregion


	#pragma region Static

private:
	static void Regist(GameObject* aGameObject);

public:
	static GameObject* Find(const CHAR* aName) {
		return Find(GameObjectName(aName));
	}
	static GameObject* Find(const GameObjectName& aName) {

	}

private:
	static Vector<GameObject*> mGameObjects;

	#pragma endregion
};

}
