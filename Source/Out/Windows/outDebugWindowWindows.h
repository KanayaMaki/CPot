//
//	content	:	Windows�ŁAVisualStudio�̃f�o�b�O�E�B���h�E�ɏo��
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include "./Out/out.h"


namespace cpot {

namespace windows {


//	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���@�\�̃N���X
class OutDebugWindowDevice : public Singleton<OutDebugWindowDevice> {
	friend Singleton<OutDebugWindowDevice>;

public:
	void Output(const CHAR* aStr);
};


//	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���AOutBase����h�������N���X
class OutDebugWindow : public OutBase {
private:
	void OutputStr(const CHAR* aStr) override {

		//	�f�o�b�O�E�B���h�E�ɏo�͂���N���X�ɈϏ�����
		OutDebugWindowDevice::S().Output(aStr);
	}
};


}


}