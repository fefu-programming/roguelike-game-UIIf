#pragma once
#include <vector>
#include <fstream>

class GameObj {
protected:
	int _x, _y;
	char _sym;
public:
	char GetSym()const;
	std::vector<int> GetPos() const;
};

int findInfConfig(std::string what);