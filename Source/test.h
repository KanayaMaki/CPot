#include "./Atom/atom.h"

#include <Windows.h>


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
void TestInputDirectInput(HINSTANCE aHInstance, HWND aHwnd);
void TestInputXInput();

#pragma endregion
