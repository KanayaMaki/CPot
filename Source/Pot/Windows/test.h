//
//	content	:	ライブラリのテストを行う
//	author	:	SaitoYoshiki
//

#include "./Pot/Atom/atom.h"

#include <Windows.h>

#pragma region OpenGL

void TestOpenGL(HWND aHwnd);

#pragma endregion

#pragma region Pmx

void TestPmx();

#pragma endregion

#pragma region Texture

void TestTexture();

#pragma endregion

#pragma region DirectX11

void TestDirectX11(HWND aHwnd);

#pragma endregion

#pragma region Animation

void TestAnimation();

#pragma endregion

#pragma region Audio

void TestAudio();

#pragma endregion


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
