//
//	��莞�ԃX���b�h���~�߂�A�X���[�v�N���X�̎���
//

#pragma once

#include "./Sleep/sleep.h"
#include "./Usefull/singleton.h"

#include <unistd.h>

namespace cpot {

namespace android {


//	�X���[�v�̋@�\��񋟂���N���X
class SleepDevice : public Singleton<SleepDevice> {

public:
	void SleepSecond(f32 aSecond) {
		timespec t;

		u64 lNanoSec = aSecond * 1000.0f * 1000.0f * 1000.0f;
		t.tv_sec = lNanoSec / 1000000000;
		t.tv_nsec = lNanoSec % 1000000000;
		::nanosleep(&t, nullptr);
	}
};


//	�X���[�v�N���X
class Sleep : public SleepBase {

public:
	void SleepSecond(f32 aSecond) override {
		SleepDevice::S().SleepSecond(aSecond);
	}
};


}

//	�v���O�������ł́A����Sleep���g�p����
using Sleep = android::Sleep;

}