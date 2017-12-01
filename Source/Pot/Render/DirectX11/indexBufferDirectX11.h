//
//	content	:	DirectX11‚Å‚ÌIndexBuffer
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/indexBuffer.h"
#include "./Pot/Render/DirectX11/Platform/indexBufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class IndexBuffer : public IndexBufferBase {

public:
	IndexBuffer() {
		mIndexBuffer.reset(new platform::IndexBuffer);
	}

	#pragma region Load

public:
	BOOL Load(CType aIndexType, u32 aIndexNum, CTopology aTopology, void* aInitData) CPOT_OR {
		return mIndexBuffer->Load(ConvertType(aIndexType), aIndexNum, aInitData, ConvertTopology(aTopology));
	}

	#pragma endregion


	//Žæ“¾
	#pragma region Getter

public:
	CType GetIndexType() const CPOT_OR {
		return ConvertType(mIndexBuffer->GetFormat());
	}
	u32 GetIndexNum() const CPOT_OR {
		return mIndexBuffer->GetIndexNum();
	}
	CTopology GetTopology() const CPOT_OR {
		return ConvertTopology(mIndexBuffer->GetTopology());
	}

	#pragma endregion


public:
	void Release() CPOT_OR {
		mIndexBuffer->Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mIndexBuffer->IsLoaded();
	}


	#pragma region Convert

public:
	static CType ConvertType(DXGI_FORMAT aIndexType) {
		switch (aIndexType) {
			case DXGI_FORMAT_R8_UINT:
				return cU8;
			case DXGI_FORMAT_R16_UINT:
				return cU16;
			case DXGI_FORMAT_R32_SINT:
				return cS32;
		}
		return cInvalidType;
	}
	static DXGI_FORMAT ConvertType(CType aIndexType) {
		switch (aIndexType) {
			case cU8:
				return DXGI_FORMAT_R8_UINT;
			case cU16:
				return DXGI_FORMAT_R16_UINT;
			case cS32:
				return DXGI_FORMAT_R32_SINT;
		}
		return DXGI_FORMAT_UNKNOWN;
	}

	static CTopology ConvertTopology(D3D11_PRIMITIVE_TOPOLOGY aTopology) {
		switch (aTopology) {
			case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
				return cTriangleList;
			case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
				return cTriangleStrip;
		}
		return cInvalidTopology;
	}
	static D3D11_PRIMITIVE_TOPOLOGY ConvertTopology(CTopology aTopology) {
		switch (aTopology) {
			case cTriangleList:
				return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			case cTriangleStrip:
				return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		}
		return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}

	#pragma endregion




public:
	std::shared_ptr<platform::IndexBuffer> mIndexBuffer;

};

}

using IndexBuffer = directX11::IndexBuffer;

}