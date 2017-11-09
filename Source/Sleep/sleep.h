//
//	��莞�ԃX���b�h���~�߂�A�X���[�v�N���X�̎���
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
#include "./Sleep/Windows/sleep.h"
#elif defined CPOT_ON_ANDROID
#include "./Sleep/Android/sleep.h"
#endif