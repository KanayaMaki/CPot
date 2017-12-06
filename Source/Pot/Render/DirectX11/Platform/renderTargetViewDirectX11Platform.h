#pragma once

#include "./Pot/Render/DirectX11/Platform/viewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class RenderTargetView : public View<ID3D11RenderTargetView> {

public:
	BOOL Load(Texture1D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE1D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		D3D11_RENDER_TARGET_VIEW_DESC lRenderTargetViewDesc;
		lRenderTargetViewDesc.Format = lTextureDesc.Format;
		lRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
		lRenderTargetViewDesc.Texture2D.MipSlice = 0;


		HRESULT hr;

		hr = Device::S().GetDevice()->CreateRenderTargetView(aTexture.Get(), &lRenderTargetViewDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("RenderTargetViewDirectX11.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		return true;
	}

	BOOL Load(Texture2D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE2D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		D3D11_RENDER_TARGET_VIEW_DESC lRenderTargetViewDesc;
		lRenderTargetViewDesc.Format = lTextureDesc.Format;
		lRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		lRenderTargetViewDesc.Texture2D.MipSlice = 0;


		HRESULT hr;

		hr = Device::S().GetDevice()->CreateRenderTargetView(aTexture.Get(), &lRenderTargetViewDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("RenderTargetViewDirectX11.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		mHeight = aTexture.GetHeight();
		return true;
	}

	BOOL Load(Texture3D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE3D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		D3D11_RENDER_TARGET_VIEW_DESC lRenderTargetViewDesc;
		lRenderTargetViewDesc.Format = lTextureDesc.Format;
		lRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
		lRenderTargetViewDesc.Texture2D.MipSlice = 0;


		HRESULT hr;

		hr = Device::S().GetDevice()->CreateRenderTargetView(aTexture.Get(), &lRenderTargetViewDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("RenderTargetViewDirectX11.Load : FailedCreate");
			return false;
		}

		mWidth = aTexture.GetWidth();
		mHeight = aTexture.GetHeight();
		mDepth = aTexture.GetDepth();
		return true;
	}

	void ClearTexture(const Color& aColor) {
		Device::S().GetDeviceContext()->ClearRenderTargetView(mView, aColor.ToFloat4().v);
	}


	//ロードの設定の作成
	#pragma region CreateDesc

public:
	static D3D11_RENDER_TARGET_VIEW_DESC GetDesc(DXGI_FORMAT aFormat) {
		D3D11_RENDER_TARGET_VIEW_DESC lRenderTargetViewDesc;
		lRenderTargetViewDesc.Format = aFormat;
		lRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		lRenderTargetViewDesc.Texture2D.MipSlice = 0;
		return lRenderTargetViewDesc;
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