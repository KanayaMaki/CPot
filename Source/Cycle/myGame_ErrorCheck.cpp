//
//	content	:	�Q�[��
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


//CPOT������������O�̒i�K�ŌĂ΂��B��ʃT�C�Y�Ȃǂ̐ݒ���s��
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


//�Q�[���̏�����
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


//�Q�[���̍X�V
void MyGame::Update() {}

void MyGame::Render() {
	
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program.GetGLNum());

	// �ŏ��̑����o�b�t�@�F���_
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer.GetGLNum());
	glVertexAttribPointer(
		0,                  // ����0�F0�ɓ��ɗ��R�͂���܂���B�������A�V�F�[�_����layout�Ƃ��킹�Ȃ��Ƃ����܂���B
		3,                  // �T�C�Y
		GL_FLOAT,           // �^�C�v
		GL_FALSE,           // ���K���H
		0,                  // �X�g���C�h
		(void*)0            // �z��o�b�t�@�I�t�Z�b�g
	);

	// �O�p�`��`���܂��I
	glDrawArrays(GL_TRIANGLES, 0, 3); // ���_0����n�܂�܂��B���v3�̒��_�ł��B&rarr;1�̎O�p�`�ł��B

	glDisableVertexAttribArray(0);


	Render::S().Present();
}


}
