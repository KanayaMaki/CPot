//
//	ファイルの入出力のインターフェースとなるクラス
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./Usefull/buffer.h"

namespace cpot {


//ファイルの最大サイズを格納できる型
using FileSize = u32;


//ファイル出力のベースクラス
#pragma region FileOutBase

class FileOutBase {

	//仮想デストラクタ
	#pragma region Destructor

public:
	CPOT_VI ~FileOutBase() {}

	#pragma endregion


	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	CPOT_VI BOOL Open(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion

	
	//ファイルを閉じる
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;
	
	#pragma endregion


	//ファイルに書き込む
	#pragma region Write

public:
	CPOT_VI void Write(const Buffer& aBuffer) CPOT_ZR;
	CPOT_VI void Write(const CHAR* aStr, FileSize aSize) CPOT_ZR;
	CPOT_VI void Write(const CHAR* aStr) CPOT_ZR;

	#pragma endregion

	
	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	CPOT_VI BOOL IsOpen() const CPOT_ZR;

	//ファイルのオープン設定
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion

};

#pragma endregion



//ファイル入力のベースクラス
#pragma region FileInBase

class FileInBase {

	//仮想デストラクタ
	#pragma region Destructor

public:
	CPOT_VI ~FileInBase() {}

	#pragma endregion

	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	CPOT_VI BOOL Open(const CHAR* aFileName, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion


	//ファイルを閉じる
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;

	#pragma endregion


	//ファイルから読み込む
	//現在のPositionから読み込む
	//読み込んだサイズを返す
	#pragma region Read

public:
	CPOT_VI FileSize Read(BYTE* aBuffer, FileSize aSize) CPOT_ZR;
	CPOT_VI FileSize Read(Buffer& aBuffer) CPOT_ZR;
	CPOT_VI FileSize Read(Buffer& aBuffer, FileSize aSize) CPOT_ZR;

	#pragma endregion


	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	CPOT_VI BOOL IsOpen() const CPOT_ZR;

	//ファイルの大きさ
	CPOT_VI FileSize GetSize() const CPOT_ZR;

	//ファイルの現在位置
	CPOT_VI FileSize GetPosition() const CPOT_ZR;

	//ファイルのオープン設定
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion


	//設定する
	#pragma region Setter

public:
	//ファイルの現在位置
	CPOT_VI void SetPosition(FileSize aPosition) CPOT_ZR;

	#pragma endregion
};

#pragma endregion

}