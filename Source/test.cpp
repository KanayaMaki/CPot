#include <iostream>
#include <fstream>

int main() {

	std::fstream f;
	f.open("a.txt");

	//�����J���Ȃ�������
	if (!f) {
		//�G���[
		return 0;
	}

	f.write("kokoko", 6);
}