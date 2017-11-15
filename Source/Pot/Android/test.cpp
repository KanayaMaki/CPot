#include "./Pot/Android/test.h"

#include "./Pot/Time/time.h"
#include "./Pot/Sleep/sleep.h"
#include "./Pot/Out/Android/outLogAndroid.h"


void TestFunc() {

	cpot::Time t;
	cpot::f64 now = t.GetDetail();
	cpot::UnixTimeType u = t.GetUnix();
	cpot::f64 end = t.GetDetail();

	cpot::Sleep s;
	s.SleepSecond(1.0f);

	
}