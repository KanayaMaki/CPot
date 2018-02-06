//
//	content	:	�W���o�͂���
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Out/out.h"

#include <cstdio>


namespace cpot {

namespace standard {


//	�W���o�͂���N���X
class OutStandard : public OutBase {

	//���̑�
	#pragma region Other

private:
	//OutBase�̊֐��̃I�[�o�[���C�h�B��������o�͂���
	void OutputStr(const CHAR* aStr) override {
		std::printf(aStr);
	}

	#pragma endregion

};


}


}