//
//	content	:	���ԂɊւ���N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


//�Q�[�����̎��Ԃ̒P�ʁATick�̒�`
#pragma region Tick


using TickType = u64;
const TickType cTickUnit = 1200000UL;	//1�b����Tick��

//�b���`�b�N��
inline TickType ToTick(f32 aSecond) {
	return static_cast<TickType>( aSecond * cTickUnit );
}

//�`�b�N��b��
inline f32 ToSecond(TickType aTick) {
	return static_cast<f32>( (f64)aTick / cTickUnit );
}


#pragma endregion


//�O�̃t���[������̌o�ߎ���
#pragma region DeltaTime

//�o�ߎ��Ԃ�b�Ŏ擾
f32 DeltaTime();

//�o�ߎ��Ԃ��`�b�N�Ŏ擾
TickType DeltaTick();

//�o�ߎ��Ԃ�ݒ�
void SetDeltaTick(TickType aDeltaTick);
void SetDeltaTime(f32 aDeltaTime);

#pragma endregion


using UnixTimeType = s64;


//����
#pragma region DateTime

struct DateTimeData {
	s32 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
	enum CYoubi : u8 {
		cSunday,
		cMonday,
		cTuesday,
		cWednesday,
		cThursday,
		cFriday,
		cSaturday,
	} youbi;

};


class DateTime {

public:
	//���݂̓������擾����
	DateTimeData Get();

	//UnixTime�����݂̓����ɕϊ�����
	DateTimeData ToDateTime(UnixTimeType aUnixTime);
};



#pragma endregion


//���Ԃ��擾
#pragma region Time

class TimeBase {
public:
	//���j�b�N�X�^�C�����擾
	CPOT_VI UnixTimeType GetUnix() const CPOT_ZR;

	//�ז��Ȏ��Ԃ��擾
	CPOT_VI f64 GetDetail() const CPOT_ZR;
};

#pragma endregion


}


#ifdef CPOT_ON_WINDOWS
#include "./Time/Windows/timeWindows.h"
#elif defined CPOT_ON_ANDROID
#include "./Time/Android/timeAndroid.h"
#endif