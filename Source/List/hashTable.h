//
//	内容　:　RandBaseクラスの実装
//

#pragma once

#include "./Atom/atom.h"

namespace cpot {


using RandType = u32;
using SeedType = u32;


class RandBase {

	//終了処理
	#pragma region Final

public:
	//仮想デストラクタ
	virtual ~RandBase() {}

	#pragma endregion


	//乱数の生成
	#pragma region Next

public:
	//MinValue() <= x, x <= MaxValue()の乱数を生成
	RandType Next() {
		return NextInner();
	}

	//0 <= x, x <= aMaxの乱数を生成
	RandType Next(RandType aMax) {

		//全ての数が均等に出るように、中途半端な余りならもう一度生成する
		RandType lMaxMode = Mod(MaxValue(), aMax + 1); //中途半端な余りの大きさ
		RandType lMaxJust = MaxValue() - lMaxMode;	//ちょうど割り切れる最大数を求める

		while (true) {

			RandType v = Next();

			if (v >= lMaxJust) {
				continue;	//ちょうど割り切れる最大数以上なら、もう一度計算する
			}

			return Mod(v, aMax + 1);
		}
	}

	//aMin <= x, x <= aMaxの乱数を生成
	RandType Next(RandType aMin, RandType aMax) {
		CPOT_ASSERT(aMin < aMax);
		return Next(aMax - aMin) + aMin;
	}
	f32 Nextf() {
		return (f64)(Next()) / MaxValue();
	}

	f32 Nextf(f32 aMin, f32 aMax) {
		f32 v = Nextf();
		return Replace(v, aMin, aMax);
	}

	f32 Nextf(f32 aMax) {
		return Nextf(0.0f, aMax);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//乱数の最大値
	RandType MaxValue() const {
		return MaxValueInner();
	}
	//乱数の最小値
	RandType MinValue() const {
		return MinValueInner();
	}

	//現在のシード値の取得
	SeedType GetSeed() const {
		GetSeedInner();
	}

	#pragma endregion


	//操作
	#pragma region Operate

public:
	//シード値の設定
	void SetSeed(SeedType aSeed) {
		SetSeedInner(aSeed);
	}

	//現在のシード値でリセット
	void Reload() {
		SetSeed(GetSeed());
	}
	//シード値0でリセット
	void Reset() {
		SetSeed(SeedType(0));
	}

	#pragma endregion


	//派生先でオーバーライドする必要のある関数
	#pragma region Virtual

protected:
	//乱数を生成する関数。派生先で実装する必要がある
	virtual RandType NextInner() = 0;

	//乱数の最大値
	virtual RandType MaxValueInner() const = 0;
	//乱数の最小値
	virtual RandType MinValueInner() const = 0;

	//現在のシード値の取得
	virtual SeedType GetSeedInner() const = 0;

	//シード値を設定
	virtual void SetSeedInner(SeedType aSeed) = 0;


	#pragma endregion

};


}


#ifdef CPOT_ON_WINDOWS
#include "./Standard/rand.h"
#endif
