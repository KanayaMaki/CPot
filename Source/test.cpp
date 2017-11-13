#include "./Atom/atom.h"

#include "./test.h"

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
#include "Input\XInput\inputXInput.h"
#include "Input\input.h"

//FileOut
#include "File\file.h"

#include <Windows.h>

using namespace cpot;


#pragma region File

void TestFileOut() {

	FileOut o;
	if (!o.Open("aa.txt", false, true)) {
		CPOT_LOG("FileOut.Open:Failed");
	}
	Vector4 lData(1.0f, 2.0f, 3.0f, 4.0f);
	Buffer b((const BYTE*)(&lData), sizeof(lData));
	o.Write(b);
}

void TestFileIn() {
	FileIn lIn("aa.txt", true);
	Vector4 lData;
	Buffer b;
	lIn.Read(b);
	b.Read(&lData, sizeof(lData));
}

#pragma endregion



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

/*
void TestInputWindows(HINSTANCE aHInstance, HWND aHwnd) {

	windows::Input::S().Init(aHInstance, aHwnd);

	while (true) {
		windows::Input::S().Update();

		if (windows::Input::S().GetValue(windows::cA) > 0.0f) {
			CPOT_LOG("A");
		}
		if (windows::Input::S().GetValue(windows::CInputCode::cMouseButton1) > 0.0f) {
			CPOT_LOG("MouseClick");
			CPOT_LOG("MouseLocX:", windows::Input::S().GetValue(windows::cMouseCursorX));
			CPOT_LOG("MouseLocY:", windows::Input::S().GetValue(windows::cMouseCursorY));
		}
		
		::Sleep(16);
	}

}
*/
/*
void TestInputXInput() {

	while (true) {
		xInput::Input::S().Update();

		if (xInput::Input::S().GetButtonDown(xInput::cLTrigger) > 0.0f) {
			CPOT_LOG("LStick");
		}

		::Sleep(16);
	}
}
*/

void TestInputInputWindows(HINSTANCE aHInstance, HWND aHwnd) {

	windows::Input::S().Init(aHInstance, aHwnd);

	while (true) {
		windows::Input::S().Update();

		if (Input::GetButtonDown(windows::cA) > 0.0f) {
			CPOT_LOG("A");
		}
		if (Input::GetValue(windows::cMouseButton1) > 0.0f) {
			CPOT_LOG("MouseClick");
			CPOT_LOG("MouseLocX:",Input::GetValue(windows::cMouseCursorX));
			CPOT_LOG("MouseLocY:", Input::GetValue(windows::cMouseCursorY));
		}

		::Sleep(16);
	}

}

void TestInputInputXInput() {

	while (true) {
		xInput::Input::S().Update();

		if (Input::GetButtonDown(xInput::cLTrigger) > 0.0f) {
			CPOT_LOG("LStick");
		}

		::Sleep(16);
	}
}

#pragma endregion