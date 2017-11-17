/*
* Copyright (C) 2010 The Android Open Source Project
*
* Apache License Version 2.0 (�u�{���C�Z���X�v) �Ɋ�Â��ă��C�Z���X����܂��B;
* �{���C�Z���X�ɏ������Ȃ��ꍇ�͂��̃t�@�C�����g�p�ł��܂���B
* �{���C�Z���X�̃R�s�[�́A�ȉ��̏ꏊ�������ł��܂��B
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* �K�p�����@�߂܂��͏��ʂł̓��ӂɂ���Ė������Ȃ�����A�{���C�Z���X�Ɋ�Â��ĔЕz�����\�t�g�E�F�A�́A
* �����َ����킸�A�����Ȃ�ۏ؂��������Ȃ��Ɍ���̂܂�
* �Еz����܂��B
* �{���C�Z���X�ł̌����Ɛ������K�肵���������ẮA
* �{���C�Z���X���Q�Ƃ��Ă��������B
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
* �ۑ���Ԃ̃f�[�^�ł��B
*/
struct saved_state {
	cpot::f32 x;
	cpot::f32 y;
};


// �f�B�X�v���C���̌��݂̃t���[���̂݁B
void engine_draw_frame(struct engine* engine) {
	if (engine->display == NULL) {
		// �f�B�X�v���C������܂���B
		return;
	}

	// �F�ŉ�ʂ�h��Ԃ��܂��B
	glClearColor((cpot::android::Application::S().GetEngine()->State<saved_state>()->x) / engine->width, 1.0f,
		(cpot::android::Application::S().GetEngine()->State<saved_state>()->y) / engine->height, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	eglSwapBuffers(engine->display, engine->surface);
}

/**
* ����́Aandroid_native_app_glue ���g�p���Ă���l�C�e�B�u �A�v���P�[�V����
* �̃��C�� �G���g�� �|�C���g�ł��B���ꎩ�̂̃X���b�h�ŃC�x���g ���[�v�ɂ���Ď��s����A
* ���̓C�x���g���󂯎�����葼�̑�������s�����肵�܂��B
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
	// ���[�v�̓X�^�b�t�ɂ��J�n��҂��Ă��܂��B

	cpot::f64 lBeforeTime = lTime.GetDetail();

	while (1) {
		
		if (cpot::android::Application::S().IsAnimate()) {
			
			//���͂̍X�V
			cpot::android::Input::S().Update();

			//���[�_�̍X�V
			//cpot::LoaderManager::S().Update();

			//
			if (cpot::Input::GetButton(cpot::android::cTouch)) {
				cpot::android::Application::S().GetEngine()->State<saved_state>()->x = cpot::Input::GetValue(cpot::android::cTouchPosX);
				cpot::android::Application::S().GetEngine()->State<saved_state>()->y = cpot::Input::GetValue(cpot::android::cTouchPosY);
			}

			//�Q�[���̍X�V
			lGame->Update();

			//�Q�[���̕`��
			lGame->Render();

			//
			engine_draw_frame(cpot::android::Application::S().GetEngine());


			//DeltaTime�̌v��
			#pragma region DeltaTime

			cpot::f64 lNowTime = lTime.GetDetail();

			//DeltaTime�́A�ő�ł�Fps����̌v�Z�l�̓�{�܂łƂ���
			cpot::SetDeltaTime(cpot::Min(lNowTime - lBeforeTime, 2.0f / cpot::Config::S().GetFps()));

			lBeforeTime = lNowTime;

			#pragma endregion
		}
	}
}
