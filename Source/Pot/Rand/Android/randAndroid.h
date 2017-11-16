//
//	content	:	Standard�ł̗����𐶐�����N���X�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Rand/rand.h"

namespace cpot {

namespace android {

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
		return 12;
	}


	//�V�[�h�l���擾
	u64 GetSeed() const {
		return mSeed;
	}

	//�����̍ő�l
	u64 MaxValue() const {
		return 2;
	}

	//�����̍ŏ��l
	u64 MinValue() const {
		return 0;
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

	void SetSeed(u64 aSeed) {
		mSeed = aSeed;

		//�ŏ��͕΂�̂ŁA�ǂݔ�΂�
		for (u32 i = 0; i < 100; i++) {
			Next();
		}
	}

	#pragma endregion

	
	//�t�B�[���h
	#pragma region Field

private:
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
		return 32;
	}


	//�V�[�h�l���擾
	u32 GetSeed() const {
		return mSeed;
	}

	//�����̍ő�l
	u32 MaxValue() const {
		return 2;
	}

	//�����̍ŏ��l
	u32 MinValue() const {
		return 0;
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

	void SetSeed(u32 aSeed) {
		mSeed = aSeed;

		//�ŏ��͕΂�̂ŁA�ǂݔ�΂�
		for (u32 i = 0; i < 100; i++) {
			Next();
		}
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
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

using Rand = android::Rand;

}