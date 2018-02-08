//
//	content	:	�Q�[���̃R���t�B�O��Linux��
//	author	:	SaitoYoshiki
//

#include "./Pot/Config/Linux/configLinux.h"


namespace cpot {

namespace linux {


void Config::SetTitle(const CHAR* aTitle) {
	MutexLocker m(mTitleMutex);
	mTitle = aTitle;

}


}

}