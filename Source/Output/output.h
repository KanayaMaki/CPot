//	�t�@�C����	:	Output/output.h
//	���		:	ꎓ��F�I
//	�쐬����	:	2017/11/09
//	�X�V����	:	2017/11/09
//	���e		:	Output�N���X�̎���

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./Usefull/buffer.h"

namespace cpot {


//�A�E�g�v�b�g�̃x�[�X�N���X
#pragma region OutputBase


class OutputBase {

public:
	virtual ~OutputBase() {}	//���z�f�X�g���N�^

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



//�����o�͂��Ȃ��k���I�u�W�F�N�g
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



//������Output�N���X�ɏo�͂���Log
#pragma region Log

class Log : public OutputBase {

	//	TODO	�v���O�����̂ǂ�����ł��Ă΂��̂ŁA�}���`�X���b�h�ɑΉ�����

	//���������s��
	#pragma region Init

public:
	Log() {
		Reset();
	}

	void Reset() {
		//�f�t�H���g�ł́A�k���o��
		mOut = &(OutputNull::S());
	}

	#pragma endregion


	//�I���������s��
	#pragma region Final

public:
	~Log() override {}

	#pragma endregion



	//�ݒ�
	#pragma region Setter

public:
	//�o�͐��ݒ肷��
	void Set(OutputBase* aOut) {
		mOut = aOut;
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	//�O���[�o���I�Ɏg�p�ł���A���O�̃C���X�^���X���擾
	static Log& S() {
		static Log s;
		return s;
	}

	#pragma endregion


	//����
	#pragma region Operate

private:
	//��������o�͂���BOutBase�ɃI�[�o�[���C�h�ŌĂ΂��
	void OutputStr(const CHAR* aStr) override {
		//MutexLocker m(mMutex);
		mOut->Output(aStr);
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	OutputBase* mOut;
	//Mutex mMutex;

	#pragma endregion
};



#pragma endregion



//Log���o���Ƃ��ɕ֗��ȃ}�N��
#pragma region CPOT_LOG

//�\�[�X�R�[�h�̒��̒萔�����񂪁A�n���ɂȂ�Ȃ��������ʂɂȂ�C������̂ŁA
//���̃}�N�����g���Ə������Ƃ��ɒ萔�����񂪃R�[�h�Ɏc��Ȃ�

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