//
//	content	:	Animation�N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


//�l�̕�ԂɎg���֐��Q
#pragma region Interpolation


//�f�t�H���g
template<typename T>
inline T Interpolation(const T& aStart, const T& aEnd, f32 aRate) {
	return Lerp(aStart, aEnd, aRate);
}

//�|�C���^
template<typename T>
inline T* Interpolation(T* aStart, T* aEnd, f32 aRate) {
	if (aRate >= 1.0f) {
		return aEnd;
	}
	return aStart;
}

//�N�H�[�^�j�I��
template<>
inline Quaternion Interpolation(const Quaternion& aStart, const Quaternion& aEnd, f32 aRate) {
	return SLerp(aStart, aEnd, aRate);
}


#pragma endregion



//�A�j���[�V�����̃L�[�t���[��
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



//�A�j���[�V����
#pragma region Animation


template <typename T>
class Animation {

public:
	Animation() {
		mTime = 0.0f;
		mIsLoop = false;
		Add(0.0f, mDefault);
	}

	//�ǉ�
	#pragma region Add

public:
	void Add(f32 aTime, const T& aValue) {
		Remove(aTime);
		mKeyFrames.PushBack(KeyFrame<T>(aTime, aValue));
		Sort();
		mEndTime = mKeyFrames[GetKeyFrameNum() - 1].mTime;
	}

	#pragma endregion


	//�폜
	#pragma region Remove

public:
	void Remove(f32 aTime) {
		mKeyFrames.Remove(KeyFrame<T>(aTime));
	}

	#pragma endregion


	//�擾
	#pragma region Getter

	//�l�̎擾
	#pragma region Value

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

	#pragma endregion


	//���Ԃɂ���Ďg�p����L�[�t���[���́A�C���f�b�N�X
	#pragma region Index

private:
	s32 GetKeyFrameIndex(f32 aTime) {
		s32 aIdx = -1;
		for (u32 i = 0; i < mKeyFrames.GetSize(); i++) {
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

	#pragma endregion

	
	//����
	#pragma region Time

public:
	//���ݎ���
	f32 GetTime() const {
		return mTime;
	}
	//�I������
	f32 GetEndTime() const {
		return mEndTime;
	}

	#pragma endregion


public:
	BOOL GetIsLoop() const {
		return mIsLoop;
	}

public:
	u32 GetKeyFrameNum() const {
		return mKeyFrames.GetSize();
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

public:
	//���݂̎��Ԃ�ݒ�
	void SetTime(f32 aTime) {
		mTime = aTime;
		TimeInRange();
	}

	#pragma endregion


	//����
	#pragma region Operate

public:
	//���ѕς���
	void Sort() {
		mKeyFrames.Sort();
	}

	//����
	#pragma region Time

public:
	//���݂̎��Ԃ�i�߂�
	void ForwardTime(f32 aTime) {
		mTime += aTime;
		TimeInRange();
	}
	void BackTime(f32 aTime) {
		ForwardTime(-aTime);
	}

private:
	void TimeInRange() {
		if (GetIsLoop()) {
			mTime = Wrap(mTime, GetEndTime());
		}
		else {
			mTime = Clamp(mTime, GetEndTime());
		}
	}

	#pragma endregion

public:
	void SetIsLoop(BOOL aIsLoop) {
		mIsLoop = aIsLoop;
	}

	#pragma endregion




	//�t�B�[���h
	#pragma region Field

private:
	Vector<KeyFrame<T>> mKeyFrames;
	f32 mTime;
	f32 mEndTime;
	BOOL mIsLoop;

	static T mDefault;	//�ŏ���0.0f�ɒǉ����Ă����A�f�t�H���g�̒l

	#pragma endregion
};

template <typename T>
T Animation<T>::mDefault;


#pragma endregion

}