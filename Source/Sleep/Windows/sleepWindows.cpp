//
//	��莞�ԃX���b�h���~�߂�A�X���[�v�N���X�̎���
//

#include "./Sleep/Windows/sleep.h"

#include <Windows.h>


namespace cpot {

namespace windows {

void SleepDevice::SleepSecond(f32 aSecond) {

	f32 lMilliSecond = aSecond * 1000.0f;
	::Sleep(lMilliSecond);
}


}

}