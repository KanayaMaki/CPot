//
//	content	:	ShaderのOpenGLでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/shader.h"
#include "./Pot/Render/OpenGL/Platform/shaderOpenGLPlatform.h"


namespace cpot {

namespace openGL {

struct ShaderLoadDataElement {
	String<128> filePath;
};

struct ShaderLoadData {
	ShaderLoadDataElement vertexShader;
	ShaderLoadDataElement geometryShader;
	ShaderLoadDataElement fragmentShader;
};


class ShaderOpenGLData : public ResourceLoadList<ShaderOpenGLData, ShaderLoadData> {

};

class Shader : public ShaderBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mProgram.Load(ShaderOpenGLData::S().Get(aUnionName).vertexShader.filePath.Get(),
			ShaderOpenGLData::S().Get(aUnionName).geometryShader.filePath.Get(),
			ShaderOpenGLData::S().Get(aUnionName).fragmentShader.filePath.Get());
	};

public:
	void Release() CPOT_OR {
		mProgram.Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mProgram.IsLoaded();
	};


	//フィールド
	#pragma region Field

public:
	platform::Program mProgram;
	
	#pragma endregion
};

}

using Shader = openGL::Shader;

}