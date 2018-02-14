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
#include "./Pot/ModelLoader/ConvertBufferMesh.h"
#include "./Pot/Render/render.h"

#include "./Pot/Config/config.h"

#include "./Pot/Usefull/path.h"

#include "./Pot/Game/componentSystem.h"
#include "./Cycle/skyWalkComponent.h"
#include "./Cycle/autoRotateComponent.h"
#include "./Cycle/playerComponent.h"
#include "./Cycle/morphComponent.h"
#include "./Pot/Game/cameraComponent.h"
#include "./Pot/Game/lightComponent.h"

#include "./Pot/Game/spriteRenderer.h"
#include "./Pot/Game/staticModelRenderer.h"
#include "./Pot/Game/staticTangentModelRenderer.h"
#include "./Pot/Game/toonModelRenderer.h"

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


std::shared_ptr<AudioVoice> voice;

std::shared_ptr<Texture2D> whiteTexture;
std::shared_ptr<Texture2D> testTexture;
std::shared_ptr<Sampler> diffuseSampler;

std::shared_ptr<Texture2D> backBuffer;
std::shared_ptr<Texture2D> backBufferDepth;

std::shared_ptr<Texture2D> renderTarget;
std::shared_ptr<Texture2D> renderTargetDepth;

std::shared_ptr<Blend> blend;
std::shared_ptr<DepthStencil> depthStencilTest;
std::shared_ptr<DepthStencil> depthStencilNoTest;
std::shared_ptr<DepthStencil> depthStencilNoWrite;
std::shared_ptr<ConstantBuffer> wvpBuffer;
std::shared_ptr<ConstantBuffer> materialBuffer;
std::shared_ptr<ConstantBuffer> otherBuffer;
std::shared_ptr<ConstantBuffer> toonLineBuffer;

std::shared_ptr<Viewport> viewport;
std::shared_ptr<Rasterizer> rasterizer;
std::shared_ptr<Rasterizer> toonLineRasterizer;

Animation<Vector3> positionAnimation;
Animation<Quaternion> rotationAnimation;
bool isAnimation = true;
f32 spriteRotDeg = 0.0f;


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	Vector2 lScreenSize = Vector2(1920.0f, 1080.0f) / 3.0f;
	cpot::Config::S().SetScreenSize(lScreenSize);

	#ifdef CPOT_ON_WINDOWS

	#ifdef CPOT_ON_DIRECTX11
	Config::S().SetTitle("Windows + DirectX11 Game!");
	#elif defined CPOT_ON_OPENGL
	Config::S().SetTitle("Windows + OpenGL Game!");
	#endif

	#elif defined CPOT_ON_LINUX
	Config::S().SetTitle("Linux + OpenGL Game!");
	#endif
}


//ゲームの初期化
void MyGame::Init() {
	//CPOT_LOG("Init!");

	//アニメーションの設定
	rotationAnimation.Add(0.0f, Quaternion::YAxis(ToRad(0.0f)));
	rotationAnimation.Add(3.0f, Quaternion::YAxis(ToRad(0.0f)));
	rotationAnimation.Add(4.0f, Quaternion::YAxis(ToRad(90.0f)));
	rotationAnimation.Add(7.0f, Quaternion::YAxis(ToRad(90.0f)));
	rotationAnimation.Add(8.0f, Quaternion::YAxis(ToRad(180.0f)));
	rotationAnimation.Add(11.0f, Quaternion::YAxis(ToRad(180.0f)));
	rotationAnimation.Add(12.0f, Quaternion::YAxis(ToRad(270.0f)));
	rotationAnimation.Add(15.0f, Quaternion::YAxis(ToRad(270.0f)));
	rotationAnimation.Add(16.0f, Quaternion::YAxis(ToRad(360.0f)));
	rotationAnimation.SetIsLoop(true);

	const f32 cEdgeHalfXLen = 20.0f;
	const f32 cEdgeHalfZLen = 15.0f;
	positionAnimation.Add(0.0f, Vector3(cEdgeHalfXLen, 0.0f, cEdgeHalfZLen));
	positionAnimation.Add(3.0f, Vector3(cEdgeHalfXLen, 0.0f, -cEdgeHalfZLen));
	positionAnimation.Add(4.0f, Vector3(cEdgeHalfXLen, 0.0f, -cEdgeHalfZLen));
	positionAnimation.Add(7.0f, Vector3(-cEdgeHalfXLen, 0.0f, -cEdgeHalfZLen));
	positionAnimation.Add(8.0f, Vector3(-cEdgeHalfXLen, 0.0f, -cEdgeHalfZLen));
	positionAnimation.Add(11.0f, Vector3(-cEdgeHalfXLen, 0.0f, cEdgeHalfZLen));
	positionAnimation.Add(12.0f, Vector3(-cEdgeHalfXLen, 0.0f, cEdgeHalfZLen));
	positionAnimation.Add(15.0f, Vector3(cEdgeHalfXLen, 0.0f, cEdgeHalfZLen));
	positionAnimation.Add(16.0f, Vector3(cEdgeHalfXLen, 0.0f, cEdgeHalfZLen));
	positionAnimation.SetIsLoop(true);


	Rand lRand;
	lRand.SetSeed(Time().GetUnix());

	
	//Loaderのスタート
	LoaderManager::S().Start(2);

	//バックバッファの初期化
	backBuffer.reset(new Texture2D);
	backBuffer->SetName("BackBuffer");
	backBufferDepth.reset(new Texture2D);
	backBufferDepth->SetName("BackBufferDepth");


	#ifdef CPOT_ON_DIRECTX11

	directX11::Texture2DDirectX11Data::S().Regist("Test", "./test.png");
	directX11::Texture2DDirectX11Data::S().Regist("White", "./white.png");

	directX11::ShaderDirectX11Data::S().Regist("Lambert",
	{
		{ "./lambert.fx", "VS_MAIN" },
		{ "", "" },
		{ "./lambert.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("Toon",
	{
		{ "./toon.fx", "VS_MAIN" },
		{ "", "" },
		{ "./toon.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("ToonLine",
	{
		{ "./toonLine.fx", "VS_MAIN" },
		{ "", "" },
		{ "./toonLine.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("Bamp",
	{
		{ "./bamp.fx", "VS_MAIN" },
		{ "", "" },
		{ "./bamp.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("Sprite",
	{
		{ "./sprite.fx", "VS_MAIN" },
		{ "", "" },
		{ "./sprite.fx", "PS_MAIN" },
	});


	backBuffer->LoadPlatform(directX11::platform::Device::S().GetBackBuffer());
	backBufferDepth->Load(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y, Texture2D::cR32Float, false, true, true);

	#elif defined CPOT_ON_OPENGL

	openGL::Texture2DData::S().Regist("Test", "./test.png");
	openGL::Texture2DData::S().Regist("White", "./white.png");

	openGL::platform::InputLayout lInputLayout;
	openGL::platform::InputLayoutElement element[] = {
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticMeshVertex), sizeof(f32) * 0),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticMeshVertex), sizeof(f32) * 3),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 2, sizeof(StaticMeshVertex), sizeof(f32) * 6),
	};
	lInputLayout.Load(element, sizeof(element) / sizeof(element[0]));

	openGL::ShaderData::S().Regist("Lambert",
	{
		{ "lambert.vert" },
		{ "" },
		{ "lambert.frag" },
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

	openGL::ShaderData::S().Regist("Sprite",
	{
		{ "sprite.vert" },
		{ "" },
		{ "sprite.frag" },
		lInputLayout
	});

	openGL::platform::InputLayout lBampInputLayout;
	openGL::platform::InputLayoutElement lBampElement[] = {
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticTangentMeshVertex), sizeof(f32) * 0),	//InPos
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticTangentMeshVertex), sizeof(f32) * 3),	//InNor
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticTangentMeshVertex), sizeof(f32) * 6),	//InTan
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(StaticTangentMeshVertex), sizeof(f32) * 9),	//InBiNor
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 2, sizeof(StaticTangentMeshVertex), sizeof(f32) * 12),	//InTexCoord
	};
	lBampInputLayout.Load(lBampElement, sizeof(lBampElement) / sizeof(lBampElement[0]));

	openGL::ShaderData::S().Regist("Bamp",
	{
		{ "bamp.vert" },
		{ "" },
		{ "bamp.frag" },
		lBampInputLayout
	});

	backBuffer->LoadPlatform();
	backBufferDepth->LoadPlatform();


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	#endif



	ResourceList<Texture2D>::S().Regist(backBuffer);
	ResourceList<Texture2D>::S().Regist(backBufferDepth);


	renderTarget.reset(new Texture2D);
	renderTarget->Load(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y, Texture2D::cRGBA32Float, true, true, false);
	renderTarget->SetName("RenderTarget");
	ResourceList<Texture2D>::S().Regist(renderTarget);

	renderTargetDepth.reset(new Texture2D);
	renderTargetDepth->Load(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y, Texture2D::cR32Float, false, false, true);
	renderTargetDepth->SetName("RenderTargetDepth");
	ResourceList<Texture2D>::S().Regist(renderTargetDepth);

	whiteTexture = ResourceList<Texture2D>::S().Find("White");
	testTexture = ResourceList<Texture2D>::S().Find("Test");

	diffuseSampler.reset(new Sampler);
	diffuseSampler->Load(Sampler::cWrap);
	diffuseSampler->SetName("Diffuse");
	ResourceList<Sampler>::S().Regist(diffuseSampler);

	blend.reset(new Blend);
	blend->Load(Blend::cNormal);
	blend->SetName("Normal");
	ResourceList<Blend>::S().Regist(blend);

	depthStencilTest.reset(new DepthStencil);
	depthStencilTest->Load(DepthStencil::cTest);
	depthStencilTest->SetName("Test");
	ResourceList<DepthStencil>::S().Regist(depthStencilTest);

	depthStencilNoTest.reset(new DepthStencil);
	depthStencilNoTest->Load(DepthStencil::cTest);
	depthStencilNoTest->SetName("NoTest");
	ResourceList<DepthStencil>::S().Regist(depthStencilNoTest);

	depthStencilNoWrite.reset(new DepthStencil);
	depthStencilNoWrite->Load(DepthStencil::cNoWrite);
	depthStencilNoWrite->SetName("NoWrite");
	ResourceList<DepthStencil>::S().Regist(depthStencilNoWrite);

	viewport.reset(new Viewport);
	viewport->Load(Vector2(0.0f, 0.0f), Config::S().GetScreenSize());

	rasterizer.reset(new Rasterizer);
	rasterizer->Load(Rasterizer::cSolid, Rasterizer::cCullCCW);
	rasterizer->SetName("CullCCW");
	ResourceList<Rasterizer>::S().Regist(rasterizer);

	toonLineRasterizer.reset(new Rasterizer);
	toonLineRasterizer->Load(Rasterizer::cSolid, Rasterizer::cCullCW);
	toonLineRasterizer->SetName("CullCW");
	ResourceList<Rasterizer>::S().Regist(toonLineRasterizer);

	wvpBuffer.reset(new ConstantBuffer);
	wvpBuffer->Load(new WVPBuffer);
	wvpBuffer->SetName("WVP");
	ResourceList<ConstantBuffer>::S().Regist(wvpBuffer);

	materialBuffer.reset(new ConstantBuffer);
	materialBuffer->Load(new MaterialBuffer);
	materialBuffer->SetName("Material");
	ResourceList<ConstantBuffer>::S().Regist(materialBuffer);
	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();

	otherBuffer.reset(new ConstantBuffer);
	otherBuffer->Load(new OtherBuffer);
	otherBuffer->SetName("Other");
	ResourceList<ConstantBuffer>::S().Regist(otherBuffer);

	toonLineBuffer.reset(new ConstantBuffer);
	toonLineBuffer->Load(new ToonLineBuffer);
	toonLineBuffer->SetName("ToonLine");
	ResourceList<ConstantBuffer>::S().Regist(toonLineBuffer);
	toonLineBuffer->GetCPUBuffer<ToonLineBuffer>()->mLineWidth = 2.0f;

	{
		GameObject* lLight = new GameObject;
		lLight->SetName("Light");
		lLight->AddComponent<DirectionalLightComponent>();
		lLight->GetComponent<DirectionalLightComponent>()->SetDirection(-Vector3::One());
	}
	
	{
		//	PMXの読み込み
		//
		StaticMeshModelCPU lMikuMeshCPU;
		PathString lFilePath("./Miku/miku.pmo");
		//PathString lFilePath("./Alicia/Alicia_solid.pmx");
		BufferToMesh::Load(lMikuMeshCPU, lFilePath);


		auto mikuModel = std::make_shared<StaticMeshModel>();
		ModelCPUToModel::Load(*mikuModel, lMikuMeshCPU);

		//　ゲームオブジェクトの作成
		//
		GameObject* lObject = new GameObject;
		lObject->SetName("Player");
		lObject->AddComponent<ToonModelRenderer>();
		lObject->GetComponent<ToonModelRenderer>()->model = mikuModel;
		lObject->GetTransform().mPosition = Vector3(10.0f, 0.0f, 0.0f);
	}

	{
		//	箱の読み込み
		//
		StaticMeshModelCPU lMeshCPU;
		PathString lFilePath("./Box/box.pmo");
		BufferToMesh::Load(lMeshCPU, lFilePath);

		auto model = std::make_shared<StaticMeshModel>();
		ModelCPUToModel::Load(*model, lMeshCPU, true);


		//	ゲームオブジェクトの作成
		//
		GameObject* lObject = new GameObject;
		lObject->SetName("Box");
		lObject->AddComponent<StaticModelRenderer>();
		lObject->GetComponent<StaticModelRenderer>()->model = model;


		//Morph
		auto morph = lObject->AddComponent<MorphComponent>();
		morph->mBefore;

		lMeshCPU.LoadVertex(morph->mBefore);
		lMeshCPU.LoadVertex(morph->mAfter);
		lMeshCPU.LoadVertex(morph->mNow);

		for (u32 i = 0; i < lMeshCPU.vertex.GetSize(); i++) {
			morph->mAfter[i].position = ((morph->mAfter[i].position - Vector3(0.0f, 0.0f, 0.0f)).NormalSafe() * 10.0f);
			morph->mAfter[i].normal = morph->mAfter[i].position.NormalSafe();
		}

		morph->mMorphTime.SetIsLoop(true);
		morph->mMorphTime.Add(0.0f, 0.0f);
		morph->mMorphTime.Add(1.0f, 1.0f);
		morph->mMorphTime.Add(1.5f, 1.0f);
		morph->mMorphTime.Add(2.5f, 0.0f);
		morph->mMorphTime.Add(3.0f, 0.0f);


		//Transform
		lObject->GetTransform().mPosition = Vector3(10.0f, 0.0f, 0.0f);
	}

	{
		//	球の読み込み
		//
		StaticTangentMeshModelCPU lBampMeshCPU;
		PathString lFilePath("./Cube/cube.pmo");
		BufferToMesh::Load(lBampMeshCPU, lFilePath);

		auto bampModel = std::make_shared<StaticTangentMeshModel>();
		ModelCPUToModel::Load(*bampModel, lBampMeshCPU);


		//	ゲームオブジェクトの作成
		//
		GameObject* lObject = new GameObject;
		lObject->SetName("Cube");
		lObject->AddComponent<StaticTangentModelRenderer>();
		lObject->GetComponent<StaticTangentModelRenderer>()->model = bampModel;
		lObject->AddComponent<AutoRotateComponent>();
		lObject->GetComponent<AutoRotateComponent>()->SetRotateSpeed(Quaternion::FromAxis(Vector3::Up(), ToRad(-45.0f)));

		lObject->GetTransform().mPosition = Vector3(-10.0f, 0.0f, 0.0f);
	}



	///*
	{
		GameObject* lObject = new GameObject;
		lObject->SetName("Sprite");
		lObject->AddComponent<SpriteRenderer>();
		lObject->GetComponent<SpriteRenderer>()->renderTarget = ResourceList<Texture2D>::S().Find("BackBuffer");
		lObject->GetComponent<SpriteRenderer>()->renderTargetDepth = ResourceList<Texture2D>::S().Find("BackBufferDepth");
		lObject->GetComponent<SpriteRenderer>()->texture = ResourceList<Texture2D>::S().Find("RenderTarget");
	}
	//*/

	/*
	{
		GameObject* lObject = new GameObject;
		lObject->SetName("SkySprite");
		lObject->AddComponent<SpriteRenderer>();
		lObject->GetComponent<SpriteRenderer>()->priority = -5;
		lObject->GetComponent<SpriteRenderer>()->texture = ResourceList<Texture2D>::S().Find("Test");
		lObject->GetComponent<SpriteRenderer>()->sprite.quad.SetRect(Vector2(), Config::S().GetScreenSize() / 2);
	}//*/

	{
		GameObject* lCamera = new GameObject;
		lCamera->SetName("Camera");

		lCamera->AddComponent<PersCameraComponent>();

		lCamera->GetComponent<PersCameraComponent>()->mPersCamera.SetAspectRatio(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);
		lCamera->GetTransform().mPosition = Vector3(0.0f, 1.0f, -1.0f) * 40.0f + Vector3(0.0f, 10.0f, 0.0f);
		lCamera->GetTransform().mRotation *= Quaternion::FromAxis(lCamera->GetTransform().mRotation.Right(), ToRad(45.0f));

		lCamera->AddComponent("SkyWalkComponent");
	}


	#ifdef CPOT_ON_WINDOWS
	xaudio::AudioLoadData::S().Regist("test", "./test.wav");
	#elif defined CPOT_ON_ANDROID

	#endif

	//LoaderManager::S().Regist(new LoaderModel("./Miku/miku.pmx", loadModel));
}


//ゲームの更新
void MyGame::Update() {

	ComponentSystem::S().Update();

	//ゲーム終了
	#pragma region GameEnd

	if (Input::GetButtonDown(cEsc)) {
		Config::S().SetGameEnd();
	}

	#pragma endregion


	//サウンド
	#pragma region Audio

	if (Input::GetButtonDown(c1)) {
		if (!voice) {
			voice = ResourceList<AudioVoice>::S().Find("test");
		}
		voice->Play();
	}
	if (Input::GetButtonDown(c6)) {
		voice->Stop();
	}

	if (Input::GetButtonDown(c7)) {
		voice = nullptr;
	}

	
	#pragma endregion



	///*
	//ローダ
	#pragma region Loader

	static cpot::BOOL lLoading = false;

	if (Input::GetButtonDown(c2)) {
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



	//カーソル移動
	if (Input::GetButton(cL)) {
		//windows::Window::S().SetCursorPos(Vector2(100.0f, 100.0f));
	}


	//スプライトの回転
	if (Input::GetButton(c5)) {
		spriteRotDeg += DeltaTime() * 360.0f / 5.0f;
	}
	else {
		spriteRotDeg = 0.0f;
	}

	GameObject::Find("Sprite")->GetComponent<SpriteRenderer>()->sprite.quad.SetRect(
		Rect2D::FromCenter(Config::S().GetScreenSize() / 2.0f, Config::S().GetScreenSize(), spriteRotDeg));
	


	//ミクのモデルの移動
	GameObject::Find("Player")->GetTransform().mPosition = positionAnimation.Get();
	GameObject::Find("Player")->GetTransform().mRotation = rotationAnimation.Get();

	if (isAnimation) {
		positionAnimation.ForwardTime(DeltaTime());
		rotationAnimation.ForwardTime(DeltaTime());
	}

	//スペースキーが押されたら
	if (Input::GetButton(cSpace)) {
		//アニメーションを止める
		isAnimation = false;
		positionAnimation.SetTime(0.0f);
		rotationAnimation.SetTime(0.0f);
	}

	//もし10秒の倍数の時間なら、アニメーションをスタート
	if (isAnimation == false) {
		DateTimeData d = DateTime().Get();
		if (d.second % 10 == 0) {
			isAnimation = true;
		}
	}
}

void MyGame::Render() {
	//描画するテクスチャのクリア
	#ifdef CPOT_ON_DIRECTX11
	Color lResetColor = Color::Red();
	#elif defined CPOT_ON_OPENGL
	Color lResetColor = Color::Blue();
	#else
	Color lResetColor = Color::White();
	#endif

	ResourceList<Texture2D>::S().Find("RenderTarget")->ClearColor(lResetColor);
	ResourceList<Texture2D>::S().Find("RenderTargetDepth")->ClearDepth(1.0f);

	ResourceList<Texture2D>::S().Find("BackBuffer")->ClearColor(Color::White());
	ResourceList<Texture2D>::S().Find("BackBufferDepth")->ClearDepth(1.0f);

	Render::S().SetViewPort(viewport, 0);

	ComponentSystem::S().Render();

	Render::S().Present();
}


}
