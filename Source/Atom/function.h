//
//	content	:	��{�ƂȂ�֐�
//	author	:	SaitoYoshiki
//

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

inline f32 ToRad(f32 aDegree) {
	return aDegree / 360.0f * c2Pi;
}

inline f32 ToDeg(f32 aRadian) {
	return aRadian / c2Pi * 360.0f;
}

#pragma endregion



//	�͈͓��ɐ������ꂽ�l��Ԃ�
#pragma region Clamp

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

template <typename T>
inline T Clamp01(T aVal) {
	return Clamp(aVal, T(0), T(1));
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



//	�͈͓��Ɏ��܂�悤�Ƀ��[�v���ꂽ��
#pragma region Wrap

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




//	�l�̕�����Ԃ�
#pragma region Sign

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



//	���K�������l��Ԃ�
#pragma region Normal

template <typename T>
inline f32 Normal(T aVal, T aMin, T aMax) {
	return (f32)(aVal - aMin) / (aMax - aMin);
}

#pragma endregion


//	���K�������l���A�͈͂ɍĔz�u����
#pragma region Replace

inline f32 Replace(f32 aNormal, f32 aMin, f32 aMax) {
	return aMin + (aMax - aMin) * aNormal;
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



//	��Βl�ōŏ��l�����߂�
//	��FWeak(-1.0, 2, 3)�̂Ƃ��A-1.0���Ԃ��Ă���
#pragma region Weak

template <typename T, typename U>
inline T Weak(const T& a, const U& b) {
	return Abs(a) <= Abs(b) ? a : b;
}

template <typename T, typename... Rest>
inline T Weak(const T& a, const Rest&... rest) {
	return Weak(a, Weak(rest...));
}

#pragma endregion


//	��Βl�ōő�l�����߂�
#pragma region Strong

template <typename T, typename U>
inline T Strong(const T& a, const U& b) {
	return Abs(a) >= Abs(b) ? a : b;
}

template <typename T, typename... Rest>
inline T Strong(const T& a, const Rest&... rest) {
	return Strong(a, Strong(rest...));
}

#pragma endregion



//	�ݏ悷��
#pragma region Pow

template <typename T>
inline T Pow(T aVal, u32 aTimes) {
	T tV = T(1);
	for (u32 i = 0; i < aTimes; i++) {
		tV *= aVal;
	}
	return tV;
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
	return IsEqual(aVal, aOther, cFloatEpsilon * Max(Abs(aVal), Abs(aOther)));
}


#pragma endregion


//	�ق�0���ǂ���
inline BOOL IsZero(f32 aVal) {
	return IsEqual(aVal, 0.0f);
}
inline BOOL IsZero(f64 aVal) {
	return IsEqual(aVal, 0.0);
}

//	0�łȂ�
inline BOOL NotZero(f32 aVal) {
	return !IsZero(aVal);
}
inline BOOL NotZero(f64 aVal) {
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



//���̑�
#pragma region Other


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


//�G���f�B�A�����t�]������B��F���g���G���f�B�A�����r�b�O�G���f�B�A���ɂ���
template <typename T>
inline T ReverseEndian(const T aVal) {

	u32 lByteNum = sizeof(T);

	//���ʂ��i�[����ϐ�
	T lRes;

	const u8* lFrom = (const u8*)(&aVal);
	u8* lTo = (u8*)(&lRes);

	//�o�C�g����4�̏ꍇ�A0��3�A1��2�A�Ƃ������ɂȂ�悤�ɓ���ւ���
	for (u32 i = 0; i < lByteNum; i++) {
		lTo[i] = lFrom[lByteNum - i - 1];
	}

	return lRes;
}

//�G���f�B�A�������ւ���ivoid*�ŁA�ł���Ώ�̃e���v���[�g�ł��g���ė~�����j
inline void ReverseEndian(void* aVal, u32 aByteNum) {

	CPOT_ASSERT(Mod(aByteNum, 2) == 0);
	
	//�o�C�g����4�̏ꍇ�A0��3�A1��2�A�Ƃ������ɂȂ�悤�ɓ���ւ���
	for (u32 i = 0; i < aByteNum / 2; i++) {

		//�����̒l��ۑ�
		u8 tB = ((u8*)aVal)[i];
		//�����ɁA�E���̒l����
		((u8*)aVal)[i] = ((u8*)aVal)[aByteNum - i - 1];
		//�E���ɁA��قǕۑ����������̒l����
		((u8*)aVal)[aByteNum - i - 1] = tB;
	}
}


#pragma endregion



//��Ԋ֐�
#pragma region Tween

//���`��Ԃ��s��
inline f32 Lerp(f32 start, f32 end, f32 now) {
	f32 dist = end - start;
	CPOT_ASSERT(NotZero(dist));
	return (now - start) / dist;
}


//0.0f�ɋ߂��قǁA���`�Ɣ�ׂĒl���������Ȃ�Lerp
inline f32 EaseIn(f32 t) {
	return t * t;
}


//0.0f�ɋ߂��قǁA���`�Ɣ�ׂĒl���傫���Ȃ�
inline f32 EaseOut(f32 t) {
	return 1.0f - EaseIn(1.0f - t);
}


//0.0f�ɋ߂��قǁA�܂�1.0f�ɋ߂��قǁA���`�Ɣ�ׂĒl���傫���Ȃ�
inline f32 EaseInOut(f32 r) {
	return (-2 * r * r * r + 3 * r * r);
}

#pragma endregion


}