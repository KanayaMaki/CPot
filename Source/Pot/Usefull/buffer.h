//
//	content	:	バッファクラスの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using BufferSize = u32;

class Buffer {
	
	//コンストラクタなど
	#pragma region Constructor


public:
	Buffer() {
		Reset();
	}
	Buffer(const BYTE* aBuffer, BufferSize aSize) {
		Reset();
		Load(aBuffer, aSize);
	}

	Buffer(const CHAR* aStr) {
		Reset();
		Load(aStr);
	}
	const Buffer& operator=(const Buffer& aB) {
		Reset();
		Load(aB.mBuffer, aB.mSize);
		return (*this);
	}
	Buffer(const Buffer& aB) {
		Reset();
		Load(aB.mBuffer, aB.mSize);
	}


	void Reset() {
		mBuffer = nullptr;
		mSize = 0;
		mPosition = 0;
	}

	#pragma endregion


	//デストラクタなど
	#pragma region Destructor

	~Buffer() {
		Release();
	}

	void Release() {
		if (IsLoaded()) {
			delete[] mBuffer;
			Reset();
		}
	}

	#pragma endregion


	//作成
	#pragma region Create

	template <typename T>
	void Load(const T& aData) {
		Load((const BYTE*)(&aData), sizeof(T));
	}

	void Load(const BYTE* aBuffer, BufferSize aSize) {

		Release();

		if (aSize > 0) {
			mBuffer = new BYTE[aSize];
			CopyMem(&(mBuffer[0]), &(aBuffer[0]), aSize);
			mSize = aSize;
		}
	}
	void Load(const CHAR* aStr) {
		Load((const BYTE*)aStr, StringLen(aStr));
	}

	void Create(BufferSize aSize) {

		Release();

		if (aSize > 0) {
			mBuffer = new BYTE[aSize];
			ZeroMem(&(mBuffer[0]), aSize);
			mSize = aSize;
		}
	}

	#pragma endregion


	//取得
	#pragma region Getter

	//バッファ
	BYTE* Get() const {
		return mBuffer;
	}

	//バッファのサイズ
	BufferSize GetSize() const {
		return mSize;
	}

	//バッファのカーソルの現在位置
	BufferSize GetPosition() const {
		return mPosition;
	}

	//読み込み済みかどうか
	BOOL IsLoaded() const {
		return mBuffer != nullptr;
	}

	#pragma endregion


	//設定
	#pragma region Setter

	//現在位置を設定する
	void Position(BufferSize aPosition) {
		mPosition = Clamp(aPosition, BufferSize(0), mSize - 1);
	}

	#pragma endregion
	

	//操作
	#pragma region Operation

	//バッファからデータを読み込む
	BufferSize Read(void* aBuffer, BufferSize aSize) {
		
		if (IsLoaded() == false) {
			return 0;
		}
		CPOT_ASSERT(aSize >= 0);

		BufferSize lEnd = mPosition + aSize;
		if (GetSize() < lEnd) {
			lEnd = GetSize();
		}
		BufferSize lReadSize = lEnd - mPosition;

		CopyMem(aBuffer, &(mBuffer[mPosition]), lReadSize);
		mPosition += lReadSize;

		return lReadSize;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	BYTE* mBuffer;
	BufferSize mSize;
	BufferSize mPosition;

	#pragma endregion
};


}