#include <iostream>
#include <fstream>

int main() {

	std::fstream f;
	f.open("a.txt");

	//もし開けなかったら
	if (!f) {
		//エラー
		return 0;
	}

	f.write("kokoko", 6);
}