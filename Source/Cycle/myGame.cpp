//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"

#include "./Pot/Out/out.h"
#include "./Pot/Config/config.h"

#include "./Pot/Input/input.h"
#include "./Pot/Audio/audio.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Rand/rand.h"
#include "./Pot/Time/time.h"
#include "./Pot/File/file.h"

#include "./Pot/Animation/animation.h"


#include "./Pot/Render/DirectX11/Platform/renderDirectX11Platform.h"
#include "./Pot/Config/config.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}


class LoaderTimer : public Loader {
public:
	LoaderTimer(const CHAR* aFileName) {
		mFileName = aFileName;
		mTakeTime = 3.0f;
	}
	LoaderTimer(const CHAR* aFileName, f32 aTakeTime) {
		mFileName = aFileName;
		mTakeTime = aTakeTime;
	}

public:
	void Start() override {
		CPOT_LOG("LoadStart:", mFileName.Get());
	}
	void Load() override {

		CPOT_LOG("Loading:", mFileName.Get());

		Sleep lSleep;
		lSleep.SleepSecond(mTakeTime);
	}
	void Finish() override {
		CPOT_LOG("LoadFinish:", mFileName.Get());
	}
public:
	String<128> mFileName;
	f32 mTakeTime;
};

class LoaderTimerHurry : public LoaderTimer {
public:
	LoaderTimerHurry(const CHAR* aFileName) : LoaderTimer(aFileName) {}
	LoaderTimerHurry(const CHAR* aFileName, f32 aTakeTime) : LoaderTimer(aFileName, aTakeTime) {}

	BOOL IsHurry() const override {
		return true;
	}
};
class LoaderGenerate : public Loader {
public:
	void Load() override {

		LoaderManager::S().Regist(new LoaderTimer("Generated", 2.0f));
		CPOT_LOG("LoaderGenerateLoading");

		Sleep lSleep;
		lSleep.SleepSecond(2.0f);
	}

	BOOL IsHurry() const override {
		return true;
	}
};

}

using namespace cpot;

namespace myspc {

Animation<f32> v;
std::shared_ptr<AudioVoice> voice;

struct BasicVertex {
	Vector3 mPosition;
	Vector3 mNormal;
	Vector2 mUV;
};
struct WVPBuffer {
	ShaderMatrix4x4 mView;
	ShaderMatrix4x4 mProjection;
	ShaderMatrix4x4 mWorld;
	ShaderMatrix4x4 mNormalWorld;
};
struct DiffuseBuffer {
	Color mDiffuse;
};
struct TimerBuffer {
	f32 mTimer;
};


std::shared_ptr<directX11::platform::IndexBuffer> indexBuffer;
std::shared_ptr<directX11::platform::VertexBuffer> vertexBuffer;
std::shared_ptr<directX11::platform::ConstantBuffer> wvpBuffer;
std::shared_ptr<directX11::platform::ConstantBuffer> diffuseBuffer;
std::shared_ptr<directX11::platform::ConstantBuffer> timerBuffer;
std::shared_ptr<directX11::platform::Texture2DAll> texture;
std::shared_ptr<directX11::platform::Texture2DAll> depthTexture;
std::shared_ptr<directX11::platform::Texture2DAll> renderTexture;
std::shared_ptr<directX11::platform::SamplerState> sampler;
std::shared_ptr<directX11::platform::BlendState> blendState;
std::shared_ptr<directX11::platform::DepthStencilState> depthStencilState;
std::shared_ptr<directX11::platform::RasterizerState> rasterizerState;
std::shared_ptr<directX11::platform::VertexShader> vertexShader;
std::shared_ptr<directX11::platform::GeometryShader> geometryShader;
std::shared_ptr<directX11::platform::PixelShader> pixelShader;


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
	cpot::Config::S().SetTitle("MyGame!");
}

//ゲームの初期化
void MyGame::Init() {
	//CPOT_LOG("Init!");

	//Loaderのスタート
	//LoaderManager::S().Start(2);

	v.Add(0.0f, 0.0f);
	v.Add(2.0f, 0.5f);
	v.Add(4.0f, 1.0f);
	v.SetIsLoop(true);


	wvpBuffer.reset(new directX11::platform::ConstantBuffer);
	wvpBuffer->Load<WVPBuffer>(new WVPBuffer);

	diffuseBuffer.reset(new directX11::platform::ConstantBuffer);
	diffuseBuffer->Load<DiffuseBuffer>(new DiffuseBuffer);
	diffuseBuffer->GetCPUBuffer<DiffuseBuffer>()->mDiffuse = Color::White();

	timerBuffer.reset(new directX11::platform::ConstantBuffer);
	timerBuffer->Load<TimerBuffer>(new TimerBuffer);
	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer = 0.0f;

	sampler.reset(new directX11::platform::SamplerState);
	sampler->Load(directX11::platform::SamplerState::CreateDescClamp());

	rasterizerState.reset(new directX11::platform::RasterizerState);
	rasterizerState->Load(directX11::platform::RasterizerState::CreateDescNoCull());

	depthStencilState.reset(new directX11::platform::DepthStencilState);
	depthStencilState->Load(directX11::platform::DepthStencilState::CreateDescNoZTest());

	blendState.reset(new directX11::platform::BlendState);
	blendState->Load(directX11::platform::BlendState::CreateDescNormal());

	PathString p = Path::FromRelative("./", "./test.png");

	texture.reset(new directX11::platform::Texture2DAll);
	texture->Load(p.Get());
	
	depthTexture.reset(new directX11::platform::Texture2DAll);
	depthTexture->Load(directX11::platform::Texture2D::CreateDesc(
		Config::S().GetScreenSize().x, Config::S().GetScreenSize().y,
		DXGI_FORMAT_R32_TYPELESS, D3D11_USAGE_DEFAULT, directX11::platform::GetBindFlags(false, true, true), 0));

	renderTexture.reset(new directX11::platform::Texture2DAll);
	renderTexture->Load(directX11::platform::Texture2D::CreateDesc(
		Config::S().GetScreenSize().x, Config::S().GetScreenSize().y,
		DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_USAGE_DEFAULT, directX11::platform::GetBindFlags(true, true, false), 0));

	BasicVertex lVertex[]{
		{ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 1.0f } },
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f } },
		{ { 1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f } },
	};
	vertexBuffer.reset(new directX11::platform::VertexBuffer);
	vertexBuffer->Load(sizeof(BasicVertex), 4, lVertex);

	u16 lIndex[]{ 0, 1, 2, 2, 1, 3 };
	indexBuffer.reset(new directX11::platform::IndexBuffer);
	indexBuffer->Load(DXGI_FORMAT_R16_UINT, 6, lIndex, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	vertexShader.reset(new directX11::platform::VertexShader);
	vertexShader->CompileFromFile("./test.fx", "VS_TEST", "vs_4_0");
	directX11::platform::Render::S().GetVertexShaderManager().SetShader(vertexShader);
	directX11::platform::Render::S().GetInputLayoutManager().Set(vertexShader->GetInputLayout());

	geometryShader.reset(new directX11::platform::GeometryShader);
	geometryShader->CompileFromFile("./test.fx", "GS_TEST", "gs_4_0");
	directX11::platform::Render::S().GetGeometryShaderManager().SetShader(geometryShader);

	pixelShader.reset(new directX11::platform::PixelShader);
	pixelShader->CompileFromFile("./test.fx", "PS_TEST", "ps_4_0");
	directX11::platform::Render::S().GetPixelShaderManager().SetShader(pixelShader);

	directX11::platform::Render::S().GetVertexShaderManager().SetConstantBuffer(wvpBuffer, 0);
	directX11::platform::Render::S().GetGeometryShaderManager().SetConstantBuffer(wvpBuffer, 0);
	directX11::platform::Render::S().GetPixelShaderManager().SetConstantBuffer(wvpBuffer, 0);
	directX11::platform::Render::S().GetVertexShaderManager().SetConstantBuffer(diffuseBuffer, 1);
	directX11::platform::Render::S().GetGeometryShaderManager().SetConstantBuffer(diffuseBuffer, 1);
	directX11::platform::Render::S().GetPixelShaderManager().SetConstantBuffer(diffuseBuffer, 1);
	directX11::platform::Render::S().GetVertexShaderManager().SetConstantBuffer(timerBuffer, 2);
	directX11::platform::Render::S().GetGeometryShaderManager().SetConstantBuffer(timerBuffer, 2);
	directX11::platform::Render::S().GetPixelShaderManager().SetConstantBuffer(timerBuffer, 2);

	directX11::platform::Render::S().GetVertexShaderManager().SetShaderResource(texture->GetShaderResourceView(), 0);
	directX11::platform::Render::S().GetGeometryShaderManager().SetShaderResource(texture->GetShaderResourceView(), 0);
	directX11::platform::Render::S().GetPixelShaderManager().SetShaderResource(texture->GetShaderResourceView(), 0);

	directX11::platform::Render::S().GetVertexShaderManager().SetSampler(sampler, 0);
	directX11::platform::Render::S().GetGeometryShaderManager().SetSampler(sampler, 0);
	directX11::platform::Render::S().GetPixelShaderManager().SetSampler(sampler, 0);

	directX11::platform::Render::S().GetBlendStateManager().Set(blendState, nullptr);
	directX11::platform::Render::S().GetDepthStencilStateManager().Set(depthStencilState, nullptr);
	directX11::platform::Render::S().GetRasterizerStateManager().Set(rasterizerState);

	directX11::platform::Render::S().GetDepthStencilViewManager().Set(depthTexture->GetDepthStencilView());

	directX11::platform::Render::S().GetVertexBufferManager().Set(vertexBuffer, 0);
	directX11::platform::Render::S().GetIndexBufferManager().Set(indexBuffer);

	directX11::platform::Render::S().GetRenderTargetViewManager().Set(directX11::platform::Device::S().GetBackBuffer()->GetRenderTargetView(), 0);

	D3D11_VIEWPORT v;
	v.MinDepth = 0.0f;
	v.MaxDepth = 1.0f;
	v.TopLeftX = 0;
	v.TopLeftY = 0;
	v.Width = 960;
	v.Height = 540;
	directX11::platform::Device::S().GetDeviceContext()->RSSetViewports(1, &v);


	#ifdef CPOT_ON_WINDOWS
	xaudio::AudioLoadData::S().Regist("test", "./test.wav");
	#else defined CPOT_ON_ANDROID

	#endif
}


//ゲームの更新
void MyGame::Update() {
	
	//ゲーム終了
	#pragma region GameEnd

	if (Input::GetButtonUp(windows::c0)) {
		Config::S().SetGameEnd();
	}

	#pragma endregion


	//サウンド
	#pragma region Audio

	if (Input::GetButtonUp(windows::c1)) {
		voice = ResourceList<AudioVoice>::S().Find("test");
		voice->Play();
	}
	if (Input::GetButtonUp(windows::c6)) {
		voice->Stop();
	}

	if (Input::GetButtonUp(windows::c7)) {
		voice = nullptr;
	}

	
	#pragma endregion


	///*
	//ローダ
	#pragma region Loader

	static cpot::BOOL lLoading = false;

	if (Input::GetButtonUp(windows::c2)) {
		lLoading = true;

		for (u32 i = 0; i < 5; i++) {
			LoaderManager::S().Regist(new LoaderTimer(ToString::Do(i).Get(), 2.0f));
		}
	}

	if (lLoading == true) {
		if (!LoaderManager::S().IsLoading()) {
			lLoading = false;
			CPOT_LOG("FinishLoading");
		}
	}

	#pragma endregion


	//アニメーション
	#pragma region Animation

	if (Input::GetButton(windows::c3)) {
		v.ForwardTime(DeltaTime());
		CPOT_LOG(v.Get());
	}

	#pragma endregion

	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer += DeltaTime() / 4.0f;
	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer = Wrap(timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer, 1.0f);
	//CPOT_LOG(timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer);

	wvpBuffer->Write();
	diffuseBuffer->Write();
	timerBuffer->Write();

	directX11::platform::Render::S().SetToDevice();
	directX11::platform::Render::S().DrawIndexed(6, 0, 0);
	directX11::platform::Render::S().Present();
}


}