#pragma once
#include <vector>
#include <iostream>
class GameObj {
protected:
	int _x = -1, _y = -1;
	char _sym = ' ';
public:
	std::vector<int> GetPos() const;
	char GetSym() const;
	virtual bool TakeDmg(int dmg) { std::cout << std::endl << "GmObj"; return 0; };
};

class Wall : public GameObj {
public:
	Wall(int x, int y);
};

class Space : public GameObj {
public:
	Space(int x, int y);
	Space(std::vector<int> cord);
};