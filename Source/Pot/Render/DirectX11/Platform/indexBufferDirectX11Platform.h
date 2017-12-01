#pragma once

#include "./Pot/Render/DirectX11/Platform/bufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class IndexBuffer : public Buffer {

	//ロード
	#pragma region Load

public:
	BOOL Load(D3D11_USAGE aUsage, UINT aCPUAccessFlags, DXGI_FORMAT aIndexFormat, u32 aIndexNum, void* aInitData, D3D11_PRIMITIVE_TOPOLOGY aTopology) {
		return Load(Buffer::CreateBufferDesc(aUsage, D3D11_BIND_INDEX_BUFFER, aCPUAccessFlags, GetFormatSize(aIndexFormat) * aIndexNum), aIndexFormat, aIndexNum, aInitData, aTopology);
	}
	BOOL Load(DXGI_FORMAT aIndexFormat, u32 aIndexNum, void* aInitData, D3D11_PRIMITIVE_TOPOLOGY aTopology) {
		return Load(CreateBufferDesc(GetFormatSize(aIndexFormat) * aIndexNum), aIndexFormat, aIndexNum, aInitData, aTopology);
	}
	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc, DXGI_FORMAT aIndexFormat, u32 aIndexNum, void* aInitData, D3D11_PRIMITIVE_TOPOLOGY aTopology) {
		if ((aBufferDesc.BindFlags & D3D11_BIND_INDEX_BUFFER) == false) {
			return false;
		}
		mFormat = aIndexFormat;
		mTopology = aTopology;
		mIndexNum = aIndexNum;
		return Buffer::Load(aBufferDesc, aInitData);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	DXGI_FORMAT GetFormat() const {
		return mFormat;
	}
	u32 GetIndexNum() const {
		return mIndexNum;
	}
	u32 GetIndexSize() const {
		return GetFormatSize(GetFormat());
	}
	D3D11_PRIMITIVE_TOPOLOGY GetTopology() const {
		return mTopology;
	}

	#pragma endregion


	//静的
	#pragma region Static

public:
	static D3D11_BUFFER_DESC CreateBufferDesc(u32 aSize) {
		D3D11_BUFFER_DESC lBufferDesc;
		lBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		lBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		lBufferDesc.CPUAccessFlags = 0;
		lBufferDesc.ByteWidth = aSize;
		lBufferDesc.StructureByteStride = 0;
		lBufferDesc.MiscFlags = 0;
		return lBufferDesc;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	DXGI_FORMAT mFormat;
	D3D11_PRIMITIVE_TOPOLOGY mTopology;
	u32 mIndexNum;

	#pragma endregion


};


}

}

}
