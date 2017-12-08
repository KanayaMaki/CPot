//
//	content	:	OpenGL‚Å‚ÌDepthStencil
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/depthStencil.h"
#include "./Pot/Render/DirectX11/Platform/depthStencilStateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class DepthStencil : public DepthStencilBase {

public:
	DepthStencil() {
		mDepthStencil.reset(new platform::DepthStencilState);
	}

public:
	void Load(CDepthMode aMode) CPOT_OR {

		switch (aMode)
		{
			case cTest:
				mDepthStencil->Load(platform::DepthStencilState::CreateDescZTest());
				break;
			case cNoWrite:
				mDepthStencil->Load(platform::DepthStencilState::CreateDescNoZWrite());
				break;
			case cNoTest:
				mDepthStencil->Load(platform::DepthStencilState::CreateDescNoZTest());
				break;
		}
	}

public:
	void Release() CPOT_OR {
		mDepthStencil->Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mDepthStencil->IsLoaded();
	}

public:
	std::shared_ptr<platform::DepthStencilState> mDepthStencil;

};

}

using DepthStencil = directX11::DepthStencil;

}