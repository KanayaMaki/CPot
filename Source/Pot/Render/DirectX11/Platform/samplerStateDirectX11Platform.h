#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class SamplerState : public State<ID3D11SamplerState> {

	//ÉçÅ[Éh
	#pragma region Load

public:
	BOOL Load(const D3D11_SAMPLER_DESC& aDesc) {
		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateSamplerState(&aDesc, &mState);
		if (FAILED(hr)) {
			Log::S().Output("SamplerStateDirectX11.Load : FailedCreate");
			return false;
		}

		return true;
	}

	BOOL Load() {
		return Load(CreateDescWrap());
	}

	#pragma endregion


	//ê›íËÇÃçÏê¨
	#pragma region CreateDesc

public:
	static D3D11_SAMPLER_DESC CreateDescClamp() {
		D3D11_SAMPLER_DESC lSamplerDesc;
		lSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		lSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		lSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		lSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		lSamplerDesc.MipLODBias = 0.0f;
		lSamplerDesc.MaxAnisotropy = 2;
		lSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		lSamplerDesc.BorderColor[0] = 0.0f;
		lSamplerDesc.BorderColor[1] = 0.0f;
		lSamplerDesc.BorderColor[2] = 0.0f;
		lSamplerDesc.BorderColor[3] = 0.0f;
		lSamplerDesc.MinLOD = -FLT_MAX;
		lSamplerDesc.MaxLOD = FLT_MAX;
		return lSamplerDesc;
	}
	static D3D11_SAMPLER_DESC CreateDescWrap() {
		D3D11_SAMPLER_DESC lSamplerDesc;
		lSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		lSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		lSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		lSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		lSamplerDesc.MipLODBias = 0.0f;
		lSamplerDesc.MaxAnisotropy = 2;
		lSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		lSamplerDesc.BorderColor[0] = 0.0f;
		lSamplerDesc.BorderColor[1] = 0.0f;
		lSamplerDesc.BorderColor[2] = 0.0f;
		lSamplerDesc.BorderColor[3] = 0.0f;
		lSamplerDesc.MinLOD = -FLT_MAX;
		lSamplerDesc.MaxLOD = FLT_MAX;
		return lSamplerDesc;
	}
};

	#pragma endregion

}

}

}
