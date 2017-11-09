//	�t�@�C����	:	Atom/vector.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/07
//	�X�V����	:	2017/11/07
//	���e		:	Vector3�Ȃǂ̎���

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"


namespace cpot {


//2��f32�����N���X
#pragma region Vector2

class Vector2 {
public:
	f32 x, y;

public:
	//�R���X�g���N�^
	#pragma region Constructor

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(f32 aX, f32 aY) : x(aX), y(aY) {}

	#pragma endregion


	//�l��ݒ肷��
	#pragma region Setter

	Vector2 X(f32 aV) const {
		return Vector2(aV, y);
	}
	Vector2 Y(f32 aV) const {
		return Vector2(x, aV);
	}
	Vector2 XY(f32 aV) const {
		return Vector2(aV, aV);
	}

	#pragma endregion

	//�l���擾����
	#pragma region Getter

	f32 X() const {
		return x;
	}
	f32 Y() const {
		return y;
	}
	Vector2 XX() const {
		return Vector2(x, x);
	}
	Vector2 XY() const {
		return Vector2(x, y);
	}
	Vector2 YX() const {
		return Vector2(y, x);
	}
	Vector2 YY() const {
		return Vector2(y, y);
	}

	#pragma endregion


	//�v�Z�̃I�y���[�^
	#pragma region Calculate

	const Vector2& operator +=(const Vector2& aVal) {
		x += aVal.x;
		y += aVal.y;
		return *this;
	}
	Vector2 operator +(const Vector2& aVal) const {
		Vector2 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	const Vector2& operator -=(const Vector2& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		return *this;
	}
	Vector2 operator -(const Vector2& aVal) const {
		Vector2 tRes(*this);
		tRes -= aVal;
		return tRes;
	}

	const Vector2& operator *=(f32 aVal) {
		x *= aVal;
		y *= aVal;
		return *this;
	}
	Vector2 operator *(f32 aVal) const {
		Vector2 tRes(*this);
		tRes *= aVal;
		return tRes;
	}
	
	const Vector2& operator *=(const Vector2& aVal) {
		x *= aVal.x;
		y *= aVal.y;
		return *this;
	}
	Vector2 operator *(const Vector2& aVal) const {
		Vector2 tRes(*this);
		tRes *= aVal;
		return tRes;
	}

	const Vector2& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));	//�O�ł͊���Ȃ�
		x /= aVal;
		y /= aVal;
		return *this;
	}
	Vector2 operator /(f32 aVal) const {
		Vector2 result(*this);
		result /= aVal;
		return result;
	}

	const Vector2& operator /=(const Vector2& aVal) {
		CPOT_ASSERT(NotZero(aVal.x));	//�O�ł͊���Ȃ�
		CPOT_ASSERT(NotZero(aVal.y));	//�O�ł͊���Ȃ�
		x /= aVal.x;
		y /= aVal.y;
		return *this;
	}
	Vector2 operator /(const Vector2& aVal) const {
		Vector2 result(*this);
		result /= aVal;
		return result;
	}

	Vector2 operator -() const {
		Vector2 result(-x, -y);
		return result;
	}

	#pragma endregion

	//��r�̃I�y���[�^
	#pragma region Compare
	BOOL operator ==(const Vector2& aVal) const {
		//�����̌덷�͔F�߂�
		if (!IsEqual(x, aVal.x, cFloatEpsilon * Abs(x))) return false;
		if (!IsEqual(y, aVal.y, cFloatEpsilon * Abs(y))) return false;
		return true;
	}
	BOOL operator !=(const Vector2& aVal) const {
		return !(*this == aVal);
	}

	BOOL operator <(const Vector2& aOther) const {
		return LenQuad() < aOther.LenQuad();
	}
	BOOL operator >=(const Vector2& aOther) const {
		return !(*this < aOther);
	}
	BOOL operator >(const Vector2& aOther) const {
		return LenQuad() > aOther.LenQuad();
	}
	BOOL operator <=(const Vector2& aOther) const {
		return !(*this > aOther);
	}

	#pragma endregion


	//���̑��v�Z
	#pragma region Other

	//�x�N�g���̒���
	f32 Len() const {
		return Sqrt(LenQuad());
	}
	//�x�N�g���̒����̓��
	f32 LenQuad() const {
		return (x * x) + (y * y);
	}

	//���K��
	Vector2 Normal() const {
		return *this / Len();
	}
	//0���Z�����Ȃ����K��
	Vector2 NormalSafe() const {
		f32 tLen = Len();

		if (IsZero(tLen)) {
			return *this;	//������0�̎��������̂܂ܕԂ�
		}
		return *this / tLen;
	}

	
	//�O��
	f32 Cross(const Vector2& aVec) const {
		return x * aVec.y - y * aVec.x;
	}
	//����
	f32 Dot(const Vector2& aVec) const {
		return x * aVec.x + y *  aVec.y;
	}

	#pragma endregion


	//���̑��ÓI�Ȋ֐�
	#pragma region Static

	//��{�ƂȂ�P�ʃx�N�g��
	static Vector2 Unit() {
		return Vector2(1.0f, 0.0f);
	}
	static Vector2 One() {
		return Vector2(1.0f, 1.0f);
	}
	static Vector2 Zero() {
		return Vector2(0.0f, 0.0f);
	}

	//���ꂼ��̕�����\���x�N�g��
	static Vector2 Left() {
		return Vector2(-1.0f, 0.0f);
	}
	static Vector2 Right() {
		return Vector2(1.0f, 0.0f);
	}
	static Vector2 Up() {
		return Vector2(0.0f, 1.0f);
	}
	static Vector2 Down() {
		return Vector2(0.0f, -1.0f);
	}

	#pragma endregion


	//float�l�̔z����擾����
	#pragma region ToFloat

	struct Float2 {
		float v[2];
	};
	Float2 ToFloat2() const {
		return Float2{ x, y };
	}

	#pragma endregion



	//�w���p�֐�
	#pragma region Helper

	friend Vector2 Lerp(const Vector2& aFrom, const Vector2& aTo, f32 aRate) {
		return aFrom * (1.0f - aRate) + aTo * aRate;
	}

	//���ꂼ��̍ő�̗v�f��I��
	friend Vector2 MaxElement(const Vector2& aVal1, const Vector2& aVal2) {
		Vector2 tRes(Max(aVal1.x, aVal2.x), Max(aVal1.x, aVal2.y));
		return tRes;
	}
	friend Vector2 MinElement(const Vector2& aVal1, const Vector2& aVal2) {
		Vector2 tRes(Min(aVal1.x, aVal2.x), Min(aVal1.y, aVal2.y));
		return tRes;
	}

	#pragma endregion
};

#pragma endregion


//3��f32�����N���X
#pragma region Vector3

class Vector3 {
public:
	f32 x, y, z;


	//�R���X�g���N�^
	#pragma region Constructor

public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(f32 aX, f32 aY, f32 aZ) : x(aX), y(aY), z(aZ) {}

	#pragma endregion


	//�l��ݒ肷��
	#pragma region Setter

	Vector3 X(f32 aV) const {
		return Vector3(aV, y, z);
	}
	Vector3 Y(f32 aV) const {
		return Vector3(x, aV, z);
	}
	Vector3 Z(f32 aV) const {
		return Vector3(x, y, aV);
	}
	Vector3 XY(f32 aV) const {
		return Vector3(aV, aV, z);
	}
	Vector3 XZ(f32 aV) const {
		return Vector3(aV, y, aV);
	}
	Vector3 YZ(f32 aV) const {
		return Vector3(x, aV, aV);
	}
	Vector3 XYZ(f32 aV) const {
		return Vector3(aV, aV, aV);
	}

	Vector3 XY(f32 aX, f32 aY) const {
		return Vector3(aX, aY, z);
	}
	Vector3 XZ(f32 aX, f32 aZ) const {
		return Vector3(aX, y, aZ);
	}
	Vector3 YZ(f32 aY, f32 aZ) const {
		return Vector3(x, aY, aZ);
	}

	Vector3 XY(const Vector2& aV) const {
		return Vector3(aV.x, aV.y, z);
	}
	Vector3 YX(const Vector2& aV) const {
		return Vector3(aV.y, aV.x, z);
	}
	Vector3 XZ(const Vector2& aV) const {
		return Vector3(aV.x, y, aV.y);
	}
	Vector3 ZX(const Vector2& aV) const {
		return Vector3(aV.y, y, aV.x);
	}
	Vector3 YZ(const Vector2& aV) const {
		return Vector3(x, aV.x, aV.y);
	}
	Vector3 ZY(const Vector2& aV) const {
		return Vector3(x, aV.y, aV.x);
	}

	#pragma endregion

	//�l���擾����
	#pragma region Getter

	//f32
	#pragma region f32

	f32 X() const {
		return x;
	}
	f32 Y() const {
		return y;
	}
	f32 Z() const {
		return z;
	}

	#pragma endregion


	//Vector2
	#pragma region Vector2

	Vector2 XX() const {
		return Vector2(x, x);
	}
	Vector2 XY() const {
		return Vector2(x, y);
	}
	Vector2 XZ() const {
		return Vector2(x, z);
	}

	Vector2 YX() const {
		return Vector2(y, x);
	}
	Vector2 YY() const {
		return Vector2(y, y);
	}
	Vector2 YZ() const {
		return Vector2(y, z);
	}

	Vector2 ZX() const {
		return Vector2(z, x);
	}
	Vector2 ZY() const {
		return Vector2(z, y);
	}
	Vector2 ZZ() const {
		return Vector2(z, z);
	}

	Vector2 ToVector2() const {
		return Vector2(x, y);
	}

	#pragma endregion


	#pragma endregion


	//�v�Z�̃I�y���[�^
	#pragma region Calculate

	//Plus
	#pragma region

	const Vector3& operator +=(const Vector3& aVal) {
		x += aVal.x;
		y += aVal.y;
		z += aVal.z;
		return *this;
	}
	Vector3 operator +(const Vector3& aVal) const {
		Vector3 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	const Vector3& operator +=(f32 aVal) {
		x += aVal;
		y += aVal;
		z += aVal;
		return *this;
	}

	Vector3 operator +(f32 aVal) const {
		Vector3 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	#pragma endregion

	//Sub
	#pragma region

	const Vector3& operator -=(const Vector3& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		z -= aVal.z;
		return *this;
	}
	Vector3 operator -(const Vector3& aVal) const {
		Vector3 tRes = *this;
		tRes -= aVal;
		return tRes;
	}
	const Vector3& operator -=(f32 aVal) {
		x -= aVal;
		y -= aVal;
		z -= aVal;
		return *this;
	}
	Vector3 operator -(f32 aVal) const {
		Vector3 tRes = *this;
		tRes -= aVal;
		return tRes;
	}

	#pragma endregion

	//Multi
	#pragma region Multi

	const Vector3& operator *=(f32 aVal) {
		x *= aVal;
		y *= aVal;
		z *= aVal;
		return *this;
	}
	Vector3 operator *(f32 aVal) const {
		Vector3 tRes = *this;
		tRes *= aVal;
		return tRes;
	}

	#pragma endregion

	//Div
	#pragma region Div

	const Vector3& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));	//�O�ł͂Ȃ����Ƃ�ۏ�
		x /= aVal;
		y /= aVal;
		z /= aVal;
		return *this;
	}
	Vector3 operator /(f32 aVal) const {
		Vector3 tRes = *this;
		tRes /= aVal;
		return tRes;
	}

	#pragma endregion


	Vector3 operator -() const {
		Vector3 tRes(-x, -y, -z);
		return tRes;
	}

	#pragma endregion


	//��r�̃I�y���[�^
	#pragma region Compare

	BOOL operator ==(const Vector3& aVal) const {
		if (!IsEqual(x, aVal.x)) return false;
		if (!IsEqual(y, aVal.y)) return false;
		if (!IsEqual(z, aVal.z)) return false;
		return true;
	}
	BOOL operator !=(const Vector3& aVal) const {
		return !(*this == aVal);
	}

	BOOL operator <(const Vector3& aOther) const {
		return LenQuad() < aOther.LenQuad();
	}
	BOOL operator >=(const Vector3& aOther) const {
		return !(*this < aOther);
	}
	BOOL operator >(const Vector3& aOther) const {
		return LenQuad() > aOther.LenQuad();
	}
	BOOL operator <=(const Vector3& aOther) const {
		return !(*this > aOther);
	}

	#pragma endregion


	//���̑��v�Z
	#pragma region Other

	//�x�N�g���̒�����Ԃ�
	f32 Len() const {
		return Sqrt(LenQuad());
	}
	//�x�N�g���̒����̓���Ԃ�
	f32 LenQuad() const {
		return x * x + y * y + z * z;
	}

	//���K������
	Vector3 Normal() const {
		return *this / Len();
	}
	Vector3 NormalSafe() const {
		f32 tLen = Len();
		if (IsZero(tLen)) {
			return *this;	//����������0�Ȃ玩�g��Ԃ�
		}
		return *this / tLen;
	}


	//�O��
	Vector3 Cross(const Vector3& aVal) const {
		return Vector3(
			y * aVal.z - z * aVal.y,
			z * aVal.x - x * aVal.z,
			x * aVal.y - y * aVal.x
		);
	}
	//����
	f32 Dot(const Vector3& aVal) const {
		return x * aVal.x + y *  aVal.y + z * aVal.z;
	}

	#pragma endregion


	//�ÓI�Ȋ֐�
	#pragma region Static

	static Vector3 FromVector2(const Vector2& aVal) {
		return Vector3(aVal.x, aVal.y, 0.0f);
	}

	static Vector3 Unit() {
		return Vector3(1.0f, 0.0f, 0.0f);
	}
	static Vector3 One() {
		return Vector3(1.0f, 1.0f, 1.0f);
	}
	static Vector3 Zero() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	static Vector3 Forward() {
		return Vector3().Z(1.0f);
	}
	static Vector3 Back() {
		return Vector3().Z(-1.0f);
	}
	static Vector3 Up() {
		return Vector3().Y(1.0f);
	}
	static Vector3 Down() {
		return Vector3().Y(-1.0f);
	}
	static Vector3 Left() {
		return Vector3().X(-1.0f);
	}
	static Vector3 Right() {
		return Vector3().X(1.0f);
	}

	#pragma endregion


	//float�l�̔z����擾����
	#pragma region ToFloat

	struct Float3 {
		float v[3];
	};
	Float3 ToFloat3() const {
		return Float3{ x, y, z };
	}

	#pragma endregion


	//�w���p�֐�
	#pragma region Helper

	//���`���
	friend Vector3 Lerp(const Vector3& aFrom, const Vector3& aTo, f32 aRate) {
		return aFrom * (1.0f - aRate) + aTo * aRate;
	}

	//���ꂼ��̍ő�̗v�f��I��
	friend Vector3 MaxElement(const Vector3& aVal1, const Vector3& aVal2) {
		Vector3 tRes(Max(aVal1.x, aVal2.x), Max(aVal1.y, aVal2.y), Max(aVal1.z, aVal2.z));
		return tRes;
	}
	friend Vector3 MinElement(const Vector3& aVal1, const Vector3& aVal2) {
		Vector3 tRes(Min(aVal1.x, aVal2.x), Min(aVal1.y, aVal2.y), Min(aVal1.z, aVal2.z));
		return tRes;
	}

	#pragma endregion

};

#pragma endregion


//4��f32�����N���X
#pragma region Vector4

class Vector4 {
public:
	f32 x, y, z, w;


	//�R���X�g���N�^
	#pragma region Constructor

public:
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(f32 aX, f32 aY, f32 aZ, f32 aW) : x(aX), y(aY), z(aZ), w(aW) {}

	#pragma endregion

	
	//�l��ݒ肷��
	#pragma region Setter

	Vector4 X(f32 aVal) const {
		return Vector4(aVal, y, z, w);
	}
	Vector4 Y(f32 aVal) const {
		return Vector4(x, aVal, z, w);
	}
	Vector4 Z(f32 aVal) const {
		return Vector4(x, y, aVal, w);
	}
	Vector4 W(f32 aVal) const {
		return Vector4(x, y, z, aVal);
	}
	Vector4 XY(f32 aVal) const {
		return Vector4(aVal, aVal, z, w);
	}
	Vector4 XZ(f32 aVal) const {
		return Vector4(aVal, y, aVal, w);
	}
	Vector4 XW(f32 aVal) const {
		return Vector4(aVal, y, z, aVal);
	}
	Vector4 YZ(f32 aVal) const {
		return Vector4(x, aVal, aVal, w);
	}
	Vector4 YW(f32 aVal) const {
		return Vector4(x, aVal, z, aVal);
	}
	Vector4 ZW(f32 aVal) const {
		return Vector4(x, y, aVal, aVal);
	}
	Vector4 XYZ(f32 aVal) const {
		return Vector4(aVal, aVal, aVal, w);
	}
	Vector4 XYZW(f32 aVal) const {
		return Vector4(aVal, aVal, aVal, aVal);
	}

	#pragma endregion

	//�l���擾����
	#pragma region Getter

	#pragma region f32

	f32 X() const {
		return x;
	}
	f32 Y() const {
		return y;
	}
	f32 Z() const {
		return z;
	}
	f32 W() const {
		return w;
	}

	#pragma endregion

	#pragma region Vector2

	Vector2 XX() const {
		return Vector2(x, x);
	}
	Vector2 XY() const {
		return Vector2(x, y);
	}
	Vector2 XZ() const {
		return Vector2(x, z);
	}
	Vector2 XW() const {
		return Vector2(x, w);
	}

	Vector2 YX() const {
		return Vector2(y, x);
	}
	Vector2 YY() const {
		return Vector2(y, y);
	}
	Vector2 YZ() const {
		return Vector2(y, z);
	}
	Vector2 YW() const {
		return Vector2(y, w);
	}

	Vector2 ZX() const {
		return Vector2(z, x);
	}
	Vector2 ZY() const {
		return Vector2(z, y);
	}
	Vector2 ZZ() const {
		return Vector2(z, z);
	}
	Vector2 ZW() const {
		return Vector2(z, w);
	}

	Vector2 WX() const {
		return Vector2(w, x);
	}
	Vector2 WY() const {
		return Vector2(w, y);
	}
	Vector2 WZ() const {
		return Vector2(w, z);
	}
	Vector2 WW() const {
		return Vector2(w, w);
	}

	#pragma endregion

	Vector3 XYZ() const {
		return Vector3(x, y, z);
	}

	Vector3 ToVector3() const {
		return Vector3(x, y, z);
	}

	#pragma endregion


	//�v�Z�̃I�y���[�^
	#pragma region Calculate

	#pragma region Plus

	const Vector4& operator +=(const Vector4& aVal) {
		x += aVal.x;
		y += aVal.y;
		z += aVal.z;
		w += aVal.w;
		return *this;
	}
	Vector4 operator +(const Vector4& aVal) const {
		Vector4 tResult = *this;
		tResult += aVal;
		return tResult;
	}

	const Vector4& operator +=(f32 aVal) {
		x += aVal;
		y += aVal;
		z += aVal;
		w += aVal;
		return *this;
	}
	Vector4 operator +(f32 aVal) const {
		Vector4 tResult = *this;
		tResult += aVal;
		return tResult;
	}

	#pragma endregion


	#pragma region Sub

	const Vector4& operator -=(const Vector4& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		z -= aVal.z;
		w -= aVal.w;
		return *this;
	}
	Vector4 operator -(const Vector4& aVal) const {
		Vector4 tResult = *this;
		tResult -= aVal;
		return tResult;
	}
	const Vector4& operator -=(f32 aVal) {
		x -= aVal;
		y -= aVal;
		z -= aVal;
		w -= aVal;
		return *this;
	}
	Vector4 operator -(f32 aVal) const {
		Vector4 tResult = *this;
		tResult -= aVal;
		return tResult;
	}

	#pragma endregion

	
	#pragma region Multi

	const Vector4& operator *=(f32 aVal) {
		x *= aVal;
		y *= aVal;
		z *= aVal;
		w *= aVal;
		return *this;
	}
	Vector4 operator *(f32 aVal) const {
		Vector4 tResult = *this;
		tResult *= aVal;
		return tResult;
	}

	#pragma endregion

	
	#pragma region Div

	const Vector4& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));	//�O�ł͂Ȃ����Ƃ�ۏ�
		x /= aVal;
		y /= aVal;
		z /= aVal;
		w /= aVal;
		return *this;
	}
	Vector4 operator /(f32 aVal) const {
		Vector4 tResult = *this;
		tResult /= aVal;
		return tResult;
	}

	#pragma endregion

	
	Vector4 operator -() const {
		Vector4 tResult(-x, -y, -z, -w);
		return tResult;
	}

	#pragma endregion


	//��r�̃I�y���[�^
	#pragma region Compare

	BOOL operator ==(const Vector4& aVal) const {
		//�����̌덷��F�߂�
		if (!IsEqual(x, aVal.x, cFloatEpsilon * Max(Abs(x), Abs(aVal.x)))) return false;
		if (!IsEqual(y, aVal.y, cFloatEpsilon * Max(Abs(y), Abs(aVal.y)))) return false;
		if (!IsEqual(z, aVal.z, cFloatEpsilon * Max(Abs(z), Abs(aVal.z)))) return false;
		if (!IsEqual(w, aVal.w, cFloatEpsilon * Max(Abs(w), Abs(aVal.w)))) return false;
		return true;
	}
	BOOL operator !=(const Vector4& aVal) const {
		return !(*this == aVal);
	}

	BOOL operator <(const Vector4& aOther) {
		return LenQuad() < aOther.LenQuad();
	}
	BOOL operator >=(const Vector4& aOther) {
		return !(*this < aOther);
	}
	BOOL operator >(const Vector4& aOther) {
		return LenQuad() > aOther.LenQuad();
	}
	BOOL operator <=(const Vector4& aOther) {
		return !(*this > aOther);
	}

	#pragma endregion


	//���̑��v�Z
	#pragma region Other

	//�x�N�g���̒�����Ԃ�
	f32 Len() const {
		return Sqrt(LenQuad());
	}
	//�x�N�g���̒����̓���Ԃ�
	f32 LenQuad() const {
		return x * x + y * y + z * z + w * w;
	}

	//���K������B�������O�̏ꍇ�́A��{�x�N�g����Ԃ�
	Vector4 Normal() const {
		return *this / Len();
	}
	Vector4 NormalSafe() const {
		f32 len = Len();
		if (IsZero(len)) {
			return *this;
		}
		return *this / len;
	}

	#pragma endregion


	//�ÓI�Ȋ֐�
	#pragma region Static

	static Vector4 FromVector3(const Vector3& aVal) {
		return Vector4(aVal.x, aVal.y, aVal.z, 1.0f);
	}
	static Vector4 One() {
		return Vector4().XYZW(1.0f);
	}
	static Vector4 Zero() {
		return Vector4().XYZW(0.0f);
	}

	#pragma endregion
};

#pragma endregion


}