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

#include "./Pot/ModelLoader/PmxToMesh.h"
#include "./Pot/Render/render.h"
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


std::shared_ptr<Texture2D> texture;
std::shared_ptr<Texture2D> renderTarget;
std::shared_ptr<Texture2D> depthTexture;
std::shared_ptr<Sampler> sampler;
std::shared_ptr<Blend> blend;
std::shared_ptr<DepthStencil> depthStencil;
std::shared_ptr<ConstantBuffer> wvpBuffer;
std::shared_ptr<ConstantBuffer> diffuseBuffer;
std::shared_ptr<ConstantBuffer> timerBuffer;
std::shared_ptr<Viewport> viewport;
std::shared_ptr<VertexBuffer> vertexBuffer;
std::shared_ptr<IndexBuffer> indexBuffer;
std::shared_ptr<Shader> shader;
std::shared_ptr<Rasterizer> rasterizer;


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


	directX11::Texture2DDirectX11Data::S().Regist("test", "./test.png");

	directX11::ShaderDirectX11Data::S().Regist("test",
	{
		{ "test.fx", "VS_TEST" },
		{ "test.fx", "GS_TEST" },
		{ "test.fx", "PS_TEST" },
	});

	texture.reset(new Texture2D);
	texture->Load("test");

	renderTarget.reset(new Texture2D);
	renderTarget->LoadPlatform(directX11::platform::Device::S().GetBackBuffer());

	depthTexture.reset(new Texture2D);
	depthTexture->Load(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y, Texture2D::cR32Float, false, true, true);

	sampler.reset(new Sampler);
	sampler->Load(Sampler::cClamp);
	
	blend.reset(new Blend);
	blend->Load(Blend::cNormal);

	depthStencil.reset(new DepthStencil);
	depthStencil->Load(DepthStencil::cNoTest);

	viewport.reset(new Viewport);
	viewport->Load(Vector2(0.0f, 0.0f), Config::S().GetScreenSize());

	shader.reset(new Shader);
	shader->Load("test");

	rasterizer.reset(new Rasterizer);
	rasterizer->Load(Rasterizer::cSolid, Rasterizer::cCullNone);

	wvpBuffer.reset(new ConstantBuffer);
	wvpBuffer->Load(new WVPBuffer);

	diffuseBuffer.reset(new ConstantBuffer);
	diffuseBuffer->Load(new DiffuseBuffer);
	diffuseBuffer->GetCPUBuffer<DiffuseBuffer>()->mDiffuse = Color::White();

	timerBuffer.reset(new ConstantBuffer);
	timerBuffer->Load(new TimerBuffer);
	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer = 0.0f;

	BasicVertex lVertex[]{
		{ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 1.0f } },
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f } },
		{ { 1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f } },
	};
	vertexBuffer.reset(new VertexBuffer);
	vertexBuffer->Load(sizeof(BasicVertex), 4, lVertex, true);

	u16 lIndex[]{ 0, 1, 2, 2, 1, 3 };
	indexBuffer.reset(new IndexBuffer);
	indexBuffer->Load(IndexBuffer::cU16, 6, IndexBuffer::cTriangleList, lIndex);

	Render::S().SetBlend(blend);
	Render::S().SetRasterizer(rasterizer);
	Render::S().SetDepthStencil(depthStencil);
	Render::S().SetIndexBuffer(indexBuffer);
	Render::S().SetVertexBuffer(vertexBuffer);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(depthTexture);
	Render::S().SetTexture2D(texture, 0);
	Render::S().SetSampler(sampler, 0);
	Render::S().SetConstantBuffer(wvpBuffer, 0);
	Render::S().SetConstantBuffer(diffuseBuffer, 1);
	Render::S().SetConstantBuffer(timerBuffer, 2);
	Render::S().SetRenderTexture(renderTarget, 0);
	Render::S().SetShader(shader);




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

	depthTexture->ClearDepth(1.0f);
	renderTarget->ClearColor(Color::Black().Translate());

	Render::S().SetToDevice();
	Render::S().DrawIndexed(6, 0);
	Render::S().Present();
}


}