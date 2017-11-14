//
//	content	:	OutBase�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./Usefull/buffer.h"

#include "./Thread/mutex.h"

namespace cpot {


//�A�E�g�̃x�[�X�N���X
#pragma region OutBase


class OutBase {

	//�o�͂��s���֐�
	#pragma region Output

	//�ϒ��e���v���[�g
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


	//�����𕶎���ɂ��āAOutputStr�ɈϏ����Ă���
public:
	void Output(const CHAR* aStr) {
		OutputStr(aStr);
	}
	void Output(s8 aVal) {
		OutputStr(ToString::Do((s32)aVal));
	}
	void Output(u8 aVal) {
		OutputStr(ToString::Do((u32)aVal));
	}
	void Output(s16 aVal) {
		OutputStr(ToString::Do((s32)aVal));
	}
	void Output(u16 aVal) {
		OutputStr(ToString::Do((u32)aVal));
	}
	void Output(s32 aVal) {
		OutputStr(ToString::Do(aVal));
	}
	void Output(u32 aVal) {
		OutputStr(ToString::Do(aVal));
	}
	void Output(s64 aVal) {
		OutputStr(ToString::Do(aVal));
	}
	void Output(u64 aVal) {
		OutputStr(ToString::Do(aVal));
	}
	void Output(f32 aVal) {
		OutputStr(ToString::Do(aVal));
	}
	void Output(f64 aVal) {
		OutputStr(ToString::Do(aVal));
	}
	template<u32 aSize>
	void Output(const String<aSize>& aVal) {
		OutputStr(aVal.Get());
	}
	void Output(const Buffer& aBuffer) {
		OutputByte(aBuffer);
	}

	#pragma endregion


	//�h����ŃI�[�o�[���C�h�����
	#pragma region Virtual

public:
	virtual ~OutBase() {}	//���z�f�X�g���N�^

protected:
	virtual void OutputStr(const CHAR* aStr) = 0;	//��������o�́B�K�{
	virtual void OutputByte(const Buffer& aBuffer) {}	//�o�C�g����o�́B�C��

	#pragma endregion
};


#pragma endregion



//�����o�͂��Ȃ��k���I�u�W�F�N�g
#pragma region OutNull

class OutNull : public OutBase {
private:
	void OutputStr(const CHAR* aStr) override {}

public:
	static OutNull& S() {
		static OutNull s;
		return s;
	}
};

#pragma endregion



//������Output�N���X�ɏo�͂���Log
#pragma region Log

class Log : public OutBase {

	//	TODO	�v���O�����̂ǂ�����ł��Ă΂��̂ŁA�}���`�X���b�h�ɑΉ�����

	//���������s��
	#pragma region Init

public:
	Log() {
		Reset();
	}

	void Reset() {
		//�f�t�H���g�ł́A�k���o��
		mOut = &(OutNull::S());
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
	void Set(OutBase* aOut) {
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
		MutexLocker m(mMutex);
		mOut->Output(aStr);
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	OutBase* mOut;
	Mutex mMutex;

	#pragma endregion
};



#pragma endregion



//Log���o���Ƃ��ɕ֗��ȃ}�N��
#pragma region CPOT_LOG

//�\�[�X�R�[�h�̒��̒萔�����񂪁A�n���ɂȂ�Ȃ��������ʂɂȂ�C������̂ŁA
//���̃}�N�����g���Ə������Ƃ��ɒ萔�����񂪃R�[�h�Ɏc��Ȃ�

#ifdef CPOT_VALID_LOG
#define CPOT_LOG(...) \
	Log::S().Output(__VA_ARGS__, "\n");
#define CPOT_LOG_NO_ENDL(...) \
	Log::S().Output(__VA_ARGS__);
#else
#define CPOT_LOG(...)
#define CPOT_LOG_NO_ENDL(...)
#endif

#pragma endregion


}