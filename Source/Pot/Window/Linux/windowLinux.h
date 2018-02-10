//
//	content	:	�E�B���h�E�Y�̃E�B���h�E�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"
#include "./Pot/Out/out.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

namespace cpot {

namespace linux {


class Window : public Singleton<Window> {
	friend class Singleton<Window>;


	//�R���X�g���N�^�Ȃ�
	#pragma region Constructor

private:
	//���[�U�����new�ł����Adelete���ł��Ȃ�
	Window() {
		mSize = Vector2::Zero();
	}
	~Window() {
		
	}

	#pragma endregion


	//������
	#pragma region Load

public:
	void Init(int* argc, char ** argvconst, Vector2& aWindowSize, const CHAR* aCaption) {
		
		glutInitContextVersion(4, 5);
		glutInit(argc, argvconst);

		glutInitWindowPosition(100, 50);
		glutInitWindowSize(aWindowSize.x, aWindowSize.y);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		glutCreateWindow(aCaption);

		glewExperimental = GL_TRUE;
		glewInit();

		CPOT_LOG((const CHAR*)glGetString(GL_VERSION));
	}

	#pragma endregion



	//���삷��
	#pragma region Operate

public:
	//�E�B���h�E�̑傫���̕ύX
	void SetSize(Vector2 aSize) {}
	void SetSize(f32 aWidth, f32 aHeight) {
		SetSize(Vector2(aWidth, aHeight));
	}

	void SetTitle(const CHAR* aTitle) {}


	//�J�[�\���̕\���E��\��
	#pragma region Cursor

	/*
public:
	static void ShowCursor() {
		Cursor::S().Show();
	}
	static void HideCursor() {
		Cursor::S().Hide();
	}
	static BOOL IsShowCursor() {
		Cursor::S().IsShow();
	}

	void SetCursorPos(const Vector2& aCursorPos) {
		Cursor::S().SetClientPos(GetHwnd(), aCursorPos);
	}
	Vector2 GetCursorPos() {
		return Cursor::S().GetClientPos(GetHwnd());
	}
	*/

	#pragma endregion


	//�l���擾����
	#pragma region Getter

public:
	f32 GetWidth() const {
		return mSize.x;
	}
	f32 GetHeight() const {
		return mSize.y;
	}
	Vector2 GetSize() const {
		return mSize;
	}

	#pragma endregion


	//�t�B�[���h
	#pragma region Field

private:
	Vector2 mSize;

	#pragma endregion
};


}

}
