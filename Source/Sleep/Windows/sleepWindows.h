//
//	��莞�ԃX���b�h���~�߂�A�X���[�v�N���X�̎���
//

#pragma once

#include "./Sleep/sleep.h"
#include "./Usefull/singleton.h"


namespace cpot {

namespace windows {


//	�X���[�v�̋@�\��񋟂���N���X
class SleepDevice : public Singleton<SleepDevice> {

public:
	void SleepSecond(f32 aSecond);
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
using Sleep = windows::Sleep;

}