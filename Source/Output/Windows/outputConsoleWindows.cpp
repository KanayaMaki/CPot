//
//	内容	:	Windowsで、コンソールを作成して標準出力で出力するクラス
//

#include "./outputConsole.h"


namespace cpot {

namespace windows {


#pragma region Init

void OutputConsoleDevice::Load() {
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

void OutputConsoleDevice::Final() {
	Release();
}

void OutputConsoleDevice::Release() {
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

void OutputConsoleDevice::Alloc() {
	if (!IsLoaded()) {
		Load();	//コンソールを取得する
	}
	mUserNum++;
}

void OutputConsoleDevice::Free() {

	mUserNum--;

	if (mUserNum == 0) {
		Release();	//誰からも参照されていないなら、コンソールを解放する
	}
}

void OutputConsoleDevice::Output(const CHAR* aStr) {

	//標準出力すれば、コンソールに表示され
	std::printf("%s", aStr);
}

#pragma endregion


}

}