//
//	content	:	TextureのDirectX11での実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/texture2D.h"
#include "./Pot/Render/DirectX11/Platform/textureAllDirectX11Platform.h"


namespace cpot {

namespace directX11 {


class Texture2DDirectX11Data : public ResourceLoadList<Texture2DDirectX11Data, String<128>> {

};

class Texture2D : public Texture2DBase {

public:
	static DXGI_FORMAT Convert(CFormat aFormat) {
		switch (aFormat) {
			case cR8Uint:
				return DXGI_FORMAT_R8_UNORM;
			case cRGBA8Uint:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			case cR32Float:
				return DXGI_FORMAT_R32_FLOAT;
			case cRGBA32Float:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		return DXGI_FORMAT_UNKNOWN;
	}
	static CFormat Convert(DXGI_FORMAT aFormat) {
		switch (aFormat) {

		}
	}

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mTexture.Load(Texture2DDirectX11Data::S().Get(aUnionName).Get());
	};
	void Load(u32 aWidth, u32 aHeight, CFormat aFormat, BOOL aIsRenderTarget, BOOL aIsShaderResource) CPOT_OR {
		Load(aWidth, aHeight, aFormat, aIsRenderTarget, aIsShaderResource, false);
	}
	void Load(u32 aWidth, u32 aHeight, CFormat aFormat, BOOL aIsRenderTarget, BOOL aIsShaderResource, BOOL aIsDepthStencil) CPOT_OR {
		mTexture.Load(platform::Texture2D::CreateDesc(aWidth, aHeight, Convert(aFormat), D3D11_USAGE_DEFAULT,
			platform::GetBindFlags(aIsRenderTarget, aIsShaderResource, aIsDepthStencil), 0));
	}
	void LoadFileName(const CHAR* aFileName) CPOT_OR {
		mTexture.Load(aFileName);
	};

	void LoadPlatform(std::shared_ptr<platform::Texture2D> aTexture) {
		mTexture.Load(aTexture);
	}

public:
	void Release() CPOT_OR {
		mTexture.Release();
	};

	void ClearDepth(f32 aDepth) CPOT_OR {
		mTexture.GetDepthStencilView()->ClearDepth(aDepth);
	}
	void ClearColor(const Color& aColor) CPOT_OR {
		mTexture.GetRenderTargetView()->ClearTexture(aColor);
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mTexture.IsLoaded();
	};

public:
	u32 GetWidth() CPOT_OR {
		return mTexture.GetTexture()->GetWidth();
	}
	u32 GetHeight() CPOT_OR {
		return mTexture.GetTexture()->GetHeight();
	}


	//フィールド
	#pragma region Field

public:
	platform::Texture2DAll mTexture;

	#pragma endregion
};

}

using Texture2D = directX11::Texture2D;

}