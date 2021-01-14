#include "Character.h"
int Character::GetDmg() const {
	return _sword_dmg;
}


int Character::GetHp() const {
	return _hp;
}
int Character::GetArrowsDmg() const {
	return _arrow_dmg;
}

int Character::GetArrows() const {
	return _arrows;
}
bool Character::TakeDmg(int dmg) {
	_hp -= dmg;
	if (_hp <= 0) {
		return 1;
	}
	return 0;
}

Projectile::Projectile(int x, int y, int dmg, char dir, bool fromHero) {
	_x = x;
	_y = y;
	_dmg = dmg;
	_sym = dir;
	_fromHero = fromHero;
}
Projectile::Projectile(Character parent, char dir) {
	_x = parent.GetPos()[0];
	_y = parent.GetPos()[1];
	_dmg = parent.GetArrowsDmg();
	switch (dir)
	{
	case 1:
		_sym = '^';
		_y--;
		break;
	case 2:
		_sym = '>';
		_x++;
		break;
	case 3:
		_sym = 'v';
		_y++;
		break;
	case 4:
		_sym = '<';
		_x--;
		break;
	default:
		_sym = 'o';
		break;
	}
	_fromHero = false;
	if(parent.GetSym() == 'K')
		_fromHero = true;
}

int  Projectile::GetDmg() const {
	return _dmg;
}

bool Projectile::WhosArrow()const {
	return _fromHero;
}

char Projectile::Move(Map m) {
	char res = -1;
	int x = _x;
	int y = _y;
	char Near;
	switch (_sym) {
	case '^':
		y--;
		res = 1;
		break;
	case '>':
		x++;
		res = 2;
		break;
	case 'v':
		y++;
		res = 3;
		break;
	case '<':
		x--;
		res = 4;
		break;
	}
	Near = m.GetSmth(x,y);
	if (Near == 'K' || Near == 'Z' || Near == 'D') {
		res += 4;
	}
	else if (Near == '#' || Near == -1 || Near =='+' || Near == '=' || Near =='P') {
		res = -1;
	}
	_x = x;
	_y = y;
	return res;
}


Stuff::Stuff(int x, int y, char sym) {
	_x = x;
	_y = y;
	_sym = sym;
}

char Monster::GetDir(Map m) const {
	return rand()%4 + 1;
}

char Monster::Move(Map m) {
	char res = -1;
	int x = _x;
	int y = _y;
	char Near;
	char  d = this->GetDir(m);
	switch (d) {
	case 1:
		y--;
		res = 1;
		break;
	case 2:
		x++;
		res = 2;
		break;
	case 3:
		y++;
		res = 3;
		break;
	case 4:
		x--;
		res = 4;
		break;
	case 5:
		y--;
		break;
	case 6:
		x++;
		break;
	case 7:
		y++;
		break;
	case 8:
		x--;
		break;
	}
	if (d > 4 && d < 9) {
		res = d;
		Near = m.GetSmth(x, y);
		if (Near == 'K') {
			res += 4;
		}
	}
	else {
		Near = m.GetSmth(x, y);
		if (Near == -1) {
			res = -1;
		}
		else if (Near == 'K') {
			res = 0;
		}
		else if (Near == '^' || Near == '>' || Near == 'v' || Near == '<') {
			res = 13;
			_x = x;
			_y = y;
		}
		else if(Near != '#' && Near != '+' && Near != '=' && Near != 'P'){
			_x = x;
			_y = y;
		}
	}
	return res;
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
	char toRet = -1;
	char Near = m.GetSmth(x,y);
	//std::cout << Near;
	if (Near == 'Z' || Near == 'D') {
		toRet = 5;
	}
	else if (Near != '#') {
		_x = x;
		_y = y;
		if (!m.IsInMidle(*this)) {
			toRet = dir;
		}
	}
	/*else if (Near == 'Z' || Near == 'D') {
		toRet = 5;
	}*/
	
	return toRet;
}

char Knight::Shoot(Map m) {
	char dir,tmp, toRes;
	std::cin >> dir;
	int x = _x, y = _y;
	switch (dir)
	{
	case 'w':
		y--;
		dir = 1;
		break;
	case 'd':
		x++;
		dir = 2;
		break;
	case 's':
		y++;
		dir = 3;
		break;
	case 'a':
		x--;
		dir = 4;
		break;
	}
	tmp = m.GetSmth(x,y);
	toRes = -1;
	if (tmp == '#' || _arrows < 1) {
		toRes = -1;
	}
	else if (tmp == '.') {
		toRes = dir;
		_arrows--;
	}
	else if (tmp == 'Z' || tmp == 'D') {
		toRes = 4+dir;
		_arrows--;
	}
	return toRes;
}

void Knight::TakeArrow(int a) {
	_arrows += a;
}
void Knight::TakeHp(int h) {
	_hp += h;
	if (_hp > _max_hp) {
		_hp = _max_hp;
	}
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