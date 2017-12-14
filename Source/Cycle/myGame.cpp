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

#include "./Pot/Game/componentSystem.h"
#include "./Cycle/skyWalkComponent.h"
#include "./Cycle/autoRotateComponent.h"
#include "./Pot/Game/cameraComponent.h"
#include "./Pot/Game/lightComponent.h"


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



class LoaderModel : public Loader {
public:
	LoaderModel(const CHAR* aFileName, std::shared_ptr<StaticMeshModel>& aResult) : mResult(aResult) {
		mFileName = aFileName;
	}
public:
	void Start() override {
		mModel.reset(new StaticMeshModel);
	}
	void Load() override {
		PmxLoader lPmx;
		lPmx.Load(mFileName.Get());

		StaticMeshModelCPU lSkinMeshCPU;
		PmxToMesh::Load(lSkinMeshCPU, lPmx.Get());

		ModelCPUToModel::Load(*mModel, lSkinMeshCPU, true);
	}
	void Finish() override {
		mResult = mModel;
	}
public:
	String<128> mFileName;
	std::shared_ptr<StaticMeshModel> mModel;
	std::shared_ptr<StaticMeshModel>& mResult;
};


}

using namespace cpot;

namespace myspc {

Animation<f32> mikuMorphAnim;
Animation<Vector3> mikuLocAnim;
Animation<Quaternion> mikuRotAnim;

std::shared_ptr<AudioVoice> voice;

struct WVPBuffer {
	ShaderMatrix4x4 mWorld;
	ShaderMatrix4x4 mView;
	ShaderMatrix4x4 mProjection;
	ShaderMatrix4x4 mNormalWorld;
};
struct MaterialBuffer {
	Color mDiffuse;
};
struct OtherBuffer {
	Vector3 mLightDirection;
	f32 mDummy0;
	f32 mTimer;
	f32 mDummy1[3];
};
struct ToonLineBuffer {
	f32 mLineWidth;
	f32 mDummy0[3];
};

VectorSimple<StaticMeshVertex> lBefore;
VectorSimple<StaticMeshVertex> lAfter;
VectorSimple<StaticMeshVertex> lNow;

std::shared_ptr<Texture2D> whiteTexture;
std::shared_ptr<Texture2D> diffuseTexture;
std::shared_ptr<Sampler> diffuseSampler;

std::shared_ptr<Texture2D> renderTarget;
std::shared_ptr<Texture2D> depthTexture;
std::shared_ptr<Blend> blend;
std::shared_ptr<DepthStencil> depthStencil;
std::shared_ptr<DepthStencil> depthStencilNoWrite;
std::shared_ptr<ConstantBuffer> wvpBuffer;
std::shared_ptr<ConstantBuffer> materialBuffer;
std::shared_ptr<ConstantBuffer> otherBuffer;
std::shared_ptr<ConstantBuffer> toonLineBuffer;
std::shared_ptr<Viewport> viewport;
std::shared_ptr<VertexBuffer> vertexBuffer;
std::shared_ptr<IndexBuffer> indexBuffer;
std::shared_ptr<Shader> lambertShader;
std::shared_ptr<Shader> toonShader;
std::shared_ptr<Shader> toonLineShader;
std::shared_ptr<Rasterizer> rasterizer;
std::shared_ptr<Rasterizer> toonLineRasterizer;
std::shared_ptr<StaticMeshModel> model;
std::shared_ptr<StaticMeshModel> loadModel;

Transform planeTransform;


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	Vector2 lScreenSize = Vector2(960.0f, 540.0f);
	cpot::Config::S().SetScreenSize(lScreenSize);

	#ifdef CPOT_ON_DIRECTX11
	Config::S().SetTitle("DirectX11 Game!");
	#else ifdef CPOT_ON_OPENGL
	Config::S().SetTitle("OpenGL Game!");
	#endif
}

//ゲームの初期化
void MyGame::Init() {
	//CPOT_LOG("Init!");

	
	//Loaderのスタート
	LoaderManager::S().Start(2);

	const f32 lBeforeBalling = 0.5f;
	const f32 lBalling = 0.5f;
	const f32 lAfterBalling = 0.5f;
	const f32 lRolling = 2.0f;
	const f32 lBeforeUnBalling = 0.5f;
	const f32 lUnBalling = 0.5f;
	const f32 lAfterUnBalling = 0.5f;
	const f32 lRotating = 1.0f;
	f32 lTime;

	//ミクのモーフィングのアニメーション
	mikuMorphAnim.SetIsLoop(true);
	lTime = 0.0f;
	mikuMorphAnim.Add(lTime, 0.0f);
	lTime += lBeforeBalling;
	mikuMorphAnim.Add(lTime, 0.0f);
	lTime += lBalling;
	mikuMorphAnim.Add(lTime, 1.0f);
	lTime += lAfterBalling + lRolling + lBeforeBalling;
	mikuMorphAnim.Add(lTime, 1.0f);
	lTime += lUnBalling;
	mikuMorphAnim.Add(lTime, 0.0f);
	lTime += lAfterUnBalling + lRotating;
	mikuMorphAnim.Add(lTime, 0.0f);


	//ミクの移動アニメーション
	mikuLocAnim.SetIsLoop(true);
	lTime = 0.0f;
	mikuLocAnim.Add(lTime, Vector3(0.0f, 0.0f, 20.0f));
	lTime += lBeforeBalling + lBalling + lAfterBalling;
	mikuLocAnim.Add(lTime, Vector3(0.0f, 0.0f, 20.0f));
	lTime += lRolling;
	mikuLocAnim.Add(lTime, Vector3(0.0f, 0.0f, -20.0f));
	lTime += lBeforeUnBalling + lUnBalling + lAfterUnBalling + lRotating + lBeforeBalling + lBalling + lAfterBalling;
	mikuLocAnim.Add(lTime, Vector3(0.0f, 0.0f, -20.0f));
	lTime += lRolling;
	mikuLocAnim.Add(lTime, Vector3(0.0f, 0.0f, 20.0f));
	lTime += lBeforeUnBalling + lUnBalling + lAfterUnBalling + lRotating;
	mikuLocAnim.Add(lTime, Vector3(0.0f, 0.0f, 20.0f));

	//ミクの回転アニメーション
	mikuRotAnim.SetIsLoop(true);
	lTime = 0.0f;
	mikuRotAnim.Add(lTime, Quaternion::XAxis(ToRad(0.0f)));
	lTime += lBeforeBalling + lBalling + lAfterBalling;
	mikuRotAnim.Add(lTime, Quaternion::XAxis(ToRad(0.0f)));
	lTime += lRolling / 2.0f;
	mikuRotAnim.Add(lTime, Quaternion::XAxis(ToRad(180.0f)));
	lTime += lRolling / 2.0f;
	mikuRotAnim.Add(lTime, Quaternion::XAxis(ToRad(360.0f)));
	lTime += lBeforeUnBalling + lUnBalling + lAfterUnBalling;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(0.0f)));
	lTime += lRotating;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(180.0f)));
	lTime += lBeforeBalling + lBalling + lAfterBalling;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(180.0f)));
	lTime += lRolling / 2.0f;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(180.0f)) * Quaternion::XAxis(ToRad(-180.0f)));
	lTime += lRolling / 2.0f;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(180.0f)) * Quaternion::XAxis(ToRad(-360.0f)));
	lTime += lBeforeUnBalling + lUnBalling + lAfterUnBalling;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(180.0f)));
	lTime += lRotating;
	mikuRotAnim.Add(lTime, Quaternion::YAxis(ToRad(360.0f)));

	renderTarget.reset(new Texture2D);
	depthTexture.reset(new Texture2D);

	#ifdef CPOT_ON_DIRECTX11

	directX11::Texture2DDirectX11Data::S().Regist("test", "./test.png");
	directX11::Texture2DDirectX11Data::S().Regist("white", "./white.png");

	directX11::ShaderDirectX11Data::S().Regist("Lambert",
	{
		{ "./lambert.fx", "VS_MAIN" },
		{ "./lambert.fx", "GS_MAIN" },
		{ "./lambert.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("Toon",
	{
		{ "./toon.fx", "VS_MAIN" },
		{ "./toon.fx", "GS_MAIN" },
		{ "./toon.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("ToonLine",
	{
		{ "./toonLine.fx", "VS_MAIN" },
		{ "./toonLine.fx", "GS_MAIN" },
		{ "./toonLine.fx", "PS_MAIN" },
	});


	renderTarget->LoadPlatform(directX11::platform::Device::S().GetBackBuffer());
	depthTexture->Load(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y, Texture2D::cR32Float, false, true, true);

	#elif defined CPOT_ON_OPENGL

	openGL::Texture2DData::S().Regist("test", "./test.png");
	openGL::Texture2DData::S().Regist("white", "./white.png");

	openGL::platform::InputLayout lInputLayout;
	openGL::platform::InputLayoutElement element[] = {
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticMeshVertex), sizeof(f32) * 0),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticMeshVertex), sizeof(f32) * 3),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 2, sizeof(StaticMeshVertex), sizeof(f32) * 6),
	};
	lInputLayout.Load(element, 3);

	openGL::ShaderData::S().Regist("Lambert",
	{
		{ "toon.vert" },
		{ "" },
		{ "toon.frag" },
		lInputLayout
	});

	openGL::ShaderData::S().Regist("Toon",
	{
		{ "toon.vert" },
		{ "" },
		{ "toon.frag" },
		lInputLayout
	});

	openGL::ShaderData::S().Regist("ToonLine",
	{
		{ "toonLine.vert" },
		{ "" },
		{ "toonLine.frag" },
		lInputLayout
	});

	renderTarget->LoadPlatform();
	depthTexture->LoadPlatform();
	#endif

	whiteTexture.reset(new Texture2D);
	whiteTexture->Load("white");

	diffuseTexture.reset(new Texture2D);
	diffuseTexture->Load("test");

	diffuseSampler.reset(new Sampler);
	diffuseSampler->Load(Sampler::cClamp);

	blend.reset(new Blend);
	blend->Load(Blend::cNormal);

	depthStencil.reset(new DepthStencil);
	depthStencil->Load(DepthStencil::cTest);

	depthStencilNoWrite.reset(new DepthStencil);
	depthStencilNoWrite->Load(DepthStencil::cNoWrite);

	viewport.reset(new Viewport);
	viewport->Load(Vector2(0.0f, 0.0f), Config::S().GetScreenSize());

	lambertShader.reset(new Shader);
	lambertShader->Load("Lambert");

	toonShader.reset(new Shader);
	toonShader->Load("Toon");

	toonLineShader.reset(new Shader);
	toonLineShader->Load("ToonLine");

	rasterizer.reset(new Rasterizer);
	rasterizer->Load(Rasterizer::cSolid, Rasterizer::cCullCCW);

	toonLineRasterizer.reset(new Rasterizer);
	toonLineRasterizer->Load(Rasterizer::cSolid, Rasterizer::cCullCW);

	wvpBuffer.reset(new ConstantBuffer);
	wvpBuffer->Load(new WVPBuffer);

	materialBuffer.reset(new ConstantBuffer);
	materialBuffer->Load(new MaterialBuffer);
	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();

	otherBuffer.reset(new ConstantBuffer);
	otherBuffer->Load(new OtherBuffer);
	otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer = 0.0f;

	toonLineBuffer.reset(new ConstantBuffer);
	toonLineBuffer->Load(new ToonLineBuffer);
	toonLineBuffer->GetCPUBuffer<ToonLineBuffer>()->mLineWidth = 2.0f;

	StaticMeshVertex lVertex[]{
		{ { -0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 2.0f } },
		{ { -0.5f, 0.5f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f } },
		{ { 0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 2.0f, 2.0f } },
		{ { 0.5f, 0.5f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 2.0f, 0.0f } },
	};
	vertexBuffer.reset(new VertexBuffer);
	vertexBuffer->Load(sizeof(StaticMeshVertex), 4, lVertex, true);

	u16 lIndex[]{ 0, 1, 2, 2, 1, 3 };
	indexBuffer.reset(new IndexBuffer);
	indexBuffer->Load(IndexBuffer::cU16, 6, IndexBuffer::cTriangleList, lIndex);


	PmxLoader lPmx;
	lPmx.Load("./Miku/miku.pmx");

	StaticMeshModelCPU lSkinMeshCPU;
	PmxToMesh::Load(lSkinMeshCPU, lPmx.Get());

	model.reset(new StaticMeshModel);
	ModelCPUToModel::Load(*model, lSkinMeshCPU, true);

	PmxToMesh::LoadVertex(lBefore, lPmx.Get());
	PmxToMesh::LoadVertex(lNow, lPmx.Get());
	PmxToMesh::LoadVertex(lAfter, lPmx.Get());

	for (u32 i = 0; i < lSkinMeshCPU.vertex.GetSize(); i++) {
		lAfter[i].position = ((lAfter[i].position - Vector3(0.0f, 10.0f, 0.0f)).NormalSafe() * 10.0f) * 0.9f + lAfter[i].position * 0.1f;
	}

	planeTransform.mScale = Vector3::One() * 10.0f;

	{
		GameObject* lCamera = new GameObject;
		lCamera->AddComponent<SkyWalkComponent>();
		lCamera->AddComponent<PersCameraComponent>();

		lCamera->GetComponent<PersCameraComponent>()->mPersCamera.SetAspectRatio(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);
		lCamera->GetTransform().mPosition = Vector3(30.0f, 45.0f, -30.0f);
		lCamera->GetTransform().mRotation = Quaternion::FromAxis(lCamera->GetTransform().mRotation.Up(), ToRad(-45.0f));
		lCamera->GetTransform().mRotation *= Quaternion::FromAxis(lCamera->GetTransform().mRotation.Right(), ToRad(45.0f));
	}

	{
		GameObject* lLight = new GameObject;
		lLight->AddComponent<DirectionalLightComponent>();
		lLight->GetComponent<DirectionalLightComponent>()->SetDirection(-Vector3::One());

		lLight->AddComponent<AutoRotateComponent>();
		lLight->GetComponent<AutoRotateComponent>()->SetRotateSpeed(Quaternion::FromAxis(Vector3::Up(), ToRad(90.0f)));
	}
	
	#ifdef CPOT_ON_WINDOWS
	xaudio::AudioLoadData::S().Regist("test", "./test.wav");
	#else defined CPOT_ON_ANDROID

	#endif

	//LoaderManager::S().Regist(new LoaderModel("./Miku/miku.pmx", loadModel));
}


//ゲームの更新
void MyGame::Update() {
	
	ComponentSystem::S().Update();

	//ゲーム終了
	#pragma region GameEnd

	if (Input::GetButtonDown(windows::cEsc)) {
		Config::S().SetGameEnd();
	}

	#pragma endregion


	//サウンド
	#pragma region Audio

	if (Input::GetButtonDown(windows::c1)) {
		if (!voice) {
			voice = ResourceList<AudioVoice>::S().Find("test");
		}
		voice->Play();
	}
	if (Input::GetButtonDown(windows::c6)) {
		voice->Stop();
	}

	if (Input::GetButtonDown(windows::c7)) {
		voice = nullptr;
	}

	
	#pragma endregion


	///*
	//ローダ
	#pragma region Loader

	static cpot::BOOL lLoading = false;

	if (Input::GetButtonDown(windows::c2)) {
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

	//モーフ
	mikuMorphAnim.ForwardTime(DeltaTime());
	for (u32 i = 0; i < lNow.GetSize(); i++) {
		f32 t = mikuMorphAnim.Get();
		lNow[i].position = Lerp(lBefore[i].position, lAfter[i].position, t);
	}
	//model->mesh.vertex->Write(&lNow[0]);

	//トランスフォーム
	//mikuRotAnim.ForwardTime(DeltaTime());
	//mikuLocAnim.ForwardTime(DeltaTime());
	
	#pragma endregion


	auto lCamera = CameraManager::S().GetCamera();
	if (lCamera) {
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = lCamera->GetProjectionMatrix();
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = lCamera->GetViewMatrix();
	}
	auto lLight = LightManager::S().GetDirectionalLight();
	if (lLight) {
		otherBuffer->GetCPUBuffer<OtherBuffer>()->mLightDirection = lLight->GetDirection();
	}
	
	otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer += DeltaTime() / 4.0f;
	otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer = Wrap(otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer, 1.0f);

	materialBuffer->Write();
	otherBuffer->Write();

	depthTexture->ClearDepth(1.0f);
	renderTarget->ClearColor(Color::Blue());

	///*
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = planeTransform.GetMatrix();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4(planeTransform.mRotation);
	wvpBuffer->Write();

	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
	materialBuffer->Write();

	Render::S().SetBlend(blend);
	Render::S().SetRasterizer(rasterizer);
	Render::S().SetDepthStencil(depthStencil);
	Render::S().SetVertexBuffer(vertexBuffer);
	Render::S().SetIndexBuffer(indexBuffer);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(depthTexture);
	Render::S().SetConstantBuffer(wvpBuffer, 0);
	Render::S().SetConstantBuffer(materialBuffer, 1);
	Render::S().SetConstantBuffer(otherBuffer, 2);
	Render::S().SetRenderTexture(renderTarget, 0);
	Render::S().SetShader(toonShader);

	Render::S().SetSampler(diffuseSampler, 0);
	Render::S().SetSampler(diffuseSampler, 1);
	Render::S().SetTexture2D(diffuseTexture, 0);
	Render::S().SetTexture2D(whiteTexture, 1);
	Render::S().SetToDevice();
	Render::S().DrawIndexed(6, 0);
	//*/


	//PMXの描画
	///*
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4(mikuRotAnim.Get(), mikuLocAnim.Get());
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4(mikuRotAnim.Get());
	wvpBuffer->Write();
	

	///*
	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::Black();
	materialBuffer->Write();

	toonLineBuffer->GetCPUBuffer<ToonLineBuffer>()->mLineWidth = 0.1f;
	toonLineBuffer->Write();

	Render::S().SetBlend(blend);
	Render::S().SetRasterizer(toonLineRasterizer);
	Render::S().SetDepthStencil(depthStencilNoWrite);
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(depthTexture);
	Render::S().SetConstantBuffer(wvpBuffer, 0);
	Render::S().SetConstantBuffer(materialBuffer, 1);
	Render::S().SetConstantBuffer(otherBuffer, 2);
	Render::S().SetConstantBuffer(toonLineBuffer, 3);
	Render::S().SetRenderTexture(renderTarget, 0);
	Render::S().SetShader(toonLineShader);

	for (u32 i = 0; i < model->submeshNum; i++) {
		Render::S().SetToDevice();
		Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
	}
	//*/

	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
	materialBuffer->Write();

	Render::S().SetBlend(blend);
	Render::S().SetRasterizer(rasterizer);
	Render::S().SetDepthStencil(depthStencil);
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(depthTexture);
	Render::S().SetSampler(diffuseSampler, 0);
	Render::S().SetSampler(diffuseSampler, 1);
	Render::S().SetConstantBuffer(wvpBuffer, 0);
	Render::S().SetConstantBuffer(materialBuffer, 1);
	Render::S().SetConstantBuffer(otherBuffer, 2);
	Render::S().SetRenderTexture(renderTarget, 0);
	Render::S().SetShader(toonShader);

	for (u32 i = 0; i < model->submeshNum; i++) {
		Render::S().SetTexture2D(model->submesh[i].material.texture, 0);
		if (model->submesh[i].material.toonTexture->IsLoad()) {
			Render::S().SetTexture2D(model->submesh[i].material.toonTexture, 1);
		}
		else {
			Render::S().SetTexture2D(whiteTexture, 1);
		}
		Render::S().SetToDevice();
		Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
	}

	//*/


	ComponentSystem::S().Render();

	Render::S().Present();
}


}