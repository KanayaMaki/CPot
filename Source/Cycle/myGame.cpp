//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"

#include "./Pot/Out/out.h"
#include "./Pot/Config/config.h"

#include "./Pot/Input/input.h"
#include "./Pot/Audio/audio.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Rand/rand.h"

namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}


class LoaderTimer : public Loader {
public:
	LoaderTimer(const CHAR* aFileName) {
		mFileName = aFileName;
		mTakeTime = 3.0f;
	}
	LoaderTimer(const CHAR* aFileName, f32 aTakeTime) {
		mFileName = aFileName;
		mTakeTime = aTakeTime;
	}

public:
	void Start() override {
		CPOT_LOG("LoadStart:", mFileName.Get());
	}
	void Load() override {

		CPOT_LOG("Loading:", mFileName.Get());

		Sleep lSleep;
		lSleep.SleepSecond(mTakeTime);
	}
	void Finish() override {
		CPOT_LOG("LoadFinish:", mFileName.Get());
	}
public:
	String<128> mFileName;
	f32 mTakeTime;
};

class LoaderTimerHurry : public LoaderTimer {
public:
	LoaderTimerHurry(const CHAR* aFileName) : LoaderTimer(aFileName) {}
	LoaderTimerHurry(const CHAR* aFileName, f32 aTakeTime) : LoaderTimer(aFileName, aTakeTime) {}

	BOOL IsHurry() const override {
		return true;
	}
};
class LoaderGenerate : public Loader {
public:
	void Load() override {

		LoaderManager::S().Regist(new LoaderTimer("Generated", 2.0f));
		CPOT_LOG("LoaderGenerateLoading");

		Sleep lSleep;
		lSleep.SleepSecond(2.0f);
	}

	BOOL IsHurry() const override {
		return true;
	}
};


}

using namespace cpot;

namespace myspc {


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
	cpot::Config::S().SetTitle("MyGame!");
}

//ゲームの初期化
void MyGame::Init() {
	CPOT_LOG("Init!");

	//Loaderのスタート
	LoaderManager::S().Start(2);
}



//ゲームの更新
void MyGame::Update() {
	static cpot::u32 i = 0;
	i++;
	//CPOT_LOG("Update! : ", i);

	//ゲーム終了
	if (Input::GetButtonUp(windows::c0)) {
		Config::S().SetGameEnd();
	}

	//サウンド
	if (Input::GetButtonUp(windows::c1)) {
		auto a = new AudioClip;
		a->Load("./test.wav");

		auto c = new AudioVoice;
		c->Load(*a);

		c->Play();
	}

	static cpot::BOOL lLoading = false;

	//ローダ
	if (Input::GetButtonUp(windows::c2)) {
		lLoading = true;

		Rand r;

		for (u32 i = 0; i < 10; i++) {
			//LoaderManager::S().Regist(new LoaderTimer(ToString::Do(i), r.Nextf(2.0f, 5.0f)));
		}
		for (u32 i = 0; i < 10; i++) {
			LoaderManager::S().Regist(new LoaderGenerate);
		}
	}

	if (lLoading == true) {
		if (!LoaderManager::S().IsLoading()) {
			lLoading = false;
			Config::S().SetTitle("FinishLoading");
		}
	}

}

}