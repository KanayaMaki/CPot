//
//	ファイルの入出力のインターフェースとなるクラス
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./Usefull/buffer.h"

namespace cpot {


//アウトプットのベースクラス
#pragma region FileBase


//ファイルの最大サイズを格納できる型
using FileSize = u32;


class FileBase {

	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	CPOT_VI BOOL OpenToWrite(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_ZR;
	CPOT_VI BOOL OpenToRead(const CHAR* aFileName, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion

	
	//ファイルを閉じる
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;
	
	#pragma endregion


	//ファイルから読み込む。読み込み設定でOpenしていないと失敗する
	//現在のPositionから読み込む
	//読み込んだサイズを返す
	#pragma region Read

public:
	CPOT_VI FileSize Read(BYTE* aBuffer, FileSize aSize) CPOT_ZR;
	CPOT_VI FileSize Read(Buffer& aBuffer) CPOT_ZR;
	CPOT_VI FileSize Read(Buffer& aBuffer, FileSize aSize) CPOT_ZR;
	
	#pragma endregion


	//ファイルに書き込む。書き込み設定でOpenしていないと失敗する
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

	//ファイルの大きさ
	CPOT_VI FileSize GetSize() const CPOT_ZR;

	//ファイルの現在位置
	CPOT_VI FileSize GetPosition() const CPOT_ZR;

	//ファイルのオープン設定
	CPOT_VI BOOL IsRead() const CPOT_ZR;
	CPOT_VI BOOL IsWrite() const CPOT_ZR;
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion


	//設定する
	#pragma region Setter

public:
	//ファイルの現在位置
	CPOT_VI void SetPosition(FileSize aPosition) CPOT_ZR;

	#pragma endregion


	//オープンフラグ
	#pragma region OpenFlag

protected:
	enum COpenFlag {
		cWrite,
		cRead,
		cBinary,
		cAdd
	};

	#pragma endregion

};


#pragma endregion


}