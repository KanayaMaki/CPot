//	ファイル名	:	Atom/function.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/06
//	更新日時	:	2017/11/06
//	内容		:	基本の関数を定義

#pragma once


#include "defines.h"
#include "typedef.h"

#include "math.h"

namespace cpot {


#pragma region マクロの定義

#define CPOT_NAME(name) #name
#define CPOT_NAME_EXTEND(name) CPOT_NAME(name)	//マクロの中で使うときに、CPOT_NAMEだと展開されないため
#define CPOT_ARRAY_SIZE(t) ((sizeof((t)) / sizeof((t[0]))))

#pragma endregion


#pragma region deleteの定義

#define CPOT_DELETE(p) if(p) { delete p; }
#define CPOT_DELETE_ARRAY(p) if(p) { delete[] p; }

#pragma endregion


//ラジアンからディグリーへの変換、その逆
#pragma region Radian

inline f32 ToRadian(f32 aDegree) {
	return aDegree / 360.0f * (2 * cPif);
}

inline f32 ToDegree(f32 aRadian) {
	return aRadian / (2 * cPif) * 360.0f;
}

#pragma endregion



#pragma region Clamp


//	範囲内に制限された値を返す
template <typename T>
inline T Clamp(T aVal, T aMin, T aMax) {
	if (aVal < aMin) {
		return aMin;
	}
	if (aVal > aMax) {
		return aMax;
	}
	return aVal;
}

//	範囲内に制限された値を返す
template <typename T>
inline T Clamp(T aVal, T aMax) {
	return Clamp(aVal, T(0), aMax);
}

//	範囲内に制限された値を返す
template <typename T>
inline T ClampRange(T aVal, T aEdge1, T aEdge2) {
	if (aEdge1 < aEdge2) {
		return Clamp(aVal, aEdge1, aEdge2);
	}
	else {
		return Clamp(aVal, aEdge2, aEdge1);
	}
}


#pragma endregion


#pragma region Wrap


//	範囲内に収まるようにループされた数
template <typename T>
inline T Wrap(T aVal, T aMin, T aMax) {
	T dist = aMax - aMin + 1;
	while (aVal >= aMax) aVal -= dist;
	while (aVal < aMin) aVal += dist;
	return aVal;
}

template <typename T>
inline T Wrap(T aVal, T aMax) {
	return Wrap(aVal, T(0), aMax);
}


#pragma endregion



#pragma region Abs

//	値の絶対値を返す
template <typename T>
inline T Abs(T aVal) {
	if (aVal < T(0)) aVal *= -1;
	return aVal;
}

#pragma endregion



#pragma region Sign

//	値の符号を返す
template <typename T>
inline s32 Sign(T aVal) {
	if (aVal > T(0)) return 1;
	if (aVal < T(0)) return -1;
	return 0;
}


template <typename T>
inline s32 SignSafe(T aVal) {
	if (aVal > T(0)) return 1;
	if (aVal < T(0)) return -1;
	return 1;
}


#pragma endregion



#pragma region Normal

//	正規化した値を返す
template <typename T>
inline f32 Normal(T aVal, T aMin, T aMax) {
	return (f32)(aVal - aMin) / (aMax - aMin);
}

#pragma endregion


//	最小値を求める
#pragma region Min

template <typename T, typename U>
inline T Min(const T& a, const U& b) {
	return a <= b ? a : b;
}

template <typename T, typename... Rest>
inline T Min(const T& a, const Rest&... rest) {
	return Min(a, Min(rest...));
}

#pragma endregion


//	最大値を求める
#pragma region Max

template <typename T, typename U>
inline T Max(const T& a, const U& b) {
	return a >= b ? a : b;
}

template <typename T, typename... Rest>
inline T Max(const T& a, const Rest&... rest) {
	return Max(a, Max(rest...));
}

#pragma endregion



//	絶対値を減少させる
#pragma region DecrAbs

template <typename T>
inline T DcrAbs(T aVal, T aDecrAbs) {

	T res = Sign(aVal) * Max(T(0), Abs(aVal) - aDecrAbs);	//絶対値を減らす
	return res;
}

#pragma endregion



//	値が範囲内かなどを判定する
#pragma region Judge


//	範囲内かどうかを返す
#pragma region IsRange

template <typename T>
inline BOOL IsRange(T aVal, T aMin, T aMax) {
	if (aVal < aMin) {
		return false;
	}
	if (aVal > aMax) {
		return false;
	}
	return true;
}

template <typename T>
inline BOOL IsRange(T aVal, T aMax) {
	return IsRange(aVal, T(0), aMax);
}

#pragma endregion


//	値が、別の値とほぼ等しいか
#pragma region IsEqual

template <typename T>
inline BOOL IsEqual(T aVal, T aOther, T aEp) {
	T v = Abs(aVal - aOther);
	if (v <= aEp) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
inline BOOL IsEqual(T aVal, T aOther) {
	return IsEqual(aVal, aOther, T(0));
}

template <>
inline BOOL IsEqual<f32>(f32 aVal, f32 aOther) {
	return IsEqual(aVal, aOther, cFloatEpsilon);
}


#pragma endregion


//	ほぼ0かどうか
inline BOOL IsZero(f32 aVal) {
	return IsEqual(aVal, 0.0f);
}

//	0でない
inline BOOL NotZero(f32 aVal) {
	return !IsZero(aVal);
}


inline BOOL IsNull(void* aVal) {
	return aVal == nullptr;
}
inline BOOL NotNull(void* aVal) {
	return !IsNull(aVal);
}


inline BOOL Is(BOOL aExp) {
	return aExp == true;
}
inline BOOL Not(BOOL aExp) {
	return aExp != true;
}


#pragma endregion



//	文字列が等しいかどうか
inline BOOL StringSame(const CHAR* aStr1, const CHAR* aStr2) {

	for (s32 i = 0;; i++) {

		//もし文字が違ったら
		if (aStr1[i] != aStr2[i]) {
			return false;	//等しくない
		}

		//文字列が終わっているかどうか
		bool end1 = (aStr1[i] == '\0');
		bool end2 = (aStr2[i] == '\0');

		//両方終わっているなら
		if (end1 && end2) {
			return true;	//等しい
		}
		//どちらかだけが終わっているなら
		else if (end1 || end2) {
			return false;	//等しくない
		}
		//どちらも終わっていないなら
		else {
			//処理を続ける
		}
	}
	return true;	//ここまでは来ない
}


//	文字列の長さを計算する
inline constexpr u32 StringLen(const CHAR* aStr) {
	u32 i = 0;
	while (aStr[i] != '\0') {
		i++;
	}
	return i;
}


//	メモリをコピーする
inline void CopyMem(void* aTo, const void* aFrom, Pointer aSize) {
	for (Pointer i = 0; i < aSize; i++) {
		((u8*)aTo)[i] = ((const u8*)aFrom)[i];
	}
}


//メモリを０で埋める
inline void ZeroMem(void* aMem, Pointer aSize) {
	for (Pointer i = 0; i < aSize; i++) {
		((u8*)aMem)[i] = 0;
	}
}


//補間関数
#pragma region Tween

//線形補間を行う
inline f32 Lerp(f32 start, f32 end, f32 now) {
	f32 dist = end - start;
	CPOT_ASSERT(NotZero(dist));
	return (now - start) / dist;
}


//	0.0fに近いほど、線形と比べて値が小さくなるLerp
inline f32 EaseIn(f32 t) {
	return t * t;
}


/**
* @brief  0.0fに近いほど、線形と比べて値が大きくなる
*
* @param[in]  t 0.0f～1.0fの値
*
* @return  0.0f～1.0fの間の値
*
* @note
*/
inline f32 EaseOut(f32 t) {
	return 1.0f - EaseIn(1.0f - t);
}


/**
* @brief  0.0fに近いほど、また1.0fに近いほど、線形と比べて値が大きくなる
*
* @param[in]  t 0.0f～1.0fの値
*
* @return  0.0f～1.0fの間の値
*
* @note
*/
inline f32 EaseInOut(f32 r) {
	return (-2 * r * r * r + 3 * r * r);
}

#pragma endregion


}