//
//	content	:	DirectX11‚Å‚ÌSampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/rasterizer.h"
#include "./Pot/Render/DirectX11/Platform/rasterizerStateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class Rasterizer : public RasterizerBase {

public:
	Rasterizer() {
		mRasterizer.reset(new platform::RasterizerState);
	}

public:
	void Load(CFillMode aFillMode, CCullMode aCullMode) CPOT_OR {
		BOOL lIsSolid = aFillMode == cSolid;
		BOOL lCullCW = aCullMode == cCullCW;
		BOOL lCullCCW = aCullMode == cCullCCW;
		mRasterizer->Load(platform::RasterizerState::CreateDesc(lIsSolid, lCullCW, lCullCCW));
	}

public:
	void Release() CPOT_OR {
		mRasterizer->Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mRasterizer->IsLoaded();
	}

public:
	std::shared_ptr<platform::RasterizerState> mRasterizer;

};

}

using Rasterizer = directX11::Rasterizer;

}