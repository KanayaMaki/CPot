//
//	content	:	Standard‚Å‚ÌMath‚Ì’è‹`
//	author	:	SaitoYoshiki
//

#pragma once

#include <cmath>
#include <cfloat>

#include "../defines.h"
#include "../typedef.h"


namespace cpot {


const f32 cPi = 3.1415926535f;
const f32 c2Pi = 2 * 3.1415926535f;

const f32 cFloatEpsilon = FLT_EPSILON;


inline s32 Round(f32 aVal) {
	return s32(std::roundf(aVal));
}

inline s32 Ceil(f32 aVal) {
	return s32(std::ceilf(aVal));
}

inline s32 Floor(f32 aVal) {
	return s32(std::floorf(aVal));
}

inline f32 Mod(f32 aVal, f32 aM) {
	return std::fmodf(aVal, aM);
}


inline f32 Sin(f32 aRad) {
	return std::sinf(aRad);
}

inline f32 Cos(f32 aRad) {
	return std::cosf(aRad);
}

inline f32 Tan(f32 aRad) {
	return std::tanf(aRad);
}

inline f32 Asin(f32 aVal) {
	return std::asinf(aVal);
}

inline f32 Acos(f32 aVal) {
	return std::acosf(aVal);
}

inline f32 Atan(f32 aVal) {
	return std::atanf(aVal);
}


inline f32 Sqrt(f32 val) {
	return std::sqrtf(val);
}

inline f32 Exp(f32 val) {
	return std::expf(val);
}


}