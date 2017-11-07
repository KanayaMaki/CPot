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
#include "vector.h"


namespace cpot {

#pragma region Quaternion


class Quaternion {
public:
	f32 w;
	Vector3 v;


	//�R���X�g���N�^
	#pragma region

public:
	Quaternion() : w(1.0f), v(0.0f, 0.0f, 0.0f) {
	}
	Quaternion(f32 aX, f32 aY, f32 aZ, f32 aW) : v(aX, aY, aZ), w(aW) {

	}
	Quaternion(const Vector3& aAxis, f32 aRad) {
		*this = FromAxis(aAxis, aRad);
	}

	#pragma endregion


	//�������擾����
	#pragma region Getter

	Vector3 XAxis() const {
		return Right();
	}
	Vector3 YAxis() const {
		return Up();
	}
	Vector3 ZAxis() const {
		return Forward();
	}

	Vector3 Forward() const {
		return Rotate(Vector3::Forward());
	}
	Vector3 Back() const {
		return Rotate(Vector3::Back());
	}
	Vector3 Left() const {
		return Rotate(Vector3::Left());
	}
	Vector3 Right() const {
		return Rotate(Vector3::Right());
	}
	Vector3 Up() const {
		return Rotate(Vector3::Up());
	}
	Vector3 Down() const {
		return Rotate(Vector3::Down());
	}

	#pragma endregion


	//�v�Z
	#pragma region Calculate


	//�x�N�g������]������
	Vector3 Rotate(const Vector3& aVec) const {
		Quaternion p = Quaternion::FromVector(aVec);
		return ((-(*this)) * p * (*this)).v;
	}

	Vector2 Rotate(const Vector2& aVec) const {
		return Rotate(Vector3::FromVector2(aVec)).ToVector2();
	}


	//��]��K�p
	const Quaternion& operator *=(const Quaternion& aQ) {
		f32 tW = w;
		w = aQ.w * tW - v.Dot(aQ.v);
		v = aQ.v * tW + v * aQ.w + v.Cross(aQ.v);
		return *this;
	}
	Quaternion operator*(const Quaternion& aQ) const {
		Quaternion tRes(*this);
		tRes *= aQ;
		return tRes;
	}

	//���΂̉�]���쐬
	Quaternion operator -() const {
		Quaternion res(*this);
		res.v = -res.v;
		return res;
	}


	//���K������
	Quaternion Normal() const {
		Quaternion tRes(*this);
		f32 tLenQuad = tRes.w * tRes.w + tRes.v.x * tRes.v.x + tRes.v.y * tRes.v.y + tRes.v.z * tRes.v.z;

		if (NotZero(tLenQuad)) {
			f32 tLen = Sqrtf(tLenQuad);
			tRes.w /= tLen;
			tRes.v /= tLen;
		}
		return tRes;
	}

	#pragma endregion


	//�쐬
	#pragma region Create

	//���Ɖ�]�ʂ���쐬����
	static Quaternion FromAxis(const Vector3& aV, f32 aRad) {
		Quaternion tRes;
		f32 tHalfRad = -aRad / 2.0f;
		tRes.w = Cosf(tHalfRad);
		tRes.v = aV.Normal() * Sinf(tHalfRad);
		return tRes;
	}

	//�x�N�^�[����쐬
	static Quaternion FromVector(const Vector3& aV) {
		Quaternion tQ;
		tQ.v = aV;
		tQ.w = 0.0f;
		return tQ;
	}

	//�x�N�^�[���m�̍�����쐬
	static Quaternion FromVectorDistance(const Vector3& aFrom, const Vector3& aTo) {
		//�N�H�[�^�j�I���̉�]�������߂�
		Vector3 lTo = aTo.Normal();
		Vector3 lFrom = aFrom.Normal();

		Vector3 lAxis = lTo.Cross(lFrom);

		BOOL lFail = false;

		//�������̒������O�Ȃ�
		if (IsZero(lAxis.LenQuad())) {
			lFail = true;	//�쐬�Ɏ��s
		}

		//���s����Ȃ�
		if (lFail == true) {
			if (lTo == -lFrom) {
				return Quaternion(Vector3(0.0f, 1.0f, 0.0f), ToRad(180)); //����lTo��lFrom���^�t�̎�
			}
			return Quaternion::Unit();	//�쐬�Ɏ��s�B�P�ʃN�H�[�^�j�I����Ԃ�
		}

		//	ToDo
		//	���p�̎��ɉ�]���Ȃ��B��������
		f32 lDot = lTo.Dot(lFrom);
		lDot = Clamp(lDot, -1.0f, 1.0f);
		f32 lAngle = Acosf(lDot);

		return Quaternion(lAxis, -lAngle);
	}

	#pragma endregion


	//��r
	#pragma region Compare

	BOOL operator==(const Quaternion& aQ) const {
		if (aQ.v != v) return false;
		if (!IsEqual(w, aQ.w)) return false;
		return true;
	}
	BOOL operator!=(const Quaternion& aQ) const {
		return !(*this == aQ);
	}

	#pragma endregion


	//�ÓI�Ȋ֐�
	#pragma region static

	static Quaternion XAxis(f32 rad) {
		return Quaternion(Vector3::Right(), rad);
	}
	static Quaternion YAxis(f32 rad) {
		return Quaternion(Vector3::Up(), rad);
	}
	static Quaternion ZAxis(f32 rad) {
		return Quaternion(Vector3::Forward(), rad);
	}
	static Quaternion Unit() {
		return Quaternion();
	}
	static Vector3 BaseDirection() {
		return Vector3::Forward();
	}

	#pragma endregion

};

#pragma endregion


}