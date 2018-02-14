//
//	content	:	Quad2DÅAQuad3DÇ»Ç«ÇÃé¿ëï
//	author	:	SaitoYoshiki
//

#pragma once

#include "vector.h"


namespace cpot {

enum CPointIndex {
	cLeftBottom,
	cLeftTop,
	cRightBottom,
	cRightTop,
	cPointIndexMax,
};

struct Rect2D {

	Rect2D() {
		mCenter = Vector2(0.0f, 0.0f);
		mSize = Vector2(0.0f, 0.0f);
		mRotRad = 0.0f;
	}

	Rect2D(const Vector2& aCenter, const Vector2& aSize) {
		*this = FromCenter(aCenter, aSize);
	}
	Rect2D(const Vector2& aCenter, const Vector2& aSize, f32 aRotDeg) {
		*this = FromCenter(aCenter, aSize, aRotDeg);
	}

	static Rect2D FromCenter(const Vector2& aCenter, const Vector2& aSize) {
		return FromCenter(aCenter, aSize, 0.0f);
	}
	static Rect2D FromCenter(const Vector2& aCenter, const Vector2& aSize, f32 aRotDeg) {
		Rect2D lRes;
		lRes.mCenter = aCenter;
		lRes.mSize = aSize;
		lRes.mRotRad = ToRad(aRotDeg);
		return lRes;
	}

	static Rect2D FromLeftBottom(const Vector2& aLeftBottom, const Vector2& aSize) {
		return FromCenter(aLeftBottom + aSize / 2.0f, aSize, 0.0f);
	}


	Rect2D operator *(const Vector2& aScale) const {
		Rect2D lRes = *this;
		lRes *= aScale;
		return lRes;
	}
	Rect2D& operator *=(const Vector2& aScale) {
		mSize *= aScale;
	}

	Rect2D operator +(const Vector2& aValue) const {
		Rect2D lRes = *this;
		lRes += aValue;
		return lRes;
	}
	Rect2D& operator +=(const Vector2& aValue) {
		mCenter += aValue;
	}

	Vector2 GetPoint(CPointIndex aIndex) const {
		CPOT_ASSERT(0 <= aIndex && aIndex < cPointIndexMax);
		Vector2 lOffset;
		switch (aIndex) {
			case cLeftBottom:
				lOffset = Vector2(-0.5f, -0.5f);
				break;
			case cLeftTop:
				lOffset = Vector2(-0.5f, 0.5f);
				break;
			case cRightBottom:
				lOffset = Vector2(0.5f, -0.5f);
				break;
			case cRightTop:
				lOffset = Vector2(0.5f, 0.5f);
				break;
		}
		return mCenter + Quaternion::ZAxis(mRotRad).Rotate(mSize * lOffset);
	}

	Vector2 mCenter;
	Vector2 mSize;
	f32 mRotRad;
};

struct Quad2D {
	Vector2 GetPoint(CPointIndex aIndex) const {
		CPOT_ASSERT(0 <= aIndex && aIndex < cPointIndexMax);
		return point[aIndex];
	}
	void SetPoint(CPointIndex aIndex, const Vector2& aPoint) {
		CPOT_ASSERT(0 <= aIndex && aIndex < cPointIndexMax);
		point[aIndex] = aPoint;
	}
	void SetRect(const Rect2D& aRect) {
		point[cLeftBottom] = aRect.GetPoint(cLeftBottom);
		point[cLeftTop] = aRect.GetPoint(cLeftTop);
		point[cRightBottom] = aRect.GetPoint(cRightBottom);
		point[cRightTop] = aRect.GetPoint(cRightTop);
	}
	
	Quad2D operator *(const Vector2& aValue) const {
		Quad2D q(*this);
		return q *= aValue;
	}
	Quad2D operator *=(const Vector2& aValue) {
		for (u32 i = 0; i < cPointIndexMax; i++) {
			point[i] *= aValue;
		}
		return *this;
	}

	Quad2D operator +(const Vector2& aValue) const {
		Quad2D q(*this);
		return q += aValue;
	}
	Quad2D operator +=(const Vector2& aValue) {
		for (u32 i = 0; i < cPointIndexMax; i++) {
			point[i] += aValue;
		}
		return *this;
	}

	Vector2 point[4];
};

}