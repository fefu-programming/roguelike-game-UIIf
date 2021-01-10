#pragma once
#include <vector>
#include "Map.h"

class Character :public GameObj
{
protected:
	int _hp,
		_damage,
		_max_hp;

public:
	int GetHp() const;
	int GetDamage() const;
	bool TakeDmg(int dmg);
	char Move(Map m);
};

class Princess : public GameObj {
public:
	Princess(int x, int y);
};

class Monster : public Character {
protected:
	int fild_of_view;
	char choose_direction(Map m) const;
	bool TakeDmg(int dmg);
};

class Knight : public Character {
public:
	Knight(int x, int y);
	void Enteract(Map m, char dir);
	void Shoot() const;
};

class Zombie : public Monster {
public:
	Zombie(int x, int y);
};

class Dragon : public Monster {
public:
	Dragon(int x, int y);
};

Monster* EnemyFactory(int x, int y);