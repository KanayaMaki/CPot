//
//	���e	:	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���N���X
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include "./Output/output.h"


namespace cpot {

namespace windows {


//	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���@�\�̃N���X
class OutputDebugWindowDevice : public Singleton<OutputDebugWindowDevice> {
	friend Singleton<OutputDebugWindowDevice>;

public:
	void Output(const CHAR* aStr);
};


//	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���AOutputBase����h�������N���X
class OutputDebugWindow : public OutputBase {
private:
	void OutputStr(const CHAR* aStr) override {

		//	�f�o�b�O�E�B���h�E�ɏo�͂���N���X�ɈϏ�����
		OutputDebugWindowDevice::S().Output(aStr);
	}
};


}


}