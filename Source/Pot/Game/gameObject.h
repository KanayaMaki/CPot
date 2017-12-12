//
//	content	:	ゲームオブジェクト
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"
#include "./Pot/Game/component.h"
#include "./Pot/Game/unique.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {

using GameObjectName = HashString<28>;


class GameObject {

	//初期化
	#pragma region Init

public:
	GameObject() {
		Init();
	}
	GameObject(const CHAR* aName) {
		Init(aName);
	}

private:
	void Init(const CHAR* aName);
	void Init() {
		Init("GameObject");
	}

	#pragma endregion

	
	//終了処理
	#pragma region Final

public:
	~GameObject();

	#pragma endregion


	//トランスフォーム
	#pragma region Transform

public:
	Transform& GetTransform() {
		return mTransform;
	}
private:
	Transform mTransform;

	#pragma endregion


	//ゲームオブジェクトの名前
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


	//コンポーネント
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


	//状態
	#pragma region Flags

private:
	BitFlag mFlags;
	enum CFlags {
		cDelete,
		cActive,
	};

	//削除されるか
	#pragma region Delete

public:
	BOOL GetDelete() const {
		return mFlags.IsStand(cDelete);
	}
	void SetDelete() {
		mFlags.Stand(cDelete);
	}

	#pragma endregion

	
	//有効か
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


	//固有の数
	#pragma region Unique

public:
	u32 GetUnique() const {
		return mUnique;
	}

private:
	u32 mUnique;
	
	#pragma endregion


	#pragma region Static

public:
	static GameObject* Find(const CHAR* aName) {
		return Find(GameObjectName(aName));
	}
	static GameObject* Find(const GameObjectName& aName);

	#pragma endregion
};


class GameObjectManager : public Singleton<GameObjectManager> {
	friend class GameObject;

private:
	void Regist(GameObject* aGameObject) {
		mGameObjects.PushBack(aGameObject);
	}
	void Remove(GameObject* aGameObject) {
		mGameObjects.Remove(aGameObject);
	}

public:
	GameObject* Find(const CHAR* aName) {
		return Find(GameObjectName(aName));
	}
	GameObject* Find(const GameObjectName& aName) {
		for (u32 i = 0; i < mGameObjects.GetSize(); i++) {
			GameObject* lG = mGameObjects[i];
			if (lG->GetName() == aName) {
				return lG;
			}
		}
		return nullptr;
	}

	Vector<GameObject*> mGameObjects;
};


}
