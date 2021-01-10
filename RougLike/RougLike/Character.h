#pragma once
#include <vector>
#include "Map.h"
#include "Projectile.h"

class Character :public GameObj
{
protected:
	std::vector<Projectile> bullets;
	int _hp,
		_damage,
		_max_hp;

public:
	int GetHp() const;
	int GetDamage() const;
	bool TakeDmg(int dmg);
};

class Princess : public GameObj {
public:
	Princess(int x, int y);
};

class Monster : public Character {
protected:
	int _fild_of_view;
	char choose_direction(Map m) const;
public:
	bool TakeDmg(int dmg);
	void Move(Map m);
};

class Knight : public Character {
public:
	Knight(int x, int y);
	bool Enteract(Map m, char dir);
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