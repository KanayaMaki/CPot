//
//	���e	:	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���N���X
//

#include "./outputDebugWindow.h"

#include <Windows.h>


namespace cpot {

namespace windows {


//	�f�o�b�O�E�B���h�E�ɏo��
void OutputDebugWindowDevice::Output(const CHAR* aStr) {
	::OutputDebugStringA(aStr);
}


}


}