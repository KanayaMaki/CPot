//
//	content	:	パスクラスの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using PathString = String<128>;

class Path {
	
public:
	static PathString FromRelative(const PathString& aNowPath, const PathString& aRelativePath) {
		PathString lRes = aNowPath;

		for (u32 i = lRes.GetLength() - 1; i >= 0; i--) {
			if (lRes[i] == '/' || lRes[i] == '\\') {
				break;
			}
			lRes.Pop(1);
		}

		return lRes + aRelativePath;
	}
};


}