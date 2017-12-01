//
//	content	:	TextureのDirectX11での実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/shader.h"
#include "./Pot/Render/DirectX11/Platform/shaderDirectX11Platform.h"


namespace cpot {

namespace directX11 {

struct ShaderLoadDataElement {
	String<128> filePath;
	String<64> entryPoint;
};

struct ShaderLoadData {
	ShaderLoadDataElement vertexShader;
	ShaderLoadDataElement geometryShader;
	ShaderLoadDataElement pixelShader;
};


class ShaderDirectX11Data : public ResourceLoadList<ShaderDirectX11Data, ShaderLoadData> {

};

class Shader : public ShaderBase {

public:
	Shader() {
		mVertexShader.reset(new platform::VertexShader);
		mGeometryShader.reset(new platform::GeometryShader);
		mPixelShader.reset(new platform::PixelShader);
	}

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mVertexShader->CompileFromFile(
			ShaderDirectX11Data::S().Get(aUnionName).vertexShader.filePath.Get(),
			ShaderDirectX11Data::S().Get(aUnionName).vertexShader.entryPoint.Get(),
			"vs_4_0");
		mGeometryShader->CompileFromFile(
			ShaderDirectX11Data::S().Get(aUnionName).geometryShader.filePath.Get(),
			ShaderDirectX11Data::S().Get(aUnionName).geometryShader.entryPoint.Get(),
			"gs_4_0");
		mPixelShader->CompileFromFile(
			ShaderDirectX11Data::S().Get(aUnionName).pixelShader.filePath.Get(),
			ShaderDirectX11Data::S().Get(aUnionName).pixelShader.entryPoint.Get(),
			"ps_4_0");
	};

public:
	void Release() CPOT_OR {
		mVertexShader->Release();
		mGeometryShader->Release();
		mPixelShader->Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mVertexShader->IsLoaded() || mGeometryShader->IsLoaded() || mPixelShader->IsLoaded();
	};


	//フィールド
	#pragma region Field

public:
	std::shared_ptr<platform::VertexShader> mVertexShader;
	std::shared_ptr<platform::GeometryShader> mGeometryShader;
	std::shared_ptr<platform::PixelShader> mPixelShader;

	#pragma endregion
};

}

using Shader = directX11::Shader;

}