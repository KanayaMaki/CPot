//
//	一定時間スレッドを止める、スリープクラスの実装
//

#include "./Pot/Sleep/Windows/sleepWindows.h"

#include <Windows.h>


namespace cpot {

namespace windows {

void SleepDevice::SleepSecond(f32 aSecond) {

	f32 lMilliSecond = aSecond * 1000.0f;
	::Sleep(lMilliSecond);
}


}

}