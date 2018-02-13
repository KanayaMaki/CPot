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
		{
			const cpot::directX11::ShaderLoadDataElement& e = ShaderDirectX11Data::S().Get(aUnionName).vertexShader;

			if (e.filePath != "" && e.entryPoint != "") {
				mVertexShader->CompileFromFile(
					e.filePath.Get(),
					e.entryPoint.Get(),
					"vs_4_0");
			}
		}
		
		{
			const cpot::directX11::ShaderLoadDataElement& e = ShaderDirectX11Data::S().Get(aUnionName).geometryShader;

			if (e.filePath != "" && e.entryPoint != "") {
				mGeometryShader->CompileFromFile(
					e.filePath.Get(),
					e.entryPoint.Get(),
					"gs_4_0");
			}
		}

		{
			const cpot::directX11::ShaderLoadDataElement& e = ShaderDirectX11Data::S().Get(aUnionName).pixelShader;

			if (e.filePath != "" && e.entryPoint != "") {
				mPixelShader->CompileFromFile(
					e.filePath.Get(),
					e.entryPoint.Get(),
					"ps_4_0");
			}
		}
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