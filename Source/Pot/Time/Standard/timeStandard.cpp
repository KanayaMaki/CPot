//
//	content	:	Standardでの時間に関するクラス
//	author	:	SaitoYoshiki
//

#include "./Pot/Time/Standard/timeStandard.h"

#include <ctime>


namespace cpot {

namespace standard {


UnixTimeType UnixTimeDevice::Get() {
	return std::time(nullptr);
}

DateTimeData DateTimeDevice::ToDateTime(UnixTimeType aUnixTime) {

	std::time_t t = static_cast<s64>(aUnixTime);
	std::tm tm;

	#ifdef CPOT_ON_WINDOWS
	localtime_s(&tm, &t);
	#else
	std::tm* tTm;
	tTm = std::localtime(&t);
	tm = *tTm;
	#endif

	DateTimeData res;
	res.year = tm.tm_year + 1900;
	res.month = tm.tm_mon + 1;
	res.day = tm.tm_mday;
	res.hour = tm.tm_hour;
	res.minute = tm.tm_min;
	res.second = tm.tm_sec;
	// TODO 曜日の計算

	return res;
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
