//	�t�@�C����	:	Window/Windows/window.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/08
//	�X�V����	:	2017/11/08
//	���e		:	�E�B���h�E�N���X�̎���

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "cursor.h"

#include <Windows.h>

namespace cpot {


using WindowProcFunc = LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM);

class Window {

	//�R���X�g���N�^�Ȃ�
	#pragma region Constructor

private:
	//���[�U�����new�ł����Adelete���ł��Ȃ�
	Window() {
		mSize = Vector2::Zero();
		mHwnd = nullptr;
	}
	~Window() {
		Release();
	}


public:
	//�E�B���h�E�̍쐬
	static Window* Create() {
		return new Window;
	}
	//�E�B���h�E�̏���
	static void Destroy(Window* aWindow) {
		CPOT_DELETE(aWindow);
	}

	#pragma endregion


	//������
	#pragma region Load

public:
	void Load(HINSTANCE& aHInstance, Vector2 aWindowSize, const CHAR* aTitle, UINT aStyle = (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)),
		WindowProcFunc WndProc = WindowProc);

private:
	void RegistWindowClass(WindowProcFunc WndProc, const CHAR* aTitle);
	void CreateWindow_CPot(const CHAR* aTitle);

	#pragma endregion


	//�I��
	#pragma region Release

private:
	void Release();

	#pragma endregion


	//���삷��
	#pragma region Operate

public:
	//�E�B���h�E�̑傫���̕ύX
	void SetSize(Vector2 aSize);
	void SetSize(f32 aWidth, f32 aHeight) {
		SetSize(Vector2(aWidth, aHeight));
	}
	
	void SetTitle(const CHAR* aTitle);


	//�J�[�\���̕\���E��\��
	#pragma region Cursor

public:
	static void ShowCursor() {
		Cursor::S().Show();
	}
	static void HideCursor() {
		Cursor::S().Hide();
	}
	static BOOL IsShowCursor() {
		Cursor::S().IsShow();
	}

	#pragma endregion


	//���b�Z�[�W���[�v
	#pragma region MessageLoop

	static s32 MessageLoop() {

		MSG msg;
		while (1) {
			if (PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				if (GetMessageA(&msg, nullptr, 0, 0) == 0) {
					break;
				}
				else {
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
				}
			}
		}
		return msg.wParam;
	}

	#pragma endregion


	#pragma endregion


	//�l���擾����
	#pragma region Getter

public:
	f32 GetWidth() const { 
		return mSize.x;
	}
	f32 GetHeight() const {
		return mSize.y;
	}
	Vector2 GetSize() const {
		return mSize;
	}
	BOOL GetFocus() const {
		return mFocus;
	}

	HWND& GetHwnd() {
		return mHwnd;
	}
	HINSTANCE& GetHInstance() {
		return mHInstance;
	}

	BOOL IsLoaded() const {
		return NotNull(mHwnd);	//mHwnd��null�łȂ��Ȃ烍�[�h�ς�
	}

	#pragma endregion


	//���̑�
	#pragma region Other

private:
	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	HINSTANCE mHInstance;
	HWND mHwnd;
	Vector2 mSize;
	UINT mStyle;
	BOOL mFocus;

	#pragma endregion

};


class WindowManager : public Singleton<WindowManager> {
	friend class Singleton<WindowManager>;

	//�R���X�g���N�^
	#pragma region Constructor

protected:
	WindowManager() {
		mWindow = nullptr;
	}

	#pragma endregion


	//����
	#pragma region Operate

public:
	//�o�^
	void Regist(Window* aWindow) {
		if (mWindow == nullptr) {
			mWindow = aWindow;
		}
	}
	//���
	void Free(Window* aWindow) {
		if (mWindow == aWindow) {
			mWindow = nullptr;
		}
	}

	//�擾
	Window* Get() {
		return mWindow;
	}

	//�w�肳�ꂽHWND�����E�B���h�E������
	Window* Find(HWND aHwnd) {
		if (mWindow != nullptr) {
			if (mWindow->GetHwnd() == aHwnd) {
				return mWindow;
			}
		}
		return nullptr;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	Window* mWindow;

	#pragma endregion

};


}
