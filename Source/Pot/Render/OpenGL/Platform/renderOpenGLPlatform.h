#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/managerOpenGLPlatform.h"

namespace cpot {

namespace openGL {

namespace platform {


class Render : public Singleton<Render> {
private:
	friend Singleton<Render>;
	Render() {
		
	}

public:
	void SwapBuffer() {
		Device::S().SwapBuffer();
	}
	void Clear() {

	}

	ArrayBufferManager& GetArrayBufferManager() {
		return mArrayBufferManager;
	}
	BlendManager& GetBlendManager() {
		return mBlendManager;
	}
	CullManager& GetCullManager() {
		return mCullManager;
	}
	UniformBufferManager& GetUniformBufferManager() {
		return mUniformBufferManager;
	}
	ElementArrayBufferManager& GetElementArrayBufferManager() {
		return mElementArrayBufferManager;
	}
	VertexArrayObjectManager& GetVertexArrayObjectManager() {
		return mVertexArrayObjectManager;
	}
	ProgramManager& GetProgramManager() {
		return mProgramManager;
	}
	TextureManager& GetTextureManager() {
		return mTextureManager;
	}
	SamplerManager& GetSamplerManager() {
		return mSamplerManager;
	}
	DepthManager& GetDepthManager() {
		return mDepthManager;
	}
	StencilManager& GetStencilManager() {
		return mStencilManager;
	}
	RenderTextureManager& GetRenderTextureManager() {
		return mRenderTextureManager;
	}
	InputLayoutManager& GetInputLayoutManager() {
		return mInputLayoutManager;
	}
	ViewportManager& GetViewportManager() {
		return mViewportManager;
	}

	void Init() {

	}
	void DrawElement() {
		glDrawElements(
			mElementArrayBufferManager.Get()->GetMode(),      // mode
			mElementArrayBufferManager.Get()->GetIndexNum(),    // count
			mElementArrayBufferManager.Get()->GetType(),   // type
			nullptr           // element array buffer offset
		);
	}
	void DrawElement(u32 aCount, u32 aOffset) {
		glDrawElements(
			mElementArrayBufferManager.Get()->GetMode(),      // mode
			aCount,    // count
			mElementArrayBufferManager.Get()->GetType(),   // type
			(void*)(aOffset * mElementArrayBufferManager.Get()->GetIndexSize())
		);
	}

	void Draw(GLenum aMode, u32 aVertexCount, u32 aStartVertexLocation) {
		glDrawArrays(aMode, aStartVertexLocation, aVertexCount);
	}
	void SetToDevice() {
		mBlendManager.SetToDevice();
		mCullManager.SetToDevice();
		mProgramManager.SetToDevice(mUniformBufferManager);
		mTextureManager.SetToDevice(mSamplerManager);
		mDepthManager.SetToDevice();
		mStencilManager.SetToDevice();
		mVertexArrayObjectManager.SetToDevice();
		mElementArrayBufferManager.SetToDevice();
		mRenderTextureManager.SetToDevice();
		mInputLayoutManager.SetToDevice(mArrayBufferManager);
		mViewportManager.SetToDevice();
	}


private:
	ArrayBufferManager mArrayBufferManager;
	BlendManager mBlendManager;
	CullManager mCullManager;
	VertexArrayObjectManager mVertexArrayObjectManager;
	ElementArrayBufferManager mElementArrayBufferManager;
	ProgramManager mProgramManager;
	UniformBufferManager mUniformBufferManager;
	TextureManager mTextureManager;
	SamplerManager mSamplerManager;
	DepthManager mDepthManager;
	StencilManager mStencilManager;
	RenderTextureManager mRenderTextureManager;
	InputLayoutManager mInputLayoutManager;
	ViewportManager mViewportManager;
};


void SaveScreenShot(Texture2D& aTexture, const CHAR* aName);
void SaveScreenShot(const CHAR* aName);



inline void __stdcall OutputGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

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



}

}

}
