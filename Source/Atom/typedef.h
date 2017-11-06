//	ファイル名	:	Atom/typedef.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/06
//	更新日時	:	2017/11/06
//	内容		:	基本のtypedefを定義

#pragma once

//Windows環境だと、voidとBOOLがdefineされていることがある為undefしておく
#undef void
#undef BOOL

#include "defines.h"


namespace cpot {


using s8 = signed char;	//符号付8bit整数
using u8 = unsigned char;	//符号無8bit整数
using s16 = signed short int;
using u16 = unsigned short int;
using s32 = signed long int;
using u32 = unsigned long int;
using s64 = signed long long int;
using u64 = unsigned long long int;

using f32 = float;	//32bit浮動小数点
using f64 = double;	//64bit浮動小数点

using CHAR = char;	//文字列の型
using BOOL = bool;	//真偽をあらわす型

using BYTE = u8;

//ポインタの値をすべて表せる整数型の定義
#ifdef CPOT_ON_32BIT
using Pointer = u32;
#elif defined CPOT_ON_64BIT
using Pointer = u64;
#endif


}