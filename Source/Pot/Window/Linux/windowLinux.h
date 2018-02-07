//
//	content	:	ウィンドウズのウィンドウの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"

#include <GL/glew.h>
#include <GL/glfw.h>

namespace cpot {

namespace linux {


class Window : public Singleton<Window> {
	friend class Singleton<Window>;


	//コンストラクタなど
	#pragma region Constructor

private:
	//ユーザからはnewできず、deleteもできない
	Window() {
		mSize = Vector2::Zero();
	}
	~Window() {
		
	}

	#pragma endregion


	//初期化
	#pragma region Load

public:
	void Init(Vector2& aWindowSize, const CHAR* aCaption) {
		
		int lResult;	//戻り値用

		//GLFWの初期化
		lResult = glfwInit();
		if (lResult == GL_FALSE) {
			CPOT_LOG("GLFWの初期化に失敗しました");
			return;
		}


		//使用するOpenGLのバージョンの設定
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 5);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwOpenWindowHint(GLFW_RESIZABLE, GL_FALSE);


		//ウィンドウの作成
		mWindow = glfwOpenWindow(
			aWindowSize.x, aWindowSize.y,
			8, 8, 8,
			8,
			0,
			0,
			GLFW_WINDOW);

		if (mWindow == GL_FALSE) {
			CPOT_LOG("ウィンドウの作成に失敗しました");
			return;
		}


		//変更
		glfwSwapInterval(1);
		glfwSetWindowTitle(aCaption);

		//コンテキストを有効化
		glfwMakeContextCurrent(mWindow);


		//GLEWの初期化
		glewInit();
	}

	void Final() {
		glfwTerminate();
	}

	#pragma endregion



	//操作する
	#pragma region Operate

public:
	//ウィンドウの大きさの変更
	void SetSize(Vector2 aSize) {}
	void SetSize(f32 aWidth, f32 aHeight) {
		SetSize(Vector2(aWidth, aHeight));
	}

	void SetTitle(const CHAR* aCaption) {
		glfwSetWindowTitle(aCaption);
	}


	//カーソルの表示・非表示
	#pragma region Cursor

	/*
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

	void SetCursorPos(const Vector2& aCursorPos) {
		Cursor::S().SetClientPos(GetHwnd(), aCursorPos);
	}
	Vector2 GetCursorPos() {
		return Cursor::S().GetClientPos(GetHwnd());
	}
	*/

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

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	Vector2 mSize;
	int mWindow;

	#pragma endregion
};


}

}
