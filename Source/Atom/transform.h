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
#include "matrix4x4.h"


namespace cpot {


//Transform
#pragma region Transform

class Transform {

	//フィールド
	#pragma region Field

public:
	Quaternion mRotation;
	Vector3 mPosition;
	Vector3 mScale;

	#pragma endregion


public:
	Transform() {
		mRotation = Quaternion::Unit();
		mPosition = Vector3::Zero();
		mScale = Vector3::One();
	}

	Matrix4x4 GetMatrix() const {
		Matrix4x4 lM;
		lM *= Matrix4x4::FromScale(mScale);
		lM *= Matrix4x4::FromRotate(mRotation);
		lM *= Matrix4x4::FromTransform(mPosition);
		return lM;
	}

	BOOL operator ==(const Transform& aT) const {
		if (mRotation != aT.mRotation) return false;
		if (mPosition != aT.mPosition) return false;
		if (mScale != aT.mScale) return false;
		return true;
	}
	BOOL operator !=(const Transform& aT) {
		return !((*this) == aT);
	}
};

#pragma endregion


}