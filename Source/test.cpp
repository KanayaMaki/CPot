#include <iostream>
#include <fstream>

#include <Windows.h>

#include "Atom/atom.h"

using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	std::fstream f;
	f.open("a.txt");

	//Ç‡ÇµäJÇØÇ»Ç©Ç¡ÇΩÇÁ
	if (!f) {
		//ÉGÉâÅ[
		return 0;
	}

	BitFlag b;
	b.StandRange(0, 30);
	f.write(b.ToString().Get(), 32);

	return 0;
}