#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"
#include "./Pot/Usefull/singleton.h"


#include "./Pot/Render/DirectX11/Platform/shaderDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/constantBufferDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/vertexBufferDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/indexBufferDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/samplerStateDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/depthStencilStateDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/blendStateDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/rasterizerStateDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/renderTargetViewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/shaderResourceViewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/depthStencilViewDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/unorderedAccessViewDirectX11Platform.h"


namespace cpot {

namespace directX11 {

namespace platform {


template <typename ElementType, u32 cSlotMax>
class ElementManager {
public:
	ElementManager() {
		Reset();
	}

protected:
	void Reset() {
		for (s32 i = 0; i < cSlotMax; i++) {
			mElement[i] = nullptr;
		}
		mChanged = false;
	}

public:
	void Set(std::shared_ptr<ElementType> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < cSlotMax);
		if (mElement[aSlotNum] == aElement) {
			return;
		}
		mElement[aSlotNum] = aElement;
		SetChanged();
	}

	std::shared_ptr<ElementType> Get() const {
		return mElement[0];
	}
	std::shared_ptr<ElementType> Get(u32 aSlotNum) const {
		return mElement[aSlotNum];
	}

	BOOL IsChanged() const {
		return mChanged;
	}
	void SetChanged() {
		mChanged = true;
	}
	void SetNotChanged() {
		mChanged = false;
	}
	u32 SlotMaxNum() {
		return cSlotMax;
	}

protected:
	std::shared_ptr<ElementType> mElement[cSlotMax];
	BOOL mChanged;
};


#pragma region BlendState

struct BlendStateData {

	BlendStateData() {
		Reset();
	}

	FLOAT mBlendFactor[4];
	UINT mSampleMask;
	BOOL operator ==(const BlendStateData& aD) {
		if (mSampleMask != aD.mSampleMask) return false;
		for (s32 i = 0; i < 4; i++) {
			if (mBlendFactor[i] != aD.mBlendFactor[i]) return false;
		}
		return true;
	}
	BOOL operator !=(const BlendStateData& aD) {
		return !((*this) == aD);
	}
	const BlendStateData& operator =(const BlendStateData& aD) {
		mSampleMask = aD.mSampleMask;
		for (s32 i = 0; i < 4; i++) {
			mBlendFactor[i] = aD.mBlendFactor[i];
		}
		return *this;
	}
	void Reset() {
		mSampleMask = 0xffffffffUL;
		for (s32 i = 0; i < 4; i++) {
			mBlendFactor[i] = 0.0f;
		}
	}
};

class BlendStateManager : public ElementManager<BlendState, 1> {
	using super = ElementManager<BlendState, 1>;

public:
	BlendStateManager() {
		Reset();
	}

private:
	void Reset() {
		mData.Reset();
		super::Reset();
	}

public:
	void Clear() {
		Reset();
		SetChanged();
	}

	void Set(std::shared_ptr<BlendState> aElement, const BlendStateData* aData) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged();
		}

		if (aData != nullptr) {
			if (mData != *aData) {
				mData = *aData;
				SetChanged();
			}
		}
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->OMSetBlendState(Get()->GetState(), mData.mBlendFactor, mData.mSampleMask);
			SetNotChanged();
		}
	}

private:
	BlendStateData mData;
};

#pragma endregion


#pragma region DepthStencilState

struct DepthStencilStateData {
	UINT mStencilRef;
	BOOL operator ==(const DepthStencilStateData& aD) {
		if (mStencilRef != aD.mStencilRef) return false;
		return true;
	}
	BOOL operator !=(const DepthStencilStateData& aD) {
		return !((*this) == aD);
	}
	const DepthStencilStateData& operator =(const DepthStencilStateData& aD) {
		mStencilRef = aD.mStencilRef;
		return *this;
	}
	void Reset() {
		mStencilRef = 0;
	}
};

class DepthStencilStateManager : public ElementManager<DepthStencilState, 1> {
	using super = ElementManager<DepthStencilState, 1>;

public:
	DepthStencilStateManager() {
		Reset();
	}

private:
	void Reset() {
		mData.Reset();
		super::Reset();
	}

public:
	void Clear() {
		Reset();
		SetChanged();
	}


	void Set(std::shared_ptr<DepthStencilState> aElement, const DepthStencilStateData* aData) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged();
		}

		if (aData != nullptr) {
			if (mData != *aData) {
				mData = *aData;
				SetChanged();
			}
		}
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->OMSetDepthStencilState(Get()->GetState(), mData.mStencilRef);
			SetNotChanged();
		}
	}

private:
	DepthStencilStateData mData;
};

#pragma endregion


#pragma region RasterizerState

class RasterizerStateManager : public ElementManager<RasterizerState, 1> {
	using super = ElementManager<RasterizerState, 1>;

public:
	void Set(std::shared_ptr<RasterizerState> aElement) {
		super::Set(aElement, 0);
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->RSSetState(Get()->GetState());
			SetNotChanged();
		}
	}
};

#pragma endregion


#pragma region DepthStencilView

class DepthStencilViewManager : public ElementManager<DepthStencilView, 1> {
	using super = ElementManager<DepthStencilView, 1>;

public:
	void Set(std::shared_ptr<DepthStencilView> aElement) {
		super::Set(aElement, 0);
	}
};

#pragma endregion


#pragma region RenderTargetView

const u32 cRenderTargetViewSlotMax = 8;

class RenderTargetViewManager : public ElementManager<RenderTargetView, cRenderTargetViewSlotMax> {
public:
	void Set(std::shared_ptr<RenderTargetView> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] == aElement) {
			return;
		}
		mElement[aSlotNum] = aElement;
		mRenderTargetView[aSlotNum] = aElement->Get();

		SetChanged();
	}


public:
	void SetToDevice(DepthStencilViewManager& aDepthStencil) {
		if (IsChanged() || aDepthStencil.IsChanged()) {
			Device::S().GetDeviceContext()->OMSetRenderTargets(SlotMaxNum(), mRenderTargetView, aDepthStencil.Get()->Get());
			SetNotChanged();
			aDepthStencil.SetNotChanged();
		}
	}

private:
	ID3D11RenderTargetView* mRenderTargetView[cRenderTargetViewSlotMax];
};

#pragma endregion


#pragma region InputLayout

class InputLayoutManager : public ElementManager<InputLayout, 1> {
	using super = ElementManager<InputLayout, 1>;

public:
	void Set(std::shared_ptr<InputLayout> aInputLayout) {
		super::Set(aInputLayout, 0);
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetInputLayout(Get()->Get());
			SetNotChanged();
		}
	}
};

#pragma endregion



#pragma region VertexBuffer

const u32 cVertexBufferSlotMax = 8;

class VertexBufferManager : public ElementManager<VertexBuffer, cVertexBufferSlotMax> {
	using super = ElementManager<VertexBuffer, cVertexBufferSlotMax>;

public:
	void Set(std::shared_ptr<VertexBuffer> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] != aElement) {
			mElement[aSlotNum] = aElement;
			mArrayElement[aSlotNum] = aElement->GetBuffer();
			mStrides[aSlotNum] = aElement->GetVertexSize();
			mOffsets[aSlotNum] = 0;
			SetChanged();
		}
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetVertexBuffers(0, SlotMaxNum(), GetArray(), mStrides, mOffsets);
			SetNotChanged();
		}
	}

public:
	ID3D11Buffer* const* GetArray() const {
		return mArrayElement;
	}

private:
	ID3D11Buffer* mArrayElement[cVertexBufferSlotMax];
	UINT mStrides[cVertexBufferSlotMax];
	UINT mOffsets[cVertexBufferSlotMax];
};

#pragma endregion


#pragma region IndexBuffer

class IndexBufferManager : public ElementManager<IndexBuffer, 1> {
	using super = ElementManager<IndexBuffer, 1>;

public:
	void Set(std::shared_ptr<IndexBuffer> aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged();
		}
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetIndexBuffer(Get()->GetBuffer(), Get()->GetFormat(), 0);
			Device::S().GetDeviceContext()->IASetPrimitiveTopology(Get()->GetTopology());
			SetNotChanged();
		}
	}
};

#pragma endregion


#pragma region SamplerState

const u32 cSamplerStateSlotMax = 8;

class SamplerStateManager : public ElementManager<SamplerState, cSamplerStateSlotMax> {
public:
	void Set(std::shared_ptr<SamplerState> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] != aElement) {
			mElement[aSlotNum] = aElement;
			mArrayElement[aSlotNum] = aElement->GetState();
			SetChanged();
		}
	}

public:
	ID3D11SamplerState* const* GetArray() const {
		return mArrayElement;
	}

private:
	ID3D11SamplerState* mArrayElement[cSamplerStateSlotMax];
};

#pragma endregion


#pragma region ShaderResourceView

const u32 cShaderResourceViewSlotMax = 8;

class ShaderResourceViewManager : public ElementManager<ShaderResourceView, cShaderResourceViewSlotMax> {

public:
	void Set(std::shared_ptr<ShaderResourceView> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] != aElement) {
			mElement[aSlotNum] = aElement;
			mArrayElement[aSlotNum] = aElement->Get();
			SetChanged();
		}
	}

public:
	ID3D11ShaderResourceView* const* GetArray() const {
		return mArrayElement;
	}

private:
	ID3D11ShaderResourceView* mArrayElement[cShaderResourceViewSlotMax];
};

#pragma endregion


#pragma region ConstantBuffer

const u32 cConstantBufferSlotMax = 8;

class ConstantBufferManager : public ElementManager<ConstantBuffer, cConstantBufferSlotMax> {
public:
	void Set(std::shared_ptr<ConstantBuffer> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] != aElement) {
			mElement[aSlotNum] = aElement;
			mArrayElement[aSlotNum] = aElement->GetBuffer();
			SetChanged();
		}
	}

public:
	ID3D11Buffer* const* GetArray() const {
		return mArrayElement;
	}

private:
	ID3D11Buffer* mArrayElement[cConstantBufferSlotMax];
};

#pragma endregion


#pragma region UnorderedAccessView

const u32 cUnorderedAccessViewSlotMax = 16;

class UnorderedAccessViewManager : public ElementManager<UnorderedAccessView, cUnorderedAccessViewSlotMax> {
public:
	void Set(std::shared_ptr<UnorderedAccessView> aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] != aElement) {
			mElement[aSlotNum] = aElement;
			mArrayElement[aSlotNum] = aElement->Get();
			SetChanged();
		}
	}

public:
	ID3D11UnorderedAccessView* const* GetArray() const {
		return mArrayElement;
	}

private:
	ID3D11UnorderedAccessView* mArrayElement[cUnorderedAccessViewSlotMax];
};

#pragma endregion


#pragma region ViewPort

class ViewPortManager {
public:
	static constexpr u32 cSlotMax = 8;

public:
	ViewPortManager() {
		Reset();
	}

protected:
	void Reset() {
		mChanged = false;
	}

public:
	void Set(D3D11_VIEWPORT aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < cSlotMax);
		if (mElement[aSlotNum] == aElement) {
			return;
		}
		mElement[aSlotNum] = aElement;
		SetChanged();
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->RSSetViewports(cSlotMax, mElement);
			SetNotChanged();
		}
	}

	D3D11_VIEWPORT* GetArray() {
		return mElement;
	}
	D3D11_VIEWPORT Get() const {
		return mElement[0];
	}

	BOOL IsChanged() const {
		return mChanged;
	}
	void SetChanged() {
		mChanged = true;
	}
	void SetNotChanged() {
		mChanged = false;
	}
	u32 SlotMaxNum() {
		return cSlotMax;
	}

protected:
	D3D11_VIEWPORT mElement[cSlotMax];
	BOOL mChanged;
};

#pragma endregion


}

}

}
