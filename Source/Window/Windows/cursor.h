//	�t�@�C����	:	Window/Windows/window.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/08
//	�X�V����	:	2017/11/08
//	���e		:	�E�B���h�E�N���X�̎���

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include <Windows.h>

namespace cpot {

class Cursor : public Singleton<Cursor> {
	friend class Singleton<Cursor>;
	friend class Window;

public:
	enum CCursorState {
		cShow,
		cHide
	};
private:
	CCursorState mCursorState;

private:
	void Show() {
		while (1) {
			int times = ::ShowCursor(true);
			if (times >= 0) break;
		}
		mCursorState = cShow;
	}
	void Hide() {
		while (1) {
			int times = ::ShowCursor(false);
			if (times < 0) break;
		}
		mCursorState = cHide;
	}
	void ShowOrHide(BOOL aShow) {
		if (aShow) {
			Show();
		}
		else {
			Hide();
		}
	}

	BOOL IsShow() const {
		return mCursorState == cShow;
	}
};

}
