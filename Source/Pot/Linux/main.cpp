#include "Pot/Window/Linux/windowLinux.h"
#include "Pot/Linux/gameMain.h"

#include "./Pot/Config/config.h"

int main(int argc , char ** argv) {

	//�E�B���h�E�̍쐬
    cpot::Vector2 lDefaultScreenSize(960.0f, 540.0f);
    cpot::Config::S().SetScreenSize(lDefaultScreenSize);
    cpot::Config::S().SetTitle("CPotGame!");
    cpot::GameMain::Setting();

    cpot::Vector2 lScreenSize = cpot::Config::S().GetScreenSize();
    cpot::linux::Window::S().Init(lScreenSize, cpot::Config::S().GetTitle());


	//�Q�[���̏�����
    cpot::GameMain::GameInit();


	//�Q�[�����[�v
	while (glfwGetWindowParam(GLFW_OPENED)) {
		cpot::GameMain::GameUpdate();
		cpot::GameMain::GameRender();
	}
    

	//�I������
    cpot::GameMain::GameFinal();
	cpot::linux::Window::S().Final();

    return 0;
}

