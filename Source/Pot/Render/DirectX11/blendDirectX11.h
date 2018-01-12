//
//	content	:	DirectX11でのBlend
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/blend.h"
#include "./Pot/Render/DirectX11/Platform/blendStateDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class Blend : public BlendBase {

public:
	Blend() {
		mBlend.reset(new platform::BlendState);
	}

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//将来は、名前からデータを検索して、ロードできるようにしたい
	};
	void Load(CBlendMode aMode) CPOT_OR {

		if (aMode == cNormal) {
			mBlend->Load(platform::BlendState::CreateDescNormal());
		}
		else if (aMode == cAdd) {
			mBlend->Load(platform::BlendState::CreateDescAdd());
		}
	}

public:
	void Release() CPOT_OR {
		mBlend->Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mBlend->IsLoaded();
	}

public:
	std::shared_ptr<platform::BlendState> mBlend;

};

}

using Blend = directX11::Blend;

}