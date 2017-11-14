//
//	content	:	Transformの実装
//	author	:	SaitoYoshiki
//

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