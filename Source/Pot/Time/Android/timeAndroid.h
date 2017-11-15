//
//	content	:	Android�ł̎��ԂɊւ���N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Time/time.h"

#include <chrono>


namespace cpot {

namespace android {


//���Ԃ��擾
#pragma region Time

class Time : public TimeBase {

public:
	Time() {
		//�J�n�n�_
		base = std::chrono::high_resolution_clock::now();
	}


	//���j�b�N�X�^�C�����擾
	UnixTimeType GetUnix() const CPOT_OR {
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

		std::time_t t = std::chrono::system_clock::to_time_t(p);
		return t;
	}

	//�ז��Ȏ��Ԃ��擾
	f64 GetDetail() const CPOT_OR {
		std::chrono::high_resolution_clock::time_point p = std::chrono::high_resolution_clock::now();
		
		std::chrono::nanoseconds t = std::chrono::duration_cast<std::chrono::nanoseconds>(p - base);
		return t.count() / 1000.0f / 1000.0f / 1000.0f;
	}

private:
	std::chrono::high_resolution_clock::time_point base;
};

#pragma endregion


}


//���̃v���O�����ł́ATime�N���X��windows::Time���g���悤�ɂ���
using Time = android::Time;

}
