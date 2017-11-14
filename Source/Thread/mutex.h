//
//	content	:	�X���b�h�Ԃł̔r��������\�ɂ���N���X�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Atom/atom.h"


namespace cpot {


class MutexBase {
public:
	CPOT_VI void Lock() CPOT_ZR;
	CPOT_VI void Unlock() CPOT_ZR;
};


}


//�f�o�C�X���Ƃ�Mutex�̐錾
#ifdef CPOT_ON_WINDOWS
#include "./Thread/Standard/mutexStandard.h"
#endif