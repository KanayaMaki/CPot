//	ファイル名	:	Atom/vector.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/07
//	更新日時	:	2017/11/07
//	内容		:	Vector3などの実装

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"
#include "vector.h"
#include "quaternion.h"


namespace cpot {


#pragma region Matrix4x4


class Matrix4x4 {

	//メンバ
	#pragma region Member

public:
	union {
		struct {
			f32 _11, _12, _13, _14;
			f32 _21, _22, _23, _24;
			f32 _31, _32, _33, _34;
			f32 _41, _42, _43, _44;
		};
		f32 v[4][4];
		Vector4 vec[4];
	};

	#pragma endregion


	//コンストラクタ
	#pragma region Constructor

public:
	Matrix4x4() {
		///*
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				v[i][j] = 0.0f;
			}
			v[i][i] = 1.0f;
		}//*/

		//対角成分だけ1.0f
		v[0][0] = 1.0f;
		v[1][1] = 1.0f;
		v[2][2] = 1.0f;
		v[3][3] = 1.0f;
	}

private:
	//初期化を行わない、効率化用
	Matrix4x4(s32 aDummy) {

	}

	#pragma endregion


	//matrixを作成する
	#pragma region Create

public:
	static Matrix4x4 Unit() {
		return Matrix4x4();
	}

	static Matrix4x4 FromRotate(const Quaternion& q) {
		Matrix4x4 tRes = Unit();
		f32 q0 = q.w; f32 q1 = q.v.x;
		f32 q2 = q.v.y; f32 q3 = q.v.z;

		tRes._11 = q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3;
		tRes._12 = 2 * (q1 * q2 - q0 * q3);
		tRes._13 = 2 * (q1 * q3 + q0 * q2);
		tRes._21 = 2 * (q1 * q2 + q0 * q3);
		tRes._22 = q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3;
		tRes._23 = 2 * (q2 * q3 - q0 * q1);
		tRes._31 = 2 * (q1 * q3 - q0 * q2);
		tRes._32 = 2 * (q2 * q3 + q0 * q1);
		tRes._33 = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
		return tRes;
	}
	static Matrix4x4 FromTransform(const Vector3& aLoc) {
		Matrix4x4 tRes = Unit();
		tRes._41 = aLoc.x;
		tRes._42 = aLoc.y;
		tRes._43 = aLoc.z;
		return tRes;
	}
	static Matrix4x4 FromScale(const Vector3& aScale) {
		Matrix4x4 tRes = Unit();
		tRes._11 *= aScale.x;
		tRes._22 = aScale.y;
		tRes._33 = aScale.z;
		return tRes;
	}


	#pragma endregion


	//計算する
	#pragma region Calculate

public:
	friend Vector3 operator *(const Vector3& aV, const Matrix4x4& aMat) {
		Vector4 lRes = Vector4::FromVector3(aV) * aMat;
		return lRes.ToVector3() / lRes.w;
	}
	friend Vector4 operator *(const Vector4& aV, const Matrix4x4& aMat) {
		Vector4 p(aV);
		Vector4 tRes;
		tRes.x = p.x * aMat._11 + p.y * aMat._21 + p.z * aMat._31 + p.w * aMat._41;
		tRes.y = p.x * aMat._12 + p.y * aMat._22 + p.z * aMat._32 + p.w * aMat._42;
		tRes.z = p.x * aMat._13 + p.y * aMat._23 + p.z * aMat._33 + p.w * aMat._43;
		tRes.w = p.x * aMat._14 + p.y * aMat._24 + p.z * aMat._34 + p.w * aMat._44;
		return tRes;
	}

	const Matrix4x4& operator *=(const Matrix4x4& aM) {
		Matrix4x4 tRes(-1);
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				tRes.v[i][j] = 0.0f;
				for (s32 k = 0; k < 4; k++) {
					tRes.v[i][j] += v[i][k] * aM.v[k][j];
				}
			}
		}
		*this = tRes;
		return *this;
	}
	Matrix4x4 operator *(const Matrix4x4& aM) {
		Matrix4x4 tRes = *this;
		tRes *= aM;
		return tRes;
	}

	#pragma endregion


	//その他
	#pragma region Other

public:
	//転置行列を取得
	Matrix4x4 T() const {
		Matrix4x4 tRes(-1);
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				tRes.v[i][j] = v[j][i];
			}
		}
		return tRes;
	}


	//逆行列を取得
	Matrix4x4 Inverse() const {
		Matrix4x4 tRes;
		
		//	TODO：逆行列の計算

		return tRes;
	}

	#pragma endregion

};

#pragma endregion


#pragma region ShaderMatrix4x4


//シェーダで使用する際のMatrix
//環境などによって、転置行列が必要だったりするのを吸収してくれる
class ShaderMatrix4x4 {
public:
	const ShaderMatrix4x4& operator=(const Matrix4x4& aM) {
		mM = aM.T();
		return *this;
	}
	operator Matrix4x4 () {
		return mM.T();
	}

	const ShaderMatrix4x4& operator *=(const Matrix4x4& aM) {
		Matrix4x4 lRes = (*this);
		lRes *= aM;
		*this = lRes;
		return *this;
	}
	ShaderMatrix4x4& operator *(const Matrix4x4& aM) {
		ShaderMatrix4x4 lRes = *this;
		lRes *= aM;
		return lRes;
	}

private:
	Matrix4x4 mM;
};


#pragma endregion



}