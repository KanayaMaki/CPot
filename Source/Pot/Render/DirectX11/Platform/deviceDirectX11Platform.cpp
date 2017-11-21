#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

namespace cpot {

namespace directX11 {

namespace platform {


HRESULT Device::Init(HWND aHwnd, const Vector2& aScreenSize) {

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	UINT              featureLevelNum = 3;   // 配列の要素数
	D3D_FEATURE_LEVEL featureLevelsSupported;

	// デバイスとスワップ・チェインの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));    // 構造体の値を初期化(必要な場合)
	sd.BufferCount = 3;       // バック・バッファ数
	sd.BufferDesc.Width = aScreenSize.x;     // バック・バッファの幅
	sd.BufferDesc.Height = aScreenSize.y;     // バック・バッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // フォーマット
	sd.BufferDesc.RefreshRate.Numerator = 60;  // リフレッシュ・レート(分子)
	sd.BufferDesc.RefreshRate.Denominator = 1; // リフレッシュ・レート(分母)
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;	// スキャンライン
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // バック・バッファの使用法
	sd.OutputWindow = aHwnd;    // 関連付けるウインドウ
	sd.SampleDesc.Count = 1;        // マルチ・サンプルの数
	sd.SampleDesc.Quality = 0;      // マルチ・サンプルのクオリティ
	sd.Windowed = TRUE;             // ウインドウ・モード
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // モード自動切り替え

	#ifdef CPOT_ON_DEBUG
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
	#else
	UINT createDeviceFlags = 0;
	#endif

	// ハードウェア・デバイスを作成
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
		featureLevels, featureLevelNum, D3D11_SDK_VERSION, &sd,
		&mSwapChain, &mDevice, &featureLevelsSupported,
		&mDeviceContext);

	if (FAILED(hr)) {
		// WARPデバイスを作成
		hr = D3D11CreateDeviceAndSwapChain(
			NULL, D3D_DRIVER_TYPE_WARP, NULL, createDeviceFlags,
			featureLevels, featureLevelNum, D3D11_SDK_VERSION, &sd,
			&mSwapChain, &mDevice, &featureLevelsSupported,
			&mDeviceContext);

		if (FAILED(hr)) {
			// リファレンス・デバイスを作成
			hr = D3D11CreateDeviceAndSwapChain(
				NULL, D3D_DRIVER_TYPE_REFERENCE, NULL, createDeviceFlags,
				featureLevels, featureLevelNum, D3D11_SDK_VERSION, &sd,
				&mSwapChain, &mDevice, &featureLevelsSupported,
				&mDeviceContext);
			if (FAILED(hr)) {
				CPOT_ERROR("デバイスの作成に失敗しました");
				Final();
				return -1L;
			}
		}
	}

	//バックバッファの取得
	hr = mSwapChain->GetBuffer(
		0,                         // バック・バッファの番号
		__uuidof(ID3D11Texture2D), // バッファにアクセスするインターフェイス
		(LPVOID*)&mBackBuffer);    // バッファを受け取る変数
	if (FAILED(hr)) {
		CPOT_ERROR("バックバッファの取得に失敗しました");
		Final();
		return -1L;
	}

	return 0L;
}


void Device::Final() {
	CPOT_SAFE_RELEASE(mDeviceContext);
	CPOT_SAFE_RELEASE(mSwapChain);
	CPOT_SAFE_RELEASE(mDevice);
	Clear();
}


}

}

}
