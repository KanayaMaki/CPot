//
//	content	:	ライブラリのテストを行う
//	author	:	SaitoYoshiki
//

#include "./Pot/Atom/atom.h"

#include "./test.h"

//Window
#include "./Pot/Window/Windows/windowWindows.h"

//Out
#include "./Pot/Out/out.h"
#include "./Pot/Out/Windows/outDebugWindowWindows.h"
#include "./Pot/Out/Windows/outConsoleWindows.h"

//Rand
#include "./Pot/Rand/rand.h"

//Sleep
#include "./Pot/Sleep/sleep.h"

//Time
#include "./Pot/Time/time.h"

//Vector
#include "./Pot/List/vector.h"

//HashTable
#include "./Pot/List/hashTable.h"

//Thread
#include "./Pot/Thread/thread.h"
#include "./Pot/Thread/mutex.h"

//Input
#include "./Pot/Input\Windows\inputWindows.h"
#include "./Pot/Input\XInput\inputXInput.h"
#include "./Pot/Input\input.h"

//FileOut
#include "./Pot/File\file.h"

//Loader
#include "./Pot/Loader\loader.h"

//Audio
#include "./Pot/Audio\audio.h"

//Animation
#include "./Pot/Animation/animation.h"

//DirectX11
#include "./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/constantBufferDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/vertexBufferDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/indexBufferDirectX11Platform.h"
#include "./Pot/Render/DirectX11/Platform/shaderResourceViewDirectX11Platform.h"
#include "./Pot/Config/config.h"

#include "./Pot/Usefull/path.h"

#include "./Pot/Render/render.h"

#include "./Pot/ModelLoader/PmxLoader.h"
#include "./Pot/ModelLoader/PmxToMesh.h"

#include <Windows.h>

using namespace cpot;


#pragma region Pmx

void TestPmx() {
	PmxLoader pmx;
	pmx.Load("./Miku/miku.pmx");

	StaticMeshModelCPU staticMesh;
	PmxToMesh::Load(staticMesh, pmx.Get());

	SkinMeshModelCPU skinMesh;
	PmxToMesh::Load(skinMesh, pmx.Get());

	for (u32 i = 0; i < skinMesh.submesh.GetSize(); i++) {
		CPOT_LOG(skinMesh.submesh[i].material.texture.name);
	}
}

#pragma endregion


#pragma region Texture

void TestTexture() {

	directX11::Texture2DDirectX11Data::S().Regist("test", "./test.png");

	directX11::ShaderDirectX11Data::S().Regist("test",
	{
		{ "test.fx", "VS_TEST" },
		{ "test.fx", "GS_TEST" },
		{ "test.fx", "PS_TEST" },
	});

	std::shared_ptr<Texture2D> texture;
	texture.reset(new Texture2D);
	texture->Load("test");
	
	std::shared_ptr<Texture2D> renderTarget;
	renderTarget.reset(new Texture2D);
	renderTarget->LoadPlatform(directX11::platform::Device::S().GetBackBuffer());

	std::shared_ptr<Texture2D> depthTexture;
	depthTexture.reset(new Texture2D);
	depthTexture->Load(960, 540, Texture2D::cR32Float, false, true, true);

	std::shared_ptr<Sampler> sampler;
	sampler.reset(new Sampler);
	sampler->Load(Sampler::cClamp);

	std::shared_ptr<Blend> blend;
	blend.reset(new Blend);
	blend->Load(Blend::cNormal);

	std::shared_ptr<DepthStencil> depthStencil;
	depthStencil.reset(new DepthStencil);
	depthStencil->Load(DepthStencil::cTest);

	std::shared_ptr<ConstantBuffer> constantBuffer;
	constantBuffer.reset(new ConstantBuffer);
	constantBuffer->Load(&texture);

	std::shared_ptr<Viewport> viewport;
	viewport.reset(new Viewport);
	viewport->Load(Vector2(0.0f, 0.0f), Vector2(960.0f, 540.0f));

	Vector3 vertexData[20];
	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer);
	vertexBuffer->Load(sizeof(Vector3), 20, vertexData, true);
	vertexBuffer->Write(vertexData);

	u16 indexData[20];
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(new IndexBuffer);
	indexBuffer->Load(IndexBuffer::cU16, 20, IndexBuffer::cTriangleStrip, indexData);
	
	std::shared_ptr<Shader> shader;
	shader.reset(new Shader);
	shader->Load("test");

	std::shared_ptr<Rasterizer> rasterizer;
	rasterizer.reset(new Rasterizer);
	rasterizer->Load(Rasterizer::cSolid, Rasterizer::cCullNone);


	Render::S().SetBlend(blend);
	Render::S().SetRasterizer(rasterizer);
	Render::S().SetDepthStencil(depthStencil);
	Render::S().SetIndexBuffer(indexBuffer);
	Render::S().SetVertexBuffer(vertexBuffer);
	Render::S().SetViewPort(viewport, 0);
	Render::S().SetDepthTexture(depthTexture);
	Render::S().SetTexture2D(texture, 0);
	Render::S().SetSampler(sampler, 0);
	Render::S().SetConstantBuffer(constantBuffer, 0);
	Render::S().SetRenderTexture(renderTarget, 0);
	Render::S().SetShader(shader);

	Render::S().SetToDevice();

	Render::S().DrawIndexed(6, 0);
	Render::S().Present();
}

#pragma endregion


#pragma region DirectX11

void TestDirectX11(HWND aHwnd) {

}

#pragma endregion


#pragma region Animation

void TestAnimation() {
	
	/*
	Animation<Quaternion> v;
	v.Add(0.0f, Quaternion::FromAxis(Vector3(0.0f, 1.0f, 0.0f), ToRad(0.0f)));
	v.Add(2.0f, Quaternion::FromAxis(Vector3(0.0f, 1.0f, 0.0f), ToRad(90.0f)));
	v.Add(4.0f, Quaternion::FromAxis(Vector3(0.0f, 0.0f, 1.0f), ToRad(90.0f)));

	CPOT_LOG(v.Get().ToString());
	for (u32 i = 0; i < 100; i++) {
		v.Forward(4.0f / 100);
		CPOT_LOG(v.Get().ToString());
	}
	//*/

	/*
	Animation<f32> v;
	v.Add(0.0f, 0.0f);
	v.Add(2.0f, 2.0f);
	v.Add(4.0f, 6.0f);
	v.SetIsLoop(true);

	CPOT_LOG(v.Get());
	for (u32 i = 0; i < 100; i++) {
		v.ForwardTime(8.0f / 100);
		CPOT_LOG(v.Get());
	}
	//*/

	/*
	Animation<Vector3*> v;
	v.Add(0.0f, nullptr);
	v.Add(2.0f, (Vector3*)1010);
	v.Add(4.0f, (Vector3*)3030);

	CPOT_LOG((u32)v.Get());
	for (u32 i = 0; i < 100; i++) {
		v.Forward(4.0f / 100);
		CPOT_LOG((u32)v.Get());
	}
	//*/
}

#pragma endregion



#pragma region Audio

void TestAudio() {

	//XAudioの初期化
	xaudio::platform::Device::S().Init();

	xaudio::AudioLoadData::S().Regist("test", "./test.wav");


	/*
	v.Play();

	::Sleep(1000 * 2);

	CPOT_LOG(ToString::Do(v.GetVolume()));

	c.Release();
	CPOT_LOG(ToString::Do(v.IsLoad()));
	//*/
}

#pragma endregion


#pragma region Loader

void TestLoader() {
	LoaderManager::S().Start(4);
	Rand r;
	r.SetSeed(Time().GetUnix());

	for (u32 i = 0; i < 10; i++) {
		//LoaderManager::S().Regist(new LoaderTimer(ToString::Do(i), r.Nextf(2.0f, 5.0f)));
	}
	for (u32 i = 0; i < 10; i++) {
		String<32> lFileName("Hurry");
		lFileName += ToString::Do(i);
		//LoaderManager::S().Regist(new LoaderTimerHurry(lFileName, r.Nextf(2.0f, 5.0f)));
	}


	while (true) {
		LoaderManager::S().Update();

		if (LoaderManager::S().IsLoading() == false) {
			CPOT_LOG("AllIsEnd");
			break;
		}

		::Sleep(16);
	}
}

#pragma endregion


#pragma region File

void TestFileOut() {

	FileOut o;
	if (!o.Open("aa.txt", false, true)) {
		CPOT_LOG("FileOut.Open:Failed");
	}
	Vector4 lData(1.0f, 2.0f, 3.0f, 4.0f);
	Buffer b((const BYTE*)(&lData), sizeof(lData));
	o.Write(b);
}

void TestFileIn() {
	FileIn lIn("aa.txt", true);
	Vector4 lData;
	Buffer b;
	lIn.Read(b);
	b.Read(&lData, sizeof(lData));
	Log::S().Output(lData.ToString());
}

#pragma endregion



#pragma region Output

void TestOutput(HWND aHwnd) {

	#ifdef CPOT_VALID_LOG
	windows::OutConsoleDevice::S().Init(aHwnd);

	auto o = new windows::OutConsole;
	o->Load();
	Log::S().Set(o);
	#endif
}

#pragma endregion


#pragma region Time

void TestDeltaTime() {
	CPOT_LOG("TestDeltaTime");

	CPOT_LOG("DeltaTime:", DeltaTime());
	CPOT_LOG("DeltaTick:", (u64)DeltaTick());

	CPOT_LOG("SetDeltaTime(1.0f / 30.0f)");
	SetDeltaTime(1.0f / 30.0f);

	CPOT_LOG("DeltaTime:", DeltaTime());
	CPOT_LOG("DeltaTick:", (u64)DeltaTick());
}
void TestTick() {

	CPOT_LOG("TestTick");

	CPOT_LOG(2.0f, "=", (u64)(ToTick(2.0f)), "Tick");
	CPOT_LOG(12000000UL, "=", ToSecond(12000000), "Second");
}

void TestDetailTime() {

	CPOT_LOG("TestDetailTime");

	Time lTime;

	cpot::Sleep lSleep;

	f64 lStart, lEnd;
	lStart = lTime.GetDetail();

	lSleep.SleepSecond(2.0f);

	lEnd = lTime.GetDetail();

	CPOT_LOG(lEnd - lStart);	//2.0 is right

}

void TestUnixTime() {
	CPOT_LOG("TestUnixTime");

	Time lTime;

	CPOT_LOG("Time :", lTime.GetUnix());
	CPOT_LOG("Right:", time(nullptr));
}

void TestDateTime() {

	CPOT_LOG("TestDateTime");

	DateTime lDateTime;
	DateTimeData lDate = lDateTime.Get();

	CPOT_LOG("YEAR  :", lDate.year);
	CPOT_LOG("MONTH :", lDate.month);
	CPOT_LOG("DAY   :", lDate.day);
	CPOT_LOG("HOUR  :", lDate.hour);
	CPOT_LOG("MINUTE:", lDate.minute);
	CPOT_LOG("SECOND:", lDate.second);
}

#pragma endregion


#pragma region Vector

void TestVector() {

	Vector<u32> v;
	v.PushBack(32);
	v.PushBack(100);
	v.PushBack(200);
	v.PushBack(200);
	v.PushBack(100);

	for (u32 i = 0; i < v.GetSize(); i++) {
		CPOT_LOG(v[i]);
	}

	CPOT_LOG(v.Count(100));

	u32 a = v.Remove(100);
	CPOT_LOG(a);

	CPOT_LOG(v.Count(100));

	for (u32 i = 0; i < v.GetSize(); i++) {
		CPOT_LOG(v[i]);
	}
}

#pragma endregion


#pragma region HashTable

void TestHashTable() {

	HashTable<s32> hash;

	hash.Add("data1", 43);
	hash.Add("data2", 45);
	hash.Add("data3", 47);
	hash.Add("data4", 49);

	CPOT_LOG(hash.Find("data1"));
}

#pragma endregion


#pragma region Thread

Mutex gMutex;

void* TestMutex(u32* aData) {

	MutexLocker lMl(gMutex);

	for (u32 i = 0; i < 2; i++) {
		CPOT_LOG(i);
	}
	return nullptr;
}

void TestThread() {

	Thread t[10];

	for (u32 i = 0; i < 10; i++) {
		t[i].Start(TestMutex, nullptr);
	}

	for (u32 i = 0; i < 10; i++) {
		t[i].Join();
	}
}

#pragma endregion


#pragma region Rand

void TestRand() {
	Rand r;
	for (u32 i = 0; i < 10; i++) {
		CPOT_LOG(r.Next());
	}
}

#pragma endregion



#pragma region Input

#ifdef CPOT_VALID_INPUT_WINDOWS
void TestInputWindows(HINSTANCE aHInstance, HWND aHwnd) {

	windows::Input::S().Init(aHInstance, aHwnd);

	while (true) {
		windows::Input::S().Update();

		if (windows::Input::S().GetValue(windows::cA) > 0.0f) {
			CPOT_LOG("A");
		}
		if (windows::Input::S().GetValue(windows::CInputCode::cMouseButton1) > 0.0f) {
			CPOT_LOG("MouseClick");
			CPOT_LOG("MouseLocX:", windows::Input::S().GetValue(windows::cMouseCursorX));
			CPOT_LOG("MouseLocY:", windows::Input::S().GetValue(windows::cMouseCursorY));
		}
		
		::Sleep(16);
	}

}
#endif

#ifdef CPOT_VALID_XINPUT
void TestInputXInput() {

	while (true) {
		xInput::Input::S().Update();

		if (xInput::Input::S().GetButtonDown(xInput::cLTrigger) > 0.0f) {
			CPOT_LOG("LStick");
		}

		::Sleep(16);
	}
}
#endif

void TestInputInputWindows(HINSTANCE aHInstance, HWND aHwnd) {

	windows::Input::S().Init(aHInstance, aHwnd);

	while (true) {
		windows::Input::S().Update();

		if (Input::GetButtonDown(windows::cA) > 0.0f) {
			CPOT_LOG("A");
		}
		if (Input::GetValue(windows::cMouseButton1) > 0.0f) {
			CPOT_LOG("MouseClick");
			CPOT_LOG("MouseLocX:",Input::GetValue(windows::cMouseCursorX));
			CPOT_LOG("MouseLocY:", Input::GetValue(windows::cMouseCursorY));
		}

		::Sleep(16);
	}

}

void TestInputInputXInput() {

	while (true) {
		xInput::Input::S().Update();

		if (Input::GetButtonDown(xInput::cLTrigger) > 0.0f) {
			CPOT_LOG("LStick");
		}

		::Sleep(16);
	}
}

#pragma endregion