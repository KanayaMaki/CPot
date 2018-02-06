//
//	content	:	Windows�ł̎��ԂɊւ���N���X
//	author	:	SaitoYoshiki
//


#include "./Pot/Time/Windows/timeWindows.h"

#include "./Pot/Time/Standard/timeStandard.h"

#include <Windows.h>

namespace cpot {

namespace windows {


#pragma region DetailTimeDevice

u64 DetailTimeDevice::GetCount() {
	LARGE_INTEGER lTime;
	QueryPerformanceCounter(&lTime);

	return (lTime.QuadPart);
}

u64 DetailTimeDevice::GetTimeUnit() {

	static LARGE_INTEGER lUnit;
	static BOOL lIsInit = false;	//�������ς݂��̃t���O

									//����������Ă��Ȃ��Ȃ�
	if (Not(lIsInit)) {
		QueryPerformanceFrequency(&lUnit);	//������
		lIsInit = true;	//�������ς�
	}
	return lUnit.QuadPart;
}


#pragma endregion


#pragma region Time

UnixTimeType Time::GetUnix() const {
	return standard::UnixTimeDevice::Get();	//standard�̊֐��ɈϏ�
}

#pragma endregion


}


}
