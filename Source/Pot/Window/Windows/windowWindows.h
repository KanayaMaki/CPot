//
//	content	:	ウィンドウズのウィンドウの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"
#include "./Pot/Window/Windows/cursorWindows.h"

#include <Windows.h>

namespace cpot {

namespace windows {



using WindowProcFunc = LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM);

class Window : public Singleton<Window> {
	friend class Singleton<Window>;


	//コンストラクタなど
	#pragma region Constructor

private:
	//ユーザからはnewできず、deleteもできない
	Window() {
		mSize = Vector2::Zero();
		mHwnd = nullptr;
	}
	~Window() {
		Release();
	}

	#pragma endregion


	//初期化
	#pragma region Load

public:
	void Load(HINSTANCE& aHInstance, Vector2 aWindowSize, const CHAR* aTitle, UINT aStyle = (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)),
		WindowProcFunc WndProc = WindowProc);

private:
	void RegistWindowClass(WindowProcFunc WndProc, const CHAR* aTitle);
	void CreateWindow_CPot(const CHAR* aTitle);

	#pragma endregion


	//終了
	#pragma region Release

private:
	void Release();

	#pragma endregion


	//操作する
	#pragma region Operate

public:
	//ウィンドウの大きさの変更
	void SetSize(Vector2 aSize);
	void SetSize(f32 aWidth, f32 aHeight) {
		SetSize(Vector2(aWidth, aHeight));
	}

	void SetTitle(const CHAR* aTitle);


	//カーソルの表示・非表示
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


	//メッセージループ
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


	//値を取得する
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
		return NotNull(mHwnd);	//mHwndがnullでないならロード済み
	}

	#pragma endregion


	//その他
	#pragma region Other

private:
	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	HINSTANCE mHInstance;
	HWND mHwnd;
	Vector2 mSize;
	UINT mStyle;
	BOOL mFocus;

	#pragma endregion
};


}

}
