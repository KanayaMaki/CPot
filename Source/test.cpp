#include <iostream>
#include <fstream>

#include <Windows.h>

#include "Atom/atom.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	std::fstream f;
	f.open("a.txt");

	//Ç‡ÇµäJÇØÇ»Ç©Ç¡ÇΩÇÁ
	if (!f) {
		//ÉGÉâÅ[
		return 0;
	}

	cpot::Vector3 r(0.0f, 0.0f, 1.0f);
	cpot::Quaternion q = cpot::Quaternion::FromVectorDistance(cpot::Vector3(0.0f, 0.0f, 1.0f), cpot::Vector3(1.0f, 0.0f, 1.0f));
	r = q.Rotate(r);

	f.write("kokoko", 6);

	return 0;
}