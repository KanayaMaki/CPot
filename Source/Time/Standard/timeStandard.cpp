//
//	Standard環境での、時間に関するクラス
//

#include "./Time/Standard/time.h"

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
	#elif
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

}
