#include "./Pot/Fps/fps.h"


namespace cpot {


void Fps::Init(Time* aTime, Sleep* aSleep, f32 aTargetFps, s32 aSampleNum) {
	mTime = aTime;
	mSleep = aSleep;

	Reset(aTargetFps, aSampleNum);
}


void Fps::Reset(f32 aTargetFps, s32 aSampleNum) {

	mTargetFps = aTargetFps;
	mSampleNum = aSampleNum;
	mNowFps = mTargetFps;
	mCount = 0L;
	mOverTime = false;
	mBeforeOverTime = false;
	mMaxFps = mTargetFps;
	mTotalWaitTime = 0.0;
}

void Fps::Restart() {
	mStartTime = mTime->GetDetail();
	mBeforeTime = mTime->GetDetail();
}



void Fps::Update() {

	Wait();	//60fps��ۂ��߂ɑ҂�

	//�����J�E���g�������ɂȂ�����
	if (mCount == mSampleNum) {
		f64 lEndTime = mTime->GetDetail();

		f64 lRealTakeTime = lEndTime - mStartTime;	//���ۂɂ���������������
		f64 lTargetTakeTime = ((f64)mSampleNum * cTickUnit) / mTargetFps;	//�T���v�����ԂŁA�{���Ȃ炩����Tick��
		mNowFps = lTargetTakeTime / lRealTakeTime * mTargetFps;

		if (mTotalWaitTime >= 0) {
			u64 lTrueRealTakeTime = lRealTakeTime - mTotalWaitTime;
			mMaxFps = lTargetTakeTime / lTrueRealTakeTime * mTargetFps;
		}
		else {
			mMaxFps = mNowFps;
		}
		mStartTime = lEndTime;
		mCount = 0;
		mTotalWaitTime = 0;
	}
}


void Fps::Wait() {

	mCount++;	//�t���[�����𑝂₷

	f64 lNowTime = mTime->GetDetail();	//���݂̎��Ԃ̎擾

	f64 lTakeTime = (lNowTime - mStartTime);	//�����ɂ����������Ԃ��v�Z
	f64 lWaitTime = 1.0f / mTargetFps * mCount - lTakeTime;	//Sleep���ׂ����Ԃ��v�Z

	//�t�B�[���h�Ƀf�[�^��ۑ�
	mDeltaTime = lNowTime - mBeforeTime;
	mBeforeTime = lNowTime;

	mBeforeOverTime = mOverTime;

	//Sleep
	if (lWaitTime > 0) {
		mSleep->SleepSecond(lWaitTime);
		mOverTime = false;
	}
	else {
		mOverTime = true;
	}
	mTotalWaitTime += lWaitTime;


	//DeltaTime�̐ݒ�
	SetDeltaTime(mDeltaTime);
}

}