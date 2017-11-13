//
//	�Q�[���̏������s���N���X�̎���
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {

//Game�̏������s�����N���X
class GameBase {

public:
	//���z�f�X�g���N�^
	virtual ~GameBase() {}

	//CPOT������������O�̒i�K�ŌĂ΂��B��ʃT�C�Y�Ȃǂ̐ݒ���s��
	virtual void Setting() = 0;

	//�Q�[���̏�����
	virtual void Init() = 0;

	//�Q�[���̍X�V
	virtual void Update() = 0;

	//�Q�[���̕`��
	virtual void Render() = 0;
};

//���[�U�[����������K�v������
GameBase* CreateGame();

}