//
//	content	:	ViewPortのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class ViewportBase {

public:
	CPOT_VI void Load(const Vector2& aLeftTop, const Vector2& aSize) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;
};

}

#ifdef CPOT_ON_WINDOWS
#include "./Pot/Render/DirectX11/viewportDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Render/Android/viewportAndroid.h"
#endif