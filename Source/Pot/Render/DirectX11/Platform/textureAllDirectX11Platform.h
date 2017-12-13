#pragma once

#include"./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"
#include"./Pot/Render/DirectX11/Platform/renderTargetViewDirectX11Platform.h"
#include"./Pot/Render/DirectX11/Platform/shaderResourceViewDirectX11Platform.h"
#include"./Pot/Render/DirectX11/Platform/depthStencilViewDirectX11Platform.h"


namespace cpot {

namespace directX11 {

namespace platform {


#pragma region Texture2D

class Texture2DAll {

public:
	void Release() {
		CPOT_SAFE_RELEASE(mTexture);
		CPOT_SAFE_RELEASE(mRenderTargetView);
		CPOT_SAFE_RELEASE(mDepthStencilView);
		CPOT_SAFE_RELEASE(mShaderResourceView);
		Reset();
	}
	void Reset() {
		mTexture = nullptr;
		mRenderTargetView = nullptr;
		mShaderResourceView = nullptr;
		mDepthStencilView = nullptr;
	}

	BOOL IsLoaded() const {
		if (mTexture == nullptr) return false;
		return mTexture->IsLoaded();
	}

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

		D3D11_TEXTURE2D_DESC lDesc = aDesc;
		if (lDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL) {
			lDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		}

		mTexture.reset(new Texture2D);
		mTexture->Load(lDesc, aInitData);
		LoadView();
		return true;
	}

	BOOL Load(const CHAR* aFileName, D3DX11_IMAGE_LOAD_INFO* aLoadInfo) {
		if (IsLoaded()) {
			Release();
		}
		mTexture.reset(new Texture2D);
		mTexture->Load(aFileName, aLoadInfo);
		LoadView();
		return true;
	}
	BOOL Load(const CHAR* aFileName) {
		return Load(aFileName, nullptr);
	}
	BOOL Load(std::shared_ptr<Texture2D> aTexture) {
		if (IsLoaded()) {
			Release();
		}
		mTexture = aTexture;
		LoadView();
		return true;
	}

	#pragma endregion

	void LoadView() {
		if (mTexture->IsBindRenderTarget()) {
			mRenderTargetView.reset(new RenderTargetView);
			mRenderTargetView->Load(*mTexture);
		}
		if (mTexture->IsBindDepthStencil()) {
			mDepthStencilView.reset(new DepthStencilView);
			mDepthStencilView->Load(*mTexture);
		}
		if (mTexture->IsBindShaderResource()) {
			mShaderResourceView.reset(new ShaderResourceView);
			mShaderResourceView->Load(*mTexture);
		}
	}


	//取得
	#pragma region Getter

public:
	std::shared_ptr<Texture2D> GetTexture() const {
		return mTexture;
	}
	std::shared_ptr<RenderTargetView> GetRenderTargetView() const{
		return mRenderTargetView;
	}
	std::shared_ptr<ShaderResourceView> GetShaderResourceView() const {
		return mShaderResourceView;
	}
	std::shared_ptr<DepthStencilView> GetDepthStencilView() const {
		return mDepthStencilView;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::shared_ptr<Texture2D> mTexture;
	std::shared_ptr<RenderTargetView> mRenderTargetView;
	std::shared_ptr<ShaderResourceView> mShaderResourceView;
	std::shared_ptr<DepthStencilView> mDepthStencilView;

	#pragma endregion

};

#pragma endregion


}

}

}