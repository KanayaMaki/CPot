//
//	content	:	DirectX11‚Å‚ÌSampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/sampler.h"
#include "./Pot/Render/DirectX11/Platform/samplerStateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class Sampler : public SamplerBase {

public:
	Sampler() {
		mSampler.reset(new platform::SamplerState);
	}

public:
	void Load(CUVMode aMode) CPOT_OR {

		if (aMode == cWrap) {
			mSampler->Load(platform::SamplerState::CreateDescWrap());
		}
		else if (aMode == cClamp) {
			mSampler->Load(platform::SamplerState::CreateDescClamp());
		}
	}

public:
	void Release() CPOT_OR {
		mSampler->Release();
		mSampler = nullptr;
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mSampler->IsLoaded();
	}

public:
	std::shared_ptr<platform::SamplerState> mSampler;

};

}

using Sampler = directX11::Sampler;

}