//
//	content	:	�Q�[��
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Out/out.h"
#include "./Pot/Game/game.h"

namespace myspc {

//Game�̏������s�����N���X
class MyGame : public cpot::GameBase {

public:
	//CPOT������������O�̒i�K�ŌĂ΂��B��ʃT�C�Y�Ȃǂ̐ݒ���s��
	void Setting() override {
		CPOT_LOG("Setting!");
	}

	//�Q�[���̏�����
	void Init() override {
		CPOT_LOG("Init!");
	}

	//�Q�[���̍X�V
	void Update() override {
		static cpot::u32 i = 0;
		i++;
		CPOT_LOG("Update! : ", i);
	}

	//�Q�[���̕`��
	void Render() override {
	}
};


}
