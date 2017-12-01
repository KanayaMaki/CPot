#pragma once

#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"

#include "./Pot/Usefull/buffer.h"

#include <vector>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")


namespace cpot {

namespace directX11 {

namespace platform {


class InputLayout {
public:
	InputLayout() {
		Reset();
	}
	~InputLayout() {
		Release();
	}

	void Reset() {
		mInputLayout = nullptr;
	}

	ID3D11InputLayout* Get() const {
		return mInputLayout;
	}
	BOOL IsLoaded() const {
		return mInputLayout != nullptr;
	}

	void Release() {
		if (IsLoaded()) {
			CPOT_SAFE_RELEASE(mInputLayout);
			Reset();
		}
	}

public:
	DXGI_FORMAT GetFormat(const D3D11_SIGNATURE_PARAMETER_DESC& aParameterDesc) {

		s32 lParameterNum = 0;
		if (aParameterDesc.Mask <= 1) {
			lParameterNum = 1;
		}
		else if (aParameterDesc.Mask <= 3) {
			lParameterNum = 2;
		}
		else if (aParameterDesc.Mask <= 7) {
			lParameterNum = 3;
		}
		else if (aParameterDesc.Mask <= 15) {
			lParameterNum = 4;
		}


		switch (aParameterDesc.ComponentType) {
			case D3D_REGISTER_COMPONENT_FLOAT32: {
				switch (lParameterNum) {
					case 1: return DXGI_FORMAT_R32_FLOAT;
					case 2: return DXGI_FORMAT_R32G32_FLOAT;
					case 3: return DXGI_FORMAT_R32G32B32_FLOAT;
					case 4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
				}
			}
			case D3D_REGISTER_COMPONENT_SINT32: {
				switch (lParameterNum) {
					case 1: return DXGI_FORMAT_R32_SINT;
					case 2: return DXGI_FORMAT_R32G32_SINT;
					case 3: return DXGI_FORMAT_R32G32B32_SINT;
					case 4: return DXGI_FORMAT_R32G32B32A32_SINT;
				}
			}
			case D3D_REGISTER_COMPONENT_UINT32: {
				switch (lParameterNum) {
					case 1: return DXGI_FORMAT_R32_UINT;
					case 2: return DXGI_FORMAT_R32G32_UINT;
					case 3: return DXGI_FORMAT_R32G32B32_UINT;
					case 4: return DXGI_FORMAT_R32G32B32A32_UINT;
				}
			}
		}

		return DXGI_FORMAT_UNKNOWN;
	}

	void Load(const cpot::Buffer& aBuffer) {

		HRESULT hr;

		ID3D11ShaderReflection* lShaderReflection = nullptr;
		hr = D3DReflect(aBuffer.Get(), aBuffer.GetSize(), IID_ID3D11ShaderReflection, (void**)(&lShaderReflection));
		if (FAILED(hr)) {
			Log::S().Output("ShaderDirectX11.CreateInputLayout : Failed CreateReflection");
			return;
		}


		//ShaderDescの取得
		D3D11_SHADER_DESC lShaderDesc;
		lShaderReflection->GetDesc(&lShaderDesc);


		u32 aByteOffset = 0;

		//インプットレイアウトの作成
		std::vector<D3D11_INPUT_ELEMENT_DESC> lInputElementDesc;
		for (UINT i = 0; i < lShaderDesc.InputParameters; i++) {
			D3D11_SIGNATURE_PARAMETER_DESC lParameterDesc;
			lShaderReflection->GetInputParameterDesc(i, &lParameterDesc);

			D3D11_INPUT_ELEMENT_DESC lElementDesc;
			lElementDesc.SemanticName = lParameterDesc.SemanticName;
			lElementDesc.SemanticIndex = lParameterDesc.SemanticIndex;
			lElementDesc.Format = GetFormat(lParameterDesc);
			lElementDesc.InputSlot = 0;
			lElementDesc.AlignedByteOffset = aByteOffset;
			aByteOffset += GetFormatSize(lElementDesc.Format);
			lElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			lElementDesc.InstanceDataStepRate = 0;

			lInputElementDesc.push_back(lElementDesc);
		}

		// 入力レイアウト・オブジェクトの作成
		hr = Device::S().GetDevice()->CreateInputLayout(
			&(lInputElementDesc[0]),                            // 定義の配列
			lInputElementDesc.size(),                  // 定義の要素数
			aBuffer.Get(),       // バイト・コードへのポインタ
			aBuffer.GetSize(),          // バイト・コードのサイズ
			&mInputLayout);                  // 受け取る変数のポインタ

		if (FAILED(hr)) {
			Log::S().Output("ShaderDirectX11.CreateInputLayout : Failed CreateInputLayout");
			CPOT_SAFE_RELEASE(lShaderReflection);
			return;
		}
		CPOT_SAFE_RELEASE(lShaderReflection);
	}
	void Load(const cpot::Buffer& aBuffer, const D3D11_INPUT_ELEMENT_DESC* aInputElement, u32 aInputElementNum) {

		HRESULT hr;

		// 入力レイアウト・オブジェクトの作成
		hr = Device::S().GetDevice()->CreateInputLayout(
			&(aInputElement[0]),                            // 定義の配列
			aInputElementNum,                  // 定義の要素数
			aBuffer.Get(),       // バイト・コードへのポインタ
			aBuffer.GetSize(),          // バイト・コードのサイズ
			&mInputLayout);                  // 受け取る変数のポインタ

		if (FAILED(hr)) {
			Log::S().Output("ShaderDirectX11.CreateInputLayout : Failed CreateInputLayout");
			return;
		}
	}


private:
	ID3D11InputLayout* mInputLayout;
};


template <typename ShaderType>
class Shader {

	//初期化
	#pragma region Init

public:
	Shader() {
		Clear();
	}

protected:
	void Clear() {
		mShader = nullptr;
	}

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	~Shader() {
		Release();
	}

public:
	void Release() {
		CPOT_SAFE_RELEASE(mShader);
		Clear();
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	ShaderType* GetShader() const {
		return mShader;
	}
	BOOL IsLoaded() const {
		return mShader != nullptr;
	}

	#pragma endregion


public:
	void GetCompiledBuffer(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType, cpot::Buffer& aBuffer) {

		#if defined DEBUG || defined _DEBUG
		const UINT lCompileFlag = D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION | D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR;
		#else
		const UINT lCompileFlag = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_SKIP_OPTIMIZATION;
		#endif

		ID3DBlob* lBlob = nullptr;
		ID3DBlob* lError = nullptr;
		HRESULT hr;

		// 頂点シェーダのコードをコンパイル
		lBlob = NULL;
		hr = D3DX11CompileFromFileA(
			aFileName,  // ファイル名
			NULL,          // マクロ定義(なし)
			NULL,          // インクルード・ファイル定義(なし)
			aEntryPoint,          // 「VS関数」がシェーダから実行される
			aShaderType,      // 頂点シェーダ
			lCompileFlag, // コンパイル・オプション
			0,             // エフェクトのコンパイル・オプション(なし)
			NULL,          // 直ぐにコンパイルしてから関数を抜ける。
			&lBlob,      // コンパイルされたバイト・コード
			&lError,          // エラーメッセージは不要
			NULL);         // 戻り値
		if (FAILED(hr)) {
			Log::S().Output("ShaderCompileError:", (const CHAR*)(lError->GetBufferPointer()));
			return;
		}

		aBuffer.Load((BYTE*)(lBlob->GetBufferPointer()), lBlob->GetBufferSize());
		
		CPOT_SAFE_RELEASE(lBlob);
		CPOT_SAFE_RELEASE(lError);
	}


	//フィールド
	#pragma region Field

protected:
	ShaderType* mShader;

	#pragma endregion

};



class VertexShader : public Shader<ID3D11VertexShader> {

public:
	void CompileFromFile(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType, const D3D11_INPUT_ELEMENT_DESC* aInputElement = nullptr, u32 aInputElementNum = 0) {
		cpot::Buffer lBuffer;
		GetCompiledBuffer(aFileName, aEntryPoint, aShaderType, lBuffer);
		CreateFromCompiledBuffer(lBuffer, aInputElement, aInputElementNum);
	}
	void CreateFromCompiledBuffer(const cpot::Buffer& mBuffer, const D3D11_INPUT_ELEMENT_DESC* aInputElement = nullptr, u32 aInputElementNum = 0) {

		HRESULT hr;

		ID3D11VertexShader* lTmp;

		// 頂点シェーダの作成
		hr = Device::S().GetDevice()->CreateVertexShader(
			mBuffer.Get(), // バイト・コードへのポインタ
			mBuffer.GetSize(),    // バイト・コードの長さ
			NULL,
			&lTmp); // 頂点シェーダを受け取る変数

		if (FAILED(hr)) {
			Log::S().Output("VertexShaderDirectX11.CreateError:");
			return;
		}

		{
			mShader = lTmp;
			mInputLayout = std::shared_ptr<InputLayout>(new InputLayout);
		}

		if (aInputElement == nullptr) {
			mInputLayout->Load(mBuffer);
		}
		else {
			mInputLayout->Load(mBuffer, aInputElement, aInputElementNum);
		}
	}


private:
	void Clear() {
		mInputLayout = nullptr;
		Shader<ID3D11VertexShader>::Clear();
	}
public:
	void Release() {
		mInputLayout->Release();
		Shader<ID3D11VertexShader>::Release();
		Clear();
	}

public:
	std::shared_ptr<InputLayout> GetInputLayout() const {
		return mInputLayout;
	}
private:
	std::shared_ptr<InputLayout> mInputLayout;
};


class GeometryShader : public Shader<ID3D11GeometryShader> {
public:
	void CompileFromFile(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType) {
		cpot::Buffer lBuffer;
		GetCompiledBuffer(aFileName, aEntryPoint, aShaderType, lBuffer);
		CreateFromCompiledBuffer(lBuffer);
	}
	void CreateFromCompiledBuffer(const cpot::Buffer& aBuffer) {

		HRESULT hr;

		ID3D11GeometryShader* lTmp;

		// 頂点シェーダの作成
		hr = Device::S().GetDevice()->CreateGeometryShader(
			aBuffer.Get(), // バイト・コードへのポインタ
			aBuffer.GetSize(),    // バイト・コードの長さ
			NULL,
			&lTmp); // 頂点シェーダを受け取る変数

		if (FAILED(hr)) {
			Log::S().Output("GeometryShaderDirectX11.CreateError:");
			return;
		}

		mShader = lTmp;
	}
};


class PixelShader : public Shader<ID3D11PixelShader> {

public:
	void CompileFromFile(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType) {
		cpot::Buffer lBuffer;
		GetCompiledBuffer(aFileName, aEntryPoint, aShaderType, lBuffer);
		CreateFromCompiledBuffer(lBuffer);
	}
	void CreateFromCompiledBuffer(const cpot::Buffer& aBuffer) {

		HRESULT hr;

		ID3D11PixelShader* lTmp;

		// 頂点シェーダの作成
		hr = Device::S().GetDevice()->CreatePixelShader(
			aBuffer.Get(), // バイト・コードへのポインタ
			aBuffer.GetSize(),    // バイト・コードの長さ
			NULL,
			&lTmp); // 頂点シェーダを受け取る変数

		if (FAILED(hr)) {
			Log::S().Output("PixelShaderDirectX11.CreateError:");
			return;
		}

		mShader = lTmp;
	}
};


class HullShader : public Shader<ID3D11HullShader> {

public:
	void CompileFromFile(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType) {
		cpot::Buffer lBuffer;
		GetCompiledBuffer(aFileName, aEntryPoint, aShaderType, lBuffer);
		CreateFromCompiledBuffer(lBuffer);
	}
	void CreateFromCompiledBuffer(const cpot::Buffer& aBuffer) {

		HRESULT hr;

		ID3D11HullShader* lTmp;

		// 頂点シェーダの作成
		hr = Device::S().GetDevice()->CreateHullShader(
			aBuffer.Get(), // バイト・コードへのポインタ
			aBuffer.GetSize(),    // バイト・コードの長さ
			NULL,
			&lTmp); // 頂点シェーダを受け取る変数

		if (FAILED(hr)) {
			Log::S().Output("HullShaderDirectX11.CreateError:");
			return;
		}

		mShader = lTmp;
	}
};


class DomainShader : public Shader<ID3D11DomainShader> {
public:
	void CompileFromFile(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType) {
		cpot::Buffer lBuffer;
		GetCompiledBuffer(aFileName, aEntryPoint, aShaderType, lBuffer);
		CreateFromCompiledBuffer(lBuffer);
	}
	void CreateFromCompiledBuffer(const cpot::Buffer& aBuffer) {

		HRESULT hr;

		ID3D11DomainShader* lTmp;

		// 頂点シェーダの作成
		hr = Device::S().GetDevice()->CreateDomainShader(
			aBuffer.Get(), // バイト・コードへのポインタ
			aBuffer.GetSize(),    // バイト・コードの長さ
			NULL,
			&lTmp); // 頂点シェーダを受け取る変数

		if (FAILED(hr)) {
			Log::S().Output("DomainShaderDirectX11.CreateError:");
			return;
		}

		mShader = lTmp;
	}
};


class ComputeShader : public Shader<ID3D11ComputeShader> {

public:
	void CompileFromFile(const CHAR* aFileName, const CHAR* aEntryPoint, const CHAR* aShaderType) {
		cpot::Buffer lBuffer;
		GetCompiledBuffer(aFileName, aEntryPoint, aShaderType, lBuffer);
		CreateFromCompiledBuffer(lBuffer);
	}
	void CreateFromCompiledBuffer(const cpot::Buffer& aBuffer) {

		HRESULT hr;

		ID3D11ComputeShader* lTmp;

		// 頂点シェーダの作成
		hr = Device::S().GetDevice()->CreateComputeShader(
			aBuffer.Get(), // バイト・コードへのポインタ
			aBuffer.GetSize(),    // バイト・コードの長さ
			NULL,
			&lTmp); // 頂点シェーダを受け取る変数

		if (FAILED(hr)) {
			Log::S().Output("ComputeShaderDirectX11.CreateError:");
			return;
		}

		mShader = lTmp;
	}
};


}

}

}
