#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

inline Matrix4x4 CreatePerspectiveProjectionMatrix(f32 aViewAngle, f32 aAspectRatio, f32 aNearClipLen, f32 aFarClipLen) {

	Matrix4x4 myMat;
	myMat._11 /= aAspectRatio;

	f32 rad = ToRad(aViewAngle);
	f32 sy = Sin(rad / 2) / Cos(rad / 2);
	myMat._11 *= 1.0f / sy;
	myMat._22 *= 1.0f / sy;
	myMat *= Matrix4x4::FromTransform(Vector3(0.0f, 0.0f, -aNearClipLen));

	myMat._44 = 0.0f;
	myMat._34 = 1.0f;

	//myMat *= Matrix4x4::FromScale(Vector3::One().Z(1.0f / (aFarClipLen - aNearClipLen)));
	myMat *= Matrix4x4::FromScale(Vector3::One().Z(aFarClipLen / (aFarClipLen - aNearClipLen)));

	return myMat;
}

inline Matrix4x4 CreateViewMatrix(const Vector3& aLoc, const Quaternion& aRot) {

	//逆向きに変換していく
	Matrix4x4 lRes;

	//移動の逆向きの変換
	lRes *= Matrix4x4::FromTransform(-aLoc);

	//回転の逆向きの変換
	lRes *= Matrix4x4::FromRotate(-aRot);

	return lRes;
}


class CameraView {
public:
	CameraView() {
		Reset();
	}

	void Reset() {
		mLocation = Vector3::Zero();
		mRotation = Quaternion::Unit();
		CalculateMatrix();
	}

	void Update() {
		if (IsChanged()) {
			CalculateMatrix();
		}
	}

public:
	BOOL IsChanged() const { return mChanged; }
	void Change() { mChanged = true; }
private:
	void UnChange() { mChanged = false; }

public:
	void SetLocation(const Vector3& aLocation) {
		if (mLocation != aLocation) {
			mLocation = aLocation;
			Change();
		}
	}
	void SetRotation(const Quaternion& aRotation) {
		if (mRotation != aRotation) {
			mRotation = aRotation;
			Change();
		}
	}

	Matrix4x4 GetMatrix() const {
		return mMatrix;
	}

public:
	void CalculateMatrix() {
		mMatrix = CreateViewMatrix(mLocation, mRotation);
		UnChange();
	}


private:
	Matrix4x4 mMatrix;
	Vector3 mLocation;
	Quaternion mRotation;

	BOOL mChanged;	//行列を更新する必要があるか
};

class CameraProjection {
public:
	CameraProjection() {
		Reset();
	}

	void Reset() {
		mAspectRatio = 1.0f;
		mNearClipLen = 0.01f;
		mFarClipLen = 10000.0f;
		Change();
	}

public:
	BOOL IsChanged() const { return mChanged; }
	void Change() { mChanged = true; }
protected:
	void UnChange() { mChanged = false; }

public:
	f32 GetAspectRatio() const { return mAspectRatio; }
	void SetAspectRatio(f32 aWidth, f32 aHeight) {
		f32 lAspectRatio = aWidth / aHeight;
		if (mAspectRatio != lAspectRatio) {
			mAspectRatio = lAspectRatio;
			Change();
		}
	}

	f32 GetNearClipLen() const { return mNearClipLen; }
	void SetNearClipLen(f32 aNearClipLen) {
		if (mNearClipLen != aNearClipLen) {
			mNearClipLen = aNearClipLen;
			Change();
		}
	}

	f32 GetFarClipLen() const { return mFarClipLen; }
	void SetFarClipLen(f32 aFarClipLen) {
		if (mFarClipLen != aFarClipLen) {
			mFarClipLen = aFarClipLen;
			Change();
		}
	}


protected:
	Matrix4x4 mMatrix;
	f32 mAspectRatio;	//アスペクト比
	f32 mNearClipLen;	//近いクリップ面までの距離
	f32 mFarClipLen;	//遠いクリップ面までの距離

	BOOL mChanged;	//行列を更新する必要があるか
};

class CameraPersProjection : public CameraProjection {
public:
	CameraPersProjection() {
		Reset();
	}

	void Reset() {
		CameraProjection::Reset();
		mViewAngle = 45.0f;
		Change();
	}

	void Update() {
		if (IsChanged()) {
			CalculateMatrix();
		}
	}

public:
	Matrix4x4 GetMatrix() const {
		return mMatrix;
	}

public:
	void CalculateMatrix() {
		mMatrix = CreatePerspectiveProjectionMatrix(mViewAngle, GetAspectRatio(), GetNearClipLen(), GetFarClipLen());
		UnChange();
	}


public:
	f32 ViewAngle() { return mViewAngle; }
	void ViewAngle(f32 aViewAngle) {
		if (mViewAngle != aViewAngle) {
			mViewAngle = aViewAngle;
			Change();
		}
	}

private:
	f32 mViewAngle;	//視野角

};

class PersCamera {
public:
	PersCamera() {
		Reset();
	}

public:
	void Reset() {
		mProjection.Reset();
		mView.Reset();
	}

	void Update() {
		mProjection.Update();
		mView.Update();
	}

public:
	Vector3 ProjectionLocation(const Vector3& aLocation) const {
		Vector4 proj = Vector4::FromVector3(aLocation) * mView.GetMatrix() * mProjection.GetMatrix();
		Vector3 projLoc = proj.XYZ() / proj.w;
		return projLoc;
	}

	CameraPersProjection mProjection;
	CameraView mView;
};


}
