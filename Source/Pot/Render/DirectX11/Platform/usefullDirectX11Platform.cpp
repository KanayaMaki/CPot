#include "./Pot/Render/DirectX11/Platform/usefullDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/textureAllDirectX11Platform.h"

#include "./Pot/Out/out.h"
#include "./Pot/Time/time.h"

#include <Windows.h>
#include <Shlwapi.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")

namespace cpot {

namespace directX11 {

namespace platform {

UINT GetBindFlags(BOOL aIsRenderTarget, BOOL aIsShaderResourceView, BOOL aIsDepthStencilView) {
	UINT lBindFlags = 0;
	if (aIsRenderTarget) {
		lBindFlags += D3D11_BIND_RENDER_TARGET;
	}
	if (aIsShaderResourceView) {
		lBindFlags += D3D11_BIND_SHADER_RESOURCE;
	}
	if (aIsDepthStencilView) {
		lBindFlags += D3D11_BIND_DEPTH_STENCIL;
	}
	return lBindFlags;
}
UINT GetCPUAccessFlags(BOOL aIsReadable, BOOL aIsWritable) {
	UINT lCPUAccessFlags = 0;
	if (aIsReadable) {
		lCPUAccessFlags += D3D11_CPU_ACCESS_READ;
	}
	if (aIsWritable) {
		lCPUAccessFlags += D3D11_CPU_ACCESS_WRITE;
	}
	return lCPUAccessFlags;
}

u32 GetFormatSize(DXGI_FORMAT aFormat) {
	switch (aFormat) {

		//8bit
		case DXGI_FORMAT_R8_UINT:
		case DXGI_FORMAT_R8_SINT:
		case DXGI_FORMAT_R8_UNORM:
		case DXGI_FORMAT_R8_SNORM:
		case DXGI_FORMAT_R8_TYPELESS:
			return 1 * 1;

		case DXGI_FORMAT_R8G8_UINT:
		case DXGI_FORMAT_R8G8_SINT:
		case DXGI_FORMAT_R8G8_UNORM:
		case DXGI_FORMAT_R8G8_SNORM:
		case DXGI_FORMAT_R8G8_TYPELESS:
			return 1 * 2;

		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SINT:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
			return 1 * 4;


			//16bit
		case DXGI_FORMAT_R16_FLOAT:
		case DXGI_FORMAT_R16_UINT:
		case DXGI_FORMAT_R16_SINT:
		case DXGI_FORMAT_R16_UNORM:
		case DXGI_FORMAT_R16_SNORM:
		case DXGI_FORMAT_R16_TYPELESS:
			return 2 * 1;

		case DXGI_FORMAT_R16G16_FLOAT:
		case DXGI_FORMAT_R16G16_UINT:
		case DXGI_FORMAT_R16G16_SINT:
		case DXGI_FORMAT_R16G16_UNORM:
		case DXGI_FORMAT_R16G16_SNORM:
		case DXGI_FORMAT_R16G16_TYPELESS:
			return 2 * 2;

		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SINT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
			return 2 * 4;


			//32bit
		case DXGI_FORMAT_R32_FLOAT:
		case DXGI_FORMAT_R32_UINT:
		case DXGI_FORMAT_R32_SINT:
		case DXGI_FORMAT_R32_TYPELESS:
			return 4 * 1;

		case DXGI_FORMAT_R32G32_FLOAT:
		case DXGI_FORMAT_R32G32_UINT:
		case DXGI_FORMAT_R32G32_SINT:
		case DXGI_FORMAT_R32G32_TYPELESS:
			return 4 * 2;

		case DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT_R32G32B32_UINT:
		case DXGI_FORMAT_R32G32B32_SINT:
		case DXGI_FORMAT_R32G32B32_TYPELESS:
			return 4 * 3;

		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
			return 4 * 4;
	}
	return 0;
}

DXGI_FORMAT GetFormat(cFormatType aType, u32 aByteNumPerElement, u32 aElementNum) {
	if (aByteNumPerElement == 1) {
		if (aElementNum == 1) {
			switch (aType) {
				case cFloat: break;
				case cUNorm: return DXGI_FORMAT_R8_UNORM;
				case cSNorm: return DXGI_FORMAT_R8_SNORM;
				case cUInt: return DXGI_FORMAT_R8_UINT;
				case cSInt: return DXGI_FORMAT_R8_SINT;
				case cTypeless: return DXGI_FORMAT_R8_TYPELESS;
			}
		}
		else if (aElementNum == 2) {
			switch (aType) {
				case cFloat: break;
				case cUNorm: return DXGI_FORMAT_R8G8_UNORM;
				case cSNorm: return DXGI_FORMAT_R8G8_SNORM;
				case cUInt: return DXGI_FORMAT_R8G8_UINT;
				case cSInt: return DXGI_FORMAT_R8G8_SINT;
				case cTypeless: return DXGI_FORMAT_R8G8_TYPELESS;
			}
		}
		else if (aElementNum == 3) {
			switch (aType) {
				case cFloat: break;
				case cUNorm: break;
				case cSNorm: break;
				case cUInt: break;
				case cSInt: break;
				case cTypeless: break;
			}
		}
		else if (aElementNum == 4) {
			switch (aType) {
				case cFloat: break;
				case cUNorm: return DXGI_FORMAT_R8G8B8A8_UNORM;
				case cSNorm: return DXGI_FORMAT_R8G8B8A8_SNORM;
				case cUInt: return DXGI_FORMAT_R8G8B8A8_UINT;
				case cSInt: return DXGI_FORMAT_R8G8B8A8_SINT;
				case cTypeless: return DXGI_FORMAT_R8G8B8A8_TYPELESS;
			}
		}
	}
	else if (aByteNumPerElement == 2) {
		if (aElementNum == 1) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R16_FLOAT;
				case cUNorm: return DXGI_FORMAT_R16_UNORM;
				case cSNorm: return DXGI_FORMAT_R16_SNORM;
				case cUInt: return DXGI_FORMAT_R16_UINT;
				case cSInt: return DXGI_FORMAT_R16_SINT;
				case cTypeless: return DXGI_FORMAT_R16_TYPELESS;
			}
		}
		else if (aElementNum == 2) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R16G16_FLOAT;
				case cUNorm: return DXGI_FORMAT_R16G16_UNORM;
				case cSNorm: return DXGI_FORMAT_R16G16_SNORM;
				case cUInt: return DXGI_FORMAT_R16G16_UINT;
				case cSInt: return DXGI_FORMAT_R16G16_SINT;
				case cTypeless: return DXGI_FORMAT_R16G16_TYPELESS;
			}
		}
		else if (aElementNum == 3) {
			switch (aType) {
				case cFloat: break;
				case cUNorm: break;
				case cSNorm: break;
				case cUInt: break;
				case cSInt: break;
				case cTypeless: break;
			}
		}
		else if (aElementNum == 4) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R16G16B16A16_FLOAT;
				case cUNorm: return DXGI_FORMAT_R16G16B16A16_UNORM;
				case cSNorm: return DXGI_FORMAT_R16G16B16A16_SNORM;
				case cUInt: return DXGI_FORMAT_R16G16B16A16_UINT;
				case cSInt: return DXGI_FORMAT_R16G16B16A16_SINT;
				case cTypeless: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
			}
		}
	}
	else if (aByteNumPerElement == 3) {
		//該当するものなし
	}
	else if (aByteNumPerElement == 4) {
		if (aElementNum == 1) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R32_FLOAT;
				case cUNorm: break;
				case cSNorm: break;
				case cUInt: return DXGI_FORMAT_R32_UINT;
				case cSInt: return DXGI_FORMAT_R32_SINT;
				case cTypeless: return DXGI_FORMAT_R32_TYPELESS;
			}
		}
		else if (aElementNum == 2) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R32G32_FLOAT;
				case cUNorm: break;
				case cSNorm: break;
				case cUInt: return DXGI_FORMAT_R32G32_UINT;
				case cSInt: return DXGI_FORMAT_R32G32_SINT;
				case cTypeless: return DXGI_FORMAT_R32G32_TYPELESS;
			}
		}
		else if (aElementNum == 3) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R32G32B32_FLOAT;
				case cUNorm: break;
				case cSNorm: break;
				case cUInt: return DXGI_FORMAT_R32G32B32_UINT;
				case cSInt: return DXGI_FORMAT_R32G32B32_SINT;
				case cTypeless: return DXGI_FORMAT_R32G32B32_TYPELESS;
			}
		}
		else if (aElementNum == 4) {
			switch (aType) {
				case cFloat: return DXGI_FORMAT_R32G32B32A32_FLOAT;
				case cUNorm: break;
				case cSNorm: break;
				case cUInt: return DXGI_FORMAT_R32G32B32A32_UINT;
				case cSInt: return DXGI_FORMAT_R32G32B32A32_SINT;
				case cTypeless: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
			}
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}


void SaveScreenShot(ID3D11Resource* aResource, const CHAR* aName) {

	String<128> lFolderName("./ScreenShot/");

	//フォルダの作成
	if (!::PathFileExistsA(lFolderName.Get())) {
		if (::CreateDirectoryA(lFolderName.Get(), NULL) == FALSE) {
			Log::S().Output("フォルダ『", lFolderName.Get(), "』の作成に失敗しました\n");
			return;
		}
	}

	String<256> lFileName = lFolderName;

	if (aName != nullptr) {
		lFileName += aName;
	}
	else {
		DateTime lDateTime;
		DateTimeData lNowDateTime = lDateTime.Get();

		lFileName += ToString::Do((s32)lNowDateTime.month).Padding('0', 2);
		lFileName += ToString::Do((s32)lNowDateTime.day).Padding('0', 2);
		lFileName += "_";
		lFileName += ToString::Do((s32)lNowDateTime.hour).Padding('0', 2);
		lFileName += ToString::Do((s32)lNowDateTime.minute).Padding('0', 2);
		lFileName += ToString::Do((s32)lNowDateTime.second).Padding('0', 2);
	}
	lFileName += ".png";

	HRESULT hr = D3DX11SaveTextureToFileA(Device::S().GetDeviceContext(), // デバイス・コンテキスト
		aResource,		// 保存するバック バッファ
		D3DX11_IFF_PNG,		// PNG形式で保存
		lFileName.Get());  // 保存先のファイル名
	if (FAILED(hr)) {
		Log::S().Output("スクリーンショットの保存に失敗しました\n");
		return;
	}
}
void SaveScreenShot(const CHAR* aName) {
	SaveScreenShot(Device::S().GetBackBuffer()->Get(), aName);
}


}

}

}
