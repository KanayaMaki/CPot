#include <iostream>
#include <fstream>

#include <Windows.h>

#include "Atom/atom.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	std::fstream f;
	f.open("a.txt");

	//�����J���Ȃ�������
	if (!f) {
		//�G���[
		return 0;
	}

	cpot::f32 a = cpot::Sinf(cpot::ToRadian(90.0f));
	a = cpot::ClampRange(a, 0.5f, -0.5f);

	f.write("kokoko", 6);

	return 0;
}