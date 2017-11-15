//
//	content	:	�Q�[��
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Out/out.h"
#include "./Pot/Game/game.h"
#include "./Pot/Config/config.h"

namespace myspc {

//Game�̏������s�����N���X
class MyGame : public cpot::GameBase {

public:
	//CPOT������������O�̒i�K�ŌĂ΂��B��ʃT�C�Y�Ȃǂ̐ݒ���s��
	void Setting() override {
		cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
		cpot::Config::S().SetTitle("MyGame!");
	}

	//�Q�[���̏�����
	void Init() override {
		CPOT_LOG("Init!");
	}

	//�Q�[���̍X�V
	void Update() override;

	//�Q�[���̕`��
	void Render() override {}
};


}
