#pragma once

#include "./Pot/Render/DirectX11/Platform/viewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class DepthStencilView : public View<ID3D11DepthStencilView> {

	//ロードの設定の作成
	#pragma region CreateDesc

public:
	static D3D11_DEPTH_STENCIL_VIEW_DESC GetDesc(DXGI_FORMAT aFormat) {
		D3D11_DEPTH_STENCIL_VIEW_DESC lDepthStencilViewDesc;
		lDepthStencilViewDesc.Format = aFormat;
		lDepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		lDepthStencilViewDesc.Texture2D.MipSlice = 0;
		lDepthStencilViewDesc.Flags = 0;
		return lDepthStencilViewDesc;
	}

	static DXGI_FORMAT ConvertFormat(DXGI_FORMAT aFormat) {
		switch (aFormat) {
			case DXGI_FORMAT_R32_TYPELESS:
				return DXGI_FORMAT_D32_FLOAT;
		}
		return aFormat;
	}

	#pragma endregion


	//ロード
	#pragma region Load


public:
	BOOL Load(Texture2D& aTexture) {

		if (IsLoaded()) {
			Release();
		}

		D3D11_TEXTURE2D_DESC lTextureDesc;
		aTexture.Get()->GetDesc(&lTextureDesc);

		//テクスチャがTYPELESSなどで作られていた場合、フォーマットを修正する
		DXGI_FORMAT lFormat = ConvertFormat(lTextureDesc.Format);

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateDepthStencilView(aTexture.Get(), &GetDesc(lFormat), &mView);
		if (FAILED(hr)) {
			Log::S().Output("DepthStencilViewDirectX11.Load : FailedCreate");
			return false;
		}

		return true;
	}

	BOOL Load(Texture2D& aTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC& aDesc) {

		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateDepthStencilView(aTexture.Get(), &aDesc, &mView);
		if (FAILED(hr)) {
			Log::S().Output("DepthStencilViewDirectX11.Load : FailedCreate");
			return false;
		}

		return true;
	}

	#pragma endregion


	//デプスやステンシル値をクリアする
	#pragma region ClearDepthStencil

public:
	void ClearDepthStencil(BOOL aIsDepth, BOOL aIsStencil, f32 aDepthValue, u8 aStencilValue) {
		UINT lClearFlag = 0;
		if (aIsDepth == true) {
			lClearFlag += D3D11_CLEAR_DEPTH;
		}
		if (aIsStencil == true) {
			lClearFlag += D3D11_CLEAR_STENCIL;
		}
		Device::S().GetDeviceContext()->ClearDepthStencilView(mView, lClearFlag, aDepthValue, aStencilValue);
	}
	void ClearDepthStencil(BOOL aIsDepth, BOOL aIsStencil) {
		ClearDepthStencil(aIsDepth, aIsStencil, 1.0f, 0);
	}
	void ClearDepthStencil() {
		ClearDepthStencil(true, true);
	}

	void ClearDepth(f32 aDepth) {
		ClearDepthStencil(true, false, aDepth, 0);
	}
	void ClearDepth() {
		ClearDepthStencil(true, false);
	}

	void ClearStencil(u8 aStencilValue) {
		ClearDepthStencil(false, true, 0.0f, aStencilValue);
	}
	void ClearStencil() {
		ClearDepthStencil(false, true);
	}

	#pragma endregion


};


}

}

}