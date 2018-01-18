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

std::shared_ptr<Texture2D> backBuffer;
std::shared_ptr<Texture2D> backBufferDepth;

std::shared_ptr<Texture2D> renderTarget;
std::shared_ptr<Texture2D> renderTargetDepth;

std::shared_ptr<Blend> blend;
std::shared_ptr<DepthStencil> depthStencil;
std::shared_ptr<DepthStencil> depthStencilNoWrite;
std::shared_ptr<ConstantBuffer> wvpBuffer;
std::shared_ptr<ConstantBuffer> materialBuffer;
std::shared_ptr<ConstantBuffer> otherBuffer;
std::shared_ptr<ConstantBuffer> toonLineBuffer;
std::shared_ptr<Shader> lambertShader;
std::shared_ptr<Shader> toonShader;
std::shared_ptr<Shader> toonLineShader;
std::shared_ptr<Shader> bampShader;

std::shared_ptr<Viewport> viewport;
std::shared_ptr<Rasterizer> rasterizer;
std::shared_ptr<Rasterizer> toonLineRasterizer;

std::shared_ptr<StaticTangentMeshModel> bampModel;
std::shared_ptr<StaticMeshModel> mikuModel;


//
//	スプライトを張り付けられるクラス
//
class SpriteMesh {
public:
	void Load() {
		LoadVertexBuffer();
		LoadIndexBuffer();
	}

	void WriteVertexBuffer() {
		
		//プロジェクション座標での頂点位置に変換
		Quad2D lProjQuad = quad * (Vector2::One() / Config::S().GetScreenSize()) * Vector2().XY(2.0f) - Vector2().XY(1.0f);
		const f32 lProjZLoc = 0.0f;

		//書き込むデータの作成
		StaticMeshVertex lVertex[] {
				{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cLeftBottom)).Z(lProjZLoc), { 0.0f, 0.0f, -1.0f },{ 0.0f, 1.0f } },
				{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cLeftTop)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f } },
				{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cRightBottom)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 1.0f, 1.0f } },
				{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cRightTop)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f } },
		};
		//書き込み
		vertexBuffer->Write(lVertex);
	}

private:
	void LoadVertexBuffer() {
		//頂点座標の初期化
		quad.SetRect(Vector2::Zero(), Config::S().GetScreenSize());

		vertexBuffer = std::make_shared<VertexBuffer>();
		vertexBuffer->Load(sizeof(StaticMeshVertex), 4, nullptr, true);
		WriteVertexBuffer();
	}
	void LoadIndexBuffer() {
		u16 lIndex[]{ 0, 1, 2, 2, 1, 3 };

		indexBuffer = std::make_shared<IndexBuffer>();
		indexBuffer->Load(IndexBuffer::cU16, 6, IndexBuffer::cTriangleList, lIndex);
	}

public:
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;

	Quad2D quad;
};
SpriteMesh sprite;


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

	Rand lRand;
	lRand.SetSeed(Time().GetUnix());

	
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

	directX11::ShaderDirectX11Data::S().Regist("Bamp",
	{
		{ "./bamp.fx", "VS_MAIN" },
		{ "./bamp.fx", "GS_MAIN" },
		{ "./bamp.fx", "PS_MAIN" },
	});

	directX11::ShaderDirectX11Data::S().Regist("Sprite",
	{
		{ "./sprite.fx", "VS_MAIN" },
		{ "./sprite.fx", "GS_MAIN" },
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
	diffuseTexture = ResourceList<Texture2D>::S().Find("Test");

	diffuseSampler.reset(new Sampler);
	diffuseSampler->Load(Sampler::cWrap);
	diffuseSampler->SetName("Diffuse");
	ResourceList<Sampler>::S().Regist(diffuseSampler);

	blend.reset(new Blend);
	blend->Load(Blend::cNormal);
	blend->SetName("Normal");
	ResourceList<Blend>::S().Regist(blend);

	depthStencil.reset(new DepthStencil);
	depthStencil->Load(DepthStencil::cTest);
	depthStencil->SetName("Test");
	ResourceList<DepthStencil>::S().Regist(depthStencil);

	depthStencilNoWrite.reset(new DepthStencil);
	depthStencilNoWrite->Load(DepthStencil::cNoWrite);
	depthStencilNoWrite->SetName("NoWrite");
	ResourceList<DepthStencil>::S().Regist(depthStencilNoWrite);

	viewport.reset(new Viewport);
	viewport->Load(Vector2(0.0f, 0.0f), Config::S().GetScreenSize());

	lambertShader = ResourceList<Shader>::S().Find("Lambert");
	toonShader = ResourceList<Shader>::S().Find("Toon");
	toonLineShader = ResourceList<Shader>::S().Find("ToonLine");
	bampShader = ResourceList<Shader>::S().Find("Bamp");

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
	otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer = 0.0f;

	toonLineBuffer.reset(new ConstantBuffer);
	toonLineBuffer->Load(new ToonLineBuffer);
	toonLineBuffer->SetName("ToonLine");
	ResourceList<ConstantBuffer>::S().Regist(toonLineBuffer);
	toonLineBuffer->GetCPUBuffer<ToonLineBuffer>()->mLineWidth = 2.0f;


	//スプライトデータの作成
	//

	sprite.Load();


	//	PMXの読み込み
	//
	///*
	PmxLoader lPmx;
	//lPmx.Load("./Miku/miku.pmx");
	lPmx.Load("./Alicia/Alicia_solid.pmx");

	StaticMeshModelCPU lMikuModelCPU;
	PmxToMesh::Load(lMikuModelCPU, lPmx.Get());

	mikuModel.reset(new StaticMeshModel);
	ModelCPUToModel::Load(*mikuModel, lMikuModelCPU);

	//*/

	
	//	箱の読み込み
	//
	///*
	StaticTangentMeshModelCPU lBampMeshCPU;
	BufferToMesh::Load(lBampMeshCPU, PathString("./Box/box.pmo"));
	//*/

	bampModel.reset(new StaticTangentMeshModel);
	ModelCPUToModel::Load(*bampModel, lBampMeshCPU);


	planeTransform.mScale = Vector3::One() * 10.0f;

	
	{
		GameObject* lLight = new GameObject;
		lLight->SetName("Light");
		lLight->AddComponent<DirectionalLightComponent>();
		lLight->GetComponent<DirectionalLightComponent>()->SetDirection(-Vector3::One());
	}
	
	{
		GameObject* lPlayer = new GameObject;
		lPlayer->SetName("Player");
		//lPlayer->AddComponent<PlayerComponent>();

		lPlayer->AddComponent<AutoRotateComponent>();
	}

	{
		GameObject* lCamera = new GameObject;
		lCamera->SetName("Camera");

		lCamera->AddComponent<PersCameraComponent>();

		lCamera->GetComponent<PersCameraComponent>()->mPersCamera.SetAspectRatio(Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);
		lCamera->GetTransform().mPosition = Vector3(0.0f, 1.0f, -1.0f) * 40.0f;
		lCamera->GetTransform().mRotation *= Quaternion::FromAxis(lCamera->GetTransform().mRotation.Right(), ToRad(45.0f));

		lCamera->AddComponent("SkyWalkComponent");
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
	mikuRotAnim.ForwardTime(DeltaTime());
	mikuLocAnim.ForwardTime(DeltaTime());
	
	#pragma endregion

	//カーソル移動
	if (Input::GetButton(windows::cL)) {
		windows::Window::S().SetCursorPos(Vector2(100.0f, 100.0f));
	}
	
	//プレイヤーを回転させる
	const f32 cRotateSpeed = ToRad(45.0f);
	if (Input::GetButtonDown(windows::cU)) {
		GameObject::Find("Player")->GetComponent<AutoRotateComponent>()->SetRotateSpeed(Quaternion::FromAxis(Vector3::Up(), cRotateSpeed));
	}
	if (Input::GetButtonDown(windows::cI)) {
		GameObject::Find("Player")->GetComponent<AutoRotateComponent>()->SetRotateSpeed(Quaternion::FromAxis(Vector3::Right(), cRotateSpeed));
	}
	if (Input::GetButtonDown(windows::cO)) {
		GameObject::Find("Player")->GetComponent<AutoRotateComponent>()->SetRotateSpeed(Quaternion::FromAxis(Vector3::Forward(), cRotateSpeed));
	}
	if (Input::GetButtonDown(windows::cP)) {
		GameObject::Find("Player")->GetComponent<AutoRotateComponent>()->SetRotateSpeed(Quaternion::FromAxis(Vector3::Up(), 0.0f));
	}

	auto lCamera = CameraManager::S().GetCamera();
	if (lCamera) {
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = lCamera->GetProjectionMatrix();
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = lCamera->GetViewMatrix();
	}
	auto lLight = LightManager::S().GetDirectionalLight();
	if (lLight) {
		otherBuffer->GetCPUBuffer<OtherBuffer>()->mLightDirection = lLight->GetDirection().Normal();
	}
	
	otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer += DeltaTime() / 4.0f;
	otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer = Wrap(otherBuffer->GetCPUBuffer<OtherBuffer>()->mTimer, 1.0f);

	materialBuffer->Write();
	otherBuffer->Write();

	ResourceList<Texture2D>::S().Find("RenderTarget")->ClearColor(Color::Blue());
	ResourceList<Texture2D>::S().Find("RenderTargetDepth")->ClearDepth(1.0f);

	ResourceList<Texture2D>::S().Find("BackBuffer")->ClearColor(Color::White());
	ResourceList<Texture2D>::S().Find("BackBufferDepth")->ClearDepth(1.0f);

	//PMXの描画
	///*
	//wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4(mikuRotAnim.Get(), mikuLocAnim.Get(), Vector3().XYZ(10.0f));
	//wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4(mikuRotAnim.Get());
	GameObject* lPlayer = GameObject::Find("Player");
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4(lPlayer->GetTransform().mRotation, lPlayer->GetTransform().mPosition);
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4(lPlayer->GetTransform().mRotation);
	wvpBuffer->Write();
	

	/*
	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::Black();
	materialBuffer->Write();

	toonLineBuffer->GetCPUBuffer<ToonLineBuffer>()->mLineWidth = 0.1f;
	toonLineBuffer->Write();

	Render::S().SetBlend(ResourceList<Blend>::S().Find("Normal"));
	Render::S().SetRasterizer(ResourceList<Rasterizer>::S().Find("CullCW"));
	Render::S().SetDepthStencil(ResourceList<DepthStencil>::S().Find("NoWrite"));
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(ResourceList<Texture2D>::S().Find("RenderTargetDepth"));
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("WVP"), 0);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Material"), 1);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Other"), 2);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("ToonLine"), 3);
	Render::S().SetRenderTexture(ResourceList<Texture2D>::S().Find("RenderTarget"), 0);
	Render::S().SetShader(ResourceList<Shader>::S().Find("ToonLine"));

	for (u32 i = 0; i < model->submeshNum; i++) {
		Render::S().SetToDevice();
		Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
	}
	//*/


	//PMXの描画
	//
	/*
	auto model = mikuModel;

	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
	materialBuffer->Write();

	Render::S().SetBlend(ResourceList<Blend>::S().Find("Normal"));
	Render::S().SetRasterizer(ResourceList<Rasterizer>::S().Find("CullCCW"));
	Render::S().SetDepthStencil(ResourceList<DepthStencil>::S().Find("Test"));
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(ResourceList<Texture2D>::S().Find("RenderTargetDepth"));
	Render::S().SetSampler(ResourceList<Sampler>::S().Find("Diffuse"), 0);
	Render::S().SetSampler(ResourceList<Sampler>::S().Find("Diffuse"), 1);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("WVP"), 0);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Material"), 1);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Other"), 2);
	Render::S().SetRenderTexture(ResourceList<Texture2D>::S().Find("RenderTarget"), 0);
	Render::S().SetShader(ResourceList<Shader>::S().Find("Toon"));

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


	//箱の描画
	//
	///*
	auto model = bampModel;

	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
	materialBuffer->Write();

	Render::S().SetBlend(ResourceList<Blend>::S().Find("Normal"));
	Render::S().SetRasterizer(ResourceList<Rasterizer>::S().Find("CullCCW"));
	Render::S().SetDepthStencil(ResourceList<DepthStencil>::S().Find("Test"));
	Render::S().SetVertexBuffer(model->mesh.vertex);
	Render::S().SetIndexBuffer(model->mesh.index);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(ResourceList<Texture2D>::S().Find("RenderTargetDepth"));
	Render::S().SetSampler(ResourceList<Sampler>::S().Find("Diffuse"), 0);
	Render::S().SetSampler(ResourceList<Sampler>::S().Find("Diffuse"), 1);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("WVP"), 0);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Material"), 1);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Other"), 2);
	Render::S().SetRenderTexture(ResourceList<Texture2D>::S().Find("RenderTarget"), 0);
	Render::S().SetShader(ResourceList<Shader>::S().Find("Bamp"));

	//マテリアルごとに描画
	for (u32 i = 0; i < model->submeshNum; i++) {
		Render::S().SetTexture2D(model->submesh[i].material.texture, 0);
		if (model->submesh[i].material.bampTexture->IsLoad()) {
			Render::S().SetTexture2D(model->submesh[i].material.bampTexture, 1);
		}
		else {
			Render::S().SetTexture2D(whiteTexture, 1);
		}
		Render::S().SetToDevice();
		Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
	}
	//*/


	//	バックバッファに、今までのレンダリング結果を描画する
	//
	///*
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4::Unit() * Matrix4x4::FromScale(Vector3::One() * 2.0f);
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4::Unit();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = Matrix4x4::Unit();
	wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = Matrix4x4::Unit();
	wvpBuffer->Write();

	materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
	materialBuffer->Write();

	Render::S().SetBlend(ResourceList<Blend>::S().Find("Normal"));
	Render::S().SetRasterizer(ResourceList<Rasterizer>::S().Find("CullCCW"));
	Render::S().SetDepthStencil(ResourceList<DepthStencil>::S().Find("Test"));
	sprite.quad.SetRectFromCenter(Config::S().GetScreenSize() / 2.0f, Config::S().GetScreenSize() / 2.0f);
	sprite.WriteVertexBuffer();
	Render::S().SetVertexBuffer(sprite.vertexBuffer);
	Render::S().SetIndexBuffer(sprite.indexBuffer);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(ResourceList<Texture2D>::S().Find("BackBufferDepth"));
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("WVP"), 0);
	Render::S().SetConstantBuffer(ResourceList<ConstantBuffer>::S().Find("Material"), 1);
	Render::S().SetRenderTexture(ResourceList<Texture2D>::S().Find("BackBuffer"), 0);
	Render::S().SetShader(ResourceList<Shader>::S().Find("Sprite"));

	Render::S().SetSampler(ResourceList<Sampler>::S().Find("Diffuse"), 0);
	Render::S().SetTexture2D(ResourceList<Texture2D>::S().Find("RenderTarget"), 0);
	//Render::S().SetTexture2D(ResourceList<Texture2D>::S().Find("Test"), 0);
	Render::S().SetToDevice();
	Render::S().DrawIndexed(6, 0);
	//*/


	ComponentSystem::S().Render();

	Render::S().Present();
}


}