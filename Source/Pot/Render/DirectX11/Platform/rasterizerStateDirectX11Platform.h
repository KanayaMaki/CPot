#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class RasterizerState : public State<ID3D11RasterizerState>{

	//ÉçÅ[Éh
	#pragma region Load

public:
	BOOL Load(const D3D11_RASTERIZER_DESC& aDesc) {
		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateRasterizerState(&aDesc, &mState);
		if (FAILED(hr)) {
			Log::S().Output("RasterizerStateDirectX11.Load : FailedCreate");
			return false;
		}

		return true;
	}

	BOOL Load() {
		return Load(CreateDescCullCW());
	}

	#pragma endregion


	//ÉçÅ[ÉhÇÃê›íËÇÃçÏê¨
	#pragma region CreateDesc

public:
	static D3D11_RASTERIZER_DESC CreateDescNoCull() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ïÅí Ç…ï`âÊÇ∑ÇÈ
		lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // óºñ Çï`âÊÇ∑ÇÈ
		lRasterizerDesc.FrontCounterClockwise = FALSE; // éûåvâÒÇËÇ™ï\ñ 
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDescCullCW() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ïÅí Ç…ï`âÊÇ∑ÇÈ
		lRasterizerDesc.CullMode = D3D11_CULL_FRONT;    // ó†ñ ÇÉJÉã
		lRasterizerDesc.FrontCounterClockwise = FALSE; // éûåvâÒÇËÇ™ï\ñ 
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDescCullCCW() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ïÅí Ç…ï`âÊÇ∑ÇÈ
		lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // óºñ Çï`âÊÇ∑ÇÈ
		lRasterizerDesc.FrontCounterClockwise = FALSE; // éûåvâÒÇËÇ™ï\ñ 
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDescWireFrameNoCull() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;   // ïÅí Ç…ï`âÊÇ∑ÇÈ
		lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // óºñ Çï`âÊÇ∑ÇÈ
		lRasterizerDesc.FrontCounterClockwise = FALSE; // éûåvâÒÇËÇ™ï\ñ 
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDescWireFrameCullCW() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;   // ïÅí Ç…ï`âÊÇ∑ÇÈ
		lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // óºñ Çï`âÊÇ∑ÇÈ
		lRasterizerDesc.FrontCounterClockwise = FALSE; // éûåvâÒÇËÇ™ï\ñ 
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDesc(BOOL aIsSolid, BOOL aCullCW, BOOL aCullCCW) {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = aIsSolid ? D3D11_FILL_SOLID : D3D11_FILL_WIREFRAME;   // ïÅí Ç…ï`âÊÇ∑ÇÈ
		if (!aCullCW && !aCullCCW) {
			lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // óºñ Çï`âÊÇ∑ÇÈ
		}
		else if (!aCullCW) {
			lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // óºñ Çï`âÊÇ∑ÇÈ
		}
		else if (!aCullCCW) {
			lRasterizerDesc.CullMode = D3D11_CULL_FRONT;    // óºñ Çï`âÊÇ∑ÇÈ
		}
		else {
			CPOT_LOG("ÉJÉãÇµâﬂÇ¨Çƒï`âÊÇ≈Ç´Ç‹ÇπÇÒ");
			lRasterizerDesc.CullMode = D3D11_CULL_NONE;
		}
		lRasterizerDesc.FrontCounterClockwise = FALSE; // éûåvâÒÇËÇ™ï\ñ 
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	#pragma endregion

};

}

}

}
