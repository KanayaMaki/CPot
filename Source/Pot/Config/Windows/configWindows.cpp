//
//	content	:	ゲームのコンフィグのWindows環境
//	author	:	SaitoYoshiki
//

#include "./Pot/Config/Windows/configWindows.h"

#include "./Pot/Window/Windows/windowWindows.h"

namespace cpot {

namespace windows {


void Config::SetTitle(const CHAR* aTitle) {
	MutexLocker m(mTitleMutex);
	mTitle = aTitle;

	//マルチスレッド対応する必要がある。
	//もしくは、Window側から呼び出さないといけない
	/*
	if (Window::S().IsLoaded()) {
		Window::S().SetTitle(aTitle);
	}
	*/
}


}

}