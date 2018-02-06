//
//	content	:	Windowsでの時間に関するクラス
//	author	:	SaitoYoshiki
//


#include "./Pot/Time/Windows/timeWindows.h"

#include "./Pot/Time/Standard/timeStandard.h"

#include <Windows.h>

namespace cpot {

namespace windows {


#pragma region DetailTimeDevice

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


#pragma endregion


#pragma region Time

UnixTimeType Time::GetUnix() const {
	return standard::UnixTimeDevice::Get();	//standardの関数に委譲
}

#pragma endregion


}


}
