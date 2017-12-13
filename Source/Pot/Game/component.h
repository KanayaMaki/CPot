//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Usefull/buffer.h"
#include "./Pot/List/vector.h"

namespace cpot {


class GameObject;

using ComponentName = HashString<28>;

class Component {
	CPOT_TYPE_BASE(Component);

	//����������
	#pragma region Init
public:
	//�R���X�g���N�^
	Component();

	void InitComponent(GameObject* aGameObject);

	#pragma endregion


	//�I��
	#pragma region Final
public:
	//���z�R���X�g���N�^
	virtual ~Component();

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
	void SetGameObjectActive(BOOL aIsActive) {
		mFlags.Flag(cGameObjectActive, aIsActive);
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


class ComponentManager : public Singleton<ComponentManager> {

	friend class Component;

	//�o�^&�����BComponent���Ăяo��
	#pragma region Regist&Remove

private:
	void Regist(Component* aComponent) {
		mComponentNowFrame.PushBack(aComponent);
	}
	void Remove(Component* aComponent) {
		
	}

public:
	void Clear() {
		while (mComponentNowFrame.GetSize() != 0) {
			CPOT_DELETE(mComponentNowFrame.PopBack());
		}
		while (mComponent.GetSize() != 0) {
			CPOT_DELETE(mComponent.PopBack());
		}
	}

	#pragma endregion

public:
	void Update() {
		Merge();	//�O�̃t���[���ɒǉ����ꂽ�R���|�[�l���g�𓝍�����
		Delete();	//�R���|�[�l���g���폜����
	}

private:
	void Merge() {
		while (mComponentNowFrame.GetSize() != 0) {
			mComponent.PushBack(mComponentNowFrame.PopBack());
		}
	}

	void Delete() {
		for (u32 i = 0; i < mComponent.GetSize(); i++) {
			if (mComponent[i]->GetDelete() == true) {

			}
		}
	}


private:
	Vector<Component*> mComponentNowFrame;	//�V�����ǉ����ꂽ�R���|�[�l���g
	Vector<Component*> mComponent;
};

}