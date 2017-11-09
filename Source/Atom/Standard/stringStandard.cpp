//	ファイル名	:	Atom/Standard/string.cpp
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/09
//	更新日時	:	2017/11/09
//	内容		:	数字を文字列に変換する関数などの、std空間での実装


#include "./Atom/string.h"

#include <cstdio>
#include <cstring>


namespace cpot {


//数字を文字列にしたときに、一時的に格納しておくバッファ
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