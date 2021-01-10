#pragma once
#include "Map.h"
#include "Character.h"
#include "Projectile.h"
#include <iostream>

class MainGameClass
{
private:
	Map _room;
	Projectile **_flying_stuff;
	Monster** _Enemys;
	Knight *_Player;
	int _len_of_enemy, _len_of_flying_stuff;
	std::string _message;
	bool _GameIsOn;
public:
	MainGameClass(int W = 50, int H = 50, int sW = 40, int sH = 14);
	void Generate();
	void Draw() const;
	void EnteractPlayer();
	bool GetGame() const;
};

