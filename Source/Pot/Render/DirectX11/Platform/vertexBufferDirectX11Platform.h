#pragma once

#include "./Pot/Render/DirectX11/Platform/bufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class VertexBuffer : public Buffer {


	//ロード
	#pragma region Load

public:
	BOOL Load(D3D11_USAGE aUsage, UINT aCPUAccessFlags, u32 aVertexSize, u32 aVertexNum, void* aInitData) {
		return Load(Buffer::CreateBufferDesc(aUsage, D3D11_BIND_VERTEX_BUFFER, aCPUAccessFlags, aVertexSize * aVertexNum), aVertexSize, aVertexNum, aInitData);
	}
	BOOL Load(u32 aVertexSize, u32 aVertexNum, void* aInitData) {
		return Load(VertexBuffer::CreateBufferDesc(aVertexSize * aVertexNum), aVertexSize, aVertexNum, aInitData);
	}
	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc, u32 aVertexSize, u32 aVertexNum, void* aInitData) {
		if (!(aBufferDesc.BindFlags & D3D11_BIND_VERTEX_BUFFER)) {
			return false;
		}
		mVertexNum = aVertexNum;
		mVertexSize = aVertexSize;
		return Buffer::Load(aBufferDesc, aInitData);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	u32 GetVertexSize() const {
		return mVertexSize;
	}
	u32 GetVertexNum() const {
		return mVertexNum;
	}

	#pragma endregion


public:
	static D3D11_BUFFER_DESC CreateBufferDesc(u32 aSize) {
		D3D11_BUFFER_DESC lBufferDesc;
		lBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		lBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		lBufferDesc.CPUAccessFlags = 0;
		lBufferDesc.ByteWidth = aSize;
		lBufferDesc.StructureByteStride = 0;
		lBufferDesc.MiscFlags = 0;
		return lBufferDesc;
	}

	//フィールド
	#pragma region Field

private:
	u32 mVertexSize;
	u32 mVertexNum;

	#pragma endregion

};



}

}

}
