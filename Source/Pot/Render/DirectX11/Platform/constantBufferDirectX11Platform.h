#pragma once

#include "./Pot/Render/DirectX11/Platform/bufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class ConstantBuffer : public Buffer {

	//終了処理
	#pragma region Final

public:
	~ConstantBuffer() {
		Release();
	}

	#pragma endregion

	
	//ロード
	#pragma region Load

public:
	template<typename T>
	BOOL Load(T* aInitData) {
		return Load(ConstantBuffer::CreateBufferDesc(sizeof(T)), aInitData);	//委譲
	}

	BOOL Load(void* aInitData, u32 aSize) {
		return Load(ConstantBuffer::CreateBufferDesc(aSize), aInitData);	//委譲
	}

	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc, void* aInitData) {
		if (!(aBufferDesc.BindFlags & D3D11_BIND_CONSTANT_BUFFER)) {
			return false;	//バインドフラグにConstantBufferが入っていないなら、ロード失敗
		}
		mCPUBuffer = aInitData;
		return Buffer::Load(aBufferDesc, nullptr);
	}

	#pragma endregion


	//書き込み
	#pragma region Write

public:
	BOOL Write() {
		return Buffer::Write(mCPUBuffer, GetSize());
	}
	BOOL Write(void* aBuffer) {
		return Buffer::Write(aBuffer, GetSize());
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	template<typename T>
	T* GetCPUBuffer() {
		return (T*)(mCPUBuffer);
	}

	#pragma endregion


	//設定
	#pragma region Setter

public:
	template<typename T>
	void SetCPUBuffer(T* aCPUBuffer) {
		mCPUBuffer = aCPUBuffer;
	}

	#pragma endregion


public:
	static D3D11_BUFFER_DESC CreateBufferDesc(u32 aSize) {
		D3D11_BUFFER_DESC lBufferDesc;
		lBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		lBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		lBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		lBufferDesc.ByteWidth = aSize;
		lBufferDesc.StructureByteStride = 0;
		lBufferDesc.MiscFlags = 0;
		return lBufferDesc;
	}


	//フィールド
	#pragma region Field

private:
	void* mCPUBuffer;

	#pragma endregion

};


}

}

}
