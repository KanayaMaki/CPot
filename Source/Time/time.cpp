//
//	���ԂɊւ���N���X���W�߂�
//

#include "./Time/time.h"


namespace cpot {


//�O�̃t���[������̌o�ߎ���
#pragma region DeltaTime


f32 DeltaTime() {
	return gDeltaTime;
}

TickType DeltaTick() {
	return gDeltaTick;
}

//�o�ߎ��Ԃ�ݒ�
void DeltaTick(TickType aDeltaTick) {
	gDeltaTick = aDeltaTick;
	gDeltaTime = ToSecond(aDeltaTick);
}

//�o�ߎ��Ԃ��i�[���Ă����ϐ�
static const f32 cFps = 60.0f;
static u64 gDeltaTick = cTickScale / cFps;
static u64 gDeltaTime = 1.0f / cFps;

#pragma endregion


}