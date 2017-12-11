//
//	content	:	�E�B���h�E�Y�̃E�B���h�E�̎���
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
* �A�v���̕ۑ���Ԃł��B
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


	//�R���X�g���N�^�Ȃ�
	#pragma region Constructor

private:
	//���[�U�����new�ł����Adelete���ł��Ȃ�
	Application() {
		mState = nullptr;
	}
	~Application() {
		Release();
	}

	#pragma endregion


	//������
	#pragma region Load

public:
	void Load(android_app* aState) {
		mState = aState;

		memset(&mEngine, 0, sizeof(mEngine));
		mState->userData = &mEngine;
		mState->onAppCmd = engine_handle_cmd;
		mEngine.app = mState;

		// �����x�v�̊Ď��̏���
		mEngine.sensorManager = ASensorManager_getInstance();
		mEngine.accelerometerSensor = ASensorManager_getDefaultSensor(mEngine.sensorManager,
			ASENSOR_TYPE_ACCELEROMETER);
		mEngine.sensorEventQueue = ASensorManager_createEventQueue(mEngine.sensorManager,
			mState->looper, LOOPER_ID_USER, NULL, NULL);

		if (mState->savedState != NULL) {
			// �ȑO�̕ۑ���ԂŊJ�n���܂��B�������Ă��������B
			//mEngine.state = *(struct saved_state*)mState->savedState;
		}

		mEngine.animating = 1;
	}

	#pragma endregion


	//�I��
	#pragma region Release

private:
	void Release() {}

	#pragma endregion


	//�C�x���g���擾����
	#pragma region Event

public:
	void MessageLoop() {

		// �ۗ����̂��ׂẴC�x���g��ǂݎ��܂��B
		int ident;
		int events;
		struct android_poll_source* source;

		// �A�j���[�V�������Ȃ��ꍇ�A�������Ƀu���b�N���ăC�x���g����������̂�҂��܂��B
		// �A�j���[�V��������ꍇ�A���ׂẴC�x���g���ǂݎ����܂Ń��[�v���Ă��瑱�s���܂�
		// �A�j���[�V�����̎��̃t���[����`�悵�܂��B
		while ((ident = ALooper_pollAll(mEngine.animating ? 0 : -1, NULL, &events,
			(void**)&source)) >= 0) {

			// ���̃C�x���g���������܂��B
			if (source != NULL) {
				source->process(mState, source);
			}

			// �Z���T�[�Ƀf�[�^������ꍇ�A�������������܂��B
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

			// �I�����邩�ǂ����m�F���܂��B
			if (mState->destroyRequested != 0) {
				engine_term_display(&mEngine);
				return;
			}
		}

	}


	#pragma region Handler
private:

	// ���݂̕\���� EGL �R���e�L�X�g�����������܂��B
	static int engine_init_display(struct engine* engine) {
		engine->animating = 1;
		cpot::openGL::platform::Device::S().Init(engine->app->window);
		return 0;
	}

	// ���݃f�B�X�v���C�Ɋ֘A�t�����Ă��� EGL �R���e�L�X�g���폜���܂��B
	static void engine_term_display(struct engine* engine) {
		cpot::openGL::platform::Device::S().Final();
		engine->animating = 0;
	}

	// ���̃��C�� �R�}���h���������܂��B
	static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
		struct engine* engine = (struct engine*)app->userData;
		switch (cmd) {
			case APP_CMD_SAVE_STATE:
				// ���݂̏�Ԃ�ۑ�����悤�V�X�e���ɂ���ėv������܂����B�ۑ����Ă��������B
				//engine->app->savedState = malloc(sizeof(struct saved_state));
				//*((struct saved_state*)engine->app->savedState) = engine->state;
				//engine->app->savedStateSize = sizeof(struct saved_state);
				break;
			case APP_CMD_INIT_WINDOW:
				// �E�B���h�E���\������Ă��܂��B�������Ă��������B
				if (engine->app->window != NULL) {
					engine_init_display(engine);
				}
				break;
			case APP_CMD_TERM_WINDOW:
				// �E�B���h�E����\���܂��͕��Ă��܂��B�N���[�� �A�b�v���Ă��������B
				engine_term_display(engine);
				break;
			case APP_CMD_GAINED_FOCUS:
				// �A�v�����t�H�[�J�X���擾����ƁA�����x�v�̊Ď����J�n���܂��B
				if (engine->accelerometerSensor != NULL) {
					ASensorEventQueue_enableSensor(engine->sensorEventQueue,
						engine->accelerometerSensor);
					// �ڕW�� 1 �b���Ƃ� 60 �̃C�x���g���擾���邱�Ƃł� (�č�)�B
					ASensorEventQueue_setEventRate(engine->sensorEventQueue,
						engine->accelerometerSensor, (1000L / 60) * 1000);
				}
				break;
			case APP_CMD_LOST_FOCUS:
				// �A�v�����t�H�[�J�X�������ƁA�����x�v�̊Ď����~���܂��B
				// ����ɂ��A�g�p���Ă��Ȃ��Ƃ��̃o�b�e���[��ߖ�ł��܂��B
				if (engine->accelerometerSensor != NULL) {
					ASensorEventQueue_disableSensor(engine->sensorEventQueue,
						engine->accelerometerSensor);
				}
				// �܂��A�A�j���[�V�������~���܂��B
				engine->animating = 0;
				break;
		}
	}

	#pragma endregion

	#pragma endregion


	//�l���擾����
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
		return NotNull(mState);	//mHwnd��null�łȂ��Ȃ烍�[�h�ς�
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	android_app* mState;
	BOOL mFocus;
	struct engine mEngine;

	#pragma endregion
};


}

}
