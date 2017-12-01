//
//	content	:	DirectX11‚Å‚ÌSampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/vertexBuffer.h"
#include "./Pot/Render/DirectX11/Platform/vertexBufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

class VertexBuffer : public VertexBufferBase {

public:
	VertexBuffer() {
		mVertexBuffer.reset(new platform::VertexBuffer);
	}

	#pragma region Load

public:
	BOOL Load(u32 aVertexSize, u32 aVertexNum, void* aInitData, BOOL aCPUWritable) CPOT_OR {
		return mVertexBuffer->Load(D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, aVertexSize, aVertexNum, aInitData);
	}
	BOOL Load(u32 aVertexSize, u32 aVertexNum, void* aInitData) CPOT_OR {
		return mVertexBuffer->Load(aVertexSize, aVertexNum, aInitData);
	}
	

	#pragma endregion


	#pragma region Write

public:
	BOOL Write(void* aData) CPOT_OR {
		return mVertexBuffer->Write(aData);
	}
	BOOL Write(void* aData, u32 aSize) CPOT_OR {
		return mVertexBuffer->Write(aData, aSize);
	}

	#pragma endregion


	//Žæ“¾
	#pragma region Getter

public:
	u32 GetVertexSize() const CPOT_OR {
		return mVertexBuffer->GetVertexSize();
	}
	u32 GetVertexNum() const CPOT_OR {
		return mVertexBuffer->GetVertexNum();
	}

	#pragma endregion


public:
	void Release() CPOT_OR {
		mVertexBuffer->Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mVertexBuffer->IsLoaded();
	}

public:
	std::shared_ptr<platform::VertexBuffer> mVertexBuffer;

};

}

using VertexBuffer = directX11::VertexBuffer;

}