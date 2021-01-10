#include "Character.h"
#include "GameObj.h"
#include <vector>
#include <iostream>

std::vector<int> GameObj::GetPos() const {
	return std::vector<int> {_x,_y};
}
char GameObj::GetSym() const {
	return _sym;
}

int Character::GetHp() const {
	return _hp;
}
int Character::GetDamage() const {
	return _damage;
}

bool Character::TakeDmg(int dmg) {
	_hp -= dmg;
	if (_hp < 1) {
		return 1;
	}
	return 0;
}

Wall::Wall(int x, int y) {
	_sym = '#';
	_x = x;
	_y = y;
}

Space::Space(int x, int y) {
	_sym = ' ';
	_x = x;
	_y = y;
}

Space::Space(std::vector<int> cord) {
	_sym = ' ';
	_x = cord[0];
	_y = cord[1];
}

Princess::Princess(int x, int y) {
	_sym = 'P';
	_x = x;
	_y = y;
}

Knight::Knight(int x,int y) {
	_sym = 'K';
	_x = x;
	_y = y;
	_hp = 10;
	_damage = 2;
	_max_hp = 15;
}

void Knight::Shoot() const{

}

bool Knight::Enteract(Map m, char dir) {
	GameObj* Near;
	switch (dir){
	case 1:
		Near = m.GetSmth(_x,_y-1);
		break;
	case 2:
		Near = m.GetSmth(_x + 1, _y);
		break;
	case 3:
		Near = m.GetSmth(_x, _y + 1);
		break;
	case 4:
		Near = m.GetSmth(_x - 1, _y);
		break;
	case 5:
		this->Shoot();
	default:
		return 1;
	}
	char sym = Near->GetSym();
	std::vector<int> cord = Near->GetPos();
	if (sym == ' ') {
		m.SetSmth(_x, _y,new Space(_x,_y));
		_x = cord[0];
		_y = cord[1];
		m.SetSmth(_x,_y,this);
	}
	else if (sym == 'P') {
		return 0;
	}
	else if (sym != '#') {
		std::cout << std::endl << Near->TakeDmg(_damage);
		if (Near->TakeDmg(_damage)) {
			m.SetSmth(cord, new Space(cord[0],cord[1]));
		}
	}
	return 1;
}

char Monster::choose_direction(Map m) const {
	return rand()%4 + 1;
}

bool Monster::TakeDmg(int dmg) {
	_hp -= dmg;
	if (_hp < 1) {
		return 1;
	}
	return 0;
}

void Monster::Move(Map m) {
	char d = this->choose_direction(m);
	GameObj* Near = this;
	switch (d)
	{
	case 1:
		Near = m.GetSmth(_x, _y - 1);
		break;
	case 2:
		Near = m.GetSmth(_x + 1, _y);
		break;
	case 3:
		Near = m.GetSmth(_x, _y + 1);
		break;
	case 4:
		Near = m.GetSmth(_x - 1, _y);
		break;
	default:
		break;
	}
	char sym = Near->GetSym();
	std::vector<int> cord = Near->GetPos();
	if (sym == ' ') {
		m.SetSmth(_x, _y, new Space(_x, _y));
		_x = cord[0];
		_y = cord[1];
		m.SetSmth(_x, _y, this);
	}
	else if (sym == 'K') {
		std::cout << std::endl << Near->TakeDmg(_damage);
		if (Near->TakeDmg(_damage)) {
			m.SetSmth(cord, new Space(cord[0], cord[1]));
		}
	}
}


Zombie::Zombie(int x, int y) {
	_sym = 'Z';
	_x = x;
	_y = y;
	_hp = 5;
}

Dragon::Dragon(int x, int y) {
	_sym = 'D';
	_x = x;
	_y = y;
	_hp = 10;
}

Monster* EnemyFactory(int x, int y) {
	if (rand() % 3 < 2) {
		return new Zombie(x, y);
	}
	else {
		return new Dragon(x, y);
	}
}