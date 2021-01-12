#pragma once
#include "Map.h"
#include"Character.h"
class Levle
{
private:
	Map _m;
	std::vector<std::vector<Monster>> _Enemys;
	std::vector<std::vector<Projectile>> _Ammo;
	Knight _player;
	std::string _message = "";
	bool _flag = true;
	bool _IsDrawing = false;
	void Draw();
	char MovePlayr();
	void MoveMap(char dir);
	void FullRoom(int cube);
	void SetAllChar();
public:
	Levle();
	bool PlayGame();
};

