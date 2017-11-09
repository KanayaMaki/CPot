//
//	���e		:	RandStandard�N���X�̎���
//

#pragma once

#include "./Atom/atom.h"
#include "./Rand/rand.h"

#include <random>

namespace cpot {

namespace standard {

#undef max
#undef min


//64bit�̗����𐶐�����f�o�C�X
class Rand64Device {

	//������
	#pragma region Init

public:
	Rand64Device() {
		Reset();
	}

	void Reload() {
		SetSeed(mSeed);
	}
	void Reset() {
		SetSeed(0);
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	//MinValue() <= x, x <= MaxValue()�̗����𐶐�
	u64 Next() {
		return mMt();
	}


	//�V�[�h�l���擾
	u64 GetSeed() const {
		return mSeed;
	}

	//�����̍ő�l
	u64 MaxValue() const {
		return mMt.max();
	}

	//�����̍ŏ��l
	u64 MinValue() const {
		return mMt.min();
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

	void SetSeed(u64 aSeed) {
		mMt.seed(aSeed);
		mSeed = aSeed;
	}

	#pragma endregion

	
	//�t�B�[���h
	#pragma region Field

private:
	std::mt19937_64 mMt;	//�����Z���k�c�C�X�^��64bit�̗����𐶐�����f�o�C�X
	u64 mSeed;	//�V�[�h�l

	#pragma endregion
};


//32bit�̗����𐶐�����f�o�C�X
class Rand32Device {

	//������
	#pragma region Init

public:
	Rand32Device() {
		Reset();
	}

	void Reload() {
		SetSeed(mSeed);
	}
	void Reset() {
		SetSeed(0);
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	//MinValue() <= x, x <= MaxValue()�̗����𐶐�
	u32 Next() {
		return mMt();
	}


	//�V�[�h�l���擾
	u32 GetSeed() const {
		return mSeed;
	}

	//�����̍ő�l
	u32 MaxValue() const {
		return mMt.max();
	}

	//�����̍ŏ��l
	u32 MinValue() const {
		return mMt.min();
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

	void SetSeed(u32 aSeed) {
		mMt.seed(aSeed);
		mSeed = aSeed;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	std::mt19937 mMt;	//�����Z���k�c�C�X�^��64bit�̗����𐶐�����f�o�C�X
	u32 mSeed;	//�V�[�h�l

	#pragma endregion
};


//RandBase��h�����������𐶐�����N���X
class Rand : public RandBase {

	//������
	#pragma region Init

public:
	Rand() {
		Reset();
	}

	#pragma endregion


	//�擾
	#pragma region Getter

private:
	//�����𐶐�����
	RandType NextInner() override {
		return mRand.Next();
	}

	//�����̍ő�l
	RandType MaxValueInner() const override {
		return mRand.MaxValue();
	}
	//�����̍ŏ��l
	RandType MinValueInner() const override {
		return mRand.MinValue();
	}

	//���݂̃V�[�h�l�̎擾
	SeedType GetSeedInner() const override {
		return mRand.GetSeed();
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

private:
	//�V�[�h�l��ݒ�
	void SetSeedInner(SeedType aSeed) override {
		mRand.SetSeed(aSeed);
	}

	#pragma endregion


	//�O���[�o���ɃA�N�Z�X�ł���C���X�^���X�̎擾
	#pragma region Instance

	static Rand& Inst() {
		static Rand r;
		return r;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	Rand32Device mRand;

public:
	Rand32Device GetDevice() const {
		return mRand;
	}

	#pragma endregion

};


}

}