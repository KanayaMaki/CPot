#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class Buffer {

	//初期化
	#pragma region Init

protected:
	Buffer() {
		Clear();
	}
	~Buffer() {
		Release();
	}

	Buffer(const Buffer&) = delete;
	const Buffer& operator =(const Buffer&) = delete;

protected:
	void Clear() {
		mBuffer = nullptr;
	}

	#pragma endregion


	//ロード
	#pragma region Load

protected:
	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc) {
		return Load(aBufferDesc, nullptr);
	}
	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc, const void* aInitData) {
		if (IsLoaded()) {
			Release();
		}

		D3D11_SUBRESOURCE_DATA* lUseData = nullptr;
		D3D11_SUBRESOURCE_DATA lData;

		if (aInitData) {
			lData.pSysMem = aInitData;
			lData.SysMemPitch = 0;
			lData.SysMemSlicePitch = 0;
			lUseData = &lData;
		}

		HRESULT hr;
		hr = Device::S().GetDevice()->CreateBuffer(&aBufferDesc, lUseData, &mBuffer);

		if (FAILED(hr)) {
			Log::S().Output("CreateError : BufferDirectX11.Load");
			return false;
		}

		mSize = aBufferDesc.ByteWidth;
		return true;
	}

	static D3D11_BUFFER_DESC CreateBufferDesc(D3D11_USAGE aUsage, UINT aBindFlags, UINT aCPUAccessFlags, u32 aSize) {
		D3D11_BUFFER_DESC lBufferDesc;
		lBufferDesc.Usage = aUsage;
		lBufferDesc.BindFlags = aBindFlags;
		lBufferDesc.CPUAccessFlags = aCPUAccessFlags;
		lBufferDesc.ByteWidth = aSize;
		lBufferDesc.StructureByteStride = 0;
		lBufferDesc.MiscFlags = 0;
		return lBufferDesc;
	}

	#pragma endregion


	//リリース
	#pragma region Release

public:
	void Release() {
		//読み込まれていないなら、解放処理をしない
		if (!IsLoaded()) {
			return;
		}
		CPOT_SAFE_RELEASE(mBuffer);
		Clear();
	}

	#pragma endregion


	//バッファへの書き込み
	#pragma region Write

protected:
	BOOL Write(const void* aBuffer, u32 aSize) {

		//マップ処理
		void* lToBuffer = Map(D3D11_MAP_WRITE_DISCARD);

		//もし失敗したら
		if (!lToBuffer) {
			return false;
		}

		//書き込むサイズの計算
		u32 lWriteSize = Min(aSize, GetSize());

		// データ書き込み
		CopyMemory(lToBuffer, aBuffer, lWriteSize);

		//アンマップ
		Unmap();

		return true;	//書き込み成功
	}
	template <typename T>
	BOOL Write(T& aData) {
		return Write(&aData, sizeof(T));
	}

	#pragma endregion


	//バッファからの読み込み
	#pragma region Read

protected:
	BOOL Read(void* aBuffer, u32 aSize) {
		//マップ処理
		void* lFromBuffer = Map(D3D11_MAP_READ);

		//もし失敗したら
		if (!lFromBuffer) {
			return false;
		}

		//読み込むサイズの計算
		u32 lReadSize = Min(aSize, GetSize());

		// データ読み込み
		CopyMemory(aBuffer, lFromBuffer, lReadSize);

		//アンマップ
		Unmap();

		return true;	//読み込み成功
	}
	template <typename T>
	BOOL Read(T& aData) {
		return Read(&aData, sizeof(T));
	}

	#pragma endregion


	//バッファのマップ
	#pragma region Map

protected:
	void* Map(D3D11_MAP aMapType) {
		D3D11_MAPPED_SUBRESOURCE lMappedResource;
		BOOL lResult = Map(lMappedResource, aMapType);

		//マップに失敗したら
		if (!lResult) {
			return nullptr;
		}
		return lMappedResource.pData;
	}
	BOOL Map(D3D11_MAPPED_SUBRESOURCE& aMappedResource, D3D11_MAP aMapType) {
		HRESULT hr;

		//マップ取得

		hr = Device::S().GetDeviceContext()->Map(
			mBuffer,           // マップするリソース
			0,                       // サブリソースのインデックス番号
			aMapType, // 書き込みアクセス
			0,                       //
			&aMappedResource);        // データの書き込み先ポインタ
		if (FAILED(hr)) {
			Log::S().Output("BufferDirectX11.Map : MapFailed");
			return false;
		}
		return true;
	}
	void Unmap() {
		Device::S().GetDeviceContext()->Unmap(mBuffer, 0);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mBuffer != nullptr;
	}

	ID3D11Buffer* GetBuffer() const {
		return mBuffer;
	}

	u32 GetSize() const {
		return mSize;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	ID3D11Buffer* mBuffer;
	u32 mSize;

	#pragma endregion
};


}

}

}
