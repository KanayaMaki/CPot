//
//	���e	:	VisualStudio�̃f�o�b�O�E�B���h�E�ɏo�͂���N���X
//

#include "./outDebugWindow.h"

#include <Windows.h>


namespace cpot {

namespace windows {


//	�f�o�b�O�E�B���h�E�ɏo��
void OutDebugWindowDevice::Output(const CHAR* aStr) {
	::OutputDebugStringA(aStr);
}


}


}