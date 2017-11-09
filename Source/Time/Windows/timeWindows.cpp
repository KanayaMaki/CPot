//
//	���ԂɊւ���N���X
//


#include "./Time/Windows/time.h"

#include <Windows.h>

namespace cpot {

namespace windows {

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

}


//DateTime�̎���
#pragma region DateTime

//���݂̓������擾����
DateTimeData DateTime::Get() {
	UnixTimeType lNowTime = standard::UnixTimeDevice::Get();
	return standard::DateTimeDevice::ToDateTime(lNowTime);
}

//UnixTime�����݂̓����ɕϊ�����
DateTimeData DateTime::ToDateTime(UnixTimeType aUnixTime) {
	return standard::DateTimeDevice::ToDateTime(aUnixTime);
}

#pragma endregion

}
