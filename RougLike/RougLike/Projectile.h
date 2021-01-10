#pragma once
#include "GameObj.h"
#include "Map.h"

class Projectile:public GameObj
{
protected:
	int _damage;
	char _dir, _arrows[4] = { '^', '>', 'v', '<' };
public:
	Projectile(char d);
	void Move(Map m);
	bool TakeDmg(int dmg);
};

