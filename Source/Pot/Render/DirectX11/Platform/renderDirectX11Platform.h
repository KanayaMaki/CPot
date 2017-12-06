#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Render/DirectX11/Platform/elementManagerDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/shaderManagerDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/textureAllDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/usefullDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/viewportDirectX11Platform.h"


namespace cpot {

namespace directX11 {

namespace platform {


class Render : public Singleton<Render> {

public:
	BlendStateManager& GetBlendStateManager() {
		return mBlendStateManager;
	}
	DepthStencilStateManager& GetDepthStencilStateManager() {
		return mDepthStencilStateManager;
	}
	RasterizerStateManager& GetRasterizerStateManager() {
		return mRasterizerStateManager;
	}
	RenderTargetViewManager& GetRenderTargetViewManager() {
		return mRenderTargetViewManager;
	}
	DepthStencilViewManager& GetDepthStencilViewManager() {
		return mDepthStencilViewManager;
	}
	VertexBufferManager& GetVertexBufferManager() {
		return mVertexBufferManager;
	}
	IndexBufferManager& GetIndexBufferManager() {
		return mIndexBufferManager;
	}
	InputLayoutManager& GetInputLayoutManager() {
		return mInputLayoutManager;
	}
	ViewPortManager& GetViewPortManager() {
		return mViewPortManager;
	}

	VertexShaderManager& GetVertexShaderManager() {
		return mVertexShaderManager;
	}
	GeometryShaderManager& GetGeometryShaderManager() {
		return mGeometryShaderManager;
	}
	PixelShaderManager& GetPixelShaderManager() {
		return mPixelShaderManager;
	}
	DomainShaderManager& GetDomainShaderManager() {
		return mDomainShaderManager;
	}
	HullShaderManager& GetHullShaderManager() {
		return mHullShaderManager;
	}
	ComputeShaderManager& GetComputeShaderManager() {
		return mComputeShaderManager;
	}

	void DrawIndexed(UINT aIndexCount, UINT aStartIndexLocation, UINT aBaseVertexLocation) {
		Device::S().GetDeviceContext()->DrawIndexed(aIndexCount, aStartIndexLocation, aBaseVertexLocation);
	}
	void Draw(UINT aVertexCount, UINT aStartVertexLocation) {
		Device::S().GetDeviceContext()->Draw(aVertexCount, aStartVertexLocation);
	}

	void SetToDevice() {
		mBlendStateManager.SetToDevice();
		mDepthStencilStateManager.SetToDevice();
		mRasterizerStateManager.SetToDevice();
		mRenderTargetViewManager.SetToDevice(mDepthStencilViewManager);
		mIndexBufferManager.SetToDevice();
		mVertexBufferManager.SetToDevice();
		mInputLayoutManager.SetToDevice();
		mViewPortManager.SetToDevice();

		mVertexShaderManager.SetToDevice();
		mGeometryShaderManager.SetToDevice();
		mPixelShaderManager.SetToDevice();
		mHullShaderManager.SetToDevice();
		mDomainShaderManager.SetToDevice();
		mComputeShaderManager.SetToDevice();
	}

	HRESULT Present() {
		return Device::S().GetSwapChain()->Present(0, 0);
	}

private:
	BlendStateManager mBlendStateManager;
	DepthStencilStateManager mDepthStencilStateManager;
	RasterizerStateManager mRasterizerStateManager;
	RenderTargetViewManager mRenderTargetViewManager;
	DepthStencilViewManager mDepthStencilViewManager;
	VertexBufferManager mVertexBufferManager;
	IndexBufferManager mIndexBufferManager;
	InputLayoutManager mInputLayoutManager;
	ViewPortManager mViewPortManager;

	VertexShaderManager mVertexShaderManager;
	GeometryShaderManager mGeometryShaderManager;
	PixelShaderManager mPixelShaderManager;
	DomainShaderManager mDomainShaderManager;
	HullShaderManager mHullShaderManager;
	ComputeShaderManager mComputeShaderManager;
};


}

}

}
