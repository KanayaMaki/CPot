//
//	content	:	ウィンドウズのウィンドウの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"

#include "./Pot/Config/config.h"
#include "./Pot/Application/Android/android_native_app_glue.h"

#include "./Pot/Out/out.h"
#include "./Pot/Usefull/buffer.h"

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatformAndroid.h"


/**
* アプリの保存状態です。
*/
struct engine {
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	cpot::Buffer state;

	template<typename T>
	T* State() {
		return (T*)(state.Get());
	}
};

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", __VA_ARGS__))


namespace cpot {

namespace android {

class Application : public Singleton<Application> {
	friend class Singleton<Application>;


	//コンストラクタなど
	#pragma region Constructor

private:
	//ユーザからはnewできず、deleteもできない
	Application() {
		mState = nullptr;
	}
	~Application() {
		Release();
	}

	#pragma endregion


	//初期化
	#pragma region Load

public:
	void Load(android_app* aState) {
		mState = aState;

		memset(&mEngine, 0, sizeof(mEngine));
		mState->userData = &mEngine;
		mState->onAppCmd = engine_handle_cmd;
		mEngine.app = mState;

		// 加速度計の監視の準備
		mEngine.sensorManager = ASensorManager_getInstance();
		mEngine.accelerometerSensor = ASensorManager_getDefaultSensor(mEngine.sensorManager,
			ASENSOR_TYPE_ACCELEROMETER);
		mEngine.sensorEventQueue = ASensorManager_createEventQueue(mEngine.sensorManager,
			mState->looper, LOOPER_ID_USER, NULL, NULL);

		if (mState->savedState != NULL) {
			// 以前の保存状態で開始します。復元してください。
			//mEngine.state = *(struct saved_state*)mState->savedState;
		}

		mEngine.animating = 1;
	}

	#pragma endregion


	//終了
	#pragma region Release

private:
	void Release() {}

	#pragma endregion


	//イベントを取得する
	#pragma region Event

public:
	void MessageLoop() {

		// 保留中のすべてのイベントを読み取ります。
		int ident;
		int events;
		struct android_poll_source* source;

		// アニメーションしない場合、無期限にブロックしてイベントが発生するのを待ちます。
		// アニメーションする場合、すべてのイベントが読み取られるまでループしてから続行します
		// アニメーションの次のフレームを描画します。
		while ((ident = ALooper_pollAll(mEngine.animating ? 0 : -1, NULL, &events,
			(void**)&source)) >= 0) {

			// このイベントを処理します。
			if (source != NULL) {
				source->process(mState, source);
			}

			// センサーにデータがある場合、今すぐ処理します。
			if (ident == LOOPER_ID_USER) {
				if (mEngine.accelerometerSensor != NULL) {
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(mEngine.sensorEventQueue,
						&event, 1) > 0) {
						LOGI("accelerometer: x=%f y=%f z=%f",
							event.acceleration.x, event.acceleration.y,
							event.acceleration.z);
					}
				}
			}

			// 終了するかどうか確認します。
			if (mState->destroyRequested != 0) {
				engine_term_display(&mEngine);
				return;
			}
		}

	}


	#pragma region Handler
private:

	// 現在の表示の EGL コンテキストを初期化します。
	static int engine_init_display(struct engine* engine) {
		engine->animating = 1;
		cpot::openGL::platform::Device::S().Init(engine->app->window);
		return 0;
	}

	// 現在ディスプレイに関連付けられている EGL コンテキストを削除します。
	static void engine_term_display(struct engine* engine) {
		cpot::openGL::platform::Device::S().Final();
		engine->animating = 0;
	}

	// 次のメイン コマンドを処理します。
	static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
		struct engine* engine = (struct engine*)app->userData;
		switch (cmd) {
			case APP_CMD_SAVE_STATE:
				// 現在の状態を保存するようシステムによって要求されました。保存してください。
				//engine->app->savedState = malloc(sizeof(struct saved_state));
				//*((struct saved_state*)engine->app->savedState) = engine->state;
				//engine->app->savedStateSize = sizeof(struct saved_state);
				break;
			case APP_CMD_INIT_WINDOW:
				// ウィンドウが表示されています。準備してください。
				if (engine->app->window != NULL) {
					engine_init_display(engine);
				}
				break;
			case APP_CMD_TERM_WINDOW:
				// ウィンドウが非表示または閉じています。クリーン アップしてください。
				engine_term_display(engine);
				break;
			case APP_CMD_GAINED_FOCUS:
				// アプリがフォーカスを取得すると、加速度計の監視を開始します。
				if (engine->accelerometerSensor != NULL) {
					ASensorEventQueue_enableSensor(engine->sensorEventQueue,
						engine->accelerometerSensor);
					// 目標は 1 秒ごとに 60 のイベントを取得することです (米国)。
					ASensorEventQueue_setEventRate(engine->sensorEventQueue,
						engine->accelerometerSensor, (1000L / 60) * 1000);
				}
				break;
			case APP_CMD_LOST_FOCUS:
				// アプリがフォーカスを失うと、加速度計の監視を停止します。
				// これにより、使用していないときのバッテリーを節約できます。
				if (engine->accelerometerSensor != NULL) {
					ASensorEventQueue_disableSensor(engine->sensorEventQueue,
						engine->accelerometerSensor);
				}
				// また、アニメーションを停止します。
				engine->animating = 0;
				break;
		}
	}

	#pragma endregion

	#pragma endregion


	//値を取得する
	#pragma region Getter

public:
	BOOL GetFocus() const {
		return mFocus;
	}
	android_app* GetState() {
		return mState;
	}
	engine* GetEngine() {
		return &mEngine;
	}

	BOOL IsAnimate() const {
		return mEngine.animating != 0;
	}

	BOOL IsLoaded() const {
		return NotNull(mState);	//mHwndがnullでないならロード済み
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	android_app* mState;
	BOOL mFocus;
	struct engine mEngine;

	#pragma endregion
};


}

}
