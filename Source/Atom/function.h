//	�t�@�C����	:	Atom/function.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/06
//	�X�V����	:	2017/11/06
//	���e		:	��{�̊֐����`

#pragma once


#include "defines.h"
#include "typedef.h"

#include "math.h"

namespace cpot {


#pragma region �}�N���̒�`

#define CPOT_NAME(name) #name
#define CPOT_NAME_EXTEND(name) CPOT_NAME(name)	//�}�N���̒��Ŏg���Ƃ��ɁACPOT_NAME���ƓW�J����Ȃ�����
#define CPOT_ARRAY_SIZE(t) ((sizeof((t)) / sizeof((t[0]))))

#pragma endregion


#pragma region delete�̒�`

#define CPOT_DELETE(p) if(p) { delete p; }
#define CPOT_DELETE_ARRAY(p) if(p) { delete[] p; }

#pragma endregion


//���W�A������f�B�O���[�ւ̕ϊ��A���̋t
#pragma region Radian

inline f32 ToRadian(f32 aDegree) {
	return aDegree / 360.0f * (2 * cPif);
}

inline f32 ToDegree(f32 aRadian) {
	return aRadian / (2 * cPif) * 360.0f;
}

#pragma endregion



#pragma region Clamp


//	�͈͓��ɐ������ꂽ�l��Ԃ�
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

//	�͈͓��ɐ������ꂽ�l��Ԃ�
template <typename T>
inline T Clamp(T aVal, T aMax) {
	return Clamp(aVal, T(0), aMax);
}

//	�͈͓��ɐ������ꂽ�l��Ԃ�
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


//	�͈͓��Ɏ��܂�悤�Ƀ��[�v���ꂽ��
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

//	�l�̐�Βl��Ԃ�
template <typename T>
inline T Abs(T aVal) {
	if (aVal < T(0)) aVal *= -1;
	return aVal;
}

#pragma endregion



#pragma region Sign

//	�l�̕�����Ԃ�
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

//	���K�������l��Ԃ�
template <typename T>
inline f32 Normal(T aVal, T aMin, T aMax) {
	return (f32)(aVal - aMin) / (aMax - aMin);
}

#pragma endregion


//	�ŏ��l�����߂�
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


//	�ő�l�����߂�
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



//	��Βl������������
#pragma region DecrAbs

template <typename T>
inline T DcrAbs(T aVal, T aDecrAbs) {

	T res = Sign(aVal) * Max(T(0), Abs(aVal) - aDecrAbs);	//��Βl�����炷
	return res;
}

#pragma endregion



//	�l���͈͓����Ȃǂ𔻒肷��
#pragma region Judge


//	�͈͓����ǂ�����Ԃ�
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


//	�l���A�ʂ̒l�Ƃقړ�������
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


//	�ق�0���ǂ���
inline BOOL IsZero(f32 aVal) {
	return IsEqual(aVal, 0.0f);
}

//	0�łȂ�
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



//	�����񂪓��������ǂ���
inline BOOL StringSame(const CHAR* aStr1, const CHAR* aStr2) {

	for (s32 i = 0;; i++) {

		//�����������������
		if (aStr1[i] != aStr2[i]) {
			return false;	//�������Ȃ�
		}

		//�����񂪏I����Ă��邩�ǂ���
		bool end1 = (aStr1[i] == '\0');
		bool end2 = (aStr2[i] == '\0');

		//�����I����Ă���Ȃ�
		if (end1 && end2) {
			return true;	//������
		}
		//�ǂ��炩�������I����Ă���Ȃ�
		else if (end1 || end2) {
			return false;	//�������Ȃ�
		}
		//�ǂ�����I����Ă��Ȃ��Ȃ�
		else {
			//�����𑱂���
		}
	}
	return true;	//�����܂ł͗��Ȃ�
}


//	������̒������v�Z����
inline constexpr u32 StringLen(const CHAR* aStr) {
	u32 i = 0;
	while (aStr[i] != '\0') {
		i++;
	}
	return i;
}


//	���������R�s�[����
inline void CopyMem(void* aTo, const void* aFrom, Pointer aSize) {
	for (Pointer i = 0; i < aSize; i++) {
		((u8*)aTo)[i] = ((const u8*)aFrom)[i];
	}
}


//���������O�Ŗ��߂�
inline void ZeroMem(void* aMem, Pointer aSize) {
	for (Pointer i = 0; i < aSize; i++) {
		((u8*)aMem)[i] = 0;
	}
}


//��Ԋ֐�
#pragma region Tween

//���`��Ԃ��s��
inline f32 Lerp(f32 start, f32 end, f32 now) {
	f32 dist = end - start;
	CPOT_ASSERT(NotZero(dist));
	return (now - start) / dist;
}


//	0.0f�ɋ߂��قǁA���`�Ɣ�ׂĒl���������Ȃ�Lerp
inline f32 EaseIn(f32 t) {
	return t * t;
}


/**
* @brief  0.0f�ɋ߂��قǁA���`�Ɣ�ׂĒl���傫���Ȃ�
*
* @param[in]  t 0.0f�`1.0f�̒l
*
* @return  0.0f�`1.0f�̊Ԃ̒l
*
* @note
*/
inline f32 EaseOut(f32 t) {
	return 1.0f - EaseIn(1.0f - t);
}


/**
* @brief  0.0f�ɋ߂��قǁA�܂�1.0f�ɋ߂��قǁA���`�Ɣ�ׂĒl���傫���Ȃ�
*
* @param[in]  t 0.0f�`1.0f�̒l
*
* @return  0.0f�`1.0f�̊Ԃ̒l
*
* @note
*/
inline f32 EaseInOut(f32 r) {
	return (-2 * r * r * r + 3 * r * r);
}

#pragma endregion


}