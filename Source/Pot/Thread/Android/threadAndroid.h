//
//	content	:	Standard‚Å‚ÌThread‚ÌŽÀ‘•
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/thread.h"

#include <pthread.h>


namespace cpot {

namespace android {


class Thread : public ThreadBase {
public:
	Thread() {
		mIsStarted = false;
	}

public:
	void Start(ThreadFunc aFunc, void* aData) CPOT_OR {
		if (IsStarted()) {
			return;
		}
		pthread_create(&mThread, nullptr, aFunc, aData);
		mIsStarted = true;
	}
	template <typename T>
	void Start(ThreadFuncTmp<T> aFunc, T* aData) {
		Start((ThreadFunc)aFunc, (void*)aData);
	}
	template <typename T>
	void Start(ThreadFuncTmp<T> aFunc, std::nullptr_t aNull) {
		Start((ThreadFunc)aFunc, (void*)aNull);
	}

	void Detach() CPOT_OR {
		if (!IsStarted()) {
			return;
		}
		pthread_detach(mThread);
		mIsStarted = false;
	}
	void Join() CPOT_OR {
		if (!IsStarted()) {
			return;
		}
		pthread_join(mThread, nullptr);
		mIsStarted = false;
	}

	BOOL IsStarted() CPOT_OR {
		return mIsStarted;
	}

public:
	pthread_t mThread;
	BOOL mIsStarted;
};


}

//Android‚ÌThread‚ðŽg—p
using Thread = android::Thread;

}