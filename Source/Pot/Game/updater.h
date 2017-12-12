//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/component.h"

namespace cpot {

class Updater : public Component {
	CPOT_TYPE(Updater, Component)

public:
	Updater();
	~Updater() override;


	//�Ăяo�����֐�
	#pragma region Event
public:
	//OnStart�̑O�ɌĂяo�����
	virtual void OnAwake() {}

	//�ŏ��̍X�V�̑O�ɌĂяo�����
	virtual void OnStart() {}

	//�X�V����
	virtual void OnUpdate() {}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	virtual u32 GetPriority() {
		return 0;
	}

	#pragma endregion

};

class UpdaterManager : public Singleton<UpdaterManager> {

	friend class Updater;

	//�o�^&�����BUpdater���Ăяo��
	#pragma region Regist&Remove

private:
	void Regist(Updater* aUpdater) {
		mUpdaterNowFrame.PushBack(aUpdater);
	}
	void Remove(Updater* aUpdater) {
		mUpdaterNowFrame.Remove(aUpdater);
		mUpdater.Remove(aUpdater);
	}
	void Clear() {
		mUpdater.Clear();
		mUpdaterNowFrame.Clear();
	}

	#pragma endregion


	void Update() {
		Merge();	//�O�̃t���[���ɒǉ����ꂽ�A�b�v�f�[�^�𓝍�����
		Sort();	//�D��x���ɕ��ёւ���
		UpdateUpdater();	//�A�b�v�f�[�^�̍X�V���Ăяo��
	}

private:
	void Merge() {

		//OnAwake�̌Ăяo��
		for (u32 i = 0; i < mUpdaterNowFrame.GetSize(); i++) {
			mUpdaterNowFrame[i]->OnAwake();
		}

		//OnStart�̌Ăяo��
		for (u32 i = 0; i < mUpdaterNowFrame.GetSize(); i++) {
			mUpdaterNowFrame[i]->OnStart();
		}

		//����
		while(mUpdaterNowFrame.GetSize() != 0) {
			mUpdater.PushBack(mUpdaterNowFrame.PopBack());
		}
	}

	void Sort() {
		//mUpdater.Sort();
	}

	void UpdateUpdater() {
		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnUpdate();
		}
	}


private:
	Vector<Updater*> mUpdaterNowFrame;	//�V�����ǉ����ꂽ�A�b�v�f�[�^�[
	Vector<Updater*> mUpdater;
};


}