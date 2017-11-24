#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/elementManagerDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/shaderDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/shaderResourceViewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/samplerStateDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/constantBufferDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


template <typename ShaderType>
class ShaderManager {
public:
	ShaderManager() {

	}

public:
	void SetShader(ShaderType* aShader) {
		mShader.Set(aShader, 0);
	}
	void SetSampler(ID3D11SamplerState* aSampler, u32 aSlotNum) {
		mSampler.Set(aSampler, aSlotNum);
	}
	void SetShaderResource(ShaderResourceView* aShaderResource, u32 aSlotNum) {
		mShaderResource.Set(aShaderResource, aSlotNum);
	}
	void SetConstantBuffer(ID3D11Buffer* aBuffer, u32 aSlotNum) {
		mConstantBuffer.Set(aBuffer, aSlotNum);
	}
	ShaderType* GetShader() {
		return mShader.Get();
	}
	ID3D11SamplerState* GetSampler(u32 aSlotNum) {
		return mSampler.Get(aSlotNum);
	}
	ID3D11ShaderResourceView* GetShaderResource(u32 aSlotNum) {
		return mShaderResource.Get(aSlotNum);
	}
	ID3D11Buffer* GetConstantBuffer(u32 aSlotNum) {
		return mConstantBuffer.Get(aSlotNum);
	}

	void SetConstantBufferChanged() {
		mConstantBuffer.SetChanged();
	}

	void SetToDevice() {
		if (mShader.IsChanged()) {
			SetShaderToDevice();
			mShader.SetNotChanged();
		}
		if (mSampler.IsChanged()) {
			SetSamplerToDevice();
			mSampler.SetNotChanged();
		}
		if (mShaderResource.IsChanged()) {
			SetShaderResourceToDevice();
			mShaderResource.SetNotChanged();
		}
		if (mConstantBuffer.IsChanged()) {
			SetConstantBufferToDevice();
			mConstantBuffer.SetNotChanged();
		}
	}

private:
	void SetShaderToDevice();
	void SetSamplerToDevice();
	void SetShaderResourceToDevice();
	void SetConstantBufferToDevice();

private:
	ElementManager<ShaderType, 1> mShader;
	SamplerStateManager mSampler;
	ShaderResourceViewManager mShaderResource;
	ConstantBufferManager mConstantBuffer;
};


#pragma region VertexShaderManager

using VertexShaderManager = ShaderManager<VertexShader>;

template <>
inline void VertexShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->VSSetShader(*(mShader.GetArray()), nullptr, 0);
}
template <>
inline void VertexShaderManager::SetSamplerToDevice() {
	Device::S().GetDeviceContext()->VSSetSamplers(0, mSampler.SlotMaxNum(), mSampler.GetArray());
}
template <>
inline void VertexShaderManager::SetShaderResourceToDevice() {
	Device::S().GetDeviceContext()->VSSetShaderResources(0, mShaderResource.SlotMaxNum(), mShaderResource.GetArray());
}
template <>
inline void VertexShaderManager::SetConstantBufferToDevice() {
	Device::S().GetDeviceContext()->VSSetConstantBuffers(0, mConstantBuffer.SlotMaxNum(), mConstantBuffer.GetArray());
}

#pragma endregion


#pragma region GeometryShaderManager

using GeometryShaderManager = ShaderManager<ID3D11GeometryShader>;

template <>
inline void GeometryShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->GSSetShader(*(mShader.GetArray()), nullptr, 0);
}
template <>
inline void GeometryShaderManager::SetSamplerToDevice() {
	Device::S().GetDeviceContext()->GSSetSamplers(0, mSampler.SlotMaxNum(), mSampler.GetArray());
}
template <>
inline void GeometryShaderManager::SetShaderResourceToDevice() {
	Device::S().GetDeviceContext()->GSSetShaderResources(0, mShaderResource.SlotMaxNum(), mShaderResource.GetArray());
}
template <>
inline void GeometryShaderManager::SetConstantBufferToDevice() {
	Device::S().GetDeviceContext()->GSSetConstantBuffers(0, mConstantBuffer.SlotMaxNum(), mConstantBuffer.GetArray());
}

#pragma endregion


#pragma region PixelShaderManager
using PixelShaderManager = ShaderManager<ID3D11PixelShader>;

template <>
inline void PixelShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->PSSetShader(*(mShader.GetArray()), nullptr, 0);
}
template <>
inline void PixelShaderManager::SetSamplerToDevice() {
	Device::S().GetDeviceContext()->PSSetSamplers(0, mSampler.SlotMaxNum(), mSampler.GetArray());
}
template <>
inline void PixelShaderManager::SetShaderResourceToDevice() {
	Device::S().GetDeviceContext()->PSSetShaderResources(0, mShaderResource.SlotMaxNum(), mShaderResource.GetArray());
}
template <>
inline void PixelShaderManager::SetConstantBufferToDevice() {
	Device::S().GetDeviceContext()->PSSetConstantBuffers(0, mConstantBuffer.SlotMaxNum(), mConstantBuffer.GetArray());
}

#pragma endregion


#pragma region DomainShaderManager

using DomainShaderManager = ShaderManager<ID3D11DomainShader>;

template <>
inline void DomainShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->DSSetShader(*(mShader.GetArray()), nullptr, 0);
}
template <>
inline void DomainShaderManager::SetSamplerToDevice() {
	Device::S().GetDeviceContext()->DSSetSamplers(0, mSampler.SlotMaxNum(), mSampler.GetArray());
}
template <>
inline void DomainShaderManager::SetShaderResourceToDevice() {
	Device::S().GetDeviceContext()->DSSetShaderResources(0, mShaderResource.SlotMaxNum(), mShaderResource.GetArray());
}
template <>
inline void DomainShaderManager::SetConstantBufferToDevice() {
	Device::S().GetDeviceContext()->DSSetConstantBuffers(0, mConstantBuffer.SlotMaxNum(), mConstantBuffer.GetArray());
}

#pragma endregion


#pragma region HullShaderManager

using HullShaderManager = ShaderManager<ID3D11HullShader>;

template <>
inline void HullShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->HSSetShader(*(mShader.GetArray()), nullptr, 0);
}
template <>
inline void HullShaderManager::SetSamplerToDevice() {
	Device::S().GetDeviceContext()->HSSetSamplers(0, mSampler.SlotMaxNum(), mSampler.GetArray());
}
template <>
inline void HullShaderManager::SetShaderResourceToDevice() {
	Device::S().GetDeviceContext()->HSSetShaderResources(0, mShaderResource.SlotMaxNum(), mShaderResource.GetArray());
}
template <>
inline void HullShaderManager::SetConstantBufferToDevice() {
	Device::S().GetDeviceContext()->HSSetConstantBuffers(0, mConstantBuffer.SlotMaxNum(), mConstantBuffer.GetArray());
}

#pragma endregion


#pragma region ComputeShaderManager

using ComputeShaderManager = ShaderManager<ID3D11ComputeShader>;

template <>
class ShaderManager<ID3D11ComputeShader> {
public:
	ShaderManager() {

	}

public:
	void SetShader(ID3D11ComputeShader* aShader) {
		mShader.Set(aShader, 0);
	}
	void SetSampler(ID3D11SamplerState* aSampler, u32 aSlotNum) {
		mSampler.Set(aSampler, aSlotNum);
	}
	void SetShaderResource(ID3D11ShaderResourceView* aShaderResource, u32 aSlotNum) {
		mShaderResource.Set(aShaderResource, aSlotNum);
	}
	void SetConstantBuffer(ID3D11Buffer* aBuffer, u32 aSlotNum) {
		mConstantBuffer.Set(aBuffer, aSlotNum);
	}
	void SetUnorderedAccessView(ID3D11UnorderedAccessView* aUnorderedAccessView, u32 aSlotNum) {
		mUnorderedAccessView.Set(aUnorderedAccessView, aSlotNum);
	}

	void SetToDevice() {
		if (mShader.IsChanged()) {
			SetShaderToDevice();
			mShader.SetNotChanged();
		}
		if (mSampler.IsChanged()) {
			SetSamplerToDevice();
			mSampler.SetNotChanged();
		}
		if (mShaderResource.IsChanged()) {
			SetShaderResourceToDevice();
			mShaderResource.SetNotChanged();
		}
		if (mConstantBuffer.IsChanged()) {
			SetConstantBufferToDevice();
			mConstantBuffer.SetNotChanged();
		}
		if (mUnorderedAccessView.IsChanged()) {
			SetUnorderedAccessViewToDevice();
			mUnorderedAccessView.SetNotChanged();
		}
	}

private:
	void SetShaderToDevice() {
		Device::S().GetDeviceContext()->CSSetShader(*(mShader.GetArray()), nullptr, 0);
	}
	void SetSamplerToDevice() {
		Device::S().GetDeviceContext()->CSSetSamplers(0, mSampler.SlotMaxNum(), mSampler.GetArray());
	}
	void SetShaderResourceToDevice() {
		Device::S().GetDeviceContext()->CSSetShaderResources(0, mShaderResource.SlotMaxNum(), mShaderResource.GetArray());
	}
	void SetConstantBufferToDevice() {
		Device::S().GetDeviceContext()->CSSetConstantBuffers(0, mConstantBuffer.SlotMaxNum(), mConstantBuffer.GetArray());
	}
	void SetUnorderedAccessViewToDevice() {
		Device::S().GetDeviceContext()->CSSetUnorderedAccessViews(0, mUnorderedAccessView.SlotMaxNum(), mUnorderedAccessView.GetArray(), nullptr);
	}

private:
	ElementManager<ID3D11ComputeShader, 1> mShader;
	SamplerStateManager mSampler;
	ShaderResourceViewManager mShaderResource;
	ConstantBufferManager mConstantBuffer;
	UnorderedAccessViewManager mUnorderedAccessView;
};

#pragma endregion




}

}

}
