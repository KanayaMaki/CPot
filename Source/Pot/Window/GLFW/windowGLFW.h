//
//	content	:	�E�B���h�E�Y�̃E�B���h�E�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Thread/mutex.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw3.h>

namespace cpot {

namespace glfw {


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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


		//�E�B���h�E�̍쐬
		mWindow = glfwCreateWindow(
			aWindowSize.x, aWindowSize.y,
			aCaption, nullptr, nullptr);

		if (mWindow == GL_FALSE) {
			CPOT_LOG("�E�B���h�E�̍쐬�Ɏ��s���܂���");
			return;
		}


		//�ύX
		glfwSwapInterval(1);

		//�R���e�L�X�g��L����
		glfwMakeContextCurrent(mWindow);


		//GLEW�̏�����
		glewInit();
	}

	void Final() {
		glfwTerminate();
	}

	#pragma endregion


public:
	BOOL IsClose() {
		return glfwWindowShouldClose(mWindow);
	}

	GLFWwindow* GetWindow() {
		return mWindow;
	}

	//���삷��
	#pragma region Operate

public:
	//�E�B���h�E�̑傫���̕ύX
	void SetSize(Vector2 aSize) {}
	void SetSize(f32 aWidth, f32 aHeight) {
		SetSize(Vector2(aWidth, aHeight));
	}

	void SetTitle(const CHAR* aCaption) {
		glfwSetWindowTitle(mWindow, aCaption);
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
	GLFWwindow* mWindow;

	#pragma endregion
};


}

}
