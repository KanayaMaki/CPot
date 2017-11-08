//	�t�@�C����	:	Atom/singleton.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/07
//	�X�V����	:	2017/11/07
//	���e		:	�V���O���g���̃e���v���[�g���N���X�̎���

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