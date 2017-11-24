#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Render/DirectX11/Platform/elementManagerDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/shaderManagerDirectX11Platform.h"


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
	void Set(ElementType* aElement, u32 aSlotNum) {
		CYC_POT_ASSERT(aSlotNum < cSlotMax);
		if (mElement[aSlotNum] == aElement) {
			return;
		}
		mElement[aSlotNum] = aElement;
		SetChanged();
	}

	ElementType** GetArray() {
		return mElement;
	}
	ElementType* Get() const {
		return mElement[0];
	}
	ElementType* Get(u32 aSlotNum) const {
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
	ElementType* mElement[cSlotMax];
	BOOL mChanged;
};


#pragma region BlendState

struct BlendStateData {

	BlendStateData() {}

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

	void Set(ID3D11BlendState* aElement, const BlendStateData* aData) {
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
			Device::S().GetDeviceContext()->OMSetBlendState(Get(), mData.mBlendFactor, mData.mSampleMask);
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

class DepthStencilStateManager : public ElementManager<ID3D11DepthStencilState, 1> {
	using super = ElementManager<ID3D11DepthStencilState, 1>;

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


	void Set(ID3D11DepthStencilState* aElement, const DepthStencilStateData* aData) {
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
			Device::S().GetDeviceContext()->OMSetDepthStencilState(Get(), mData.mStencilRef);
			SetNotChanged();
		}
	}

private:
	DepthStencilStateData mData;
};

#pragma endregion


#pragma region RasterizerState

class RasterizerStateManager : public ElementManager<ID3D11RasterizerState, 1> {
public:
	void Set(ID3D11RasterizerState* aRasterizer) {
		ElementManager<ID3D11RasterizerState, 1>::Set(aRasterizer, 0);
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->RSSetState(Get());
			SetNotChanged();
		}
	}
};

#pragma endregion


#pragma region DepthStencilView

class DepthStencilViewManager : public ElementManager<ID3D11DepthStencilView, 1> {
public:
	void Set(ID3D11DepthStencilView* aDepthStencil) {
		ElementManager<ID3D11DepthStencilView, 1>::Set(aDepthStencil, 0);
	}
};

#pragma endregion


#pragma region RenderTargetView

class RenderTargetViewManager : public ElementManager<ID3D11RenderTargetView, 1> {
public:
	void SetToDevice(DepthStencilViewManager& aDepthStencil) {
		if (IsChanged() || aDepthStencil.IsChanged()) {
			Device::S().GetDeviceContext()->OMSetRenderTargets(SlotMaxNum(), GetArray(), aDepthStencil.Get());
			SetNotChanged();
			aDepthStencil.SetNotChanged();
		}
	}
};

#pragma endregion


#pragma region InputLayout

class InputLayoutManager : public ElementManager<ID3D11InputLayout, 1> {
public:
	void Set(ID3D11InputLayout* aInputLayout) {
		ElementManager<ID3D11InputLayout, 1>::Set(aInputLayout, 0);
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetInputLayout(Get());
			SetNotChanged();
		}
	}
};

#pragma endregion



#pragma region VertexBuffer

const u32 cVertexBufferSlotMax = 8;

class VertexBufferManager : public ElementManager<ID3D11Buffer, cVertexBufferSlotMax> {
	using super = ElementManager<ID3D11Buffer, cVertexBufferSlotMax>;
public:
	VertexBufferManager() {
		Reset();
	}

private:
	void Reset() {
		ResetData();
		super::Reset();
	}

public:
	void Clear() {
		Reset();
		SetChanged();
	}
public:
	void Set(ID3D11Buffer* aElement, u32 aSlotNum, u32 aOffset, u32 aStride) {
		CYC_POT_ASSERT(aSlotNum < SlotMaxNum());
		if (mElement[aSlotNum] != aElement) {
			mElement[aSlotNum] = aElement;
			SetChanged();
		}

		if (mOffsets[aSlotNum] != aOffset) {
			mOffsets[aSlotNum] = aOffset;
			SetChanged();
		}

		if (mStrides[aSlotNum] != aStride) {
			mStrides[aSlotNum] = aStride;
			SetChanged();
		}
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetVertexBuffers(0, SlotMaxNum(), mElement, mStrides, mOffsets);
			SetNotChanged();
		}
	}

private:
	UINT mOffsets[cVertexBufferSlotMax];
	UINT mStrides[cVertexBufferSlotMax];

	void ResetData() {
		for (s32 i = 0; i < cVertexBufferSlotMax; i++) {
			mStrides[i] = 0;
		}
		for (s32 i = 0; i < cVertexBufferSlotMax; i++) {
			mOffsets[i] = 0;
		}
	}
};

#pragma endregion


#pragma region IndexBuffer

struct IndexBufferData {
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
	}
	void Reset() {
		mSampleMask = 0;
		for (s32 i = 0; i < 4; i++) {
			mBlendFactor[i] = 0.0f;
		}
	}
};

class IndexBufferManager : public ElementManager<ID3D11Buffer, 1> {
	using super = ElementManager<ID3D11Buffer, 1>;

public:
	IndexBufferManager() {
		Reset();
	}

private:
	void Reset() {
		ResetData();
		super::Reset();
	}

public:
	void Clear() {
		Reset();
		SetChanged();
	}

	void Set(ID3D11Buffer* aElement, DXGI_FORMAT aFormat, UINT aOffset) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged();
		}

		if (mFormat != aFormat) {
			mFormat = aFormat;
			SetChanged();
		}

		if (mOffset != aOffset) {
			mOffset = aOffset;
			SetChanged();
		}
	}

	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetIndexBuffer(Get(), mFormat, mOffset);
			SetNotChanged();
		}
	}

private:
	DXGI_FORMAT mFormat;
	UINT mOffset;

private:
	void ResetData() {
		mFormat = DXGI_FORMAT_UNKNOWN;
		mOffset = 0;
	}
};

#pragma endregion


#pragma region PrimitiveTopology

class PrimitiveTopologyManager {
public:
	PrimitiveTopologyManager() {
		Reset();
	}

private:
	void Reset() {
		mPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}

public:
	void Clear() {
		Reset();
		SetChanged();
	}

	void Set(D3D_PRIMITIVE_TOPOLOGY aPrimitiveTopology) {
		if (mPrimitiveTopology != aPrimitiveTopology) {
			mPrimitiveTopology = aPrimitiveTopology;
			SetChanged();
		}
	}
	D3D_PRIMITIVE_TOPOLOGY Get() const {
		return mPrimitiveTopology;
	}
	void SetToDevice() {
		if (IsChanged()) {
			Device::S().GetDeviceContext()->IASetPrimitiveTopology(mPrimitiveTopology);
			SetNotChanged();
		}
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

protected:
	D3D_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
	BOOL mChanged;
};

#pragma endregion


#pragma region SamplerState

class SamplerStateManager : public ElementManager<ID3D11SamplerState, 8> {

};

#pragma endregion


#pragma region ShaderResourceView

class ShaderResourceViewManager : public ElementManager<ID3D11ShaderResourceView, 16> {

};

#pragma endregion


#pragma region ConstantBuffer

class ConstantBufferManager : public ElementManager<ID3D11Buffer, 8> {

};

#pragma endregion


#pragma region UnorderedAccessView

class UnorderedAccessViewManager : public ElementManager<ID3D11UnorderedAccessView, 16> {

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
		CYC_POT_ASSERT(aSlotNum < cSlotMax);
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
