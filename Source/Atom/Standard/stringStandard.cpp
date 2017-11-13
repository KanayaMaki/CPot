//
//	内容	：	Standardでの、文字列クラス
//


#include "./Atom/string.h"

#include <cstdio>
#include <cstring>


namespace cpot {


String<15> ToString(s32 aVal) {
	CHAR toStringBuffer[16];
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%d", aVal);
	#else
	std::sprintf(toStringBuffer, "%d", aVal);
	#endif
	return String<15>(toStringBuffer);
}
String<15> ToString(u32 aVal) {
	CHAR toStringBuffer[16];
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%u", aVal);
	#else
	std::sprintf(toStringBuffer, "%u", aVal);
	#endif
	return String<15>(toStringBuffer);
}
String<31> ToString(s64 aVal) {
	CHAR toStringBuffer[32];
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%lld", aVal);
	#else
	std::sprintf(toStringBuffer, "%lld", aVal);
	#endif
	return String<31>(toStringBuffer);
}
String<31> ToString(u64 aVal) {
	CHAR toStringBuffer[32];
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%llu", aVal);
	#else
	std::sprintf(toStringBuffer, "%llu", aVal);
	#endif
	return String<31>(toStringBuffer);
}
String<15> ToString(f32 aVal) {
	CHAR toStringBuffer[16];
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%f", aVal);
	#else
	std::sprintf(toStringBuffer, "%f", aVal);
	#endif
	return String<15>(toStringBuffer);
}
String<31> ToString(f64 aVal) {
	CHAR toStringBuffer[32];
	#ifdef CPOT_ON_WINDOWS
	sprintf_s(toStringBuffer, "%f", aVal);
	#else
	std::sprintf(toStringBuffer, "%f", aVal);
	#endif
	return String<31>(toStringBuffer);
}

}