//
//	content	:	DirectX11でのSampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/constantBuffer.h"
#include "./Pot/Render/DirectX11/Platform/constantBufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class ConstantBuffer : public ConstantBufferBase {

public:
	ConstantBuffer() {
		mConstantBuffer.reset(new platform::ConstantBuffer);
	}

	#pragma region Load

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//将来は、名前からデータを検索して、ロードできるようにしたい
	};
	template<typename T>
	BOOL Load(T* aInitData) {
		return mConstantBuffer->Load(platform::ConstantBuffer::CreateBufferDesc(sizeof(T)), aInitData);
	}

	BOOL Load(void* aInitData, u32 aSize) CPOT_OR {
		return mConstantBuffer->Load(platform::ConstantBuffer::CreateBufferDesc(aSize), aInitData);
	}

	#pragma endregion


	#pragma region Write

public:
	BOOL Write() CPOT_OR {
		return mConstantBuffer->Write();
	}
	BOOL Write(const void* aBuffer) CPOT_OR {
		return mConstantBuffer->Write(aBuffer);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	template<typename T>
	T* GetCPUBuffer() {
		return mConstantBuffer->GetCPUBuffer<T>();
	}

	#pragma endregion


	//設定
	#pragma region Setter

public:
	void SetCPUBuffer(void* aCPUBuffer) CPOT_OR {
		mConstantBuffer->SetCPUBuffer(aCPUBuffer);
	}

	#pragma endregion


public:
	void Release() CPOT_OR {
		mConstantBuffer->Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mConstantBuffer->IsLoaded();
	}

public:
	std::shared_ptr<platform::ConstantBuffer> mConstantBuffer;

};

}

using ConstantBuffer = directX11::ConstantBuffer;

}