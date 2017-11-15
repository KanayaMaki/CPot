//
//	content	:	�ʃX���b�h�Ń��[�h���Ă����N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/thread.h"
#include "./Pot/Thread/mutex.h"
#include "./Pot/Out/out.h"
#include "./Pot/List/vector.h"
#include "./Pot/Sleep/sleep.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


class Loader {
public:
	//���[�h
	virtual void Load() = 0;
	
	//���C���X���b�h�Ŏ��s�����A���[�h�J�n�O�̏���
	//!Start�̒�����Loader��Regist���Ă͂����Ȃ�
	virtual void Start() {}
	
	//���C���X���b�h�Ŏ��s�����A���[�h�I����̏���
	virtual void Finish() {}

	//�D�悷�ׂ���
	virtual BOOL IsHurry() const {
		return false;
	}
};


class LoaderManager : public Singleton<LoaderManager> {
	friend class Singleton<LoaderManager>;

private:
	LoaderManager() {
		mNowLoadingCount = 0;
	}
	~LoaderManager() {
		Clear();
	}

	//���[�h���J�n����
	#pragma region Start

public:
	//���[�_�X���b�h���N������
	void Start(u32 aThreadNum) {
		//�w�肳�ꂽ�������̃X���b�h���N������
		for (u32 i = 0; i < aThreadNum; i++) {
			SetEnd(i, false);
			mThread[i].Start(Load, (u32*)i);
		}
	}

	//���[�_�X���b�h�̐����A�w�肳�ꂽ���ɂ���
	void Resize(u32 aThreadNum) {
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			//�N���\��̃X���b�h�Ȃ�
			if (i < aThreadNum) {
				SetEnd(i, false);
				mThread[i].Start(Load, (u32*)i);
			}
			//��~�\��̃X���b�h�Ȃ�
			if (i >= aThreadNum) {
				SetEnd(i, true);
			}
		}
	}

	#pragma endregion


	//���[�h���~����
	#pragma region Stop

public:
	//���[�_�X���b�h���I������
	void Stop() {

		//�S�X���b�h�̏I��
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			SetEnd(i, true);
		}
	}

	//���[�_�X���b�h���I�����āA�҂�
	void Join() {

		//�S�X���b�h�̏I��
		Stop();

		//�S�X���b�h�̍�����҂�
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			mThread[i].Join();
		}
	}

	#pragma endregion


	//���ݓo�^����Ă��郍�[�_��S�ăN���A����
	#pragma region Clear

	void Clear() {
		Join();
		Delete(mLoaderListNormal);
		Delete(mLoaderListHurry);
		Delete(mLoaderListFinish);
		mNowLoadingCount = 0;
	}

	#pragma endregion


	//�ʃX���b�h�Ŏ��s����āA�ǂݍ���
	#pragma region Load

private:
	static Loader* GetLoader() {

		Loader* l = nullptr;

		MutexLocker m0(S().mLoaderListNormalMutex);
		MutexLocker m1(S().mLoaderListHurryMutex);

		//�����}���̃��[�_�����݂���Ȃ�
		if (S().mLoaderListHurry.GetSize() != 0) {
			//��Ԍ��̃��[�_���擾����
			l = S().mLoaderListHurry.PopBack();
		}
		//�����ʏ�̃��[�_�����݂���Ȃ�
		else if (S().mLoaderListNormal.GetSize() != 0) {
			//��Ԍ��̃��[�_���擾����
			l = S().mLoaderListNormal.PopBack();
		}

		if (l) {
			S().LoadStart();	//���[�h�J�n
		}

		return l;
	}
	static void Load(u32* aThreadIndex) {

		Sleep lSleep;

		u32 lThreadIndex = (u32)aThreadIndex;

		while (true) {

			Loader* l = GetLoader();

			//�������[�_���擾�ł��Ă�����
			if (l) {

				l->Load();	//���[�h����

				//���[�h���I���������X�g�ɓ����
				MutexLocker m(S().mLoaderListFinishMutex);
				S().mLoaderListFinish.PushBack(l);

				S().LoadEnd();	//���[�h�I��
			}
			//�������[�_�����݂��Ȃ��Ȃ�
			else {
				lSleep.SleepSecond(0.1f);	//�����x��
			}

			//�X���b�h���I������Ȃ�
			if (S().GetEnd(lThreadIndex) == true) {
				break;	//���[�v�𔲂���
			}
		}
	}

	#pragma endregion


	//Loader��o�^����
	#pragma region Regist

public:
	void Regist(Loader* aLoader) {
		MutexLocker m(mLoaderListWaitMutex);
		mLoaderListWait.PushBack(aLoader);
	}

private:
	void RegistLoaderNormal(Loader* aLoader) {
		MutexLocker m(mLoaderListNormalMutex);
		mLoaderListNormal.PushBack(aLoader);
	}
	void RegistLoaderHurry(Loader* aLoader) {
		MutexLocker m(mLoaderListHurryMutex);
		mLoaderListHurry.PushBack(aLoader);
	}

	#pragma endregion


	//�X�V�B�J�n���Ă��Ȃ�Loader��Start()�ƁA�I������Loader��Finish()���Ăяo��
	#pragma region Update

public:
	void Update() {
		//�������J�n���Ă��Ȃ����[�_��Start���Ăяo��
		{
			MutexLocker m(mLoaderListWaitMutex);

			while (mLoaderListWait.GetSize() != 0) {
				Loader* l = mLoaderListWait.PopBack();
				StartLoad(l);
			}
		}


		//�����̏I��������[�_��Finish���Ăяo��
		{
			MutexLocker m(mLoaderListFinishMutex);
			for (u32 i = 0; i < mLoaderListFinish.GetSize(); i++) {
				mLoaderListFinish[i]->Finish();
			}
			Delete(mLoaderListFinish);
		}
	}


private:
	void StartLoad(Loader* aLoader) {
		aLoader->Start();
		if (aLoader->IsHurry()) {
			RegistLoaderHurry(aLoader);
		}
		else {
			RegistLoaderNormal(aLoader);
		}
	}

	#pragma endregion


	//���[�h�����ǂ���
	#pragma region IsLoading

public:
	BOOL IsLoading() {
		//LoaderListWait�Ƀ��[�_�[���c���Ă���΁A���[�h��
		{
			MutexLocker m(mLoaderListWaitMutex);
			if (mLoaderListWait.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListNormal�Ƀ��[�_�[���c���Ă���΁A���[�h��
		{
			MutexLocker m(mLoaderListNormalMutex);
			if (mLoaderListNormal.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListHurry�Ƀ��[�_�[���c���Ă���΁A���[�h��
		{
			MutexLocker m(mLoaderListHurryMutex);
			if (mLoaderListHurry.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListFinish�Ƀ��[�_�[���c���Ă���΁A���[�h��
		{
			MutexLocker m(mLoaderListFinishMutex);
			if (mLoaderListFinish.GetSize() != 0) {
				return true;
			}
		}

		//NowLoadingCount��1�ȏ�Ȃ烍�[�h��
		{
			MutexLocker m(mNowLoadingCountMutex);
			if (mNowLoadingCount >= 1) {
				return true;
			}
		}

		//�ǂ̏����ɂ����Ă͂܂�Ȃ��Ȃ�A���[�h���ł͂Ȃ�
		return false;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

	//LoaderList��Mutex
	#pragma region LoaderList & Mutex

private:
	//�������J�n���Ă��Ȃ����[�_�̃��X�g
	Vector<Loader*> mLoaderListWait;
	Mutex mLoaderListWaitMutex;

	//���ʂ̗D��x�̃��[�_�̃��X�g
	Vector<Loader*> mLoaderListNormal;
	Mutex mLoaderListNormalMutex;

	//�D��x�̍������[�_�̃��X�g
	Vector<Loader*> mLoaderListHurry;
	Mutex mLoaderListHurryMutex;

	//�����̏I��������[�_�̃��X�g
	Vector<Loader*> mLoaderListFinish;
	Mutex mLoaderListFinishMutex;

	#pragma endregion


	//Threads
	#pragma region Threads

private:
	static constexpr u32 cThreadMaxNum = 5;
	Thread mThread[cThreadMaxNum];

	BOOL GetEnd(u32 aThreadIndex) {
		MutexLocker m(mEndMutex[aThreadIndex]);
		return mEnd[aThreadIndex];
	}
	void SetEnd(u32 aThreadIndex, BOOL aEnd) {
		MutexLocker m(mEndMutex[aThreadIndex]);
		mEnd[aThreadIndex] = aEnd;
	}
	BOOL mEnd[cThreadMaxNum];
	Mutex mEndMutex[cThreadMaxNum];

	#pragma endregion


	//���݃��[�h���Ă��鐔
	#pragma region NowLoading

private:
	u32 mNowLoadingCount;
	Mutex mNowLoadingCountMutex;

private:
	void LoadStart() {
		MutexLocker m(mNowLoadingCountMutex);
		mNowLoadingCount++;
	}
	void LoadEnd() {
		MutexLocker m(mNowLoadingCountMutex);
		mNowLoadingCount--;
	}

	#pragma endregion


	#pragma endregion


	//Vector�̗v�f�̃f���[�g
	#pragma region Delete

private:
	static void Delete(Vector<Loader*>& aVector) {
		for (u32 i = 0; i < aVector.GetSize(); i++) {
			delete aVector[i];
		}
		aVector.Clear();
	}

	#pragma endregion

};

}