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
struct DiffuseBuffer {
	Color mDiffuse;
};
struct TimerBuffer {
	f32 mTimer;
};

VectorSimple<StaticMeshVertex> lBefore;
VectorSimple<StaticMeshVertex> lAfter;
VectorSimple<StaticMeshVertex> lNow;

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
std::shared_ptr<StaticMeshModel> loadModel;
PersCamera camera;
Vector3 cameraLoc;
Quaternion cameraRot;

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

	camera.mProjection.SetAspectRatio(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);
	cameraLoc = Vector3(30.0f, 45.0f, -30.0f);
	cameraRot = Quaternion::FromAxis(cameraRot.Up(), ToRad(-45.0f));
	cameraRot *= Quaternion::FromAxis(cameraRot.Right(), ToRad(45.0f));
	
	#ifdef CPOT_ON_WINDOWS
	xaudio::AudioLoadData::S().Regist("test", "./test.wav");
	#else defined CPOT_ON_ANDROID

	#endif

	//LoaderManager::S().Regist(new LoaderModel("./Miku/miku.pmx", loadModel));
}


//ゲームの更新
void MyGame::Update() {
	
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
		lNow[i].position = lBefore[i].position * (1.0f - t) + lAfter[i].position * t;
	}
	model->mesh.vertex->Write(&lNow[0]);

	//トランスフォーム
	mikuRotAnim.ForwardTime(DeltaTime());
	mikuLocAnim.ForwardTime(DeltaTime());
	
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

	f32 moveSpeed;
	if (Input::GetButton(windows::cLeftShift)) {
		moveSpeed = 20.0f;
	}
	else {
		moveSpeed = 10.0f;
	}

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

	if (Input::GetButton(windows::cT)) {
		planeTransform.mPosition += Vector3::Up() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cY)) {
		planeTransform.mPosition += Vector3::Down() * moveSpeed * DeltaTime();
	}
	if (Input::GetButton(windows::cG)) {
		planeTransform.mRotation *= Quaternion::FromAxis(Vector3::Right(), ToRad(rotSpeed * DeltaTime()));
	}
	if (Input::GetButton(windows::cH)) {
		planeTransform.mRotation *= Quaternion::FromAxis(Vector3::Right(), -ToRad(rotSpeed * DeltaTime()));
	}


	camera.mView.SetLocation(cameraLoc);
	camera.mView.SetRotation(cameraRot);
	camera.Update();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = camera.mProjection.GetMatrix();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = camera.mView.GetMatrix();

	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer += DeltaTime() / 4.0f;
	timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer = Wrap(timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer, 1.0f);
	//CPOT_LOG(timerBuffer->GetCPUBuffer<TimerBuffer>()->mTimer);

	diffuseBuffer->Write();
	timerBuffer->Write();

	depthTexture->ClearDepth(1.0f);
	renderTarget->ClearColor(Color::Blue());

	///*
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = planeTransform.GetMatrix();
	wvpBuffer->Write();
	Render::S().SetVertexBuffer(vertexBuffer);
	Render::S().SetIndexBuffer(indexBuffer);
	Render::S().SetTexture2D(texture, 0);
	Render::S().SetToDevice();
	Render::S().DrawIndexed(6, 0);
	//*/

	///*
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4(mikuRotAnim.Get(), mikuLocAnim.Get());
	wvpBuffer->Write();
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	
	for (u32 i = 0; i < model->submeshNum; i++) {
		Render::S().SetTexture2D(model->submesh[i].material.texture, 0);
		Render::S().SetToDevice();
		Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
	}
	//*/


	///*
	if (loadModel) {
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4(Quaternion::FromAxis(Vector3::Up(), ToRad(45.0f)), Vector3(20.0f, 0.0f, 0.0f));
		wvpBuffer->Write();
		Render::S().SetVertexBuffer(loadModel->mesh.vertex);
		Render::S().SetIndexBuffer(loadModel->mesh.index);

		for (u32 i = 0; i < loadModel->submeshNum; i++) {
			Render::S().SetTexture2D(loadModel->submesh[i].material.texture, 0);
			Render::S().SetToDevice();
			Render::S().DrawIndexed(loadModel->submesh[i].indexCount, loadModel->submesh[i].indexStartCount);
		}
	}
	//*/


	Render::S().Present();
}


}