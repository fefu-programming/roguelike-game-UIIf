#pragma once
#include "GameObject.h"
#include "Map.h"
class Character :public GameObj {
protected:
	int  _hp, _sword_dmg, _arrows, _arrow_dmg;
public:
	int GetDmg() const;
	int GetHp() const;
	int GetArrowsDmg() const;
	int GetArrows() const;
	bool TakeDmg(int dmg);
};

class Projectile : public GameObj{
	int _dmg;
	bool _fromHero;
public:
	Projectile(int x, int y, int dmg, char dir, bool fromHero = true);
	Projectile(Character parent, char dir);
	int GetDmg() const;
	bool WhosArrow()const;
	char Move(Map m);
};

class Monster :public Character {
protected:
	char GetDir(Map m) const;
public:
	char Move(Map m);
};

class Knight : public Character {
	int _max_hp;
public:
	Knight(int x, int y);
	char Move(Map m, char dir);
	char Shoot(Map m);
};

class Dragon : public Monster {
public:
	Dragon(int x, int y);
};
class Zombie : public Monster {
public:
	Zombie(int x, int y);
};



