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
	int _SetDragons[2];
	int _SetZombie[2];
	int _Width, _Height;
	bool _flag = true;
	bool _IsDrawing = false;
	void Draw();
	char MovePlayr();
	void MoveMap(char dir);
	void MoveArrows();
	void MoveEnem();
	void FullRoom(int cube);
	void SetAllChar();
	std::vector<int> FindEnemy(int x, int y)const;
public:
	Levle();
	bool PlayGame();
};

