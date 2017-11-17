//
//	content	:	Animationしてくれるクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


//値の補間に使う関数群
#pragma region Interpolation


//デフォルト
template<typename T>
inline T Interpolation(const T& aStart, const T& aEnd, f32 aRate) {
	return Lerp(aStart, aEnd, aRate);
}

//ポインタ
template<typename T>
inline T* Interpolation(T* aStart, T* aEnd, f32 aRate) {
	if (aRate >= 1.0f) {
		return aEnd;
	}
	return aStart;
}

//クォータニオン
template<>
inline Quaternion Interpolation(const Quaternion& aStart, const Quaternion& aEnd, f32 aRate) {
	return SLerp(aStart, aEnd, aRate);
}


#pragma endregion



//アニメーションのキーフレーム
#pragma region KeyFrame

template <typename T>
struct KeyFrame {
	KeyFrame(f32 aTime, const T& aValue) : mTime(aTime), mValue(aValue) {}
	KeyFrame(f32 aTime) : mTime(aTime) {}
	f32 mTime;
	T mValue;

	BOOL operator <(const KeyFrame& v) const {
		return mTime < v.mTime;
	}
	BOOL operator ==(const KeyFrame& v) const {
		return IsEqual(mTime, v.mTime);
	}
};

#pragma endregion



//アニメーション
#pragma region Animation


template <typename T>
class Animation {

public:
	Animation() {
		mTime = 0.0f;
		Add(0.0f, mDefault);
	}

	//追加
	#pragma region Add

public:
	void Add(f32 aTime, const T& aValue) {
		Remove(aTime);
		mKeyFrames.PushBack(KeyFrame<T>(aTime, aValue));
		Sort();
	}

	#pragma endregion


	//削除
	#pragma region Remove

public:
	void Remove(f32 aTime) {
		mKeyFrames.Remove(KeyFrame<T>(aTime));
	}

	#pragma endregion


public:
	u32 GetKeyFrameNum() const {
		return mKeyFrames.GetSize();
	}

public:
	T Get(f32 aTime) {
		s32 lBeginIndex = GetKeyFrameIndex(aTime);
		s32 lEndIndex = lBeginIndex + 1;

		if (lBeginIndex < 0) {
			return mKeyFrames[0].mValue;
		}
		else if (lEndIndex >= GetKeyFrameNum()) {
			return mKeyFrames[GetKeyFrameNum() - 1].mValue;
		}
		else {
			f32 lTimeBegin = mKeyFrames[lBeginIndex].mTime;
			f32 lTimeEnd = mKeyFrames[lEndIndex].mTime;

			f32 lLerpRate = (aTime - lTimeBegin) / (lTimeEnd - lTimeBegin);

			return Interpolation(mKeyFrames[lBeginIndex].mValue, mKeyFrames[lEndIndex].mValue, lLerpRate);
		}
	}
	T Get() {
		return Get(mTime);
	}
	s32 GetKeyFrameIndex(f32 aTime) {
		s32 aIdx = -1;
		for (s32 i = 0; i < mKeyFrames.GetSize(); i++) {
			if (mKeyFrames[i].mTime <= aTime) {
				aIdx = i;
			}
			else {
				break;
			}
		}
		return aIdx;
	}
	s32 GetKeyFrameIndex() {
		return GetKeyFrameIndex(GetTime());
	}

	void Sort() {
		mKeyFrames.Sort();
	}


	//時間
	#pragma region Time

public:
	void Forward(f32 aTime) {
		mTime += aTime;
	}
	void SetTime(f32 aTime) {
		mTime = aTime;
	}
	f32 GetTime() const {
		return mTime;
	}

	#pragma endregion


private:
	Vector<KeyFrame<T>> mKeyFrames;
	f32 mTime;

	static T mDefault;
};

template <typename T>
T Animation<T>::mDefault;


#pragma endregion

}