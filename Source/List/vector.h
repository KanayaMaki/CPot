//
//	内容　:　VectorBaseクラスの実装
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


//可変長配列のクラス
template <typename T>
class VectorBase {

	//要素の追加
	#pragma region Add

public:
	CPOT_VI void PushBack(const T& aT) CPOT_ZR;

	#pragma endregion


	//要素の消去
	#pragma region Remove
	
public:
	//指定された値と等しい要素の削除（先頭から１つだけ）
	CPOT_VI T Remove(const T& aT) CPOT_ZR;

	//等しい要素の削除（全て）
	CPOT_VI void RemoveAll(const T& aT) CPOT_ZR;

	//全ての要素を削除
	CPOT_VI void Clear() CPOT_ZR;

	#pragma endregion


	//要素の取得
	#pragma region Getter

public:
	//インデックスアクセス
	CPOT_VI T& operator[](u32 aIndex) CPOT_ZR;

	//指定された値の要素がいくつあるか
	CPOT_VI u32 Count(const T& aT) const CPOT_ZR;

	#pragma endregion


	//配列の要素数
	#pragma region Size

public:
	//現在の要素数の取得
	CPOT_VI u32 GetSize() const CPOT_ZR;

	#pragma endregion


	//確保しているバッファの要素数
	#pragma region Capacity

public:
	//バッファの要素数を増やす
	CPOT_VI void Reserve(u32 aSize) CPOT_ZR;

	//バッファの要素数を取得
	CPOT_VI u32 GetCapacity() const CPOT_ZR;

	#pragma endregion

};


}


#ifdef CPOT_ON_WINDOWS
#include "./List/Standard/vector.h"
#endif