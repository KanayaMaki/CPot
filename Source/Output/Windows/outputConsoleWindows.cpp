//
//	内容	:	Windowsで、コンソールを作成して標準出力で出力するクラス
//

#include "./outputConsole.h"


namespace cpot {

namespace windows {


void OutputConsoleDevice::Final() {
	Release();
}

void OutputConsoleDevice::Alloc() {
	if (!IsLoaded()) {
		Load();
	}
	mUserNum++;
}
void OutputConsoleDevice::Free() {
	mUserNum--;
	if (mUserNum == 0) {
		Final();
	}
}


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

void OutputConsoleDevice::Output(const CHAR* aStr) {
	std::printf("%s", aStr);
}


OutputConsole::~OutputConsole() {
	Release();
}

void OutputConsole::Load() {
	if (!IsLoaded()) {
		OutputConsoleDevice::S().Alloc();
	}
}
void OutputConsole::Release() {
	if (IsLoaded()) {
		OutputConsoleDevice::S().Free();
	}
	Reset();
}

void OutputConsole::OutputStr(const CHAR* aStr) {
	OutputConsoleDevice::S().Output(aStr);
}


}

}