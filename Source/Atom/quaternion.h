//	ファイル名	:	Atom/quaternion.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/07
//	更新日時	:	2017/11/07
//	内容		:	Quaternionの実装

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


	//コンストラクタ
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


	//方向を取得する
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


	//計算
	#pragma region Calculate


	//ベクトルを回転させる
	Vector3 Rotate(const Vector3& aVec) const {
		Quaternion p = Quaternion::FromVector(aVec);
		return ((-(*this)) * p * (*this)).v;
	}

	Vector2 Rotate(const Vector2& aVec) const {
		return Rotate(Vector3::FromVector2(aVec)).ToVector2();
	}


	//回転を適用
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

	//反対の回転を作成
	Quaternion operator -() const {
		Quaternion res(*this);
		res.v = -res.v;
		return res;
	}


	//正規化する
	Quaternion Normal() const {
		Quaternion tRes(*this);
		f32 tLenQuad = tRes.w * tRes.w + tRes.v.x * tRes.v.x + tRes.v.y * tRes.v.y + tRes.v.z * tRes.v.z;

		if (NotZero(tLenQuad)) {
			f32 tLen = Sqrt(tLenQuad);
			tRes.w /= tLen;
			tRes.v /= tLen;
		}
		return tRes;
	}

	#pragma endregion


	//作成
	#pragma region Create

	//軸と回転量から作成する
	static Quaternion FromAxis(const Vector3& aV, f32 aRad) {
		Quaternion tRes;
		f32 tHalfRad = -aRad / 2.0f;
		tRes.w = Cos(tHalfRad);
		tRes.v = aV.Normal() * Sin(tHalfRad);
		return tRes;
	}

	//ベクターから作成
	static Quaternion FromVector(const Vector3& aV) {
		Quaternion tQ;
		tQ.v = aV;
		tQ.w = 0.0f;
		return tQ;
	}

	//ベクター同士の差から作成
	static Quaternion FromVectorDistance(const Vector3& aFrom, const Vector3& aTo) {
		//クォータニオンの回転軸を求める
		Vector3 lTo = aTo.Normal();
		Vector3 lFrom = aFrom.Normal();

		Vector3 lAxis = lTo.Cross(lFrom);

		BOOL lFail = false;

		//もし軸の長さが０なら
		if (IsZero(lAxis.LenQuad())) {
			lFail = true;	//作成に失敗
		}

		//失敗するなら
		if (lFail == true) {
			if (lTo == -lFrom) {
				return Quaternion(Vector3(0.0f, 1.0f, 0.0f), ToRad(180)); //もしlToとlFromが真逆の時
			}
			return Quaternion::Unit();	//作成に失敗。単位クォータニオンを返す
		}

		//	ToDo
		//	直角の時に回転しない。おかしい
		f32 lDot = lTo.Dot(lFrom);
		lDot = Clamp(lDot, -1.0f, 1.0f);
		f32 lAngle = Acos(lDot);

		return Quaternion(lAxis, -lAngle);
	}

	#pragma endregion


	//比較
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


	//静的な関数
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


	//ヘルパ関数
	#pragma region Helper

	friend Quaternion SLerp(const Quaternion& aFrom, const Quaternion& aTo, f32 aRate) {

		f64 cosom = aFrom.v.x * aTo.v.x + aFrom.v.y * aTo.v.y +
			aFrom.v.z * aTo.v.z + aFrom.w * aTo.w;

		f32 aTo1[4];
		if (cosom < 0.0) {
			cosom = -cosom;
			aTo1[0] = -aTo.v.x;
			aTo1[1] = -aTo.v.y;
			aTo1[2] = -aTo.v.z;
			aTo1[3] = -aTo.w;
		}
		else {
			aTo1[0] = aTo.v.x;
			aTo1[1] = aTo.v.y;
			aTo1[2] = aTo.v.z;
			aTo1[3] = aTo.w;
		}


		f64 omega, sinom, scale0, scale1;

		cosom = Clamp01(cosom);

		if (NotZero(1.0 - cosom)) {
			omega = Acos(cosom);
			sinom = Sin(omega);
			scale0 = Sin((1.0 - aRate) * omega) / sinom;
			scale1 = Sin(aRate * omega) / sinom;
		}
		else {
			scale0 = 1.0 - aRate;
			scale1 = aRate;
		}

		Quaternion tRes;
		tRes.v.x = scale0 * aFrom.v.x + scale1 * aTo1[0];
		tRes.v.y = scale0 * aFrom.v.y + scale1 * aTo1[1];
		tRes.v.z = scale0 * aFrom.v.z + scale1 * aTo1[2];
		tRes.w = scale0 * aFrom.w + scale1 * aTo1[3];
		return tRes.Normal();
	}
	#pragma endregion

};

#pragma endregion


}