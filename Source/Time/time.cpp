//
//	content	:	���ԂɊւ���N���X
//	author	:	SaitoYoshiki
//

#include "./Time/time.h"


namespace cpot {


//�O�̃t���[������̌o�ߎ���
#pragma region DeltaTime


//�o�ߎ��Ԃ��i�[���Ă����ϐ�
static const f32 cFps = 60.0f;
static u64 gDeltaTick = cTickUnit / cFps;
static f32 gDeltaTime = 1.0f / cFps;


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
//�o�ߎ��Ԃ�ݒ�
void SetDeltaTime(f32 aDeltaTime) {
	gDeltaTick = ToTick(aDeltaTime);
	gDeltaTime = aDeltaTime;
}


#pragma endregion


}