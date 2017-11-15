//
//	content	:	Android�Ń��O���o�͂���
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Out/out.h"

#include <android/log.h>

namespace cpot {

namespace android {


//	�R���\�[�����쐬���āA�W���o�͂���N���X
class OutLog : public OutBase {

	//���̑�
	#pragma region Other

private:
	//OutBase�̊֐��̃I�[�o�[���C�h�B��������o�͂���
	void OutputStr(const CHAR* aStr) override {
		__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", aStr);
		//__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", aStr);
	}

	#pragma endregion

};

}

}