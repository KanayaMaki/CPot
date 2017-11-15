#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Sleep/sleep.h"
#include "./Pot/Time/time.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


class Fps : public Singleton<Fps> {

public:
	void Init(Time* aTime, Sleep* aSleep, f32 aTargetFps, s32 aSampleNum = 60);
	void Reset(f32 aTargetFps, s32 aSampleNum);
	void Restart();

public:
	void Update();
private:
	void Wait();	//�����Ŏ��Ԃ��v�Z���҂�

public:
	f32 MaxFps() const { return mMaxFps; }
	f32 NowFps() const { return mNowFps; }
	f64 DeltaTime() const { return mDeltaTime; }

	BOOL OverTime() const { return mOverTime; }
	BOOL CanRender() const {
		if (!mBeforeOverTime) {
			if (mOverTime) {
				return false;
			}
		}
		return true;
	}


private:
	Time* mTime;
	Sleep* mSleep;

private:
	f32 mTargetFps;	//fps�����̐��ɂȂ�悤�ɏ���
	s32 mSampleNum;	//����̃��[�v�����Ƃ�fps���v�Z���邩

	f64 mBeforeTime;	//�ȑO�̎��Ԃ��i�[
	f64 mStartTime;	//�J�n�������Ԃ��i�[

	f32 mNowFps;	//�v�Z���ċ��߂�fps�l���i�[�B�l�́Acount�̈�������ƂɍX�V
	s32 mCount;	//���݉���ڂ��BNUM_OF_SAMPLE�����ŉ��

	f64 mDeltaTime;	//�O�񂩂�o�߂�������
	BOOL mOverTime;	//�����ɂP�t���[���̎��Ԉȏォ���������ǂ���
	BOOL mBeforeOverTime;	//�O�̃t���[���ŁA�����ɂP�t���[���̎��Ԉȏォ���������ǂ���

	f64 mTotalWaitTime;	//numOfSample_m�����ŁA�ҋ@�������Ԃ𑫂��Ă���
	f32 mMaxFps;	//�ҋ@�������������ɂǂ�قǂ�fps���o����
};


}
