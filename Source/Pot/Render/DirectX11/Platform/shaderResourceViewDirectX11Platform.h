#pragma once

#include "./Pot/Render/DirectX11/Platform/viewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class ShaderResourceView : public View<ID3D11ShaderResourceView> {

	//1Dテクスチャのロード
	#pragma region Load1D

	BOOL Load(Texture1D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE1D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC lRenderTargetViewDesc;
		lRenderTargetViewDesc.Format = lTextureDesc.Format;
		lRenderTargetViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		lRenderTargetViewDesc.Texture1D.MipLevels = 1;
		lRenderTargetViewDesc.Texture1D.MostDetailedMip = 0;


		HRESULT hr;

		hr = Device::S().GetDevice()->CreateShaderResourceView(aTexture.Get(), &lRenderTargetViewDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("ShaderResourceView.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		return true;
	}

	#pragma endregion

	//2Dテクスチャのロード
	#pragma region Load2D

	BOOL Load(Texture2D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE2D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		DXGI_FORMAT lFormat = ConvertFormat(lTextureDesc.Format);


		HRESULT hr;

		hr = Device::S().GetDevice()->CreateShaderResourceView(aTexture.Get(), &GetDesc(lFormat), &mView);
		if (FAILED(hr)) {
			Log::S().Output("ShaderResourceView.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		mHeight = aTexture.GetHeight();
		return true;
	}

	BOOL Load(Texture2D& aTexture, const D3D11_SHADER_RESOURCE_VIEW_DESC& aDesc) {

		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateShaderResourceView(aTexture.Get(), &aDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("ShaderResourceView.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		mHeight = aTexture.GetHeight();
		return true;
	}

	#pragma endregion

	//3Dテクスチャのロード
	#pragma region Load3D

	BOOL Load(Texture3D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE3D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC lShaderResourceViewDesc;
		lShaderResourceViewDesc.Format = lTextureDesc.Format;
		lShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
		lShaderResourceViewDesc.Texture3D.MipLevels = 1;
		lShaderResourceViewDesc.Texture3D.MostDetailedMip = 0;


		HRESULT hr;

		hr = Device::S().GetDevice()->CreateShaderResourceView(aTexture.Get(), &lShaderResourceViewDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("ShaderResourceView.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		mHeight = aTexture.GetHeight();
		return true;
	}

	#pragma endregion


	//ロードの設定を作成
	#pragma region CreateDesc

public:
	static D3D11_SHADER_RESOURCE_VIEW_DESC GetDesc(DXGI_FORMAT aFormat) {
		D3D11_SHADER_RESOURCE_VIEW_DESC lRenderTargetViewDesc;
		lRenderTargetViewDesc.Format = aFormat;
		lRenderTargetViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		lRenderTargetViewDesc.Texture2D.MipLevels = 1;
		lRenderTargetViewDesc.Texture2D.MostDetailedMip = 0;

		return lRenderTargetViewDesc;
	}

	static DXGI_FORMAT ConvertFormat(DXGI_FORMAT aFormat) {
		switch (aFormat) {
			case DXGI_FORMAT_R32_TYPELESS:
				return DXGI_FORMAT_R32_FLOAT;
		}
		return aFormat;
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


}

}

}