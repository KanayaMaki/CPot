#include "Pot/Window/Linux/windowLinux.h"
#include "Pot/Linux/gameMain.h"
#include "./Pot/Out/Standard/outStandard.h"

#include "./Pot/Config/config.h"

int main(int argc , char ** argv) {

    //���O�̏o�͐�̏�����
    #ifdef CPOT_VALID_LOG
    cpot::standard::OutStandard lOut;
    cpot::Log::S().Set(&lOut);
    #endif

	//�E�B���h�E�̍쐬
    cpot::Vector2 lDefaultScreenSize(960.0f, 540.0f);
    cpot::Config::S().SetScreenSize(lDefaultScreenSize);
    cpot::Config::S().SetTitle("CPotGame!");
    cpot::GameMain::Setting();

    cpot::Vector2 lScreenSize = cpot::Config::S().GetScreenSize();
    cpot::linux::Window::S().Init(&argc, argv, lScreenSize, cpot::Config::S().GetTitle());


	//�Q�[���̏�����
    cpot::GameMain::GameInit();

	glutIdleFunc(cpot::GameMain::GameUpdate);
	glutDisplayFunc(cpot::GameMain::GameRender);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutMainLoop();

	//�I������
    cpot::GameMain::GameFinal();

    return 0;
}

