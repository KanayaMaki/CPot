#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class DepthStencilState : public State<ID3D11DepthStencilState> {

	//���[�h
	#pragma region Load

public:
	void Load(const D3D11_DEPTH_STENCIL_DESC& aDesc) {
		if (IsLoaded()) {
			Release();
		}

		HRESULT hr;

		hr = Device::S().GetDevice()->CreateDepthStencilState(&aDesc, &mState);
		if (FAILED(hr)) {
			Log::S().Output("DepthStencilStateDirectX11.Load : FailedCreate");
		}
	}

	void Load() {
		Load(CreateDescNoZTest());
	}

	#pragma endregion


	//���[�h�̐ݒ�̍쐬
	#pragma region CreateDesc

public:
	static D3D11_DEPTH_STENCIL_DESC CreateDescZTest() {

		D3D11_DEPTH_STENCIL_DESC lDepthStencilDesc;
		lDepthStencilDesc.DepthEnable = TRUE; // �[�x�e�X�g����
		lDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ��������
		lDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // ��O�̕��̂�`��
		lDepthStencilDesc.StencilEnable = FALSE; // �X�e���V���E�e�X�g�Ȃ�
		lDepthStencilDesc.StencilReadMask = 0;     // �X�e���V���ǂݍ��݃}�X�N�B
		lDepthStencilDesc.StencilWriteMask = 0;     // �X�e���V���������݃}�X�N�B
													// �ʂ��\�������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
		lDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER; // ��Ɏ��s
																		  // �ʂ����������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
		lDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // ��ɐ���

		return lDepthStencilDesc;
	}
	static D3D11_DEPTH_STENCIL_DESC CreateDescNoZWrite() {

		D3D11_DEPTH_STENCIL_DESC lDepthStencilDesc;

		lDepthStencilDesc.DepthEnable = TRUE; // �[�x�e�X�g����
		lDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // �������܂Ȃ�
		lDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // ��O�̕��̂�`��
		lDepthStencilDesc.StencilEnable = FALSE; // �X�e���V���E�e�X�g�Ȃ�
		lDepthStencilDesc.StencilReadMask = 0;     // �X�e���V���ǂݍ��݃}�X�N
		lDepthStencilDesc.StencilWriteMask = 0;     // �X�e���V���������݃}�X�N
													// �ʂ��\�������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
		lDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER; // ��Ɏ��s
																		  // �ʂ����������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
		lDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // ��ɐ���

		return lDepthStencilDesc;
	}
	static D3D11_DEPTH_STENCIL_DESC CreateDescNoZTest() {

		D3D11_DEPTH_STENCIL_DESC lDepthStencilDesc;

		lDepthStencilDesc.DepthEnable = FALSE; // �[�x�e�X�g����
		lDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // �������܂Ȃ�
		lDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // ��O�̕��̂�`��
		lDepthStencilDesc.StencilEnable = FALSE; // �X�e���V���E�e�X�g�Ȃ�
		lDepthStencilDesc.StencilReadMask = 0;     // �X�e���V���ǂݍ��݃}�X�N�B
		lDepthStencilDesc.StencilWriteMask = 0;     // �X�e���V���������݃}�X�N�B
													// �ʂ��\�������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
		lDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
		lDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER; // ��Ɏ��s
																		  // �ʂ����������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
		lDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
		lDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // ��ɐ���

		return lDepthStencilDesc;
	}

	#pragma endregion

};



}



}

}
