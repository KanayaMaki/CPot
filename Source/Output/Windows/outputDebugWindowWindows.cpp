//
//	内容	:	VisualStudioのデバッグウィンドウに出力するクラス
//

#include "./outputDebugWindow.h"

#include <Windows.h>


namespace cpot {

namespace windows {


//	デバッグウィンドウに出力
void OutputDebugWindowDevice::Output(const CHAR* aStr) {
	::OutputDebugStringA(aStr);
}


}


}