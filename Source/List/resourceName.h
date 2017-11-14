//
//	content	:	事前に登録しておいた文字列を、キーから取得する
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./List/hashTable.h"

namespace cpot {

class ResourceName {

public:
	//リソースの名前の型の定義
	using Name = String<64>;

	//登録
	#pragma region Regist

public:
	void Regist(const HashTableKey& aKey, const CHAR* aName) {
		mNameList.Add(aKey, Name(aName));
	}
	void Regist(const CHAR* aKey, const CHAR* aName) {
		Regist(HashTableKey(aKey), aName);	//委譲
	}

	#pragma endregion


	//取得
	#pragma region Get

public:
	const Name& Get(const HashTableKey& aKey) {
		if (mNameList.Exist(aKey)) {
			return mNameList.Find(aKey);
		}
		return mNameNull;
	}
	const Name& Get(const CHAR* aKey) {
		return Get(aKey);	//委譲
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	HashTable<Name> mNameList;	//キーと名前のセット
	Name mNameNull;	//見つからなかったときに返される

	#pragma endregion
};

}