//	ファイル名	:	Atom/singleton.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/07
//	更新日時	:	2017/11/07
//	内容		:	シングルトンのテンプレート基底クラスの実装

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
