#pragma once

#include "./Atom/atom.h"
#include "./Thread/thread.h"
#include "./Thread/mutex.h"
#include "./Output/output.h"
#include "./List/vector.h"
#include "./Sleep/sleep.h"

#include "./Usefull/singleton.h"


namespace cpot {


class Loader {
public:
	virtual void Load() = 0;
	virtual void Finish() {}

	virtual BOOL IsHurry() const {
		return false;
	}
};

class LoaderTimer : public Loader {
public:
	LoaderTimer(const CHAR* aFileName) {
		mFileName = aFileName;
	}

public:
	void Load() override {
		Sleep lSleep;

		for (u32 i = 0; i < 3; i++) {
			lSleep.SleepSecond(1);
			CPOT_LOG("Loading:", mFileName.Get());
		}
	}
	void Finish() override {
		CPOT_LOG("LoadFinish", mFileName.Get());
	}
public:
	String<128> mFileName;
};


class LoaderTimerHurry : public LoaderTimer {
public:
	LoaderTimerHurry(const CHAR* aFileName) : LoaderTimer(aFileName) {}

	BOOL IsHurry() const override {
		return true;
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

	//ロードを開始する
	#pragma region Start

public:
	//ローダスレッドを起動する
	void Start(u32 aThreadNum) {
		//指定された引数分のスレッドを起動する
		for (u32 i = 0; i < aThreadNum; i++) {
			SetEnd(i, false);
			mThread[i].Start(Load, (u32*)i);
		}
	}

	//ローダスレッドの数を、指定された数にする
	void Resize(u32 aThreadNum) {
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			//起動予定のスレッドなら
			if (i < aThreadNum) {
				SetEnd(i, false);
				mThread[i].Start(Load, (u32*)i);
			}
			//停止予定のスレッドなら
			if (i >= aThreadNum) {
				SetEnd(i, true);
			}
		}
	}

	#pragma endregion


	//ロードを停止する
	#pragma region Stop

public:
	//ローダスレッドを終了する
	void Stop() {

		//全スレッドの終了
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			SetEnd(i, true);
		}
	}

	//ローダスレッドを終了して、待つ
	void Join() {

		//全スレッドの終了
		Stop();

		//全スレッドの合流を待つ
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			mThread[i].Join();
		}
	}

	#pragma endregion


	//現在登録されているローダを全てクリアする
	#pragma region Clear

	void Clear() {
		Join();
		Delete(mLoaderListNormal);
		Delete(mLoaderListHurry);
		Delete(mLoaderListFinish);
		mNowLoadingCount = 0;
	}

	#pragma endregion


	//別スレッドで実行されて、読み込む
	#pragma region Load

private:
	static Loader* GetLoader() {

		Loader* l = nullptr;

		MutexLocker m0(S().mLoaderListNormalMutex);
		MutexLocker m1(S().mLoaderListHurryMutex);

		//もし急ぎのローダが存在するなら
		if (S().mLoaderListHurry.GetSize() != 0) {
			//一番後ろのローダを取得する
			l = S().mLoaderListHurry.PopBack();
			S().LoadStart();	//ロード開始
		}
		//もし通常のローダが存在するなら
		else if (S().mLoaderListNormal.GetSize() != 0) {
			//一番後ろのローダを取得する
			l = S().mLoaderListNormal.PopBack();
			S().LoadStart();	//ロード開始
		}

		return l;
	}
	static void Load(u32* aThreadIndex) {

		Sleep lSleep;

		u32 lThreadIndex = (u32)aThreadIndex;

		while (true) {

			Loader* l = GetLoader();

			//もしローダを取得できていたら
			if (l) {

				l->Load();	//ロードする

				//ロードが終了したリストに入れる
				MutexLocker m(S().mLoaderListFinishMutex);
				S().mLoaderListFinish.PushBack(l);

				S().LoadEnd();	//ロード終了
			}
			//もしローダが存在しないなら
			else {
				lSleep.SleepSecond(0.1f);	//少し休む
			}

			//スレッドを終了するなら
			if (S().GetEnd(lThreadIndex) == true) {
				break;	//ループを抜ける
			}
		}
	}

	#pragma endregion


	//Loaderを登録する
	#pragma region Regist

public:
	void Regist(Loader* aLoader) {
		if (aLoader->IsHurry()) {
			RegistLoaderHurry(aLoader);
		}
		else {
			RegistLoaderNormal(aLoader);
		}
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


	//更新。終了したLoaderのFinish()を呼び出す
	#pragma region Update

public:
	void Update() {
		MutexLocker m(mLoaderListFinishMutex);
		for (u32 i = 0; i < mLoaderListFinish.GetSize(); i++) {
			mLoaderListFinish[i]->Finish();
		}
		Delete(mLoaderListFinish);
	}

	#pragma endregion


	//ロード中かどうか
	#pragma region IsLoading

public:
	BOOL IsLoading() {
		//LoaderListにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListNormalMutex);
			if (mLoaderListNormal.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListHurryにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListHurryMutex);
			if (mLoaderListHurry.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListFinishにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListFinishMutex);
			if (mLoaderListFinish.GetSize() != 0) {
				return true;
			}
		}

		//NowLoadingCountが1以上ならロード中
		{
			MutexLocker m(mNowLoadingCountMutex);
			if (mNowLoadingCount >= 1) {
				return true;
			}
		}

		//どの条件にも当てはまらないなら、ロード中ではない
		return false;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

	//LoaderListとMutex
	#pragma region LoaderList & Mutex

private:
	Vector<Loader*> mLoaderListNormal;
	Vector<Loader*> mLoaderListHurry;
	Vector<Loader*> mLoaderListFinish;

	Mutex mLoaderListNormalMutex;
	Mutex mLoaderListHurryMutex;
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


	//現在ロードしている数
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


	//Vectorの要素のデリート
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