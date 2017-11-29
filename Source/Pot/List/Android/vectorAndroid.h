//
//	content	:	Android�ł�Vector�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include <vector>
//#include <algorithm>


namespace cpot {

namespace android {


//�ϒ��z��̃N���X
template <typename T>
class Vector : public VectorBase<T> {

	//�v�f�̒ǉ�
	#pragma region Add

public:
	void PushBack(const T& aT) CPOT_OR {
		mVector.push_back(aT);
	}

	#pragma endregion


	//�v�f�̏���
	#pragma region Remove

public:
	//�w�肳�ꂽ�l�Ɠ������v�f�̍폜�i�P�����j
	T Remove(const T& aT) CPOT_OR {
		for (auto it = mVector.begin(); it != mVector.end(); it++) {
			if (*it == aT) {
				T lVal = *it;
				mVector.erase(it);	//�v�f�̍폜
				return lVal;
			}
		}
		return T(0);
	}

	//�w�肳�ꂽ�l�Ɠ������v�f�̍폜
	void RemoveAll(const T& aT) CPOT_OR {
		//mVector.erase(std::remove(mVector.begin(), mVector.end(), aT), mVector.end());
	}

	//��ԍŌ�̗v�f���폜���ĕԂ�
	T PopBack() CPOT_OR {
		T lRes = mVector.back();
		mVector.pop_back();
		return lRes;
	}


	//�S�Ă̗v�f���폜
	void Clear() CPOT_OR {
		mVector.clear();
	}

	#pragma endregion


	//�v�f�̎擾
	#pragma region Getter

public:
	//�C���f�b�N�X�A�N�Z�X
	T& operator[](u32 aIndex) CPOT_OR {
		return mVector[aIndex];
	}

	//�w�肳�ꂽ�l�̗v�f���������邩
	u32 Count(const T& aT) const CPOT_OR {
		u32 lCount = 0;
		for (auto it = mVector.begin(); it != mVector.end(); it++) {
			if (*it == aT) {
				lCount++;
			}
		}
		return lCount;
	}

	#pragma endregion


	//����
	#pragma region Operate

public:
	//�\�[�g
	void Sort() CPOT_OR {
		//std::sort(mVector.begin(), mVector.end());
	}

	#pragma endregion


	//�z��̗v�f��
	#pragma region Size

public:
	//���݂̗v�f���̎擾
	u32 GetSize() const CPOT_OR {
		return mVector.size();
	}

	//���݂̗v�f���𑝂₷
	void SetSize(u32 aSize) CPOT_OR {
		mVector.resize(aSize);
	}

	#pragma endregion


	//�m�ۂ��Ă���o�b�t�@�̗v�f��
	#pragma region Capacity

public:
	//�o�b�t�@�̗v�f���𑝂₷
	void Reserve(u32 aSize) CPOT_OR {
		mVector.reserve(aSize);
	}

	//�o�b�t�@�̗v�f�����擾
	u32 GetCapacity() const CPOT_OR {
		return mVector.capacity();
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	std::vector<T> mVector;

	#pragma endregion

};

}

template <typename T>
using Vector = android::Vector<T>;


}