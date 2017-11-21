#pragma once

#include "./Pot/Render/DirectX11/Platform/stateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class DepthStencilState : public State<ID3D11DepthStencilState> {

	//ロード
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


	//ロードの設定の作成
	#pragma region CreateDesc

public:
	static D3D11_DEPTH_STENCIL_DESC CreateDescZTest() {

		D3D11_DEPTH_STENCIL_DESC lDepthStencilDesc;
		lDepthStencilDesc.DepthEnable = TRUE; // 深度テストあり
		lDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 書き込む
		lDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // 手前の物体を描画
		lDepthStencilDesc.StencilEnable = FALSE; // ステンシル・テストなし
		lDepthStencilDesc.StencilReadMask = 0;     // ステンシル読み込みマスク。
		lDepthStencilDesc.StencilWriteMask = 0;     // ステンシル書き込みマスク。
													// 面が表を向いている場合のステンシル・テストの設定
		lDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER; // 常に失敗
																		  // 面が裏を向いている場合のステンシル・テストの設定
		lDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // 常に成功

		return lDepthStencilDesc;
	}
	static D3D11_DEPTH_STENCIL_DESC CreateDescNoZWrite() {

		D3D11_DEPTH_STENCIL_DESC lDepthStencilDesc;

		lDepthStencilDesc.DepthEnable = TRUE; // 深度テストあり
		lDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // 書き込まない
		lDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // 手前の物体を描画
		lDepthStencilDesc.StencilEnable = FALSE; // ステンシル・テストなし
		lDepthStencilDesc.StencilReadMask = 0;     // ステンシル読み込みマスク
		lDepthStencilDesc.StencilWriteMask = 0;     // ステンシル書き込みマスク
													// 面が表を向いている場合のステンシル・テストの設定
		lDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER; // 常に失敗
																		  // 面が裏を向いている場合のステンシル・テストの設定
		lDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // 常に成功

		return lDepthStencilDesc;
	}
	static D3D11_DEPTH_STENCIL_DESC CreateDescNoZTest() {

		D3D11_DEPTH_STENCIL_DESC lDepthStencilDesc;

		lDepthStencilDesc.DepthEnable = FALSE; // 深度テストあり
		lDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // 書き込まない
		lDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // 手前の物体を描画
		lDepthStencilDesc.StencilEnable = FALSE; // ステンシル・テストなし
		lDepthStencilDesc.StencilReadMask = 0;     // ステンシル読み込みマスク。
		lDepthStencilDesc.StencilWriteMask = 0;     // ステンシル書き込みマスク。
													// 面が表を向いている場合のステンシル・テストの設定
		lDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // 維持
		lDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER; // 常に失敗
																		  // 面が裏を向いている場合のステンシル・テストの設定
		lDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;   // 維持
		lDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; // 常に成功

		return lDepthStencilDesc;
	}

	#pragma endregion

};



}



}

}
