//
//	content	:	DepthStencil�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class DepthStencilBase : public NamedResource {
public:
	enum CDepthMode {
		cTest,
		cNoWrite,
		cNoTest,
	};

public:
	CPOT_VI void Load(CDepthMode aMode) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;
};

}

#ifdef CPOT_ON_WINDOWS
#include "./Pot/Render/DirectX11/depthStencilDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Render/Android/depthStencilAndroid.h"
#endif