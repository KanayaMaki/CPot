//
//	content	:	Blendのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class BlendBase : public NamedResource {
public:
	enum CBlendMode {
		cNormal,
		cAdd,
	};

public:
	CPOT_VI void Load(CBlendMode aMode) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;
};

}

#ifdef CPOT_ON_DIRECTX11
#include "./Pot/Render/DirectX11/blendDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Render/Android/blendAndroid.h"
#endif