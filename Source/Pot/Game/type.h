//
//	content	:	�R���|�[�l���g��o�^���邽�߂̃N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/component.h"

namespace cpot {

class Component;

//�R���|�[�l���g���쐬����N���X�̊��N���X
class TypeFactoryBase {
public:
	virtual const Type& GetTypeName() = 0;
	virtual Component* Create() = 0;
};


//�R���|�[�l���g���쐬����N���X
template <typename T>
class TypeFactory : public TypeFactoryBase {
public:
	const Type& GetTypeName() override {
		return T::SGetTypeName();
	}
	Component* Create() override {
		return new T;
	}
};


//�R���|�[�l���g���쐬����N���X���Ǘ�����N���X
class TypeFactoryManager : public Singleton<TypeFactoryManager> {
	friend class Singleton<TypeFactoryManager>;
private:
	TypeFactoryManager() {
		mFactoryNum = 0;
	}


public:
	//�R���|�[�l���g���쐬����N���X�́A�ő�\�o�^��
	static const u32 cTypeFactoryMax = 1024;


public:
	//�R���|�[�l���g���쐬����N���X��o�^����
	void Regist(TypeFactoryBase* aFactory) {
		CPOT_ASSERT(mFactoryNum < cTypeFactoryMax);
		mFactory[mFactoryNum++] = aFactory;
	}

	//�R���|�[�l���g�̌^������A�R���|�[�l���g���쐬����
	Component* Create(const Type& aTypeName) {
		for (u32 i = 0; i < mFactoryNum; i++) {
			if (aTypeName == mFactory[i]->GetTypeName()) {
				return mFactory[i]->Create();
			}
		}
		return nullptr;
	}

private:
	u32 mFactoryNum;
	TypeFactoryBase* mFactory[cTypeFactoryMax];
};


//�R���|�[�l���g���쐬����N���X��o�^����N���X
template <typename T>
class TypeFactoryRegister {
public:
	TypeFactoryRegister() {
		TypeFactoryManager::S().Regist(&mFactory);
	}

private:
	TypeFactory<T> mFactory;
};


//TypeFactoryRegister�N���X�����̉�����N���X
template <typename T>
class TypeFactoryRegisterInstatiate {
private:
	static TypeFactoryRegister<T> mFactoryRegister;
};

template <typename T>
TypeFactoryRegister<T> TypeFactoryRegisterInstatiate<T>::mFactoryRegister;

#define CPOT_REGIST_TYPE(TYPE) template class TypeFactoryRegisterInstatiate<TYPE>;


}