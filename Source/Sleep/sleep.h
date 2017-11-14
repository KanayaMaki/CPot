//
//	content	:	一定時間スレッドを停止するクラスのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


class SleepBase {
public:
	//指定された秒数、そのスレッドの実行を止める
	virtual void SleepSecond(f32 aSecond) = 0;
};


}


#ifdef CPOT_ON_WINDOWS
#include "./Sleep/Windows/sleepWindows.h"
#elif defined CPOT_ON_ANDROID
#include "./Sleep/Android/sleepAndroid.h"
#endif