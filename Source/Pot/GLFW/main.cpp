#include "Pot/Window/GLFW/windowGLFW.h"
#include "Pot/GLFW/gameMain.h"

#include "./Pot/Config/config.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")

int main(int argc , char ** argv) {

	//�E�B���h�E�̍쐬
    cpot::Vector2 lDefaultScreenSize(960.0f, 540.0f);
    cpot::Config::S().SetScreenSize(lDefaultScreenSize);
    cpot::Config::S().SetTitle("CPotGame!");
    cpot::GameMain::Setting();

    cpot::Vector2 lScreenSize = cpot::Config::S().GetScreenSize();
    cpot::glfw::Window::S().Init(lScreenSize, cpot::Config::S().GetTitle());


	//�Q�[���̏�����
    cpot::GameMain::GameInit();


	//�Q�[�����[�v
	while (!cpot::glfw::Window::S().IsClose()) {
		cpot::GameMain::GameUpdate();
		cpot::GameMain::GameRender();
	}
    

	//�I������
    cpot::GameMain::GameFinal();
	cpot::glfw::Window::S().Final();

    return 0;
}

