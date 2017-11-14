//
//	内容	:	VisualStudioのデバッグウィンドウに出力するクラス
//

#include "./outDebugWindow.h"

#include <Windows.h>


namespace cpot {

namespace windows {


//	デバッグウィンドウに出力
void OutDebugWindowDevice::Output(const CHAR* aStr) {
	::OutputDebugStringA(aStr);
}


}


}