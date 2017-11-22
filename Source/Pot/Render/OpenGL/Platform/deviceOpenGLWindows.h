#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"


#include <windows.h>

#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/wglew.h>


namespace cpot {

namespace openGL {

namespace platform {

class Device : public Singleton<Device> {

public:
	void Init(HWND aHwnd);
	void Final();


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