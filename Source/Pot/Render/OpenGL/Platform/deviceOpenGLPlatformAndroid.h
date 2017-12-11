#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Config/config.h"
#include "./Pot/Out/out.h"

#include "./Pot/Application/Android/android_native_app_glue.h"


namespace cpot {

namespace openGL {

namespace platform {


class Device : public Singleton<Device> {
	friend Singleton<Device>;

private:
	Device() {
		Clear();
	}

public:
	void Init(ANativeWindow* aWindow) {
		// OpenGL ES と EGL の初期化

		/*
		* 目的の構成の属性をここで指定します。
		* 以下で、オンスクリーン ウィンドウと
		* 互換性のある、各色最低 8 ビットのコンポーネントの EGLConfig を選択します
		*/
		const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
		};
		EGLint w, h, format;
		EGLint numConfigs;
		EGLConfig config;
		EGLSurface surface;
		EGLContext context;

		EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		eglInitialize(display, 0, 0);

		/* ここで、アプリケーションは目的の構成を選択します。このサンプルでは、
		* 抽出条件と一致する最初の EGLConfig を
		* 選択する単純な選択プロセスがあります */
		eglChooseConfig(display, attribs, &config, 1, &numConfigs);

		/* EGL_NATIVE_VISUAL_ID は、ANativeWindow_setBuffersGeometry() に
		* よって受け取られることが保証されている EGLConfig の属性です。
		* EGLConfig を選択したらすぐに、ANativeWindow バッファーを一致させるために
		* EGL_NATIVE_VISUAL_ID を使用して安全に再構成できます。*/
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

		ANativeWindow_setBuffersGeometry(aWindow, 0, 0, format);

		surface = eglCreateWindowSurface(display, config, aWindow, NULL);
		context = eglCreateContext(display, config, NULL, NULL);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
			CPOT_LOG("Unable to eglMakeCurrent");
			return;
		}

		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		mDisplay = display;
		mContext = context;
		mSurface = surface;
		mWidth = w;
		mHeight = h;

		// GL の状態を初期化します。
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}
	void Final() {
		if (mDisplay != EGL_NO_DISPLAY) {
			eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if (mContext != EGL_NO_CONTEXT) {
				eglDestroyContext(mDisplay, mContext);
			}
			if (mSurface != EGL_NO_SURFACE) {
				eglDestroySurface(mDisplay, mSurface);
			}
			eglTerminate(mDisplay);
		}
		Clear();
	}
	void Clear() {
		mDisplay = EGL_NO_DISPLAY;
		mContext = EGL_NO_CONTEXT;
		mSurface = EGL_NO_SURFACE;
	}

public:
	void SwapBuffer() {
		glFlush();
		eglSwapBuffers(mDisplay, mSurface);
	}

private:
	EGLDisplay mDisplay;
	EGLSurface mSurface;
	EGLContext mContext;
	int32_t mWidth;
	int32_t mHeight;

};


}

}

}
