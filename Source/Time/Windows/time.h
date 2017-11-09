//
//	���ԂɊւ���N���X���W�߂�
//

#pragma once

#include "./Time/time.h"

#include "./Time/Standard/time.h"


namespace cpot {

namespace windows {


//�ז��Ȏ��Ԃ��擾�ł���f�o�C�X
#pragma region DetailTime

class DetailTimeDevice {

public:
	//�ז��Ȏ��ԁi�J�E���g�j
	static u64 GetCount();

	//��b�ɉ��J�E���g������̂�
	static u64 GetTimeUnit();

	//�ז��Ȏ��ԁi�b�j
	static f64 Get() {
		return (f64)(GetCount()) / GetTimeUnit();
	}
};

#pragma endregion



//���Ԃ��擾
#pragma region Time

class Time : public TimeBase {

public:
	//���j�b�N�X�^�C�����擾
	UnixTimeType GetUnix() const CPOT_OR {
		return standard::UnixTimeDevice::Get();	//standard�̊֐��ɈϏ�
	}

	//�ז��Ȏ��Ԃ��擾
	f64 GetDetail() const CPOT_OR {
		return DetailTimeDevice::Get();
	}
};

#pragma endregion


}


//���̃v���O�����ł́ATime�N���X��windows::Time���g���悤�ɂ���
using Time = windows::Time;

}
