//
// Mutex���A�R���X�g���N�^�Ń��b�N���āA�f�X�g���N�^�ŃA�����b�N����
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