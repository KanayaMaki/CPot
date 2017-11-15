//
//	content	:	�Q�[���̃R���t�B�O��Windows��
//	author	:	SaitoYoshiki
//

#include "./Pot/Config/Windows/configWindows.h"

#include "./Pot/Window/Windows/windowWindows.h"

namespace cpot {

namespace windows {


void Config::SetTitle(const CHAR* aTitle) {
	MutexLocker m(mTitleMutex);
	mTitle = aTitle;

	//�}���`�X���b�h�Ή�����K�v������B
	//�������́AWindow������Ăяo���Ȃ��Ƃ����Ȃ�
	/*
	if (Window::S().IsLoaded()) {
		Window::S().SetTitle(aTitle);
	}
	*/
}


}

}