//	�t�@�C����	:	Atom/Standard/atom.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/07
//	�X�V����	:	2017/11/07
//	���e		:	��{��typedef���`

#pragma once

#include <cmath>

#include "../defines.h"
#include "../typedef.h"


namespace cpot {


constexpr f64 cPi = 3.1415926535897932384626;	//�~����
constexpr f32 cPif = 3.1415926535f;	//32bit
constexpr f32 cFloatEpsilon = FLT_EPSILON;


s32 Ceilf(f32 val) {
	return s32(std::ceilf(val));
}

s32 Floorf(f32 val) {
	return s32(std::floorf(val));
}

f32 Modf(f32 val, f32 m) {
	return std::fmodf(val, m);
}


f32 Sinf(f32 rad) {
	return std::sinf(rad);
}

f32 Cosf(f32 rad) {
	return std::cosf(rad);
}

f32 Asinf(f32 rad) {
	return std::asinf(rad);
}

f32 Acosf(f32 rad) {
	return std::acosf(rad);
}


f32 Sqrtf(f32 val) {
	return std::sqrtf(val);
}

f32 Expf(f32 val) {
	return std::expf(val);
}


}