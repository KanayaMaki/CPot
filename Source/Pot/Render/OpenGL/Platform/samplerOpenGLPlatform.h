#pragma once

#include "./Atom/atom.h"

#include "./OpenGL/device.h"


namespace cyc {

namespace pot {

namespace openGL {


class Sampler {

public:
	Sampler() {
		Reset();
	}
	~Sampler() {
		Release();
	}
public:
	static Sampler& SNull() {
		static Sampler s;
		return s;
	}


protected:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Load(GLenum aWrapS, GLenum aWrapT) {
		if (IsLoaded()) {
			Release();
		}

		glGenSamplers(1, &mGLNum);
		glSamplerParameteri(mGLNum, GL_TEXTURE_WRAP_S, aWrapS);
		glSamplerParameteri(mGLNum, GL_TEXTURE_WRAP_T, aWrapT);
		glSamplerParameteri(mGLNum, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(mGLNum, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	void Load() {
		Load(GL_REPEAT, GL_REPEAT);
	}
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glDeleteSamplers(1, &mGLNum);
		Reset();
	}

	void Bind() {
		glBindSampler(0, mGLNum);
	}

public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}

private:
	GLuint mGLNum;
};


}

}

}
