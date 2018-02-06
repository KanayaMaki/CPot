//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/gameObject.h"

namespace cpot {

class Updater : public Component {
	CPOT_TYPE(Updater, Component)

public:
	Updater();
	~Updater() override;


	//�Ăяo�����֐�
	#pragma region Event
public:
	//�ŏ��̍X�V�̑O�ɌĂяo�����
	virtual void OnStart() {}

	//�X�V����
	virtual void OnBeforeUpdate() {}
	virtual void OnUpdate() {}
	virtual void OnAfterUpdate() {}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	virtual s32 GetPriority() {
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

public:
	void Clear() {
		mUpdater.Clear();
		mUpdaterNowFrame.Clear();
	}

	#pragma endregion

public:
	void Update() {
		Merge();	//�O�̃t���[���ɒǉ����ꂽ�A�b�v�f�[�^�𓝍�����
		Sort();	//�D��x���ɕ��ёւ���
		UpdateUpdater();	//�A�b�v�f�[�^�̍X�V���Ăяo��
	}

private:
	void Merge() {

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
		//�D��x�ɂ���ă\�[�g����B
		//�{���Ȃ�std::sort�Ń����_����n���ă\�[�g���������A�}���`�v���b�g�t�H�[���̈�std��Ԃ𒼐ڐG��Ȃ��̂ŁA�����Ńo�u���\�[�g������
		//mUpdater.Sort();

		//�~���Ƀ\�[�g
		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			for (u32 j = 0; j < mUpdater.GetSize() - 1; j++) {
				//���ɑ傫���̂������
				if (mUpdater[j]->GetPriority() > mUpdater[j + 1]->GetPriority()) {
					//�������āA�傫���̂���O�ɗ���悤��
					auto tmp = mUpdater[j];
					mUpdater[j] = mUpdater[j + 1];
					mUpdater[j + 1] = tmp;
				}
			}
		}
	}

	void UpdateUpdater() {
		
		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnBeforeUpdate();
		}

		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnUpdate();
		}

		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnAfterUpdate();
		}
	}


private:
	Vector<Updater*> mUpdaterNowFrame;	//�V�����ǉ����ꂽ�A�b�v�f�[�^�[
	Vector<Updater*> mUpdater;
};


}