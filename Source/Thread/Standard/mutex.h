//
//	StandardŠÂ‹«‰º‚Å‚ÌMutex‚ÌŽÀ‘•
//


#pragma once

#include "./Atom/atom.h"
#include "./Thread/mutex.h"

#include <mutex>


namespace cpot {

namespace standard {


class Mutex : public MutexBase {
public:
	void Lock() CPOT_OR {
		mMutex.lock();
	}
	void Unlock() CPOT_OR {
		mMutex.unlock();
	}

private:
	std::mutex mMutex;
};


}

using Mutex = standard::Mutex;

}

#include "./Thread/mutexLocker.h"