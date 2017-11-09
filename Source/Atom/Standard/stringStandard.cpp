//	�t�@�C����	:	Atom/Standard/string.cpp
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/09
//	�X�V����	:	2017/11/09
//	���e		:	�����𕶎���ɕϊ�����֐��Ȃǂ́Astd��Ԃł̎���


#include "./Atom/string.h"

#include <cstdio>
#include <cstring>


namespace cpot {


//�����𕶎���ɂ����Ƃ��ɁA�ꎞ�I�Ɋi�[���Ă����o�b�t�@
static const s32 cToStringBufferSize = 100;
static CHAR toStringBuffer[cToStringBufferSize];


const CHAR* ToString(s32 aVal) {
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%d", aVal);
	#else
	std::sprintf(toStringBuffer, "%d", aVal);
	#endif
	return toStringBuffer;
}
const CHAR* ToString(u32 aVal) {
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%u", aVal);
	#else
	std::sprintf(toStringBuffer, "%u", aVal);
	#endif
	return toStringBuffer;
}
const CHAR* ToString(s64 aVal) {
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%lld", aVal);
	#else
	std::sprintf(toStringBuffer, "%lld", aVal);
	#endif
	return toStringBuffer;
}
const CHAR* ToString(u64 aVal) {
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%llu", aVal);
	#else
	std::sprintf(toStringBuffer, "%llu", aVal);
	#endif
	return toStringBuffer;
}

const CHAR* ToString(f32 aVal) {
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%f", aVal);
	#else
	std::sprintf(toStringBuffer, "%f", aVal);
	#endif
	return toStringBuffer;
}

const CHAR* ToString(f64 aVal) {
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%f", aVal);
	#else
	std::sprintf(toStringBuffer, "%f", aVal);
	#endif
	return toStringBuffer;
}

}