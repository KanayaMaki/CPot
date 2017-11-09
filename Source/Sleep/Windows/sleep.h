//
//	一定時間スレッドを止める、スリープクラスの実装
//

#pragma once

#include "./Sleep/sleep.h"
#include "./Usefull/singleton.h"


namespace cpot {

namespace windows {


//	スリープの機能を提供するクラス
class SleepDevice : public Singleton<SleepDevice> {

public:
	void SleepSecond(f32 aSecond);
};


//	スリープクラス
class Sleep : public SleepBase {

public:
	void SleepSecond(f32 aSecond) override {
		SleepDevice::S().SleepSecond(aSecond);
	}
};


}

//	プログラム中では、このSleepを使用する
using Sleep = windows::Sleep;

}