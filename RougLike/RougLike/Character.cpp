#include "Character.h"
int Character::GetDmg() const {
	return _sword_dmg;
}


int Character::GetHp() const {
	return _hp;
}

int Character::GetArrows() const {
	return _arrows;
}

Projectile::Projectile(int x, int y, int dmg, char dir, bool fromHero) {
	_x = x;
	_y = y;
	_dmg = dmg;
	_sym = dir;
	_fromHero = fromHero;
}
Projectile::Projectile(GameObj parent, int dmg, char dir) {
	_x = parent.GetPos()[0];
	_y = parent.GetPos()[1];
	_dmg = dmg;
	_sym = dir;
	_fromHero = false;
	if(parent.GetSym() == 'K')
		_fromHero = true;
}

char Monster::GetDir(Character k) const {
	return -1;
}

Knight::Knight(int x, int y) {
	_x = x;
	_y = y;
	_sym = 'K';
	_sword_dmg = findInfConfig("KnightSwordDmg");
	if (_sword_dmg < 1) {
		_sword_dmg = 2;
	}
	_hp = findInfConfig("KnightHp");
	if (_hp < 1) {
		_hp = 10;
	}
	_max_hp = findInfConfig("KnightMaxHP");
	if (_max_hp < 1) {
		_max_hp = 15;
	}
	_arrows = findInfConfig("KnightArrowCounter");
	if (_arrows < 1) {
		_arrows = 20;
	}
	_arrow_dmg = findInfConfig("KnightArrowDmg");
	if (_arrow_dmg < 1) {
		_arrow_dmg = 1;
	}
}

char Knight::Move(Map m, char dir) {
	int x = _x, y = _y;
	switch (dir) {
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	}

	char Near = m.GetSmth(x,y);
	//std::cout << Near;
	if (Near == -1 || Near == '.') {
		_x = x;
		_y = y;
	}
	if (!m.IsInMidle(*this)) {
		return dir;
	}
	return -1;
}

char Knight::Shoot(Map m) {
	char dir,tmp;
	std::cin >> dir;
	int x = _x, y = _y;
	switch (dir)
	{
	case 'w':
		y--;
		break;
	case 'd':
		x++;
		break;
	case 's':
		y++;
		break;
	case 'a':
		x--;
		break;
	}
	tmp = m.GetSmth(x,y);
	if (tmp != -1 && tmp != '#') {
		dir = -1;
	}
	return dir;
}

Dragon::Dragon(int x, int y) {
	_x = x;
	_y = y;
	_sym = 'D';
	_hp = findInfConfig("DragonHp");
	if (_hp < 1) {
		_hp = 8;
	}
	_sword_dmg = findInfConfig("DragonSwordDmg");
	if (_sword_dmg < 1) {
		_sword_dmg = 2;
	}
	_arrow_dmg = findInfConfig("DragonArrowDmg");
	if (_arrow_dmg < 1) {
		_arrow_dmg = 1;
	}
}

Zombie::Zombie(int x, int y) {
	_x = x;
	_y = y;
	_sym = 'Z';
	_hp = findInfConfig("ZombieHp");
	if (_hp < 1) {
		_hp = 5;
	}
	_sword_dmg = findInfConfig("ZombieSwordDmg");
	if (_sword_dmg < 1) {
		_sword_dmg = 1;
	}
	_arrow_dmg = findInfConfig("ZombieArrowDmg");
	if (_arrow_dmg < 1) {
		_arrow_dmg = 0;
	}
}