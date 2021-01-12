#include "GameObject.h"
char GameObj::GetSym()const {
	return _sym;
}
std::vector<int> GameObj::GetPos() const {
	return std::vector<int>{_x, _y};
}

int findInfConfig(std::string what) {
	std::ifstream fin("config.txt");
	std::string com;
	int value = -1, len_of_file;
	fin >> len_of_file;
	for (int i = 0; i < len_of_file; i++) {
		fin >> com >> value;
		if (com == what)
			return value;
	}
	return -1;
}
