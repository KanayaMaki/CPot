//
//	content	:	�o�b�t�@�N���X�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using BufferSize = u32;

class Buffer {
	
	//�R���X�g���N�^�Ȃ�
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
		mCapacity = 0;
		mPosition = 0;
	}

	#pragma endregion


	//�f�X�g���N�^�Ȃ�
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


	//�쐬
	#pragma region Create

	void Load(const BYTE* aBuffer, BufferSize aSize) {

		Release();

		if (aSize > 0) {
			mBuffer = new BYTE[aSize];
			CopyMem(&(mBuffer[0]), &(aBuffer[0]), aSize);
			mSize = aSize;
			mCapacity = aSize;
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
			mCapacity = aSize;
		}
	}

	#pragma endregion


	//�擾
	#pragma region Getter

	//�o�b�t�@
	BYTE* Get() const {
		return mBuffer;
	}

	//�C���f�b�N�X�A�N�Z�X
	BYTE& operator[](u32 aIndex) {
		CPOT_ASSERT(aIndex < mSize);
		return mBuffer[aIndex];
	}
	BYTE operator[](u32 aIndex) const {
		CPOT_ASSERT(aIndex < mSize);
		return mBuffer[aIndex];
	}

	//�f�[�^�̃T�C�Y
	BufferSize GetSize() const {
		return mSize;
	}

	//�o�b�t�@�̃T�C�Y
	BufferSize GetCapacity() const {
		return mCapacity;
	}

	//�o�b�t�@�̃J�[�\���̌��݈ʒu
	BufferSize GetPosition() const {
		return mPosition;
	}

	//�ǂݍ��ݍς݂��ǂ���
	BOOL IsLoaded() const {
		return mBuffer != nullptr;
	}

	#pragma endregion


	//�ݒ�
	#pragma region Setter

	//���݈ʒu��ݒ肷��
	void SetPosition(BufferSize aPosition) {
		mPosition = Clamp(aPosition, BufferSize(0), mSize - 1);
	}

	#pragma endregion
	

	//����
	#pragma region Operation

	//�o�b�t�@����f�[�^��ǂݍ���
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

	void Read(Buffer& aBuffer, BufferSize aSize) {

		if (IsLoaded() == false) {
			return;
		}
		CPOT_ASSERT(aSize >= 0);

		BufferSize lEnd = mPosition + aSize;
		if (GetSize() < lEnd) {
			lEnd = GetSize();
		}
		BufferSize lReadSize = lEnd - mPosition;

		aBuffer.Load(&mBuffer[mPosition], lReadSize);
		mPosition += lReadSize;
	}

	void Add(const BYTE* aBuffer, BufferSize aSize) {

		//�V�����o�b�t�@�̃T�C�Y�̌v�Z
		BufferSize lNewSize = mSize + aSize;
		//�V�����o�b�t�@�̍쐬
		Reserve(lNewSize);

		//�ǉ�����o�b�t�@�̃f�[�^���R�s�[
		CopyMem(&mBuffer[mSize], aBuffer, aSize);
		mSize = lNewSize;
	}
	void Add(const Buffer& aBuffer) {
		Add(aBuffer.mBuffer, aBuffer.GetSize());
	}

	void Reserve(BufferSize aCapacity) {
		
		BufferSize lNewCapacity = Max(32, mCapacity);
		
		//�o�b�t�@�T�C�Y������Ȃ��Ȃ�ꍇ
		if (mCapacity < aCapacity) {

			//�o�b�t�@�T�C�Y���v�Z����
			while (lNewCapacity < aCapacity) {
				lNewCapacity *= 2;
			}

			BYTE* lNewBuffer = new BYTE[lNewCapacity];

			//�O�̃o�b�t�@�̃f�[�^���R�s�[
			CopyMem(lNewBuffer, mBuffer, mSize);

			//���݂̃o�b�t�@���폜
			delete[] mBuffer;
			mBuffer = lNewBuffer;
			mCapacity = lNewCapacity;
		}
		//���݂̃o�b�t�@�T�C�Y�ŏ\���ȏꍇ
		else {

		}
	}

	#pragma endregion


	//�f�[�^
	#pragma region Data

public:
	template <typename T>
	void LoadData(const T& aData) {
		Load((const BYTE*)(&aData), sizeof(T));
	}

	template <typename T>
	T* GetData() {
		return (T*)(mBuffer);
	}

	#pragma endregion



	//�t�B�[���h
	#pragma region Field

private:
	BYTE* mBuffer;
	BufferSize mCapacity;
	BufferSize mSize;
	BufferSize mPosition;

	#pragma endregion
};


}