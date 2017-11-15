//
//	content	:	�Q�[��
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Game/game.h"

namespace myspc {

//Game�̏������s�����N���X
class MyGame : public cpot::GameBase {

public:
	//CPOT������������O�̒i�K�ŌĂ΂��B��ʃT�C�Y�Ȃǂ̐ݒ���s��
	void Setting() override;

	//�Q�[���̏�����
	void Init() override;

	//�Q�[���̍X�V
	void Update() override;

	//�Q�[���̕`��
	void Render() override {}
};


}
