//
//	content	:	Standard�ł�File�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/File/file.h"

#include <fstream>
#include <vector>

namespace cpot {

namespace standard {


//�t�@�C���o�͂̃N���X
#pragma region FileOut

class FileOut : public FileOutBase {

	//�R���X�g���N�^
	#pragma region Constructor

public:
	FileOut() {
		
	}
	FileOut(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) {
		Open(aFileName, aIsAdd, aBinary);
	}

	#pragma endregion
	

	//�f�X�g���N�^
	#pragma region Destructor

	~FileOut() CPOT_OR {
		Close();
	}

	#pragma endregion


	//�t�@�C�����J���B�t�@�C�����J���̂ɐ��������true�A���s�����false��Ԃ�
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


	//�t�@�C�������
	#pragma region Close

public:
	void Close() CPOT_OR {
		mOfs.close();
	}

	#pragma endregion


	//�t�@�C���ɏ�������
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


	//�����擾����
	#pragma region Getter

public:
	//�t�@�C�����J����Ă��邩
	BOOL IsOpen() const CPOT_OR {
		return mOfs.is_open();
	}

	//�t�@�C���̃I�[�v���ݒ�
	BOOL IsBinary() const CPOT_OR {
		return mIsBinary;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	std::ofstream mOfs;
	BOOL mIsBinary;

	#pragma endregion

};

#pragma endregion



//�t�@�C�����͂̃x�[�X�N���X
#pragma region FileIn

class FileIn : public FileInBase {

	//�R���X�g���N�^
	#pragma region Constructor

public:
	FileIn() {}
	FileIn(const CHAR* aFileName, BOOL aBinary = false) {
		Open(aFileName, aBinary);
	}

	#pragma endregion


	//�f�X�g���N�^
	#pragma region Destructor

public:
	~FileIn() {
		Close();
	}

	#pragma endregion


	//�t�@�C�����J���B�t�@�C�����J���̂ɐ��������true�A���s�����false��Ԃ�
	#pragma region Open

public:
	BOOL Open(const CHAR* aFileName, BOOL aBinary = false) CPOT_OR {
		unsigned int lOpenMode = std::ios::in;
		if (aBinary) {
			lOpenMode |= std::ios::binary;
			mIsBinary = true;
		}
		else {
			mIsBinary = false;
		}

		mIfs.open(aFileName, lOpenMode);

		return IsOpen();
	}

	#pragma endregion


	//�t�@�C�������
	#pragma region Close

public:
	void Close() CPOT_OR {
		mIfs.close();
	}

	#pragma endregion


	//�t�@�C������ǂݍ���
	//���݂�Position����ǂݍ���
	#pragma region Read

public:
	void Read(Buffer& aBuffer) CPOT_OR {
		
		std::istreambuf_iterator<char> lTt(mIfs);
		std::istreambuf_iterator<char> lLast;
		std::vector<char> lStr(lTt, lLast);

		aBuffer.Load((const BYTE*)lStr.data(), lStr.size());
	}

	#pragma endregion


	//�����擾����
	#pragma region Getter

public:
	//�t�@�C�����J����Ă��邩
	BOOL IsOpen() const CPOT_OR {
		return mIfs.is_open();
	}

	//�t�@�C���̃I�[�v���ݒ�
	BOOL IsBinary() const CPOT_OR {
		return mIsBinary;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	std::ifstream mIfs;
	BOOL mIsBinary;

	#pragma endregion
};

#pragma endregion


}

using FileOut = standard::FileOut;
using FileIn = standard::FileIn;

}