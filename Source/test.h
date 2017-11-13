#include "./Atom/atom.h"

#include <Windows.h>


#pragma region Loader

void TestLoader();

#pragma endregion



#pragma region Output

void TestOutput(HWND aHwnd);

#pragma endregion


#pragma region Time

void TestDeltaTime();	//OK
void TestTick();	//OK

void TestDetailTime();	//OK
void TestUnixTime();	//OK

void TestDateTime();	//OK

#pragma endregion


#pragma region Vector

void TestVector();	//OK

#pragma endregion


#pragma region HashTable

void TestHashTable();

#pragma endregion


#pragma region Thread

void TestThread();

#pragma endregion


#pragma region Rand

void TestRand();

#pragma endregion


#pragma region Input

void TestInputWindows(HINSTANCE aHInstance, HWND aHwnd);
void TestInputXInput();

void TestInputInputWindows(HINSTANCE aHInstance, HWND aHwnd);
void TestInputInputXInput();

#pragma endregion


#pragma region File

void TestFileOut();
void TestFileIn();

#pragma endregion
