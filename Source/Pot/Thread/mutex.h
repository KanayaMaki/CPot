//
//	content	:	�X���b�h�Ԃł̔r��������\�ɂ���N���X�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"


namespace cpot {


class MutexBase {
public:
	CPOT_VI void Lock() CPOT_ZR;
	CPOT_VI void Unlock() CPOT_ZR;
};


}


//�f�o�C�X���Ƃ�Mutex�̐錾
#ifdef CPOT_ON_WINDOWS
#include "./Pot/Thread/Standard/mutexStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Thread/Android/mutexAndroid.h"
#endif