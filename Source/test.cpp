#include <iostream>
#include <fstream>

int main() {

	std::fstream f;
	f.open("a.txt");

	//‚à‚µŠJ‚¯‚È‚©‚Á‚½‚ç
	if (!f) {
		//ƒGƒ‰[
		return 0;
	}

	f.write("kokoko", 6);
}