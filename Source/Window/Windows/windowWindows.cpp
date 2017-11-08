#include "window.h"

namespace cpot {

//ウィンドウプロシージャの、一定間隔で呼び出すイベントの識別ID
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

	//ウィンドウクラスの登録
	RegistWindowClass(aWndProc, aTitle);

	//ウィンドウの作成
	CreateWindow_CPot(aTitle);

	//ウィンドウをマネージャに登録
	WindowManager::S().Regist(this);
}

void Window::RegistWindowClass(WindowProcFunc aWndProc, const CHAR* aTitle) {

	//ウィンドウクラスの設定
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

	//ウィンドウクラスの作成
	if (!RegisterClassA(&wc)) {
		MessageBoxA(nullptr, "ウィンドウクラスの作成に失敗しました", nullptr, MB_OK);
		return;
	}
}

void Window::CreateWindow_CPot(const CHAR* aTitle) {

	//ウィンドウの作成
	mHwnd = CreateWindowExA(WS_EX_APPWINDOW, aTitle, aTitle, mStyle,
		100, 100, mSize.x, mSize.y, nullptr, nullptr, mHInstance, nullptr);
	if (mHwnd == nullptr) {
		MessageBoxA(nullptr, "ウィンドウの作成に失敗しました", nullptr, MB_OK | MB_ICONERROR);
		return;
	}

	SetSize(mSize);	//ウィンドウのサイズを変更
	ShowWindow(mHwnd, 1);	//ウィンドウの表示

	//一定時間ごとにタイマーを呼び出して、処理を行う
	::SetTimer(mHwnd, cPotTimerID, 100, NULL);
}


#pragma endregion


#pragma region Release

void Window::Release() {

	//ウィンドウの解放
	WindowManager::S().Free(this);
}

#pragma endregion


#pragma region Operate

void Window::SetSize(Vector2 aSize) {

	//ウィンドウの新しい大きさを設定
	Vector2 lNewSize = Vector2(Clamp(aSize.x, 1920.0f), Clamp(aSize.y, 1080.0f));

	//ウィンドウ全体の大きさの取得
	RECT lWinRect;
	GetWindowRect(mHwnd, &lWinRect);

	//クライアント領域の大きさの取得
	RECT lCliRect;
	GetClientRect(mHwnd, &lCliRect);

	//デスクトップ全体の大きさの取得
	RECT lDeskRect;
	GetClientRect(::GetDesktopWindow(), &lDeskRect);


	//クライアント領域の大きさを指定された大きさにするために、ウィンドウ全体の大きさを計算する
	s32 lWindowWidth = (lWinRect.right - lWinRect.left) - (lCliRect.right - lCliRect.left) + lNewSize.x;
	s32 lWindowHeight = (lWinRect.bottom - lWinRect.top) - (lCliRect.bottom - lCliRect.top) + lNewSize.y;

	//デスクトップの中央にウィンドウがある時の、左上の座標を求める
	s32 lLocX = ((lDeskRect.right - lDeskRect.left) - lWindowWidth) / 2;
	s32 lLocY = ((lDeskRect.bottom - lDeskRect.top) - lWindowHeight) / 2;

	//ウィンドウサイズを変更し、デスクトップの中央に移動する
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
			//一定間隔で呼ばれるイベント
			if (wParam == cPotTimerID) {
				//	TODO ゲーム側で終了なら、ウィンドウも終わらせる
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
				tWindow->mFocus = false;	//フォーカスを外す
			}

			//終了していいか確認する
			int hr = MessageBoxA(hwnd, "ゲームを終了してもいいですか？", "確認", MB_YESNO | MB_ICONQUESTION);
			if (hr == IDNO) {
				//プログラムを終了しない
				//	TODO ゲーム側の終了フラグを下す
				Cursor::S().ShowOrHide(tIsShow);
				tWindow->mFocus = true;	//フォーカスを戻す
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
				tWindow->mFocus = true;	//フォーカスがセットされた
			}
		}
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);

		case WM_KILLFOCUS: {
			Window* tWindow = WindowManager::S().Find(hwnd);
			if (tWindow) {
				tWindow->mFocus = false;	//フォーカスが外れた
			}
		}
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

#pragma endregion


}
