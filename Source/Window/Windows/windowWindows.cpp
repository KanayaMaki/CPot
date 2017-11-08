#include "window.h"

namespace cpot {

//�E�B���h�E�v���V�[�W���́A���Ԋu�ŌĂяo���C�x���g�̎���ID
const u32 cPotTimerID = 10010010;


#pragma region Load

void Window::Load(
	HINSTANCE& aHInstance,
	Vector2 aWindowSize, const CHAR* aTitle,
	UINT aStyle,
	WindowProcFunc aWndProc) {

	mSize = aWindowSize;
	mStyle = aStyle;
	mHInstance = aHInstance;

	//�E�B���h�E�N���X�̓o�^
	RegistWindowClass(aWndProc, aTitle);

	//�E�B���h�E�̍쐬
	CreateWindow_CPot(aTitle);

	//�E�B���h�E���}�l�[�W���ɓo�^
	WindowManager::S().Regist(this);
}

void Window::RegistWindowClass(WindowProcFunc aWndProc, const CHAR* aTitle) {

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSA wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = aWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mHInstance;
	//wc.hIcon = LoadIcon(mHInstance, MAKEINTRESOURCE(IDI_ICON));
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = aTitle;

	//�E�B���h�E�N���X�̍쐬
	if (!RegisterClassA(&wc)) {
		MessageBoxA(nullptr, "�E�B���h�E�N���X�̍쐬�Ɏ��s���܂���", nullptr, MB_OK);
		return;
	}
}

void Window::CreateWindow_CPot(const CHAR* aTitle) {

	//�E�B���h�E�̍쐬
	mHwnd = CreateWindowExA(WS_EX_APPWINDOW, aTitle, aTitle, mStyle,
		100, 100, mSize.x, mSize.y, nullptr, nullptr, mHInstance, nullptr);
	if (mHwnd == nullptr) {
		MessageBoxA(nullptr, "�E�B���h�E�̍쐬�Ɏ��s���܂���", nullptr, MB_OK | MB_ICONERROR);
		return;
	}

	SetSize(mSize);	//�E�B���h�E�̃T�C�Y��ύX
	ShowWindow(mHwnd, 1);	//�E�B���h�E�̕\��

	//��莞�Ԃ��ƂɃ^�C�}�[���Ăяo���āA�������s��
	::SetTimer(mHwnd, cPotTimerID, 100, NULL);
}


#pragma endregion


#pragma region Release

void Window::Release() {

	//�E�B���h�E�̉��
	WindowManager::S().Free(this);
}

#pragma endregion


#pragma region Operate

void Window::SetSize(Vector2 aSize) {

	//�E�B���h�E�̐V�����傫����ݒ�
	Vector2 lNewSize = Vector2(Clamp(aSize.x, 1920.0f), Clamp(aSize.y, 1080.0f));

	//�E�B���h�E�S�̂̑傫���̎擾
	RECT lWinRect;
	GetWindowRect(mHwnd, &lWinRect);

	//�N���C�A���g�̈�̑傫���̎擾
	RECT lCliRect;
	GetClientRect(mHwnd, &lCliRect);

	//�f�X�N�g�b�v�S�̂̑傫���̎擾
	RECT lDeskRect;
	GetClientRect(::GetDesktopWindow(), &lDeskRect);


	//�N���C�A���g�̈�̑傫�����w�肳�ꂽ�傫���ɂ��邽�߂ɁA�E�B���h�E�S�̂̑傫�����v�Z����
	s32 lWindowWidth = (lWinRect.right - lWinRect.left) - (lCliRect.right - lCliRect.left) + lNewSize.x;
	s32 lWindowHeight = (lWinRect.bottom - lWinRect.top) - (lCliRect.bottom - lCliRect.top) + lNewSize.y;

	//�f�X�N�g�b�v�̒����ɃE�B���h�E�����鎞�́A����̍��W�����߂�
	s32 lLocX = ((lDeskRect.right - lDeskRect.left) - lWindowWidth) / 2;
	s32 lLocY = ((lDeskRect.bottom - lDeskRect.top) - lWindowHeight) / 2;

	//�E�B���h�E�T�C�Y��ύX���A�f�X�N�g�b�v�̒����Ɉړ�����
	SetWindowPos(mHwnd, nullptr, lLocX, lLocY, lWindowWidth, lWindowHeight, SWP_NOZORDER);

	mSize = lNewSize;
}

void Window::SetTitle(const CHAR* aTitle) {
	SetWindowTextA(mHwnd, aTitle);
}


#pragma endregion


#pragma region Other


LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

		case WM_DESTROY:
			//Config::S().GameEnd(true);
			PostQuitMessage(0);
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);

		case WM_TIMER:
			//���Ԋu�ŌĂ΂��C�x���g
			if (wParam == cPotTimerID) {
				//	TODO �Q�[�����ŏI���Ȃ�A�E�B���h�E���I��点��
				/*if (Config::S().GameEnd()) {
					SendMessageA(hwnd, WM_CLOSE, 0, 0);
					break;
				}*/
				return 0;
			}
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);

			
		case WM_CLOSE: {

			#ifdef CPOT_ON_MASTER
			BOOL tIsShow = Cursor::S().IsShow();
			Cursor::S().Show();

			Window* tWindow = WindowManager::S().Find(hwnd);
			if (tWindow) {
				tWindow->mFocus = false;	//�t�H�[�J�X���O��
			}

			//�I�����Ă������m�F����
			int hr = MessageBoxA(hwnd, "�Q�[�����I�����Ă������ł����H", "�m�F", MB_YESNO | MB_ICONQUESTION);
			if (hr == IDNO) {
				//�v���O�������I�����Ȃ�
				//	TODO �Q�[�����̏I���t���O������
				Cursor::S().ShowOrHide(tIsShow);
				tWindow->mFocus = true;	//�t�H�[�J�X��߂�
				return 0L;
			}
			#endif
		}
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);

		case WM_CREATE:
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);

		case WM_SETFOCUS: {
			Window* tWindow = WindowManager::S().Find(hwnd);
			if (tWindow) {
				tWindow->mFocus = true;	//�t�H�[�J�X���Z�b�g���ꂽ
			}
		}
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);

		case WM_KILLFOCUS: {
			Window* tWindow = WindowManager::S().Find(hwnd);
			if (tWindow) {
				tWindow->mFocus = false;	//�t�H�[�J�X���O�ꂽ
			}
		}
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

#pragma endregion


}
