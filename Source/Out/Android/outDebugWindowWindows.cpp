//
//	content	:	Windows�ŁAVisualStudio�̃f�o�b�O�E�B���h�E�ɏo��
//	author	:	SaitoYoshiki
//

#include "./outDebugWindowWindows.h"

#include <Windows.h>


namespace cpot {

namespace windows {


//	�f�o�b�O�E�B���h�E�ɏo��
void OutDebugWindowDevice::Output(const CHAR* aStr) {
	::OutputDebugStringA(aStr);
}


}


}