//
//	content	:	Windowsで、VisualStudioのデバッグウィンドウに出力
//	author	:	SaitoYoshiki
//

#include "./Pot/Out/Windows/outDebugWindowWindows.h"

#include <Windows.h>


namespace cpot {

namespace windows {


//	デバッグウィンドウに出力
void OutDebugWindowDevice::Output(const CHAR* aStr) {
	::OutputDebugStringA(aStr);
}


}


}