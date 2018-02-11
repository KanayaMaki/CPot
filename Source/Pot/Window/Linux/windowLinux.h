//
//	content	:	ウィンドウズのウィンドウの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"
#include "./Pot/Out/out.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

namespace cpot {

namespace linux {



inline void OutputGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

	static const CHAR* kSourceStrings[] = {
		"OpenGL API",
		"Window System",
		"Shader Compiler",
		"Third Party",
		"Application",
		"Other",
	};
	s32 sourceNo = (GL_DEBUG_SOURCE_API_ARB <= source && source <= GL_DEBUG_SOURCE_OTHER_ARB)
		? (source - GL_DEBUG_SOURCE_API_ARB)
		: (GL_DEBUG_SOURCE_OTHER_ARB - GL_DEBUG_SOURCE_API_ARB);

	static const CHAR* kTypeStrings[] = {
		"Error",
		"Deprecated behavior",
		"Undefined behavior",
		"Portability",
		"Performance",
		"Other",
	};
	s32 typeNo = (GL_DEBUG_TYPE_ERROR_ARB <= type && type <= GL_DEBUG_TYPE_OTHER_ARB)
		? (type - GL_DEBUG_TYPE_ERROR_ARB)
		: (GL_DEBUG_TYPE_OTHER_ARB - GL_DEBUG_TYPE_ERROR_ARB);

	static const CHAR* kSeverityStrings[] = {
		"High",
		"Medium",
		"Low",
	};
	s32 severityNo = (GL_DEBUG_SEVERITY_HIGH_ARB <= type && type <= GL_DEBUG_SEVERITY_LOW_ARB)
		? (type - GL_DEBUG_SEVERITY_HIGH_ARB)
		: (GL_DEBUG_SEVERITY_LOW_ARB - GL_DEBUG_SEVERITY_HIGH_ARB);



	if (typeNo == 0) {
		CPOT_LOG("Source : ", kSourceStrings[sourceNo], "    Type : ", kTypeStrings[typeNo], "    ID : ", (s64)id, "    Security : ", kSeverityStrings[severityNo], "    Message : ", (const CHAR*)message);
	}
}


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
	void Init(int* argc, char ** argvconst, Vector2& aWindowSize, const CHAR* aCaption) {
		
		glutInitContextVersion(4, 5);
		glutInitContextFlags(GLUT_DEBUG);
		glutInit(argc, argvconst);

		glutInitWindowPosition(100, 50);
		glutInitWindowSize(aWindowSize.x, aWindowSize.y);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		glutCreateWindow(aCaption);

		glewExperimental = GL_TRUE;
		glewInit();

		glDebugMessageCallbackARB(cpot::linux::OutputGLDebugMessage, nullptr);

		CPOT_LOG((const CHAR*)glGetString(GL_VERSION));
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

	void SetTitle(const CHAR* aTitle) {}


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

	#pragma endregion
};


}

}
