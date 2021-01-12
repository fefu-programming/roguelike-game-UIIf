#pragma once
#include "GameObject.h"
#include "Map.h"
class Character :public GameObj {
protected:
	int  _hp, _sword_dmg, _arrows, _arrow_dmg;
public:
	int GetDmg() const;
	int GetHp() const;
	int GetArrows() const;
	virtual void TakeDmg(int dmg) {};
};

class Projectile : public GameObj{
	int _dmg;
	bool _fromHero;
public:
	Projectile(int x, int y, int dmg, char dir, bool fromHero = true);
	Projectile(GameObj parent, int dmg, char dir);
};

class Monster :public Character {
protected:
	char GetDir(Character k) const;
	char Move();
};

class Knight : public Character {
	int _max_hp;
public:
	Knight(int x, int y);
	char Move(Map m, char dir);
	char Shoot(Map m);
};

class Dragon : public Monster {
	Dragon(int x, int y);
};



