//
//	�t�@�C���̓��o�͂̃C���^�[�t�F�[�X�ƂȂ�N���X
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./Usefull/buffer.h"

namespace cpot {


//�A�E�g�v�b�g�̃x�[�X�N���X
#pragma region FileBase


//�t�@�C���̍ő�T�C�Y���i�[�ł���^
using FileSize = u32;


class FileBase {

	//�t�@�C�����J���B�t�@�C�����J���̂ɐ��������true�A���s�����false��Ԃ�
	#pragma region Open

public:
	CPOT_VI BOOL OpenToWrite(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_ZR;
	CPOT_VI BOOL OpenToRead(const CHAR* aFileName, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion

	
	//�t�@�C�������
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;
	
	#pragma endregion


	//�t�@�C������ǂݍ��ށB�ǂݍ��ݐݒ��Open���Ă��Ȃ��Ǝ��s����
	//���݂�Position����ǂݍ���
	//�ǂݍ��񂾃T�C�Y��Ԃ�
	#pragma region Read

public:
	CPOT_VI FileSize Read(BYTE* aBuffer, FileSize aSize) CPOT_ZR;
	CPOT_VI FileSize Read(Buffer& aBuffer) CPOT_ZR;
	CPOT_VI FileSize Read(Buffer& aBuffer, FileSize aSize) CPOT_ZR;
	
	#pragma endregion


	//�t�@�C���ɏ������ށB�������ݐݒ��Open���Ă��Ȃ��Ǝ��s����
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

	//�t�@�C���̑傫��
	CPOT_VI FileSize GetSize() const CPOT_ZR;

	//�t�@�C���̌��݈ʒu
	CPOT_VI FileSize GetPosition() const CPOT_ZR;

	//�t�@�C���̃I�[�v���ݒ�
	CPOT_VI BOOL IsRead() const CPOT_ZR;
	CPOT_VI BOOL IsWrite() const CPOT_ZR;
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion


	//�ݒ肷��
	#pragma region Setter

public:
	//�t�@�C���̌��݈ʒu
	CPOT_VI void SetPosition(FileSize aPosition) CPOT_ZR;

	#pragma endregion


	//�I�[�v���t���O
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