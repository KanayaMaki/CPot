//
//	content	:	�����𐶐�����N���X�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {


using RandType = u32;
using SeedType = u32;


class RandBase {

	//�I������
	#pragma region Final

public:
	//���z�f�X�g���N�^
	virtual ~RandBase() {}

	#pragma endregion


	//�����̐���
	#pragma region Next

public:
	//MinValue() <= x, x <= MaxValue()�̗����𐶐�
	RandType Next() {
		return NextInner();
	}

	//0 <= x, x <= aMax�̗����𐶐�
	RandType Next(RandType aMax);

	//aMin <= x, x <= aMax�̗����𐶐�
	RandType Next(RandType aMin, RandType aMax) {
		CPOT_ASSERT(aMin < aMax);
		return Next(aMax - aMin) + aMin;
	}
	f32 Nextf() {
		return static_cast<f32>( (f64)(Next()) / MaxValue() );
	}

	f32 Nextf(f32 aMin, f32 aMax) {
		f32 v = Nextf();
		return Replace(v, aMin, aMax);
	}

	f32 Nextf(f32 aMax) {
		return Nextf(0.0f, aMax);
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	//�����̍ő�l
	RandType MaxValue() const {
		return MaxValueInner();
	}
	//�����̍ŏ��l
	RandType MinValue() const {
		return MinValueInner();
	}

	//���݂̃V�[�h�l�̎擾
	SeedType GetSeed() const {
		GetSeedInner();
	}

	#pragma endregion


	//����
	#pragma region Operate

public:
	//�V�[�h�l�̐ݒ�
	void SetSeed(SeedType aSeed) {
		SetSeedInner(aSeed);
	}

	//���݂̃V�[�h�l�Ń��Z�b�g
	void Reload() {
		SetSeed(GetSeed());
	}
	//���݂̎��Ԃ��V�[�h�Ƀ��Z�b�g
	void Reset();

	#pragma endregion


	//�h����ŃI�[�o�[���C�h����K�v�̂���֐�
	#pragma region Virtual

protected:
	//�����𐶐�����֐��B�h����Ŏ�������K�v������
	virtual RandType NextInner() = 0;

	//�����̍ő�l
	virtual RandType MaxValueInner() const = 0;
	//�����̍ŏ��l
	virtual RandType MinValueInner() const = 0;

	//���݂̃V�[�h�l�̎擾
	virtual SeedType GetSeedInner() const = 0;

	//�V�[�h�l��ݒ�
	virtual void SetSeedInner(SeedType aSeed) = 0;


	#pragma endregion

};


}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/Rand/Standard/randStandard.h"
#endif
