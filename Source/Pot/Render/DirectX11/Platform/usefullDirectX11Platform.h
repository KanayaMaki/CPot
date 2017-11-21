﻿#pragma once

#include "./Pot/Atom/atom.h"

#include <d3d11.h>
#include <d3dx11.h>

#include <xnamath.h>

namespace cpot {

namespace directX11 {

namespace platform {


UINT GetBindFlags(BOOL aIsRenderTarget, BOOL aIsShaderResourceView, BOOL aIsDepthStencilView = false);
UINT GetCPUAccessFlags(BOOL aIsReadable, BOOL aIsWritable);

u32 GetFormatSize(DXGI_FORMAT aFormat);

enum cFormatType {
	cFloat,
	cUInt,
	cSInt,
	cUNorm,
	cSNorm,
	cTypeless,
};
DXGI_FORMAT GetFormat(cFormatType aType, u32 aByteNumPerElement, u32 aElementNum);


void SaveScreenShot(ID3D11Resource* aResource, const CHAR* aName);
void SaveScreenShot(const CHAR* aName);


}


}

}
