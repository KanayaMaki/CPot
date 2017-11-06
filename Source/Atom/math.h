//	ファイル名	:	Atom/math.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/07
//	更新日時	:	2017/11/07
//	内容		:	使用するライブラリを切り替え

#pragma once

#include "defines.h"
#include "typedef.h"


#ifdef CPOT_ON_WINDOWS
#include "Standard/math.h"
#elif defined CPOT_ON_ANDROID
#include "Standard/math.h"
#endif


namespace cpot {


}