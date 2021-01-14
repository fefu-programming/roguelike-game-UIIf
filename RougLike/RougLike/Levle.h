#pragma once
#include "Map.h"
#include"Character.h"
#include <thread>
#include <time.h>
#include "windows.h"

class Levle
{
private:
	Map _m;
	std::vector<std::vector<Monster>> _Enemys;
	std::vector<std::vector<Projectile>> _Ammo;
	std::vector<std::vector<Stuff>> _Stuff;
	Knight _player;
	std::string _message = "";
	int _SetDragons[2];
	int _SetZombie[2];
	int _SetHeal[2];
	int _SetArrow[2];
	int _SetPrincess[2];
	int _Width, _Height;
	int _HealVal;
	int _ArrowVal;
	bool _flag = true;
	bool _IsDrawing = false;
	bool _IsCalculation = false;
	bool _PlayerShooting = false;
	void Draw();
	char MovePlayr();
	void MoveMap(char dir);
	void MoveArrows();
	void MoveEnem();
	void FullRoom(int cube);
	void SetAllChar();
	void PlayThread();
	void EnemyThread();
	std::vector<int> FindEnemy(int x, int y, int c = 1)const;
public:
	Levle();
	void PlayGame();
};

