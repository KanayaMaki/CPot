//
//	Thread�̃C���^�[�t�F�[�X������
//

#pragma once

#include "./Atom/atom.h"


namespace cpot {


template<typename T> using ThreadFuncTmp = void(*)(T*);
using ThreadFunc = void(*)(void*);

class ThreadBase {
public:
	CPOT_VI void Start(ThreadFunc aFunc, void* aData) CPOT_ZR;
	template <typename T>
	void Start(ThreadFuncTmp<T> aFunc, T* aData);
	CPOT_VI void Detach() CPOT_ZR;
	CPOT_VI void Join() CPOT_ZR;

	CPOT_VI BOOL IsStarted() CPOT_ZR;
};


}


//Thread��Mutex�̐錾
#ifdef CPOT_ON_WINDOWS
#include "./Thread/Standard/thread.h"
#endif