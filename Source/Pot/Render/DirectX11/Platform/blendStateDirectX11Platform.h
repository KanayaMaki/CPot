#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class BlendState : public State<ID3D11BlendState> {

	//ÉçÅ[Éh
	#pragma region Load

public:
	BOOL Load(const D3D11_BLEND_DESC& aDesc) {
		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateBlendState(&aDesc, &mState);
		if (FAILED(hr)) {
			Log::S().Output("BlendStateDirectX11.Load : FailedCreate");
			return false;
		}

		return true;
	}

	BOOL Load() {
		return Load(CreateDescNormal());	//àœè˜
	}

	#pragma endregion


	//ê›íËÇÃéÊìæ
	#pragma region CreateDesc

public:
	static D3D11_BLEND_DESC CreateDesc(D3D11_BLEND aSrcBlend, D3D11_BLEND aDestBlend, D3D11_BLEND_OP aBlendOp,
		D3D11_BLEND aSrcBlendAlpha, D3D11_BLEND aDestBlendAlpha, D3D11_BLEND_OP aBlendOpAlpha) {

		D3D11_BLEND_DESC lBlendDesc;
		ZeroMemory(&lBlendDesc, sizeof(D3D11_BLEND_DESC));
		lBlendDesc.AlphaToCoverageEnable = FALSE;
		lBlendDesc.IndependentBlendEnable = FALSE;
		lBlendDesc.RenderTarget[0].BlendEnable = true;

		lBlendDesc.RenderTarget[0].SrcBlend = aSrcBlend;
		lBlendDesc.RenderTarget[0].DestBlend = aDestBlend;
		lBlendDesc.RenderTarget[0].BlendOp = aBlendOp;
		lBlendDesc.RenderTarget[0].SrcBlendAlpha = aSrcBlendAlpha;
		lBlendDesc.RenderTarget[0].DestBlendAlpha = aDestBlendAlpha;
		lBlendDesc.RenderTarget[0].BlendOpAlpha = aBlendOpAlpha;
		lBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return lBlendDesc;
	}

	static D3D11_BLEND_DESC CreateDescNormal() {
		D3D11_BLEND_DESC lBlendDesc;
		ZeroMemory(&lBlendDesc, sizeof(D3D11_BLEND_DESC));
		lBlendDesc.AlphaToCoverageEnable = FALSE;
		lBlendDesc.IndependentBlendEnable = FALSE;
		lBlendDesc.RenderTarget[0].BlendEnable = true;
		lBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		lBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		lBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		lBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		lBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		lBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		lBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return lBlendDesc;
	}
	static D3D11_BLEND_DESC CreateDescAdd() {
		D3D11_BLEND_DESC lBlendDesc;
		ZeroMemory(&lBlendDesc, sizeof(D3D11_BLEND_DESC));
		lBlendDesc.AlphaToCoverageEnable = FALSE;
		lBlendDesc.IndependentBlendEnable = FALSE;
		lBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		lBlendDesc.RenderTarget[0].BlendEnable = true;
		lBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		lBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		lBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		lBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		lBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		lBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;

		return lBlendDesc;
	}

	#pragma endregion

};


}

}

}
