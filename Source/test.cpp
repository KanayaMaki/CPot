#include <iostream>
#include <fstream>

#include <Windows.h>

#include "Atom/atom.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	std::fstream f;
	f.open("a.txt");

	//もし開けなかったら
	if (!f) {
		//エラー
		return 0;
	}



	f.write("kokoko", 6);

	return 0;
}