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
#include "./Pot/Time/time.h"

#include "./Pot/Animation/animation.h"


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

Animation<f32> v;

//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
	cpot::Config::S().SetTitle("MyGame!");
}

//ゲームの初期化
void MyGame::Init() {
	//CPOT_LOG("Init!");

	//Loaderのスタート
	LoaderManager::S().Start(2);

	v.Add(0.0f, 0.0f);
	v.Add(2.0f, 0.5f);
	v.Add(4.0f, 1.0f);
	v.SetIsLoop(true);
}


//ゲームの更新
void MyGame::Update() {
	
	//ゲーム終了
	#pragma region GameEnd

	if (Input::GetButtonUp(windows::c0)) {
		Config::S().SetGameEnd();
	}

	#pragma endregion


	//サウンド
	#pragma region Audio

	if (Input::GetButtonUp(windows::c1)) {
		auto a = new AudioClip;
		a->Load("./test.wav");

		auto c = new AudioVoice;
		c->Load(*a);

		c->Play();
	}

	#pragma endregion


	///*
	//ローダ
	#pragma region Loader

	static cpot::BOOL lLoading = false;

	if (Input::GetButtonUp(windows::c2)) {
		lLoading = true;

		Rand r;

		for (u32 i = 0; i < 10; i++) {
			LoaderManager::S().Regist(new LoaderTimer(ToString::Do(i), r.Nextf(2.0f, 5.0f)));
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

	#pragma endregion


	//アニメーション
	#pragma region Animation

	if (Input::GetButton(windows::c3)) {
		v.ForwardTime(DeltaTime());
		CPOT_LOG(v.Get());
	}

	#pragma endregion


	//*/

	/*
	if (cpot::Input::GetButton(cpot::android::cTouch)) {
		cpot::android::Config::S().color.r = cpot::Input::GetValue(cpot::android::cTouchPosX);
		cpot::android::Config::S().color.b = cpot::Input::GetValue(cpot::android::cTouchPosY);
	}

	v.ForwardTime(DeltaTime());
	//cpot::android::Config::S().color.g = v.Get();
	v.Get();
	CPOT_LOG(v.Get());

	//*/
}

}