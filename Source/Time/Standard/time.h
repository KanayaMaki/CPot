//
//	���ԂɊւ���N���X���W�߂�
//

#pragma once

#include "./Time/time.h"

#include <ctime>


namespace cpot {

namespace standard {


//UnixTime���擾����f�o�C�X
class UnixTimeDevice {
	
public:
	//UnixTime���擾
	static UnixTimeType Get() {
		return std::time(nullptr);
	}
};


//DateTime���擾����f�o�C�X
class DateTimeDevice {

public:
	//UnixTime�����݂̓����ɕϊ�����
	static DateTimeData ToDateTime(UnixTimeType aUnixTime) {

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
		// TODO �j���̌v�Z

		return res;
	}

};

}

}
