/*
* Copyright (C) 2010 The Android Open Source Project
*
* Apache License Version 2.0 (「本ライセンス」) に基づいてライセンスされます。;
* 本ライセンスに準拠しない場合はこのファイルを使用できません。
* 本ライセンスのコピーは、以下の場所から入手できます。
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* 適用される法令または書面での同意によって命じられない限り、本ライセンスに基づいて頒布されるソフトウェアは、
* 明示黙示を問わず、いかなる保証も条件もなしに現状のまま
* 頒布されます。
* 本ライセンスでの権利と制限を規定した文言ついては、
* 本ライセンスを参照してください。
*
*/


#include "./Pot/Application/Android/android_native_app_glue.h"
#include "./Pot/Application/Android/applicationAndroid.h"

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/Android/outLogAndroid.h"
#include "./Pot/Input/Android/inputAndroid.h"
#include "./Pot/Input/input.h"

#include "./Pot/Time/time.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Thread/thread.h"
#include "./Pot/Thread/mutex.h"

#include "./Pot/File/file.h"

#include "./Pot/Game/game.h"


/**
* 保存状態のデータです。
*/
struct saved_state {
	cpot::f32 x;
	cpot::f32 y;
};


/**
* これは、android_native_app_glue を使用しているネイティブ アプリケーション
* のメイン エントリ ポイントです。それ自体のスレッドでイベント ループによって実行され、
* 入力イベントを受け取ったり他の操作を実行したりします。
*/


void android_main(struct android_app* state) {

	cpot::FileOut f;
	f.Open("./test.txt", false, false);
	f.Write("testです");

	cpot::GameBase* lGame = cpot::CreateGame();
	lGame->Setting();

	saved_state lSavedState;

	cpot::android::Application::S().Load(state);
	cpot::android::Application::S().GetEngine()->state.LoadData<saved_state>(lSavedState);
	cpot::android::Input::S().Init();

	cpot::Time lTime;
	cpot::SetDeltaTime(1.0f / cpot::Config::S().GetFps());


	lGame->Init();
	// ループはスタッフによる開始を待っています。

	cpot::f64 lBeforeTime = lTime.GetDetail();

	while (1) {
		
		cpot::android::Application::S().MessageLoop();

		if (cpot::android::Application::S().IsAnimate()) {
			
			//入力の更新
			cpot::android::Input::S().Update();

			//ローダの更新
			cpot::LoaderManager::S().Update();

			//ゲームの更新
			lGame->Update();

			//ゲームの描画
			lGame->Render();


			//DeltaTimeの計測
			#pragma region DeltaTime

			cpot::f64 lNowTime = lTime.GetDetail();

			//DeltaTimeは、最大でもFpsからの計算値の二倍までとする
			cpot::SetDeltaTime(cpot::Min(lNowTime - lBeforeTime, 2.0f / cpot::Config::S().GetFps()));

			lBeforeTime = lNowTime;

			#pragma endregion
		}
	}
}
