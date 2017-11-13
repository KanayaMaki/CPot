//
//	内容	:	FileStandardクラスの実装
//

#pragma once

#include "./Atom/atom.h"
#include "./File/file.h"

#include <fstream>

namespace cpot {

namespace standard {


//ファイル出力のクラス
#pragma region FileOut

class FileOut : public FileOutBase {

	//コンストラクタ
	#pragma region Constructor

public:
	FileOut() {
		
	}

	#pragma endregion
	

	//デストラクタ
	#pragma region Destructor

	~FileOut() CPOT_OR {
		Close();
	}

	#pragma endregion


	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	BOOL Open(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_OR {
		unsigned int lOpenMode = std::ios::out;
		if (aIsAdd) {
			lOpenMode |= std::ios::app;
		}
		else {
			lOpenMode |= std::ios::trunc;
		}
		if (aBinary) {
			lOpenMode |= std::ios::binary;
			mIsBinary = true;
		}
		else {
			mIsBinary = false;
		}

		mOfs.open(aFileName, lOpenMode);

		return IsOpen();
	}

	#pragma endregion


	//ファイルを閉じる
	#pragma region Close

public:
	void Close() CPOT_OR {
		mOfs.close();
	}

	#pragma endregion


	//ファイルに書き込む
	#pragma region Write

public:
	void Write(const Buffer& aBuffer) CPOT_OR {
		mOfs.write((const CHAR*)(aBuffer.Get()), aBuffer.GetSize());
	}
	void Write(const CHAR* aStr, FileSize aSize) CPOT_OR {
		mOfs.write(aStr, aSize);
	}
	void Write(const CHAR* aStr) CPOT_OR {
		mOfs.write(aStr, StringLen(aStr));
	}

	#pragma endregion


	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	BOOL IsOpen() const CPOT_OR {
		return mOfs.is_open();
	}

	//ファイルのオープン設定
	BOOL IsBinary() const CPOT_OR {
		return mIsBinary;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::ofstream mOfs;
	BOOL mIsBinary;

	#pragma endregion

};

#pragma endregion


}

using FileOut = standard::FileOut;

}