#include <iostream>
#include <fstream>

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	std::fstream f;
	f.open("a.txt");

	//Ç‡ÇµäJÇØÇ»Ç©Ç¡ÇΩÇÁ
	if (!f) {
		//ÉGÉâÅ[
		return 0;
	}

	f.write("kokoko", 6);
}