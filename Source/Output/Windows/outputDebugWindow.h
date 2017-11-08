//
//	内容	:	VisualStudioのデバッグウィンドウに出力するクラス
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include "./Output/output.h"


namespace cpot {

namespace windows {


//	VisualStudioのデバッグウィンドウに出力する機能のクラス
class OutputDebugWindowDevice : public Singleton<OutputDebugWindowDevice> {
	friend Singleton<OutputDebugWindowDevice>;

public:
	void Output(const CHAR* aStr);
};


//	VisualStudioのデバッグウィンドウに出力する、OutputBaseから派生したクラス
class OutputDebugWindow : public OutputBase {
private:
	void OutputStr(const CHAR* aStr) override {

		//	デバッグウィンドウに出力するクラスに委譲する
		OutputDebugWindowDevice::S().Output(aStr);
	}
};


}


}