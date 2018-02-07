//
//	content	:	�E�B���h�E�Y�̃E�B���h�E�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"

#include <GL/glew.h>
#include <GL/glfw.h>

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
	void Init(Vector2& aWindowSize, const CHAR* aCaption) {
		
		int lResult;	//�߂�l�p

		//GLFW�̏�����
		lResult = glfwInit();
		if (lResult == GL_FALSE) {
			CPOT_LOG("GLFW�̏������Ɏ��s���܂���");
			return;
		}


		//�g�p����OpenGL�̃o�[�W�����̐ݒ�
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 5);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwOpenWindowHint(GLFW_RESIZABLE, GL_FALSE);


		//�E�B���h�E�̍쐬
		mWindow = glfwOpenWindow(
			aWindowSize.x, aWindowSize.y,
			8, 8, 8,
			8,
			0,
			0,
			GLFW_WINDOW);

		if (mWindow == GL_FALSE) {
			CPOT_LOG("�E�B���h�E�̍쐬�Ɏ��s���܂���");
			return;
		}


		//�ύX
		glfwSwapInterval(1);
		glfwSetWindowTitle(aCaption);

		//�R���e�L�X�g��L����
		glfwMakeContextCurrent(mWindow);


		//GLEW�̏�����
		glewInit();
	}

	void Final() {
		glfwTerminate();
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

	void SetTitle(const CHAR* aCaption) {
		glfwSetWindowTitle(aCaption);
	}


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
	int mWindow;

	#pragma endregion
};


}

}
