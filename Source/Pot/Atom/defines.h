//
//	content	:	��{�ƂȂ�define���`
//	author	:	SaitoYoshiki
//


#pragma once

#include <cassert>


namespace cpot {


#pragma region OS�̎�ނ��`

#ifdef _WINDOWS
#define CPOT_ON_WINDOWS
#elif defined _CONSOLE
#define CPOT_ON_WINDOWS
#elif defined CPOT_ANDROID
#define CPOT_ON_ANDROID
#endif

#pragma endregion



#pragma region CPU�̃A�[�L�e�N�`�����`

#ifdef CPOT_ON_WINDOWS

#ifdef WIN32
#define CPOT_ON_32BIT
#else
#define CPOT_ON_64BIT
#endif

#elif defined CPOT_ON_ANDROID

#ifdef CPOT_32BIT
#define CPOT_ON_32BIT
#else
#define CPOT_ON_64BIT
#endif

#endif

#pragma endregion



#pragma region �g�p����O���t�B�b�NAPI���`

#ifdef CPOT_DIRECTX9
#define CPOT_ON_DIRECTX9
#endif
#ifdef CPOT_DIRECTX11
#define CPOT_ON_DIRECTX11
#endif
#ifdef CPOT_OPENGL
#define CPOT_ON_OPENGL
#endif

#pragma endregion



#pragma region �r���h�̍\�����`

#ifdef NDEBUG

#ifdef CPOT_MASTER
#define CPOT_ON_MASTER
#else
#define CPOT_ON_RELEASE
#endif

#else

#define CPOT_ON_DEBUG

#endif

#pragma endregion



#pragma region �r���h�̍\���ɂ���ėl�X�Ȑݒ���`

//�f�o�b�O�r���h��
#ifdef CPOT_ON_DEBUG

#define CPOT_VALID_ASSERT	//�A�T�[�g��L����
#define CPOT_VALID_ERROR	//�G���[��L����
#define CPOT_VALID_LOG	//���O���g�p����
#define CPOT_VALID_VI	//�o�[�`�������g�p����

#define CPOT_VALID_HASHSTRING_LEFT	//HashString�̕�������c��

//�����[�X�r���h��
#elif defined CPOT_ON_RELEASE

#define CPOT_VALID_ASSERT
#define CPOT_VALID_ERROR
#define CPOT_VALID_LOG


//�}�X�^�[�r���h��
#elif defined CPOT_ON_MASTER

#endif

#pragma endregion



#pragma region �A�T�[�g�ƃG���[��L���ɂ��邩�̐ݒ�


//�A�T�[�g�̐ݒ�
#ifdef CPOT_VALID_ASSERT
#define CPOT_ASSERT(expr) assert(expr)	//�L��

#else
#define CPOT_ASSERT(expr)	//����
#endif


//�G���[�̐ݒ�
#ifdef CPOT_VALID_ERROR
#define CPOT_ERROR(expr) assert(0 && expr)	//�L��
#else
#define CPOT_ERROR(expr)	//����
#endif


#pragma endregion



#pragma region	�}�X�^�[�ȊO�̎��ɂ����Ă΂�鎮�̐ݒ�

#ifndef CPOT_ON_MASTER
#define CPOT_DEBUG_EXP(expr) (expr)	//�L��

#else
#define CPOT_DEBUG_EXP(expr)	//����
#endif

#pragma endregion



#pragma region �o�[�`������L���ɂ��邩�̐ݒ�

//����define�́A�C���^�[�t�F�[�X�����낦�邽�߂ɊJ������virtual��override�ŊJ�����āAMaster�ł͌������̂��߂ɉ��z�֐��ɂ��Ȃ����Ɏg�p����

//�L���ɂ���
#ifdef CPOT_VALID_VI
#define CPOT_VI virtual
#define CPOT_ZR =0
#define CPOT_OR override

//����
#else
#define CPOT_VI
#define CPOT_ZR
#define CPOT_OR
#endif


#pragma endregion



}