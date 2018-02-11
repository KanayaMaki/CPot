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

#include "./Pot/Game/spriteRenderer.h"
#include "./Pot/Game/staticTangentModelRenderer.h"
#include "./Pot/Game/toonModelRenderer.h"


namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}

}

using namespace cpot;

namespace myspc {


//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
void MyGame::Setting() {
	Vector2 lScreenSize = Vector2(1920.0f, 1080.0f) / 3.0f;
	cpot::Config::S().SetScreenSize(lScreenSize);

	#ifdef CPOT_ON_DIRECTX11
	Config::S().SetTitle("DirectX11 Game!");
	#elif defined CPOT_ON_OPENGL
	Config::S().SetTitle("OpenGL Game!");
	#endif
}


GLuint VertexArrayID;

openGL::platform::ArrayBuffer arrayBuffer;
openGL::platform::Program program;


//ゲームの初期化
void MyGame::Init() {
	//CPOT_LOG("Init!");

	#ifdef CPOT_ON_OPENGL
	CPOT_LOG((const CHAR*)glGetString(GL_VERSION));
	CPOT_LOG((const CHAR*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	#endif

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	arrayBuffer.Load(sizeof(g_vertex_buffer_data[0]), sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]), g_vertex_buffer_data);


	program.Load("./simple.vert", "", "./simple.frag");
}


//ゲームの更新
void MyGame::Update() {}

void MyGame::Render() {
	
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program.GetGLNum());

	// 最初の属性バッファ：頂点
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer.GetGLNum());
	glVertexAttribPointer(
		0,                  // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
		3,                  // サイズ
		GL_FLOAT,           // タイプ
		GL_FALSE,           // 正規化？
		0,                  // ストライド
		(void*)0            // 配列バッファオフセット
	);

	// 三角形を描きます！
	glDrawArrays(GL_TRIANGLES, 0, 3); // 頂点0から始まります。合計3つの頂点です。&rarr;1つの三角形です。

	glDisableVertexAttribArray(0);


	Render::S().Present();
}


}
