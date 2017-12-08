//
//	content	:	DirectX11�ł�Sampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {


class VertexBufferBase : public NamedResource {

public:
	CPOT_VI ~VertexBufferBase() {}

	#pragma region Load

public:
	CPOT_VI BOOL Load(u32 aVertexSize, u32 aVertexNum, const void* aInitData, BOOL aCPUWritable) CPOT_ZR;
	CPOT_VI BOOL Load(u32 aVertexSize, u32 aVertexNum, const void* aInitData) CPOT_ZR;


	#pragma endregion


	#pragma region Write

public:
	CPOT_VI BOOL Write(const void* aData) CPOT_ZR;
	CPOT_VI BOOL Write(const void* aData, u32 aSize) CPOT_ZR;

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	CPOT_VI u32 GetVertexSize() const CPOT_ZR;
	CPOT_VI u32 GetVertexNum() const CPOT_ZR;

	#pragma endregion


public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}


#ifdef CPOT_ON_DIRECTX11
#include "./Pot/Render/DirectX11/vertexBufferDirectX11.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Audio/Android/vertexBufferAndroid.h"
#endif