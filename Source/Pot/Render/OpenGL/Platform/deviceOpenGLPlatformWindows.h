#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Config/config.h"
#include "./Pot/Out/out.h"

#include <windows.h>


#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/wglew.h>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")


namespace cpot {

namespace openGL {

namespace platform {


class Device : public Singleton<Device> {
	friend Singleton<Device>;

private:
	Device() {
		
	}

public:
	void Init(HWND aHwnd) {
		//HDCを保存
		mHDC = GetDC(aHwnd);


		//OpenGLの初期化
		int		pixelFormat;
		FILE	*fp;
		int		x, y;
		GLfloat	mat[16];

		//ピクセルフォーマットの作成
		static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),	// この構造体のサイズ
			1,								// バージョン番号
			PFD_DRAW_TO_WINDOW |			// Windowのサポート
			PFD_SUPPORT_OPENGL |			// OpenGLのサポート
			PFD_DOUBLEBUFFER,				// ダブルバッファリングのサポート
			PFD_TYPE_RGBA,					// ＲＧＢＡタイプ
			32,								// カラービット深度
			8, 0, 8, 0, 8, 0,				// color bits ignored 
			8,								// no alpha buffer 
			0,								// shift bit ignored 
			0,								// no accumulation buffer
			0, 0, 0, 0,						// accum bits ignored
			0,								// 32-bit z-buffer
			0,								// no stencil buffer
			0,								// no auxiliary buffer
			PFD_MAIN_PLANE,					// main layer
			0,								// reserved
			0, 0, 0 };						// layer masks ignored

		pixelFormat = ChoosePixelFormat(mHDC, &pfd);
		SetPixelFormat(mHDC, pixelFormat, &pfd);

		mHRC = wglCreateContext(mHDC);
		wglMakeCurrent(mHDC, mHRC);


		//GLEWの初期化
		glewInit();


		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// PC画像メモリーアライメント = Byte単位
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	//RGBしかないなら1を設定するしかない。RGBAなら4アラインメントでいい。多いほうが高速
		glDepthRange(0.0, 1.0);
		glClearDepth(1.0);

		//デプスステンシルの設定
		glDisable(GL_STENCIL_TEST);	//ステンシルテストは無効

									//ビューポートの設定
		glViewport(0, 0, Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}
	void Final() {
		wglMakeCurrent(mHDC, 0);
		wglDeleteContext(mHRC);
	}

public:
	void SwapBuffer() {
		glFlush();
		SwapBuffers(mHDC);
	}

public:
	HDC GetHDC() const {
		return mHDC;
	}
	HGLRC GetHRC() const {
		return mHRC;
	}

private:
	HDC mHDC;
	HGLRC mHRC;
};


}

}

}
