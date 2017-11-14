//
//	content	:	ウィンドウズのカーソルを制御する
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include <Windows.h>

namespace cpot {

namespace windows {


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

}
