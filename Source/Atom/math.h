//	ファイル名	:	Atom/math.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/07
//	更新日時	:	2017/11/07
//	内容		:	使用するライブラリを切り替え

#pragma once

#include "defines.h"
#include "typedef.h"


namespace cpot {

//	値の絶対値を返す
#pragma region Abs

template <typename T>
inline T Abs(T aVal) {
	if (aVal < T(0)) aVal *= -1;
	return aVal;
}

#pragma endregion

//	余りを求める
#pragma region Mod

inline s32 Mod(s32 aVal, u32 aM) {
	return aVal % aM;
}

#pragma endregion


//	宣言
/*
const f32 cPi;
const f32 c2Pi;

const f32 cFloatEpsilon;
//*/


s32 Roundf(f32 aVal);

s32 Ceilf(f32 aVal);

s32 Floorf(f32 aVal);


f32 Modf(f32 aVal, f32 aM);


f32 Sinf(f32 aRad);

f32 Cosf(f32 aRad);

f32 Tanf(f32 aRad);

f32 Asinf(f32 aVal);

f32 Acosf(f32 aVal);

f32 Atanf(f32 aVal);


f32 Sqrtf(f32 val);

f32 Expf(f32 val);

}



//	定義
#ifdef CPOT_ON_WINDOWS
#include "Standard/math.h"
#elif defined CPOT_ON_ANDROID
#include "Standard/math.h"
#endif