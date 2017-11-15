//
//	content	:	Windowsで、VisualStudioのデバッグウィンドウに出力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Out/out.h"


namespace cpot {

namespace windows {


//	VisualStudioのデバッグウィンドウに出力する機能のクラス
class OutDebugWindowDevice : public Singleton<OutDebugWindowDevice> {
	friend Singleton<OutDebugWindowDevice>;

public:
	void Output(const CHAR* aStr);
};


//	VisualStudioのデバッグウィンドウに出力する、OutBaseから派生したクラス
class OutDebugWindow : public OutBase {
private:
	void OutputStr(const CHAR* aStr) override {

		//	デバッグウィンドウに出力するクラスに委譲する
		OutDebugWindowDevice::S().Output(aStr);
	}
};


}


}