//
//	content	:	Android‚Å‚ÌMutex‚ÌŽÀ‘•
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/mutex.h"

#include <pthread.h>


namespace cpot {

namespace android {


class Mutex : public MutexBase {
public:
	Mutex() {
		pthread_mutex_init(&mMutex, NULL);
	}

public:
	void Lock() CPOT_OR {
		pthread_mutex_lock(&mMutex);
	}
	void Unlock() CPOT_OR {
		pthread_mutex_unlock(&mMutex);
	}

private:
	pthread_mutex_t mMutex;
};


}

//Android‚ÌMutex‚ðŽg—p
using Mutex = android::Mutex;

}

#include "./Pot/Thread/mutexLocker.h"