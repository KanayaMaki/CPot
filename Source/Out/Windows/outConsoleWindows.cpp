//
//	content	:	Windows�ŁA�R���\�[�����쐬���ĕW���o�͂ŏo�͂���N���X
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
		Load();	//�R���\�[�����擾����
	}
	mUserNum++;
}

void OutConsoleDevice::Free() {

	mUserNum--;

	if (mUserNum == 0) {
		Release();	//�N������Q�Ƃ���Ă��Ȃ��Ȃ�A�R���\�[�����������
	}
}

void OutConsoleDevice::Output(const CHAR* aStr) {

	//�W���o�͂���΁A�R���\�[���ɕ\������
	std::printf("%s", aStr);
}

#pragma endregion


}

}