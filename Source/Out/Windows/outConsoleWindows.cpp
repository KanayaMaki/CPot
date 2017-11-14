//
//	content	:	Windowsで、コンソールを作成して標準出力で出力するクラス
//	author	:	SaitoYoshiki
//

#include "./outConsole.h"


namespace cpot {

namespace windows {


#pragma region Init

void OutConsoleDevice::Load() {
	if (IsLoaded()) {
		return;
	}

	::AllocConsole();
	freopen_s(&mFp, "CONOUT$", "w", stdout);

	HWND console = ::GetConsoleWindow();
	::SetWindowPos(console, NULL, 0, 0, 0, 0, SWP_NOSIZE);

	if (mHwnd != nullptr) {
		::SetForegroundWindow(mHwnd);
	}
}

#pragma endregion


#pragma region Final

void OutConsoleDevice::Final() {
	Release();
}

void OutConsoleDevice::Release() {
	if (!IsLoaded()) {
		return;
	}

	if (mFp) {
		std::fclose(mFp);
		::FreeConsole();
	}
	Reset();
}

#pragma endregion


#pragma region Operate

void OutConsoleDevice::Alloc() {
	if (!IsLoaded()) {
		Load();	//コンソールを取得する
	}
	mUserNum++;
}

void OutConsoleDevice::Free() {

	mUserNum--;

	if (mUserNum == 0) {
		Release();	//誰からも参照されていないなら、コンソールを解放する
	}
}

void OutConsoleDevice::Output(const CHAR* aStr) {

	//標準出力すれば、コンソールに表示され
	std::printf("%s", aStr);
}

#pragma endregion


}

}