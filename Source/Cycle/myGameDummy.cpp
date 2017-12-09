//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"
#include "./Pot/Config/config.h"

#include "./Pot/Render/OpenGL/renderOpenGL.h"

namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}

}

using namespace cpot;

namespace myspc {

struct UniformMatrix {
	ShaderMatrix4x4 mWorld;
	ShaderMatrix4x4 mView;
	ShaderMatrix4x4 mProj;
} mUniformMatrix;

struct TmpData {
	Color mDiffuse;
} mTmpData;

struct Vertex {
	Vector3 loc;
	Vector3 nor;
	Vector2 uv;
};


openGL::platform::Sampler s;
openGL::platform::ArrayBuffer a;
openGL::platform::InputLayout inputLayout;
openGL::platform::ElementArrayBuffer e;
openGL::platform::Blend b;
openGL::platform::Cull c;
openGL::platform::Depth d;
openGL::platform::Stencil stencil;
openGL::platform::Program program;

openGL::platform::Texture2D texture;
openGL::platform::DepthBuffer depthBuffer;
openGL::platform::Texture2D renderTexture;
openGL::platform::UniformBuffer matrix;
openGL::platform::UniformBuffer diffuse;


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	cpot::Config::S().SetScreenSize(cpot::Vector2(960.0f, 540.0f));
	cpot::Config::S().SetTitle("MyGame!");
}

//ゲームの初期化
void MyGame::Init() {

	s.Load(openGL::platform::Sampler::cRepeat);
	openGL::platform::Render::S().GetSamplerManager().Set(&s, 0);

	Vertex lVertex[]{
		{ { -0.5f, -0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f } ,{ 0.0f, 0.0f } },
		{ { -0.5f, 0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f } ,{ 0.0f, 2.0f } },
		{ { 0.5f, -0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f } ,{ 2.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.1f },{ 0.0f, 0.0f, -1.0f } ,{ 2.0f, 2.0f } },
	};
	a.Load(sizeof(Vertex), 4, lVertex);
	openGL::platform::Render::S().GetArrayBufferManager().Set(&a);

	openGL::platform::InputLayoutElement element[] = {
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(Vertex), sizeof(f32) * 0),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 3, sizeof(Vertex), sizeof(f32) * 3),
		openGL::platform::CreateInputLayoutElement(0, GL_FLOAT, 2, sizeof(Vertex), sizeof(f32) * 6),
	};
	inputLayout.Load(element, 3);
	openGL::platform::Render::S().GetInputLayoutManager().SetInputLayout(&inputLayout);

	u16 index[] = {
		0, 1, 2, 2, 1, 3
	};
	e.Load(GL_UNSIGNED_SHORT, 6, index, GL_TRIANGLES);
	openGL::platform::Render::S().GetElementArrayBufferManager().Set(&e);

	mUniformMatrix.mWorld *= Matrix4x4::FromTransform(Vector3(0.5f, 0.0f, 0.0f));
	matrix.Load(&mUniformMatrix);
	openGL::platform::Render::S().GetUniformBufferManager().Set(&matrix, 0);

	mTmpData.mDiffuse = Color::White();
	diffuse.Load(&mTmpData);
	openGL::platform::Render::S().GetUniformBufferManager().Set(&diffuse, 1);

	b.Load(openGL::platform::Blend::cNormal);
	openGL::platform::Render::S().GetBlendManager().Set(&b);

	c.Load(true, GL_CW);
	openGL::platform::Render::S().GetCullManager().Set(&c);

	d.Load(openGL::platform::Depth::cNoTest);
	openGL::platform::Render::S().GetDepthManager().Set(&d);

	stencil.Load();
	openGL::platform::Render::S().GetStencilManager().Set(&stencil);

	program.Load("./test.vert", "", "./test.frag");
	openGL::platform::Render::S().GetProgramManager().Set(&program);

	texture.Load("./wing.bmp");
	//texture.Load("./test.bmp");
	openGL::platform::Render::S().GetTextureManager().Set(&texture, 0);
	
	depthBuffer.Load(960, 540);
	//openGL::platform::Render::S().GetRenderTextureManager().SetDepthBuffer(&depthBuffer);

	renderTexture.Load(960, 540, GL_RGBA, GL_UNSIGNED_BYTE);
}


//ゲームの更新
void MyGame::Update() {

	openGL::platform::Render::S().GetRenderTextureManager().ClearBackBuffer(Color::Black());
	openGL::platform::Render::S().GetRenderTextureManager().ClearBackBuffer(1.0f);

	openGL::platform::Render::S().SetToDevice();

	openGL::platform::Render::S().DrawElement();

	openGL::platform::Render::S().SwapBuffer();
}


}