#include "./Atom/atom.h"

//Window
#include "Window/Windows/window.h"

//Output
#include "./Output/output.h"
#include "./Output/Windows/outputDebugWindow.h"
#include "./Output/Windows/outputConsole.h"

//Rand
#include "Rand/rand.h"

//Sleep
#include "Sleep/sleep.h"

//Time
#include "Time/time.h"


#include <Windows.h>

using namespace cpot;


void TestOutput(HWND aHwnd) {

	windows::OutputConsoleDevice::S().Init(aHwnd);

	auto o = new windows::OutputConsole;
	o->Load();
	Log::S().Set(o);

}


#pragma region Time

void TestDeltaTime() {

}
void TestTick() {

	CPOT_LOG("TestTick");

	CPOT_LOG(2.0f, "=", (u64)(ToTick(2.0f)), "Tick");
	CPOT_LOG(12000000UL, "=", ToSecond(12000000), "Second");
}

void TestDetailTime() {

	CPOT_LOG("TestDetailTime");

	Time lTime;

	cpot::Sleep lSleep;

	f64 lStart, lEnd;
	lStart = lTime.GetDetail();

	lSleep.SleepSecond(2.0f);

	lEnd = lTime.GetDetail();

	CPOT_LOG(lEnd - lStart);	//2.0 is right

}

void TestUnixTime() {
	CPOT_LOG("TestUnixTime");

	Time lTime;

	CPOT_LOG("Time :", lTime.GetUnix());
	CPOT_LOG("Right:", time(nullptr));
}

void TestDateTime() {

	CPOT_LOG("TestDateTime");

	DateTime lDateTime;
	DateTimeData lDate = lDateTime.Get();

	CPOT_LOG("YEAR  :", lDate.year);
	CPOT_LOG("MONTH :", lDate.month);
	CPOT_LOG("DAY   :", lDate.day);
	CPOT_LOG("HOUR  :", lDate.hour);
	CPOT_LOG("MINUTE:", lDate.minute);
	CPOT_LOG("SECOND:", lDate.second);
}

#pragma endregion



