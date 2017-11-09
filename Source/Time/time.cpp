//
//	時間に関するクラスを集めた
//

#include "./Time/time.h"


namespace cpot {


//前のフレームからの経過時間
#pragma region DeltaTime


f32 DeltaTime() {
	return gDeltaTime;
}

TickType DeltaTick() {
	return gDeltaTick;
}

//経過時間を設定
void DeltaTick(TickType aDeltaTick) {
	gDeltaTick = aDeltaTick;
	gDeltaTime = ToSecond(aDeltaTick);
}

//経過時間を格納しておく変数
static const f32 cFps = 60.0f;
static u64 gDeltaTick = cTickScale / cFps;
static u64 gDeltaTime = 1.0f / cFps;

#pragma endregion


}