//
//	content	:	�V���O���g���̃e���v���[�g���N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {

template <class T>
class Singleton {
public:
	static T& S() {
		static T s;
		return s;
	}

protected:
	Singleton() {}
	~Singleton() {}
private:
	Singleton(const Singleton&) {}
	const Singleton& operator =(const Singleton&) {}
};


}
