//	ファイル名	:	Output/output.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/11/09
//	更新日時	:	2017/11/09
//	内容		:	Outputクラスの実装

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./Usefull/buffer.h"

namespace cpot {


//アウトプットのベースクラス
#pragma region OutputBase


class OutputBase {

public:
	virtual ~OutputBase() {}	//仮想デストラクタ

public:
	template <typename T, typename... Rest>
	void Output(const T aVal, const Rest... aRest) {
		Output(aVal);
		Output(aRest...);
	}
	template <typename T, typename U>
	void Output(const T aV1, const U aV2) {
		Output(aV1);
		Output(aV2);
	}

public:
	void Output(const CHAR* aStr) {
		OutputStr(aStr);
	}
	void Output(s32 aVal) {
		OutputStr(ToString(aVal));
	}
	void Output(u32 aVal) {
		OutputStr(ToString(aVal));
	}
	void Output(s64 aVal) {
		OutputStr(ToString(aVal));
	}
	void Output(u64 aVal) {
		OutputStr(ToString(aVal));
	}
	void Output(f32 aVal) {
		OutputStr(ToString(aVal));
	}
	void Output(const Buffer& aBuffer) {
		OutputByte(aBuffer);
	}

protected:
	virtual void OutputStr(const CHAR* aStr) = 0;
	virtual void OutputByte(const Buffer& aBuffer) {}
};


#pragma endregion



//何も出力しないヌルオブジェクト
#pragma region OutputNull

class OutputNull : public OutputBase {
private:
	void OutputStr(const CHAR* aStr) override {}

public:
	static OutputNull& S() {
		static OutputNull s;
		return s;
	}
};

#pragma endregion



//何かのOutputクラスに出力するLog
#pragma region Log

class Log : public OutputBase {

	//	TODO	プログラムのどこからでも呼ばれるので、マルチスレッドに対応する

	//初期化を行う
	#pragma region Init

public:
	Log() {
		Reset();
	}

	void Reset() {
		//デフォルトでは、ヌル出力
		mOut = &(OutputNull::S());
	}

	#pragma endregion


	//終了処理を行う
	#pragma region Final

public:
	~Log() override {}

	#pragma endregion



	//設定
	#pragma region Setter

public:
	//出力先を設定する
	void Set(OutputBase* aOut) {
		mOut = aOut;
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//グローバル的に使用できる、ログのインスタンスを取得
	static Log& S() {
		static Log s;
		return s;
	}

	#pragma endregion


	//操作
	#pragma region Operate

private:
	//文字列を出力する。OutBaseにオーバーライドで呼ばれる
	void OutputStr(const CHAR* aStr) override {
		//MutexLocker m(mMutex);
		mOut->Output(aStr);
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	OutputBase* mOut;
	//Mutex mMutex;

	#pragma endregion
};



#pragma endregion



//Logを出すときに便利なマクロ
#pragma region CPOT_LOG

//ソースコードの中の定数文字列が、馬鹿にならないメモリ量になる気がするので、
//このマクロを使うと消したときに定数文字列がコードに残らない

#ifdef CPOT_VALID_LOG
#define CPOT_LOG(...) \
	Log::S().Output(__VA_ARGS__);
#define CPOT_LOG_ENDL(...) \
	Log::S().Output(__VA_ARGS__, "\n");
#else
#define CPOT_LOG(string)
#define CPOT_LOG_ENDL(string)
#endif

#pragma endregion


}