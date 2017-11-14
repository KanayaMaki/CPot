//
//	content	:	��莞�ԃX���b�h���~����N���X�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


class SleepBase {
public:
	//�w�肳�ꂽ�b���A���̃X���b�h�̎��s���~�߂�
	virtual void SleepSecond(f32 aSecond) = 0;
};


}


#ifdef CPOT_ON_WINDOWS
#include "./Sleep/Windows/sleepWindows.h"
#elif defined CPOT_ON_ANDROID
#include "./Sleep/Android/sleepAndroid.h"
#endif