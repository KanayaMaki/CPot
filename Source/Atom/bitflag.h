//	ファイル名	:	Atom/string.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/06
//	更新日時	:	2017/11/06
//	内容		:	文字列系のクラスや関数を定義

#pragma once


#include "defines.h"
#include "typedef.h"

#include "function.h"

#include "string.h"


namespace cpot {


class BitFlag {

	//コンストラクタ
	#pragma region Constructor

public:
	BitFlag() {
		DownAll();
	}

	#pragma endregion


	//フラグを取得する
	#pragma region Getter

public:
	//インデックスで取得
	BOOL operator[](u32 aIndex) {
		return IsStand(aIndex);
	}

	//指定されたビットが立っているか
	BOOL IsStand(u32 aIndex) const {
		return mVal & BitStand(aIndex);
	}
	BOOL IsDown(u32 aIndex) const {
		return !IsStand(aIndex);
	}

	//全てのビットが立っているか
	BOOL IsStandAll() const {
		return mVal == AllBitStand();
	}
	BOOL IsDownAll() const {
		return mVal == AllBitDown();
	}

	//いずれかのビットが立っているか
	BOOL IsStandAny() const {
		return !IsDownAll();
	}
	BOOL IsDownAny() const {
		return !IsStandAll();
	}

	#pragma endregion


	//フラグを設定する
	#pragma region Setter

public:

	//ビットを立てる
	#pragma region Stand

	BitFlag& Stand(u32 aIndex) {
		mVal |= BitStand(aIndex);
		return *this;
	}
	BitFlag& StandAll() {
		mVal = AllBitStand();
		return *this;
	}
	BitFlag& StandRange(u32 aStartIndex, u32 aEndIndex) {
		mVal |= BitStandRange(aStartIndex, aEndIndex);
		return *this;
	}

	#pragma endregion

	//ビットを下ろす
	#pragma region Down

	BitFlag& Down(u32 aIndex) {
		mVal &= ~(BitStand(aIndex));
		return *this;
	}
	BitFlag& DownAll() {
		mVal = AllBitDown();
		return *this;
	}
	BitFlag& DownRange(u32 aStartIndex, u32 aEndIndex) {
		mVal &= ~(BitStandRange(aStartIndex, aEndIndex));
		return *this;
	}

	#pragma endregion

	//ビットを反転させる
	#pragma region Flip

	BitFlag& Flip(u32 aIndex) {
		mVal ^= BitStand(aIndex);
		return *this;
	}
	BitFlag& FlipAll() {
		mVal ^= AllBitStand();
		return *this;
	}
	BitFlag& FlipRange(u32 aStartIndex, u32 aEndIndex) {
		mVal ^= BitStandRange(aStartIndex, aEndIndex);
		return *this;
	}

	#pragma endregion

	//真偽によって、立てるか下ろすか決める
	#pragma region Flag

	BitFlag& Flag(u32 aIndex, BOOL aIsStand) {
		if (aIsStand) {
			Stand(aIndex);
		}
		else {
			Down(aIndex);
		}
		return *this;
	}
	BitFlag& FlagRange(u32 aStartIndex, u32 aEndIndex, BOOL aIsStand) {
		if (aIsStand) {
			StandRange(aStartIndex, aEndIndex);
		}
		else {
			DownRange(aStartIndex, aEndIndex);
		}
		return *this;
	}

	#pragma endregion

	#pragma endregion


	//メンバ
	#pragma region Member

private:
	u32 mVal;	//ビットの状態を格納する

	#pragma endregion


	//ビットの並びを文字列にする
	#pragma region ToString

public:
	using BitString = String<33>;

	BitString ToString() const {
		BitString lRes;
		for (u32 i = 0; i < 32; i++) {
			lRes += IsStand(31 - i) ? "1" : "0";
		}
		return lRes;
	}

	#pragma endregion


	//静的な関数
	#pragma region static

public:

	//指定されたインデックスのビットだけが立っている状態を返す
	static u32 BitStand(u32 aIndex) {
		//aIndexは0～31
		CPOT_ASSERT(aIndex < sizeof(u32) * 8);
		return 1U << aIndex;
	}

	//指定されたインデックスの範囲のビットだけが立っている状態を返す
	static u32 BitStandRange(u32 aStartIndex, u32 aEndIndex) {
		//aIndexは0～31
		u32 lRes = 0UL;
		for (u32 i = aStartIndex; i <= aEndIndex; i++) {
			lRes += BitStand(i);
		}
		return lRes;
	}

	//全てのビットが立っている状態を返す
	static u32 AllBitStand() {
		return 0xffffffffU;
	}

	//全てのビットが下りている状態を返す
	static u32 AllBitDown() {
		return 0U;
	}

	#pragma endregion

};


}