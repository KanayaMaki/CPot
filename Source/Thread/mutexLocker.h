//
//	content	:	Mutex�����S�Ɏg�p�ł���N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./Thread/mutex.h"

namespace cpot {

class MutexLocker {
public:
	MutexLocker(Mutex& aMutex) : mMutex(aMutex) {
		mMutex.Lock();
	}
	~MutexLocker() {
		mMutex.Unlock();
	}

	Mutex& mMutex;
};

}