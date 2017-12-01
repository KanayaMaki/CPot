//
//	content	:	Texture‚ÌDirectX11‚Å‚ÌŽÀ‘•
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Render/render.h"
#include "./Pot/Render/DirectX11/Platform/renderDirectX11Platform.h"


namespace cpot {

namespace directX11 {

class Render : public RenderBase, public Singleton<Render> {
	friend class Singleton<Render>;

public:
	void SetRasterizer(Rasterizer* aRasterizer) CPOT_OR {}
	void SetBlend(Blend* aBlend) CPOT_OR {}

	void SetDepthStencil(DepthStencil* aDepthStencil) CPOT_OR {}

	void SetViewPort(cyc::pot::ViewPort& aViewPort, u32 aSlotNum) CPOT_OR {}

	void SetSampler(std::shared_ptr<Sampler> aSampler, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetVertexShaderManager().SetSampler(aSampler->mSampler, aSlotNum);
		platform::Render::S().GetGeometryShaderManager().SetSampler(aSampler->mSampler, aSlotNum);
		platform::Render::S().GetPixelShaderManager().SetSampler(aSampler->mSampler, aSlotNum);
	}

	void SetTexture2D(std::shared_ptr<Texture2D> aTexture, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetVertexShaderManager().SetShaderResource(aTexture->mTexture.GetShaderResourceView(), aSlotNum);
		platform::Render::S().GetGeometryShaderManager().SetShaderResource(aTexture->mTexture.GetShaderResourceView(), aSlotNum);
		platform::Render::S().GetPixelShaderManager().SetShaderResource(aTexture->mTexture.GetShaderResourceView(), aSlotNum);
	}

	void SetConstantBuffer(std::shared_ptr<ConstantBuffer> aConstantBuffer, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetVertexShaderManager().SetConstantBuffer(aConstantBuffer->mConstantBuffer, aSlotNum);
		platform::Render::S().GetGeometryShaderManager().SetConstantBuffer(aConstantBuffer->mConstantBuffer, aSlotNum);
		platform::Render::S().GetPixelShaderManager().SetConstantBuffer(aConstantBuffer->mConstantBuffer, aSlotNum);
	}


	void SetShader(std::shared_ptr<Shader> aShader) CPOT_OR {
		
	}


	void SetDepthStencilView(DepthStencilView* aDepthStencilView) CPOT_OR {
		
	}
	void SetRenderTarget(RenderTarget* aRenderTarget, u32 aSlotNum) CPOT_OR {
		
	}

	void SetIndexBuffer(std::shared_ptr<IndexBuffer> aIndexBuffer) CPOT_OR {
		platform::Render::S().GetIndexBufferManager().Set(aIndexBuffer);
	}
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> aVertexBuffer) CPOT_OR {
		platform::Render::S().GetVertexBufferManager().Set(aVertexBuffer);
	}


	void SetToDevice() CPOT_OR {
		platform::Render::S().SetToDevice();
	}


	void DrawIndexed(u32 aIndexCount, u32 aStartIndexLocation) CPOT_OR {
		platform::Render::S().DrawIndexed(aIndexCount, aStartIndexLocation, 0);
	}
	void Draw(u32 aVertexCount, u32 aStartVertexLocation) CPOT_OR {
		platform::Render::S().Draw(aVertexCount, aStartVertexLocation);
	}

	void Present() CPOT_OR {
		platform::Render::S().Present();
	}
};


}

using Render = directX11::Render;

}