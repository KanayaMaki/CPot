//
//	content	:	Textureのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class Texture2DBase : public NamedResource {

public:
	CPOT_VI void Load(const HashTableKey& aUnionName) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI u32 GetWidth() CPOT_ZR;
	CPOT_VI u32 GetHeight() CPOT_ZR;


public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}

#ifdef CPOT_ON_WINDOWS
#include "./Pot/Render/DirectX11/texture2DDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Audio/Android/audioClipAndroid.h"
#endif