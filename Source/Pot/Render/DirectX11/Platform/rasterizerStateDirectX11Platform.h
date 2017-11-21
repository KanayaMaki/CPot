#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class RasterizerState : public State<ID3D11RasterizerState>{

	//ロード
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
		return Load(CreateDescCullBack());
	}

	#pragma endregion


	//ロードの設定の作成
	#pragma region CreateDesc

public:
	static D3D11_RASTERIZER_DESC CreateDescNoCull() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // 普通に描画する
		lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // 両面を描画する
		lRasterizerDesc.FrontCounterClockwise = FALSE; // 時計回りが表面
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDescCullBack() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // 普通に描画する
		lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // 両面を描画する
		lRasterizerDesc.FrontCounterClockwise = FALSE; // 時計回りが表面
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
		lRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;   // 普通に描画する
		lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // 両面を描画する
		lRasterizerDesc.FrontCounterClockwise = FALSE; // 時計回りが表面
		lRasterizerDesc.DepthBias = 0;
		lRasterizerDesc.DepthBiasClamp = 0;
		lRasterizerDesc.SlopeScaledDepthBias = 0;
		lRasterizerDesc.DepthClipEnable = TRUE;
		lRasterizerDesc.ScissorEnable = FALSE;
		lRasterizerDesc.MultisampleEnable = FALSE;
		lRasterizerDesc.AntialiasedLineEnable = FALSE;

		return lRasterizerDesc;
	}

	static D3D11_RASTERIZER_DESC CreateDescWireFrameCullBack() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;   // 普通に描画する
		lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // 両面を描画する
		lRasterizerDesc.FrontCounterClockwise = FALSE; // 時計回りが表面
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
