//
//	content	:	TextureのDirectX11での実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/texture3D.h"
#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"


namespace cpot {

namespace directX11 {


class Texture3D : public Texture3DBase {

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
	platform::Texture3D mTexture;

	#pragma endregion
};

}

using Texture3D = directX11::Texture3D;

}