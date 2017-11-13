//
//	���e	:	FileStandard�N���X�̎���
//

#pragma once

#include "./Atom/atom.h"
#include "./File/file.h"

#include <fstream>

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


}

using FileOut = standard::FileOut;

}