#pragma once

#include "./Pot/Render/DirectX11/Platform/viewDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


class UnorderedAccessView : public View<ID3D11UnorderedAccessView> {

	//2Dテクスチャのロード
	#pragma region Load2D

	BOOL Load() {

		if (IsLoaded()) {
			Release();
		}

		return false;
	}

	#pragma endregion

};


}

}

}