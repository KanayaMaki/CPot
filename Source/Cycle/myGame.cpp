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
#include "./Pot/Model/ModelCPUToModel.h"
#include "./Pot/ModelLoader/PmxLoader.h"
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
std::shared_ptr<StaticMeshModel> model;
PersCamera camera;
Vector3 cameraLoc;
Quaternion cameraRot;


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

	renderTarget.reset(new Texture2D);
	depthTexture.reset(new Texture2D);

	#ifdef CPOT_ON_DIRECTX11
	directX11::Texture2DDirectX11Data::S().Regist("test", "./test.png");

	directX11::ShaderDirectX11Data::S().Regist("test",
	{
		{ "test.fx", "VS_TEST" },
		{ "test.fx", "GS_TEST" },
		{ "test.fx", "PS_TEST" },
	});

	renderTarget->LoadPlatform(directX11::platform::Device::S().GetBackBuffer());
	depthTexture->Load(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y, Texture2D::cR32Float, false, true, true);

	#elif defined CPOT_ON_OPENGL

	openGL::Texture2DData::S().Regist("test", "./test.png");

	openGL::platform::InputLayout lInputLayout;
	openGL::platform::InputLayoutElement element[] = {
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticMeshVertex), sizeof(f32) * 0),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticMeshVertex), sizeof(f32) * 3),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 2, sizeof(StaticMeshVertex), sizeof(f32) * 6),
	};
	lInputLayout.Load(element, 3);

	openGL::ShaderData::S().Regist("test",
	{
		{ "test.vert" },
		{ "" },
		{ "test.frag" },
		lInputLayout
	});

	renderTarget->LoadPlatform();
	depthTexture->LoadPlatform();
	#endif


	texture.reset(new Texture2D);
	texture->Load("test");

	sampler.reset(new Sampler);
	sampler->Load(Sampler::cClamp);
	
	blend.reset(new Blend);
	blend->Load(Blend::cNormal);

	depthStencil.reset(new DepthStencil);
	depthStencil->Load(DepthStencil::cTest);

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

	StaticMeshVertex lVertex[]{
		{ { -0.5f, -0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 2.0f } },
		{ { -0.5f, 0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f } },
		{ { 0.5f, -0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f },{ 2.0f, 2.0f } },
		{ { 0.5f, 0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f },{ 2.0f, 0.0f } },
	};
	vertexBuffer.reset(new VertexBuffer);
	vertexBuffer->Load(sizeof(StaticMeshVertex), 4, lVertex, true);

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


	FileIn lFile;
	lFile.Open("./Miku/miku.pmx");
	Buffer lFileBuffer;
	lFile.Read(lFileBuffer);

	PmxLoader lPmx;
	lPmx.Load("./Miku/miku.pmx");

	StaticMeshModelCPU lSkinMeshCPU;
	PmxToMesh::Load(lSkinMeshCPU, lPmx.Get());

	model.reset(new StaticMeshModel);
	ModelCPUToModel::Load(*model, lSkinMeshCPU);

	camera.mProjection.SetAspectRatio(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);
	cameraLoc = Vector3(0.0f, 10.0f, -30.0f);

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


	const f32 rotSpeed = 50.0f;
	if (Input::GetButton(windows::cLeft)) {
		cameraRot *= Quaternion::FromAxis(Vector3::Up(), -ToRad(rotSpeed * DeltaTime()));
	}
	if (Input::GetButton(windows::cRight)) {
		cameraRot *= Quaternion::FromAxis(Vector3::Up(), ToRad(rotSpeed * DeltaTime()));
	}
	if (Input::GetButton(windows::cUp)) {
		cameraRot *= Quaternion::FromAxis(cameraRot.Right(), -ToRad(rotSpeed * DeltaTime()));
	}
	if (Input::GetButton(windows::cDown)) {
		cameraRot *= Quaternion::FromAxis(cameraRot.Right(), ToRad(rotSpeed * DeltaTime()));
	}

	const f32 moveSpeed = 10.0f;
	if (Input::GetButton(windows::cA)) {
		cameraLoc += cameraRot.Left() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cD)) {
		cameraLoc += cameraRot.Right() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cW)) {
		cameraLoc += cameraRot.Forward() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cS)) {
		cameraLoc += cameraRot.Back() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cE)) {
		cameraLoc += cameraRot.Up() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cQ)) {
		cameraLoc += cameraRot.Down() * moveSpeed * DeltaTime();
	}

	camera.mView.SetLocation(cameraLoc);
	camera.mView.SetRotation(cameraRot);
	camera.Update();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = camera.mProjection.GetMatrix();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = camera.mView.GetMatrix();

	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer += DeltaTime() / 4.0f;
	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer = Wrap(timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer, 1.0f);
	//CPOT_LOG(timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer);

	wvpBuffer->Write();
	diffuseBuffer->Write();
	timerBuffer->Write();

	depthTexture->ClearDepth(1.0f);
	renderTarget->ClearColor(Color::Blue());

	/*
	Render::S().SetVertexBuffer(vertexBuffer);
	Render::S().SetIndexBuffer(indexBuffer);
	Render::S().SetTexture2D(texture, 0);
	Render::S().SetToDevice();
	Render::S().DrawIndexed(6, 0);
	//*/

	///*
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	
	for (u32 i = 0; i < model->submeshNum; i++) {
		Render::S().SetTexture2D(model->submesh[i].material.texture, 0);
		Render::S().SetToDevice();
		Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
	}
	//*/

	Render::S().Present();
}


}