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

//Vector
#include "List/vector.h"

//HashTable
#include "List/hashTable.h"

//Thread
#include "Thread/thread.h"
#include "Thread/mutex.h"

//Input
#include "Input\Windows\inputWindows.h"
#include "Input\DirectInput\inputDirectInput.h"


#include <Windows.h>

using namespace cpot;


#pragma region Output

void TestOutput(HWND aHwnd) {

	windows::OutputConsoleDevice::S().Init(aHwnd);

	auto o = new windows::OutputConsole;
	o->Load();
	Log::S().Set(o);

}

#pragma endregion


#pragma region Time

void TestDeltaTime() {
	CPOT_LOG("TestDeltaTime");

	CPOT_LOG("DeltaTime:", DeltaTime());
	CPOT_LOG("DeltaTick:", (u64)DeltaTick());

	CPOT_LOG("SetDeltaTime(1.0f / 30.0f)");
	SetDeltaTime(1.0f / 30.0f);

	CPOT_LOG("DeltaTime:", DeltaTime());
	CPOT_LOG("DeltaTick:", (u64)DeltaTick());
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


#pragma region Vector

void TestVector() {

	Vector<u32> v;
	v.PushBack(32);
	v.PushBack(100);
	v.PushBack(200);
	v.PushBack(200);
	v.PushBack(100);

	for (u32 i = 0; i < v.GetSize(); i++) {
		CPOT_LOG(v[i]);
	}

	CPOT_LOG(v.Count(100));

	u32 a = v.Remove(100);
	CPOT_LOG(a);

	CPOT_LOG(v.Count(100));

	for (u32 i = 0; i < v.GetSize(); i++) {
		CPOT_LOG(v[i]);
	}
}

#pragma endregion


#pragma region HashTable

void TestHashTable() {

	HashTable<s32> hash;

	hash.Add("data1", 43);
	hash.Add("data2", 45);
	hash.Add("data3", 47);
	hash.Add("data4", 49);

	CPOT_LOG(hash.Find("data1"));
}

#pragma endregion


#pragma region Thread

Mutex gMutex;

void TestMutex(u32* aData) {

	//MutexLocker lMl(gMutex);

	for (u32 i = 0; i < 2; i++) {
		CPOT_LOG(i);
	}
}

void TestThread() {

	Thread t[10];

	for (u32 i = 0; i < 10; i++) {
		t[i].Start(TestMutex, nullptr);
	}

	for (u32 i = 0; i < 10; i++) {
		t[i].Join();
	}
}

#pragma endregion


#pragma region Rand

void TestRand() {
	Rand r;
	for (u32 i = 0; i < 10; i++) {
		CPOT_LOG(r.Next());
	}
}

#pragma endregion



#pragma region Input

void TestInputWindows(HINSTANCE aHInstance, HWND aHwnd) {

	windows::InputDevice::S().Init(aHInstance, aHwnd);

	while (true) {
		windows::InputDevice::S().Update();

		if (windows::InputDevice::S().GetValue(windows::CKeyCode::cA) > 0.0f) {
			CPOT_LOG("A");
		}
		if (windows::InputDevice::S().GetValue(windows::CKeyCode::cMouseButton1) > 0.0f) {
			CPOT_LOG("MouseClick");
			CPOT_LOG("MouseLocX:", windows::InputDevice::S().GetValue(windows::CKeyCode::cMouseCursorX));
			CPOT_LOG("MouseLocY:", windows::InputDevice::S().GetValue(windows::CKeyCode::cMouseCursorY));
		}
		
		::Sleep(16);
	}

}

void TestInputDirectInput(HINSTANCE aHInstance, HWND aHwnd) {

	directInput::JoystickDevice::S().Init(aHInstance, aHwnd);
	directInput::JoystickDevice::S().SetTranslater(0, directInput::Translater::PS4());

	while (true) {
		directInput::JoystickDevice::S().Update();

		if (directInput::JoystickDevice::S().GetValue(0, directInput::CJoystickCode::cRButtonRight) > 0.0f) {
			CPOT_LOG("A");
		}
		if (directInput::JoystickDevice::S().GetValue(0, directInput::CJoystickCode::cLStickUp) > 0.0f) {
			CPOT_LOG(directInput::JoystickDevice::S().GetValue(0, directInput::CJoystickCode::cLStickUp));
		}

		::Sleep(16);
	}
}

void TestInputXInput() {

}

#pragma endregion