//
//	content	:	DirectX11�ł�Sampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class ConstantBufferBase : public NamedResource {


	#pragma region Load

public:
	template<typename T>
	BOOL Load(T* aInitData);

	CPOT_VI BOOL Load(void* aInitData, u32 aSize) CPOT_ZR;

	#pragma endregion


	#pragma region Write

public:
	CPOT_VI BOOL Write() CPOT_ZR;
	CPOT_VI BOOL Write(const void* aBuffer) CPOT_ZR;

	#pragma endregion


	//�擾
	#pragma region Getter

public:
	template<typename T>
	T* GetCPUBuffer();

	#pragma endregion


	//�ݒ�
	#pragma region Setter

public:
	CPOT_VI void SetCPUBuffer(void* aCPUBuffer) CPOT_ZR;

	#pragma endregion


public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;
};

}

#ifdef CPOT_ON_DIRECTX11
#include "./Pot/Render/DirectX11/constantBufferDirectX11.h"
#elif defined CPOT_ON_OPENGL
#include "./Pot/Render/OpenGL/constantBufferOpenGL.h"
#endif