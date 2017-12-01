//
//	content	:	TextureのDirectX11での実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/singleton.h"

#include "./Pot/Render/texture2D.h"
#include "./Pot/Render/sampler.h"
#include "./Pot/Render/constantBuffer.h"
#include "./Pot/Render/vertexBuffer.h"
#include "./Pot/Render/indexBuffer.h"
#include "./Pot/Render/shader.h"

namespace cpot {


//シングルトンにする必要がある
class RenderBase {
public:
	CPOT_VI ~RenderBase() {}

public:
	CPOT_VI void SetRasterizer(Rasterizer* aRasterizer) CPOT_ZR;
	CPOT_VI void SetBlend(Blend* aBlend) CPOT_ZR;

	CPOT_VI void SetDepthStencil(DepthStencil* aDepthStencil) CPOT_ZR;

	CPOT_VI void SetViewPort(ViewPort& aViewPort, u32 aSlotNum) CPOT_ZR;

	CPOT_VI void SetSampler(std::shared_ptr<Sampler> aSampler, u32 aSlotNum) CPOT_ZR;
	
	CPOT_VI void SetTexture2D(std::shared_ptr<Texture2D> aTexture, u32 aSlotNum) CPOT_ZR;
	
	CPOT_VI void SetConstantBuffer(std::shared_ptr<ConstantBuffer> aConstantBuffer, u32 aSlotNum) CPOT_ZR;
	
	CPOT_VI void SetShader(std::shared_ptr<Shader> aShader) CPOT_ZR;


	CPOT_VI void SetDepthStencilView(DepthStencilView* aDepthStencilView) CPOT_ZR;
	CPOT_VI void SetRenderTarget(RenderTarget* aRenderTarget, u32 aSlotNum) CPOT_ZR;

	CPOT_VI void SetIndexBuffer(std::shared_ptr<IndexBuffer> aIndexBuffer) CPOT_ZR;
	CPOT_VI void SetVertexBuffer(std::shared_ptr<VertexBuffer> aVertexBuffer) CPOT_ZR;


	CPOT_VI void SetToDevice() CPOT_ZR;


	CPOT_VI void DrawIndexed(u32 aIndexCount, u32 aStartIndexLocation) CPOT_ZR;
	CPOT_VI void Draw(u32 aVertexCount, u32 aStartVertexLocation) CPOT_ZR;

	CPOT_VI void Present() CPOT_ZR;
};


}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/Render/DirectX11/renderDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Audio/Android/renderAndroid.h"
#endif