//
//	content	:	スレッド間での排他制御を可能にするクラスのインターフェース
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Atom/atom.h"


namespace cpot {


class MutexBase {
public:
	CPOT_VI void Lock() CPOT_ZR;
	CPOT_VI void Unlock() CPOT_ZR;
};


}


//デバイスごとのMutexの宣言
#ifdef CPOT_ON_WINDOWS
#include "./Thread/Standard/mutexStandard.h"
#endif