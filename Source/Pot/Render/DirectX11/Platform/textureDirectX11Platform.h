#pragma once

#include"./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"


namespace cpot {

namespace directX11 {

namespace platform {


inline D3DX11_IMAGE_LOAD_INFO GetTextureLoadInfo(D3D11_USAGE aUsage, UINT aBindFlags, UINT aCPUAccessFlags) {

	D3DX11_IMAGE_LOAD_INFO lLoadInfo;
	lLoadInfo.Width = D3DX11_DEFAULT;
	lLoadInfo.Height = D3DX11_DEFAULT;
	lLoadInfo.Depth = D3DX11_DEFAULT;
	lLoadInfo.FirstMipLevel = D3DX11_DEFAULT;
	lLoadInfo.MipLevels = 1;
	lLoadInfo.Usage = aUsage;
	lLoadInfo.BindFlags = aBindFlags;
	lLoadInfo.CpuAccessFlags = aCPUAccessFlags;
	lLoadInfo.MiscFlags = D3DX11_DEFAULT;
	lLoadInfo.Format = DXGI_FORMAT_FROM_FILE;
	lLoadInfo.Filter = D3DX11_DEFAULT;
	lLoadInfo.MipFilter = D3DX11_DEFAULT;
	lLoadInfo.pSrcInfo = nullptr;

	return lLoadInfo;
}

inline D3DX11_IMAGE_LOAD_INFO GetTextureLoadInfoDefault() {
	return GetTextureLoadInfo(D3D11_USAGE_DEFAULT, GetBindFlags(false, true), GetCPUAccessFlags(false, false));
}



#pragma region Texture

template <typename TextureType>
class Texture {

	//初期化
	#pragma region Init

public:
	Texture() {
		Clear();
	}

	Texture(const Texture&) = delete;
	const Texture& operator =(const Texture&) = delete;

protected:
	void Clear() {
		mTexture = nullptr;
	}

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	~Texture() {
		Release();
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		CPOT_SAFE_RELEASE(mTexture);
		Clear();
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mTexture != nullptr;
	}

	TextureType* Get() const {
		return mTexture;
	}

	//所有権を譲る
	TextureType* Free() {
		TextureType* lTexture = mTexture;
		Clear();
		return lTexture;
	}

	BOOL IsBindRenderTarget() const {
		return mData.IsStand(cBindRenderTarget);
	}
	BOOL IsBindShaderResource() const {
		return mData.IsStand(cBindShaderResource);
	}
	BOOL IsBindDepthStencil() const {
		return mData.IsStand(cBindDepthStencil);
	}
	BOOL IsCPUAccessReadable() const {
		return mData.IsStand(cCPUAccessReadable);
	}
	BOOL IsCPUAccessWritable() const {
		return mData.IsStand(cCPUAccessWritable);
	}

	void SetBindFlags(UINT aBindFlags) {
		mData.Flag(cBindRenderTarget, IsRenderTarget(aBindFlags));
		mData.Flag(cBindShaderResource, IsShaderResource(aBindFlags));
		mData.Flag(cBindDepthStencil, IsDepthStencil(aBindFlags));
	}
	void SetCPUAccessFlags(UINT aCPUAccessFlags) {
		mData.Flag(cCPUAccessReadable, IsReadable(aCPUAccessFlags));
		mData.Flag(cCPUAccessWritable, IsWritable(aCPUAccessFlags));
	}

	#pragma endregion


	enum CData {
		cBindRenderTarget,
		cBindShaderResource,
		cBindDepthStencil,
		cCPUAccessReadable,
		cCPUAccessWritable,
	};

	//フィールド
	#pragma region Field

protected:
	TextureType* mTexture;
	BitFlag mData;

	#pragma endregion

};

#pragma endregion


#pragma region Texture1D

class Texture1D : public Texture<ID3D11Texture1D> {

public:
	//ロード
	#pragma region Load

	BOOL Load(const D3D11_TEXTURE1D_DESC& aDesc) {
		return Load(aDesc, nullptr);
	}
	BOOL Load(const D3D11_TEXTURE1D_DESC& aDesc, void* aInitData) {
		if (IsLoaded()) {
			Release();
		}

		D3D11_SUBRESOURCE_DATA* lUseSubResource;
		D3D11_SUBRESOURCE_DATA lSubResource;

		if (aInitData == nullptr) {
			lUseSubResource = nullptr;
		}
		else {
			lSubResource.pSysMem = aInitData;
			lSubResource.SysMemPitch = 0;
			lSubResource.SysMemSlicePitch = 0;
			lUseSubResource = &lSubResource;
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateTexture1D(&aDesc, lUseSubResource, &mTexture);
		if (FAILED(hr)) {
			Log::S().Output("Texture1D.Load : FailedCreate");
			return false;
		}

		mWidth = aDesc.Width;
		return true;
	}

	#pragma endregion


	//ロードする設定の作成
	#pragma region CreateDesc
	static D3D11_TEXTURE1D_DESC CreateDesc(u32 aWidth, DXGI_FORMAT aFormat, D3D11_USAGE aUsage, UINT aBindFlags, UINT aCPUAccessFlags) {

		D3D11_TEXTURE1D_DESC lTextureDesc;
		ZeroMemory(&lTextureDesc, sizeof(lTextureDesc));
		lTextureDesc.Width = aWidth;
		lTextureDesc.MipLevels = 1;
		lTextureDesc.ArraySize = 1;
		lTextureDesc.Format = aFormat;
		lTextureDesc.Usage = aUsage;
		lTextureDesc.BindFlags = aBindFlags;
		lTextureDesc.CPUAccessFlags = aCPUAccessFlags;

		return lTextureDesc;
	}

	static D3D11_TEXTURE1D_DESC CreateDesc(ID3D11Texture1D* aTexture) {
		D3D11_TEXTURE1D_DESC lTextureDesc;
		aTexture->GetDesc(&lTextureDesc);
		return lTextureDesc;
	}
	#pragma endregion


	//取得
	#pragma region Getter

public:
	u32 GetWidth() const {
		return mWidth;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	u32 mWidth;

	#pragma endregion

};

#pragma endregion


#pragma region Texture2D

class Texture2D : public Texture<ID3D11Texture2D> {

public:
	
	//ロード
	#pragma region Load

	BOOL Load(const D3D11_TEXTURE2D_DESC& aDesc) {
		return Load(aDesc, nullptr);
	}
	BOOL Load(const D3D11_TEXTURE2D_DESC& aDesc, void* aInitData) {
		if (IsLoaded()) {
			Release();
		}

		D3D11_SUBRESOURCE_DATA* lUseSubResource;
		D3D11_SUBRESOURCE_DATA lSubResource;

		if (aInitData == nullptr) {
			lUseSubResource = nullptr;
		}
		else {
			lSubResource.pSysMem = aInitData;
			lSubResource.SysMemPitch = GetFormatSize(aDesc.Format) * aDesc.Width;
			lSubResource.SysMemSlicePitch = 0;
			lUseSubResource = &lSubResource;
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateTexture2D(&aDesc, lUseSubResource, &mTexture);
		if (FAILED(hr)) {
			Log::S().Output("Texture2D.Load : FailedCreate");
			return false;
		}

		mWidth = aDesc.Width;
		mHeight = aDesc.Height;
		SetBindFlags(aDesc.BindFlags);
		SetCPUAccessFlags(aDesc.CPUAccessFlags);

		return true;
	}

	BOOL Load(const CHAR* aFileName, D3DX11_IMAGE_LOAD_INFO* aLoadInfo) {
		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = D3DX11CreateTextureFromFileA(Device::S().GetDevice(), aFileName, aLoadInfo, nullptr, (ID3D11Resource**)(&mTexture), nullptr);
		if (FAILED(hr)) {
			Log::S().Output("Texture2D.Load : FailedCreate");
			return false;
		}

		D3D11_TEXTURE2D_DESC lDesc = CreateDesc(mTexture);
		mWidth = lDesc.Width;
		mHeight = lDesc.Height;
		SetBindFlags(lDesc.BindFlags);
		SetCPUAccessFlags(lDesc.CPUAccessFlags);

		return true;
	}
	void Load(const CHAR* aFileName) {
		Load(aFileName, nullptr);
	}

	void Set(ID3D11Texture2D* aTexture) {
		if (IsLoaded()) {
			Release();
		}
		mTexture = aTexture;

		auto lDesc = CreateDesc(mTexture);
		mWidth = lDesc.Width;
		mHeight = lDesc.Height;
		SetBindFlags(lDesc.BindFlags);
		SetCPUAccessFlags(lDesc.CPUAccessFlags);
	}

	#pragma endregion


	//ロードの設定の作成
	#pragma region CreateDesc

	static D3D11_TEXTURE2D_DESC CreateDesc(u32 aWidth, u32 aHeight, DXGI_FORMAT aFormat, D3D11_USAGE aUsage, UINT aBindFlags, UINT aCPUAccessFlags) {

		D3D11_TEXTURE2D_DESC lTextureDesc;
		ZeroMemory(&lTextureDesc, sizeof(lTextureDesc));
		lTextureDesc.Width = aWidth;
		lTextureDesc.Height = aHeight;
		lTextureDesc.MipLevels = 1;
		lTextureDesc.ArraySize = 1;
		lTextureDesc.Format = aFormat;
		lTextureDesc.SampleDesc.Count = 1;
		lTextureDesc.SampleDesc.Quality = 0;
		lTextureDesc.Usage = aUsage;
		lTextureDesc.BindFlags = aBindFlags;
		lTextureDesc.CPUAccessFlags = aCPUAccessFlags;
		lTextureDesc.MiscFlags = 0;

		return lTextureDesc;
	}

	static D3D11_TEXTURE2D_DESC CreateDesc(ID3D11Texture2D* aTexture) {
		D3D11_TEXTURE2D_DESC lTextureDesc;
		aTexture->GetDesc(&lTextureDesc);
		return lTextureDesc;
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	u32 GetWidth() const {
		return mWidth;
	}
	u32 GetHeight() const {
		return mHeight;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	u32 mWidth;
	u32 mHeight;

	#pragma endregion

};

#pragma endregion


#pragma region Texture3D

class Texture3D : public Texture<ID3D11Texture3D> {

public:
	//ロード
	#pragma region Load

	BOOL Load(const D3D11_TEXTURE3D_DESC& aDesc) {
		return Load(aDesc, nullptr);
	}
	BOOL Load(const D3D11_TEXTURE3D_DESC& aDesc, void* aInitData) {
		if (IsLoaded()) {
			Release();
		}

		D3D11_SUBRESOURCE_DATA* lUseSubResource;
		D3D11_SUBRESOURCE_DATA lSubResource;

		if (aInitData == nullptr) {
			lUseSubResource = nullptr;
		}
		else {
			lSubResource.pSysMem = aInitData;
			lSubResource.SysMemPitch = GetFormatSize(aDesc.Format) * aDesc.Width;
			lSubResource.SysMemSlicePitch = 0;
			lUseSubResource = &lSubResource;
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateTexture3D(&aDesc, lUseSubResource, &mTexture);
		if (FAILED(hr)) {
			Log::S().Output("Texture3D.Load : FailedCreate");
			return false;
		}

		mWidth = aDesc.Width;
		mHeight = aDesc.Height;
		mDepth = aDesc.Depth;

		return true;
	}

	#pragma endregion


	//ロードの設定の作成
	#pragma region CreateDesc

	static D3D11_TEXTURE3D_DESC CreateDesc(u32 aWidth, u32 aHeight, u32 aDepth, DXGI_FORMAT aFormat, D3D11_USAGE aUsage, UINT aBindFlags, UINT aCPUAccessFlags) {

		D3D11_TEXTURE3D_DESC lTextureDesc;
		ZeroMemory(&lTextureDesc, sizeof(lTextureDesc));
		lTextureDesc.Width = aWidth;
		lTextureDesc.Height = aHeight;
		lTextureDesc.Depth = aDepth;
		lTextureDesc.MipLevels = 1;
		lTextureDesc.Format = aFormat;
		lTextureDesc.Usage = aUsage;
		lTextureDesc.BindFlags = aBindFlags;
		lTextureDesc.CPUAccessFlags = aCPUAccessFlags;
		lTextureDesc.MiscFlags = 0;

		return lTextureDesc;
	}

	static D3D11_TEXTURE3D_DESC CreateDesc(ID3D11Texture3D* aTexture) {
		D3D11_TEXTURE3D_DESC lTextureDesc;
		aTexture->GetDesc(&lTextureDesc);
		return lTextureDesc;
	}
	#pragma endregion


	//取得
	#pragma region Getter

public:
	u32 GetWidth() const {
		return mWidth;
	}
	u32 GetHeight() const {
		return mHeight;
	}
	u32 GetDepth() const {
		return mDepth;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	u32 mWidth;
	u32 mHeight;
	u32 mDepth;

	#pragma endregion

};

#pragma endregion


}

}

}