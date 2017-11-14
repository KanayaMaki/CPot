#include "./Atom/atom.h"

#include "./Time/time.h"
#include "./Sleep/sleep.h"
#include "./Out/Android/outLogAndroid.h"

#include "./Android/test.h"

void TestFunc() {

	cpot::Time t;
	cpot::f64 now = t.GetDetail();
	cpot::UnixTimeType u = t.GetUnix();
	cpot::f64 end = t.GetDetail();

	cpot::Sleep s;
	s.SleepSecond(1.0f);

	
}