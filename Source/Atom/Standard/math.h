//	ファイル名	:	Atom/Standard/atom.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/07
//	更新日時	:	2017/11/07
//	内容		:	基本のtypedefを定義

#pragma once

#include <cmath>

#include "../defines.h"
#include "../typedef.h"


namespace cpot {


const f32 cPi = 3.1415926535f;
const f32 c2Pi = 2 * 3.1415926535f;

const f32 cFloatEpsilon = FLT_EPSILON;


inline s32 Roundf(f32 aVal) {
	return s32(std::roundf(aVal));
}

inline s32 Ceilf(f32 aVal) {
	return s32(std::ceilf(aVal));
}

inline s32 Floorf(f32 aVal) {
	return s32(std::floorf(aVal));
}

inline f32 Modf(f32 aVal, f32 aM) {
	return std::fmodf(aVal, aM);
}


inline f32 Sinf(f32 aRad) {
	return std::sinf(aRad);
}

inline f32 Cosf(f32 aRad) {
	return std::cosf(aRad);
}

inline f32 Tanf(f32 aRad) {
	return std::tanf(aRad);
}

inline f32 Asinf(f32 aVal) {
	return std::asinf(aVal);
}

inline f32 Acosf(f32 aVal) {
	return std::acosf(aVal);
}

inline f32 Atanf(f32 aVal) {
	return std::atanf(aVal);
}


inline f32 Sqrtf(f32 val) {
	return std::sqrtf(val);
}

inline f32 Expf(f32 val) {
	return std::expf(val);
}


}