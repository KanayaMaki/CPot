#include <iostream>
#include <fstream>

#include <Windows.h>

#include "Atom/atom.h"

using namespace cpot;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode) {

	std::fstream f;
	f.open("a.txt");

	//もし開けなかったら
	if (!f) {
		//エラー
		return 0;
	}

	BitFlag b;
	b.StandRange(0, 30);

	b = ReverseEndian(b);

	f.write(b.ToString().Get(), 32);

	return 0;
}