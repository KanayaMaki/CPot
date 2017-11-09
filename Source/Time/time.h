//
//	���ԂɊւ���N���X���W�߂�
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


//�Q�[�����̎��Ԃ̒P�ʁATick�̒�`
#pragma region Tick


using TickType = u64;
const TickType cTickScale = 1200000UL;	//1�b����Tick��

//�b���`�b�N��
inline TickType ToTick(f32 aSecond) {
	return aSecond * cTickScale;
}

//�`�b�N��b��
inline f32 ToSecond(TickType aTick) {
	return (f64)aTick / cTickScale;
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

#pragma endregion



struct DateTime {
	s32 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
	enum CYoubi : u8 {
		cSunday,
	} youbi;
};



class TimeBase {
public:

};


}


#ifdef CPOT_ON_WINDOWS
//#include "./Time/Windows/sleep.h"
#elif defined CPOT_ON_ANDROID
#include "./Sleep/Android/sleep.h"
#endif