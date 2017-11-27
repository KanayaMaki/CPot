#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/elementManagerDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/shaderDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/shaderResourceViewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/samplerStateDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/constantBufferDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/unorderedAccessViewDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


template <typename ShaderType>
class ShaderManager {
public:
	ShaderManager() {

	}

public:
	void SetShader(std::shared_ptr<ShaderType> aShader) {
		mShader.Set(aShader, 0);
	}
	void SetSampler(std::shared_ptr<SamplerState> aSampler, u32 aSlotNum) {
		mSampler.Set(aSampler, aSlotNum);
	}
	void SetShaderResource(std::shared_ptr<ShaderResourceView> aShaderResource, u32 aSlotNum) {
		mShaderResource.Set(aShaderResource, aSlotNum);
	}
	void SetConstantBuffer(std::shared_ptr<ConstantBuffer> aBuffer, u32 aSlotNum) {
		mConstantBuffer.Set(aBuffer, aSlotNum);
	}
	std::shared_ptr<ShaderType> GetShader() {
		return mShader.Get();
	}
	std::shared_ptr<SamplerState> GetSampler(u32 aSlotNum) {
		return mSampler.Get(aSlotNum);
	}
	std::shared_ptr<ShaderResourceView> GetShaderResource(u32 aSlotNum) {
		return mShaderResource.Get(aSlotNum);
	}
	std::shared_ptr<ConstantBuffer> GetConstantBuffer(u32 aSlotNum) {
		return mConstantBuffer.Get(aSlotNum);
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
	Device::S().GetDeviceContext()->VSSetShader(mShader.Get()->GetShader(), nullptr, 0);
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

using GeometryShaderManager = ShaderManager<GeometryShader>;

template <>
inline void GeometryShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->GSSetShader(mShader.Get()->GetShader(), nullptr, 0);
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
using PixelShaderManager = ShaderManager<PixelShader>;

template <>
inline void PixelShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->PSSetShader(mShader.Get()->GetShader(), nullptr, 0);
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

using DomainShaderManager = ShaderManager<DomainShader>;

template <>
inline void DomainShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->DSSetShader(mShader.Get()->GetShader(), nullptr, 0);
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

using HullShaderManager = ShaderManager<HullShader>;

template <>
inline void HullShaderManager::SetShaderToDevice() {
	Device::S().GetDeviceContext()->HSSetShader(mShader.Get()->GetShader(), nullptr, 0);
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

using ComputeShaderManager = ShaderManager<ComputeShader>;

template <>
class ShaderManager<ComputeShader> {
public:
	ShaderManager() {

	}

public:
	void SetShader(std::shared_ptr<ComputeShader> aShader) {
		mShader.Set(aShader, 0);
	}
	void SetSampler(std::shared_ptr<SamplerState> aSampler, u32 aSlotNum) {
		mSampler.Set(aSampler, aSlotNum);
	}
	void SetShaderResource(std::shared_ptr<ShaderResourceView> aShaderResource, u32 aSlotNum) {
		mShaderResource.Set(aShaderResource, aSlotNum);
	}
	void SetConstantBuffer(std::shared_ptr<ConstantBuffer> aBuffer, u32 aSlotNum) {
		mConstantBuffer.Set(aBuffer, aSlotNum);
	}
	void SetUnorderedAccessView(std::shared_ptr<UnorderedAccessView> aUnorderedAccessView, u32 aSlotNum) {
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
		Device::S().GetDeviceContext()->CSSetShader(mShader.Get()->GetShader(), nullptr, 0);
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
	ElementManager<ComputeShader, 1> mShader;
	SamplerStateManager mSampler;
	ShaderResourceViewManager mShaderResource;
	ConstantBufferManager mConstantBuffer;
	UnorderedAccessViewManager mUnorderedAccessView;
};

#pragma endregion




}

}

}
