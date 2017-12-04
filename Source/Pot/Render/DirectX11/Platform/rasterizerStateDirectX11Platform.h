#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class RasterizerState : public State<ID3D11RasterizerState>{

	//���[�h
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


	//���[�h�̐ݒ�̍쐬
	#pragma region CreateDesc

public:
	static D3D11_RASTERIZER_DESC CreateDescNoCull() {

		D3D11_RASTERIZER_DESC lRasterizerDesc;
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ���ʂɕ`�悷��
		lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // ���ʂ�`�悷��
		lRasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ���ʂɕ`�悷��
		lRasterizerDesc.CullMode = D3D11_CULL_FRONT;    // ���ʂ��J��
		lRasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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
		lRasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ���ʂɕ`�悷��
		lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // ���ʂ�`�悷��
		lRasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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
		lRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;   // ���ʂɕ`�悷��
		lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // ���ʂ�`�悷��
		lRasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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
		lRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;   // ���ʂɕ`�悷��
		lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // ���ʂ�`�悷��
		lRasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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
		lRasterizerDesc.FillMode = aIsSolid ? D3D11_FILL_SOLID : D3D11_FILL_WIREFRAME;   // ���ʂɕ`�悷��
		if (!aCullCW && !aCullCCW) {
			lRasterizerDesc.CullMode = D3D11_CULL_NONE;    // ���ʂ�`�悷��
		}
		else if (!aCullCW) {
			lRasterizerDesc.CullMode = D3D11_CULL_BACK;    // ���ʂ�`�悷��
		}
		else if (!aCullCCW) {
			lRasterizerDesc.CullMode = D3D11_CULL_FRONT;    // ���ʂ�`�悷��
		}
		else {
			CPOT_LOG("�J�����߂��ĕ`��ł��܂���");
			lRasterizerDesc.CullMode = D3D11_CULL_NONE;
		}
		lRasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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
