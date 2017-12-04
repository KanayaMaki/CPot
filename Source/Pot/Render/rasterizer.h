//
//	content	:	Samplerのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class RasterizerBase : public NamedResource {
public:
	enum CFillMode {
		cSolid,
		cWireFrame
	};
	enum CCullMode {
		cCullCW,
		cCullCCW,
		cCullNone,
	};

public:
	CPOT_VI void Load(CFillMode aFillMode, CCullMode aCullMode) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;
};

}

#ifdef CPOT_ON_WINDOWS
#include "./Pot/Render/DirectX11/rasterizerDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Render/Android/rasterizerAndroid.h"
#endif