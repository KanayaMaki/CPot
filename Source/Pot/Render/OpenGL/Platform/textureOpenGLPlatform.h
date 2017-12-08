#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"
#include "./Pot/File/file.h"


namespace cpot {

namespace openGL {

namespace platform {


class Texture {

public:
	Texture() {
		Reset();
	}
	virtual ~Texture() {
		Release();
	}


protected:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glDeleteTextures(1, &mGLNum);
		Reset();
	}

	virtual void Bind() = 0;


public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}

protected:
	GLuint mGLNum;
};

class Texture2D : public Texture {

public:
	void Load(u32 aWidth, u32 aHeight, void* aInitData, GLenum aInitDataFormat, GLenum aFormat, GLenum aType) {

		glGenTextures(1, &mGLNum);

		glBindTexture(GL_TEXTURE_2D, mGLNum);
		glTexImage2D(GL_TEXTURE_2D, 0, aFormat, aWidth, aHeight, 0, aInitDataFormat, aType, aInitData);

		mWidth = aWidth;
		mHeight = aHeight;
		mFormat = aFormat;
		mType = aType;
	}

	void Load(const CHAR* aFileName) {

		u8 lHeader[54];
		u32 lDataPos;
		u32 lWidth, lHeight;
		u32 lImageSize;

		//ファイルから読み込む
		FileIn lFile;
		lFile.Open(aFileName, true);
		cpot::Buffer b;
		lFile.Read(b);

		b.Read(lHeader, 54);
		if (lHeader[0] != 'B' || lHeader[1] != 'M') {
			CPOT_LOG_NO_ENDL(aFileName);
			CPOT_LOG("はBMPファイルではありません");
			return;
		}

		// バイト配列から整数を読み込む
		lDataPos = *(int*)&(lHeader[0x0A]);
		lImageSize = *(int*)&(lHeader[0x22]);
		lWidth = *(int*)&(lHeader[0x12]);
		lHeight = *(int*)&(lHeader[0x16]);
		
		BOOL lIsRGB = true;

		if (lImageSize == 0) {
			if (b.GetSize() <= lWidth * lHeight * 4) {
				lImageSize = lWidth * lHeight * 3;
			}
			else {
				lImageSize = lWidth * lHeight * 4;
			}
		}

		if (lImageSize != lWidth * lHeight * 3) {
			lIsRGB = false;
		}

		std::unique_ptr<u8> lData(new u8[lImageSize]);
		BufferSize res = b.Read(&(*lData), lImageSize);


		if (lIsRGB) {
			Load(lWidth, lHeight, &(*lData), GL_BGR, GL_RGB, GL_UNSIGNED_BYTE);
		}
		else {
			Load(lWidth, lHeight, &(*lData), GL_BGRA, GL_RGBA, GL_UNSIGNED_BYTE);
		}
	}

	void Load(u32 aWidth, u32 aHeight, GLenum aFormat, GLenum aType) {
		Load(aWidth, aHeight, nullptr, aFormat, aFormat, aType);
	}

	void GenerateMipmap() {
		glBindTexture(GL_TEXTURE_2D, mGLNum);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Bind() {
		glBindTexture(GL_TEXTURE_2D, mGLNum);
	}

public:
	u32 GetWidth() const {
		return mWidth;
	}
	u32 GetHeight() const {
		return mHeight;
	}
	GLenum GetType() const {
		return mType;
	}
	GLenum GetFormat() const {
		return mFormat;
	}

private:
	u32 mWidth;
	u32 mHeight;
	GLenum mType;
	GLenum mFormat;
};

class Texture1D : public Texture {
public:
	void Load(u32 aWidth, void* aInitData, GLenum aInitDataFormat, GLenum aFormat, GLenum aType) {

		glGenTextures(1, &mGLNum);

		glBindTexture(GL_TEXTURE_1D, mGLNum);
		glTexImage1D(GL_TEXTURE_1D, 0, aFormat, aWidth, 0, aInitDataFormat, aType, aInitData);

		mWidth = aWidth;
		mFormat = aFormat;
		mType = aType;
	}

	void Load(u32 aWidth, GLenum aFormat, GLenum aType) {
		Load(aWidth, nullptr, 0, aFormat, aType);
	}

	void GenerateMipmap() {
		glBindTexture(GL_TEXTURE_1D, mGLNum);
		glGenerateMipmap(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, 0);
	}
	void Bind() {
		glBindTexture(GL_TEXTURE_1D, mGLNum);
	}

public:
	u32 GetWidth() const {
		return mWidth;
	}
	GLenum GetType() const {
		return mType;
	}
	GLenum GetFormat() const {
		return mFormat;
	}

private:
	u32 mWidth;
	GLenum mType;
	GLenum mFormat;
};

}

}

}
