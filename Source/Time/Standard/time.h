//
//	時間に関するクラスを集めた
//

#pragma once

#include "./Time/time.h"


namespace cpot {

namespace standard {


//UnixTimeを取得するデバイス
class UnixTimeDevice {
	
public:
	//UnixTimeを取得
	static UnixTimeType Get();

};


//DateTimeを取得するデバイス
class DateTimeDevice {

public:
	//UnixTimeを現在の日時に変換する
	static DateTimeData ToDateTime(UnixTimeType aUnixTime);

};


}

}
