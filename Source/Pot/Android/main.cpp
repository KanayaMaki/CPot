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

#include "./Pot/Game/game.h"


/**
* 保存状態のデータです。
*/
struct saved_state {
	cpot::f32 x;
	cpot::f32 y;
};


// ディスプレイ内の現在のフレームのみ。
void engine_draw_frame(struct engine* engine) {
	if (engine->display == NULL) {
		// ディスプレイがありません。
		return;
	}

	// 色で画面を塗りつぶします。
	glClearColor((cpot::android::Application::S().GetEngine()->State<saved_state>()->x) / engine->width, 1.0f,
		(cpot::android::Application::S().GetEngine()->State<saved_state>()->y) / engine->height, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	eglSwapBuffers(engine->display, engine->surface);
}

/**
* これは、android_native_app_glue を使用しているネイティブ アプリケーション
* のメイン エントリ ポイントです。それ自体のスレッドでイベント ループによって実行され、
* 入力イベントを受け取ったり他の操作を実行したりします。
*/
void android_main(struct android_app* state) {

	cpot::GameBase* lGame = cpot::CreateGame();
	lGame->Setting();

	saved_state lSavedState;

	cpot::android::Application::S().Load(state);
	cpot::android::Application::S().GetEngine()->state.Load<saved_state>(lSavedState);
	cpot::android::Input::S().Init();

	cpot::Time lTime;
	cpot::SetDeltaTime(1.0f / cpot::Config::S().GetFps());


	lGame->Init();
	// ループはスタッフによる開始を待っています。

	cpot::f64 lBeforeTime = lTime.GetDetail();

	while (1) {
		
		if (cpot::android::Application::S().IsAnimate()) {
			
			//入力の更新
			cpot::android::Input::S().Update();

			//ローダの更新
			//cpot::LoaderManager::S().Update();

			//
			if (cpot::Input::GetButton(cpot::android::cTouch)) {
				cpot::android::Application::S().GetEngine()->State<saved_state>()->x = cpot::Input::GetValue(cpot::android::cTouchPosX);
				cpot::android::Application::S().GetEngine()->State<saved_state>()->y = cpot::Input::GetValue(cpot::android::cTouchPosY);
			}

			//ゲームの更新
			lGame->Update();

			//ゲームの描画
			lGame->Render();

			//
			engine_draw_frame(cpot::android::Application::S().GetEngine());


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
