//
//	content	:	TextureのDirectX11での実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/texture1D.h"
#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"


namespace cpot {

namespace directX11 {

class Texture1D : public Texture1DBase {

public:


public:
	void Release() CPOT_OR {
		mTexture.Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mTexture.IsLoaded();
	};


	//フィールド
	#pragma region Field

public:
	platform::Texture1D mTexture;

	#pragma endregion
};

}

using Texture1D = directX11::Texture1D;

}