//
//	時間に関するクラス
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
	static BOOL lIsInit = false;	//初期化済みかのフラグ

	//初期化されていないなら
	if (Not(lIsInit)) {
		QueryPerformanceFrequency(&lUnit);	//初期化
		lIsInit = true;	//初期化済み
	}
	return lUnit.QuadPart;
}

}


//DateTimeの実装
#pragma region DateTime

//現在の日時を取得する
DateTimeData DateTime::Get() {
	UnixTimeType lNowTime = standard::UnixTimeDevice::Get();
	return standard::DateTimeDevice::ToDateTime(lNowTime);
}

//UnixTimeを現在の日時に変換する
DateTimeData DateTime::ToDateTime(UnixTimeType aUnixTime) {
	return standard::DateTimeDevice::ToDateTime(aUnixTime);
}

#pragma endregion

}
