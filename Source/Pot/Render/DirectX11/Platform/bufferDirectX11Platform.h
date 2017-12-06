#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {

class Buffer {

	//������
	#pragma region Init

protected:
	Buffer() {
		Clear();
	}
	~Buffer() {
		Release();
	}

	Buffer(const Buffer&) = delete;
	const Buffer& operator =(const Buffer&) = delete;

protected:
	void Clear() {
		mBuffer = nullptr;
	}

	#pragma endregion


	//���[�h
	#pragma region Load

protected:
	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc) {
		return Load(aBufferDesc, nullptr);
	}
	BOOL Load(const D3D11_BUFFER_DESC& aBufferDesc, const void* aInitData) {
		if (IsLoaded()) {
			Release();
		}

		D3D11_SUBRESOURCE_DATA* lUseData = nullptr;
		D3D11_SUBRESOURCE_DATA lData;

		if (aInitData) {
			lData.pSysMem = aInitData;
			lData.SysMemPitch = 0;
			lData.SysMemSlicePitch = 0;
			lUseData = &lData;
		}

		HRESULT hr;
		hr = Device::S().GetDevice()->CreateBuffer(&aBufferDesc, lUseData, &mBuffer);

		if (FAILED(hr)) {
			Log::S().Output("CreateError : BufferDirectX11.Load");
			return false;
		}

		mSize = aBufferDesc.ByteWidth;
		return true;
	}

	static D3D11_BUFFER_DESC CreateBufferDesc(D3D11_USAGE aUsage, UINT aBindFlags, UINT aCPUAccessFlags, u32 aSize) {
		D3D11_BUFFER_DESC lBufferDesc;
		lBufferDesc.Usage = aUsage;
		lBufferDesc.BindFlags = aBindFlags;
		lBufferDesc.CPUAccessFlags = aCPUAccessFlags;
		lBufferDesc.ByteWidth = aSize;
		lBufferDesc.StructureByteStride = 0;
		lBufferDesc.MiscFlags = 0;
		return lBufferDesc;
	}

	#pragma endregion


	//�����[�X
	#pragma region Release

public:
	void Release() {
		//�ǂݍ��܂�Ă��Ȃ��Ȃ�A������������Ȃ�
		if (!IsLoaded()) {
			return;
		}
		CPOT_SAFE_RELEASE(mBuffer);
		Clear();
	}

	#pragma endregion


	//�o�b�t�@�ւ̏�������
	#pragma region Write

protected:
	BOOL Write(const void* aBuffer, u32 aSize) {

		//�}�b�v����
		void* lToBuffer = Map(D3D11_MAP_WRITE_DISCARD);

		//�������s������
		if (!lToBuffer) {
			return false;
		}

		//�������ރT�C�Y�̌v�Z
		u32 lWriteSize = Min(aSize, GetSize());

		// �f�[�^��������
		CopyMemory(lToBuffer, aBuffer, lWriteSize);

		//�A���}�b�v
		Unmap();

		return true;	//�������ݐ���
	}
	template <typename T>
	BOOL Write(T& aData) {
		return Write(&aData, sizeof(T));
	}

	#pragma endregion


	//�o�b�t�@����̓ǂݍ���
	#pragma region Read

protected:
	BOOL Read(void* aBuffer, u32 aSize) {
		//�}�b�v����
		void* lFromBuffer = Map(D3D11_MAP_READ);

		//�������s������
		if (!lFromBuffer) {
			return false;
		}

		//�ǂݍ��ރT�C�Y�̌v�Z
		u32 lReadSize = Min(aSize, GetSize());

		// �f�[�^�ǂݍ���
		CopyMemory(aBuffer, lFromBuffer, lReadSize);

		//�A���}�b�v
		Unmap();

		return true;	//�ǂݍ��ݐ���
	}
	template <typename T>
	BOOL Read(T& aData) {
		return Read(&aData, sizeof(T));
	}

	#pragma endregion


	//�o�b�t�@�̃}�b�v
	#pragma region Map

protected:
	void* Map(D3D11_MAP aMapType) {
		D3D11_MAPPED_SUBRESOURCE lMappedResource;
		BOOL lResult = Map(lMappedResource, aMapType);

		//�}�b�v�Ɏ��s������
		if (!lResult) {
			return nullptr;
		}
		return lMappedResource.pData;
	}
	BOOL Map(D3D11_MAPPED_SUBRESOURCE& aMappedResource, D3D11_MAP aMapType) {
		HRESULT hr;

		//�}�b�v�擾

		hr = Device::S().GetDeviceContext()->Map(
			mBuffer,           // �}�b�v���郊�\�[�X
			0,                       // �T�u���\�[�X�̃C���f�b�N�X�ԍ�
			aMapType, // �������݃A�N�Z�X
			0,                       //
			&aMappedResource);        // �f�[�^�̏������ݐ�|�C���^
		if (FAILED(hr)) {
			Log::S().Output("BufferDirectX11.Map : MapFailed");
			return false;
		}
		return true;
	}
	void Unmap() {
		Device::S().GetDeviceContext()->Unmap(mBuffer, 0);
	}

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	BOOL IsLoaded() const {
		return mBuffer != nullptr;
	}

	ID3D11Buffer* GetBuffer() const {
		return mBuffer;
	}

	u32 GetSize() const {
		return mSize;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	ID3D11Buffer* mBuffer;
	u32 mSize;

	#pragma endregion
};


}

}

}
