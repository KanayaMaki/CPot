#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Render/DirectX11/Platform/usefullDirectX11Platform.h"

#include <Windows.h>

#include <d3d11.h>
#include <d3dx11.h>


#pragma comment(lib, "d3d11.lib")
#ifndef NDEBUG
#pragma comment(lib, "d3dx11d.lib")
#else
#pragma comment(lib, "d3dx11.lib")
#endif

namespace cpot {

namespace directX11 {

namespace platform {


#define CPOT_SAFE_RELEASE(p) if(p != nullptr) {p->Release();}

class Device : public Singleton<Device> {
	friend class Singleton<Device>;

	//初期化
	#pragma region Init

private:
	Device() {
		Clear();
	}
	void Clear() {
		mDevice = nullptr;
		mDeviceContext = nullptr;
		mSwapChain = nullptr;
		mBackBuffer = nullptr;
	}

public:
	//初期化
	HRESULT Init(HWND aHwnd, const Vector2& aScreenSize);

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	void Final();

	#pragma endregion


	//デバイスなどを取得する
	#pragma region Getter

public:
	ID3D11Device* GetDevice() const {
		return mDevice;
	}
	ID3D11DeviceContext* GetDeviceContext() const {
		return mDeviceContext;
	}
	IDXGISwapChain* GetSwapChain() const {
		return mSwapChain;
	}
	ID3D11Texture2D* GetBackBuffer() const {
		return mBackBuffer;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mBackBuffer;

	#pragma endregion

};


}

}

}
