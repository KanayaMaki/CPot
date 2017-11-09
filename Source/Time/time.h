//
//	時間に関するクラスを集めた
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


//ゲーム内の時間の単位、Tickの定義
#pragma region Tick


using TickType = u64;
const TickType cTickScale = 1200000UL;	//1秒が何Tickか

//秒をチックに
inline TickType ToTick(f32 aSecond) {
	return aSecond * cTickScale;
}

//チックを秒に
inline f32 ToSecond(TickType aTick) {
	return (f64)aTick / cTickScale;
}


#pragma endregion


//前のフレームからの経過時間
#pragma region DeltaTime

//経過時間を秒で取得
f32 DeltaTime();

//経過時間をチックで取得
TickType DeltaTick();

//経過時間を設定
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