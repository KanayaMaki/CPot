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

void TestVector();

#pragma endregion
