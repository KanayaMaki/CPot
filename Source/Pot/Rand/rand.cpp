//
//	content	:	�����𐶐�����N���X�̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#include "./Pot/Rand/rand.h"
#include "./Pot/Time/time.h"

namespace cpot {


//�����̐���
#pragma region Next

//0 <= x, x <= aMax�̗����𐶐�
RandType RandBase::Next(RandType aMax) {

	//�S�Ă̐����ϓ��ɏo��悤�ɁA���r���[�ȗ]��Ȃ������x��������
	RandType lMaxMode = Mod(MaxValue(), aMax + 1); //���r���[�ȗ]��̑傫��
	RandType lMaxJust = MaxValue() - lMaxMode;	//���傤�Ǌ���؂��ő吔�����߂�

	while (true) {

		RandType v = Next();

		if (v >= lMaxJust) {
			continue;	//���傤�Ǌ���؂��ő吔�ȏ�Ȃ�A������x�v�Z����
		}

		return Mod(v, aMax + 1);
	}
}

#pragma endregion


//����
#pragma region Operate

//���݂̎��Ԃ��V�[�h�Ƀ��Z�b�g
void RandBase::Reset() {
	SetSeed(SeedType(Time().GetUnix()));
}

#pragma endregion

}