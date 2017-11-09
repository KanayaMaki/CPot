//
//	���ԂɊւ���N���X���W�߂�
//

#include "./Time/time.h"


namespace cpot {


//�O�̃t���[������̌o�ߎ���
#pragma region DeltaTime


//�o�ߎ��Ԃ��i�[���Ă����ϐ�
static const f32 cFps = 60.0f;
static u64 gDeltaTick = cTickUnit / cFps;
static u64 gDeltaTime = 1.0f / cFps;


f32 DeltaTime() {
	return gDeltaTime;
}

TickType DeltaTick() {
	return gDeltaTick;
}

//�o�ߎ��Ԃ�ݒ�
void SetDeltaTick(TickType aDeltaTick) {
	gDeltaTick = aDeltaTick;
	gDeltaTime = ToSecond(aDeltaTick);
}


#pragma endregion


}