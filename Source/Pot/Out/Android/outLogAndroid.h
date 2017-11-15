//
//	content	:	Androidでログを出力する
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Out/out.h"

#include <android/log.h>

namespace cpot {

namespace android {


//	コンソールを作成して、標準出力するクラス
class OutLog : public OutBase {

	//その他
	#pragma region Other

private:
	//OutBaseの関数のオーバーライド。文字列を出力する
	void OutputStr(const CHAR* aStr) override {
		__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", aStr);
		//__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", aStr);
	}

	#pragma endregion

};

}

}