//
//	content	:	File�̓��o�͂̃C���^�[�t�F�[�X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Usefull/buffer.h"

namespace cpot {


//�t�@�C���̍ő�T�C�Y���i�[�ł���^
using FileSize = u32;


//�t�@�C���o�͂̃x�[�X�N���X
#pragma region FileOutBase

class FileOutBase {

	//���z�f�X�g���N�^
	#pragma region Destructor

public:
	CPOT_VI ~FileOutBase() {}

	#pragma endregion


	//�t�@�C�����J���B�t�@�C�����J���̂ɐ��������true�A���s�����false��Ԃ�
	#pragma region Open

public:
	CPOT_VI BOOL Open(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion

	
	//�t�@�C�������
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;
	
	#pragma endregion


	//�t�@�C���ɏ�������
	#pragma region Write

public:
	CPOT_VI void Write(const Buffer& aBuffer) CPOT_ZR;
	CPOT_VI void Write(const CHAR* aStr, FileSize aSize) CPOT_ZR;
	CPOT_VI void Write(const CHAR* aStr) CPOT_ZR;

	#pragma endregion

	
	//�����擾����
	#pragma region Getter

public:
	//�t�@�C�����J����Ă��邩
	CPOT_VI BOOL IsOpen() const CPOT_ZR;

	//�t�@�C���̃I�[�v���ݒ�
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion

};

#pragma endregion



//�t�@�C�����͂̃x�[�X�N���X
#pragma region FileInBase

class FileInBase {

	//���z�f�X�g���N�^
	#pragma region Destructor

public:
	CPOT_VI ~FileInBase() {}

	#pragma endregion


	//�t�@�C�����J���B�t�@�C�����J���̂ɐ��������true�A���s�����false��Ԃ�
	#pragma region Open

public:
	CPOT_VI BOOL Open(const CHAR* aFileName, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion


	//�t�@�C�������
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;

	#pragma endregion


	//�t�@�C������ǂݍ���
	#pragma region Read

public:
	CPOT_VI void Read(Buffer& aBuffer) CPOT_ZR;

	#pragma endregion


	//�����擾����
	#pragma region Getter

public:
	//�t�@�C�����J����Ă��邩
	CPOT_VI BOOL IsOpen() const CPOT_ZR;

	//�t�@�C���̃I�[�v���ݒ�
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion

};

#pragma endregion

}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/File/Standard/fileStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/File/Android/fileAndroid.h"
#endif