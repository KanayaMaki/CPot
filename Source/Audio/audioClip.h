//
//	content	:	AudioClipのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

#include "./Audio/audioName.h"

namespace cpot {

class AudioClipBase {

public:
	CPOT_VI void Load(const CHAR* aFileName) CPOT_ZR;

	CPOT_VI void LoadFromKey(const HashTableKey& aFileNameKey) CPOT_ZR;
	CPOT_VI void LoadFromKey(const CHAR* aFileNameKey) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}


#ifdef CPOT_ON_WINDOWS
#include "./Audio/XAudio/audioClipXAudio.h"
#endif