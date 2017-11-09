//
//	時間に関するクラスを集めた
//

#pragma once

#include "./Time/time.h"

#include "./Time/Standard/time.h"


namespace cpot {

namespace windows {


//細密な時間を取得できるデバイス
#pragma region DetailTime

class DetailTimeDevice {

public:
	//細密な時間（カウント）
	static u64 GetCount();

	//一秒に何カウント増えるのか
	static u64 GetTimeUnit();

	//細密な時間（秒）
	static f64 Get() {
		return (f64)(GetCount()) / GetTimeUnit();
	}
};

#pragma endregion



//時間を取得
#pragma region Time

class Time : public TimeBase {

public:
	//ユニックスタイムを取得
	UnixTimeType GetUnix() const CPOT_OR {
		return standard::UnixTimeDevice::Get();	//standardの関数に委譲
	}

	//細密な時間を取得
	f64 GetDetail() const CPOT_OR {
		return DetailTimeDevice::Get();
	}
};

#pragma endregion


}


//このプログラムでは、Timeクラスはwindows::Timeを使うようにする
using Time = windows::Time;

}
