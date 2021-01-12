#include "Levle.h"

Levle::Levle() : _player(0, 0) {
	_m.SetSmth(_player);
	_Width = _m.GetWidth();
	_Height = _m.GetHeight();

	//Dragons full
	_SetDragons[0] = findInfConfig("MaxCountDragonsInRoom");
	if (_SetDragons[0] == -1) {
		_SetDragons[0] = 5;
	}
	_SetDragons[1] = findInfConfig("ProcentDragon");
	if (_SetDragons[1] == -1) {
		_SetDragons[1] = 10;
	}
	//Zombie full
	_SetZombie[0] = findInfConfig("MaxCountZombieInRoom");
	if (_SetZombie[0] == -1) {
		_SetZombie[0] = 7;
	}
	_SetZombie[1] = findInfConfig("ProcentZombie");
	if (_SetZombie[1] == -1) {
		_SetZombie[1] = 30;
	}

	for (int i = 0; i < 9; i++) {
		_Enemys.push_back(std::vector<Monster>{});
		_Ammo.push_back(std::vector<Projectile>{});
	}
	for (int i = 0; i < 9; i++) {
		if(i != 4)
			this->FullRoom(i);
	}
	this->SetAllChar();
}

void Levle::Draw(){
	while (_IsDrawing) {

	}
	_IsDrawing = true;
	system("cls");
	std::cout << _message << std::endl;
	_m.Draw(_player.GetPos());
	std::cout << "\nHp: "<<_player.GetHp()<< "  Arrows: " << _player.GetArrows()<<'\n';
	_IsDrawing = false;
}

char Levle::MovePlayr() {
	char dir;
	std::cin >> dir;
	switch (dir)
	{
	case 'w':
		dir = 1;
		break;
	case 'd':
		dir = 2;
		break;
	case 's':
		dir = 3;
		break;
	case 'a':
		dir = 4;
		break;
	default:
		dir = 0;
		break;
	}
	while(_IsDrawing){}
	_IsDrawing = true;
	_m.SetSmth(_player, '.');
	dir = _player.Move(_m,dir);
	
	_m.MoveRoom(dir);
	this->MoveMap(dir);
	_m.SetSmth(_player);
	_IsDrawing = false;
	return -1;
}

void Levle::MoveMap(char dir) {
	switch (dir)
	{
	case 1:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[6 + j - 3*i] = _Enemys[3 + j - 3 * i];
				_Ammo[6 + j - 3 * i] = _Ammo[3 + j - 3 * i];
			}
		}
		for (int i = 0; i < 3; i++) {
			_Enemys[i].clear();
			this->FullRoom(i);
			_Ammo[i].clear();
		}
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[i + j * 3] = _Enemys[i + j * 3 + 1];
				_Ammo[i + j * 3] = _Ammo[i + j * 3 + 1];
			}
		}
		for (int i = 0; i < 3; i++) {
			_Enemys[3*i+2].clear();
			this->FullRoom(3*i+2);
			_Ammo[3*i+2].clear();
		}
		break;
	case 3:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[i*3 + j] = _Enemys[3 + i*3 + j];
				_Ammo[j + 3 * i] = _Ammo[3 + j + 3 * i];
			}
		}
		for (int i = 6; i < 9; i++) {
			_Enemys[i].clear();
			this->FullRoom(i);
			_Ammo[i].clear();
		}
		break;
	case 4:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[1 -i + j * 3+1] = _Enemys[1 -i + j * 3];
				_Ammo[1 - i + j * 3 + 1] = _Ammo[1 - i + j * 3];
			}
		}
		for (int i = 0; i < 3; i++) {
			_Enemys[i*3].clear();
			this->FullRoom(i*3);
			_Ammo[i*3].clear();
		}
		break;
	default:
		return;
	}
	this->SetAllChar();
}

void Levle::FullRoom(int cube) {
	std::vector<int> LeftUpCord = _m.GetCentrCords();

	LeftUpCord[0] *= _Width;
	LeftUpCord[1] *= _Height;
	LeftUpCord[0] -= _Width / 2;
	LeftUpCord[1] -= _Height / 2;

	if (cube%3 == 0) {
		LeftUpCord[0] -= _Width;
	}
	else if (cube%3 == 2) {
		LeftUpCord[0] += _Width;
	}

	if (cube < 3) {
		LeftUpCord[1] -= _Height;
	}
	else if (cube > 5) {
		LeftUpCord[1] += _Height;
	}

 	for (int i = 0; i < _SetDragons[0]; i++) {
		if (rand() % 100 <= _SetDragons[1]) {
			std::vector<int> cords {rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.') {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
			}
			_Enemys[cube].emplace_back(*new Dragon(cords[0],cords[1]));
		}
	}

	for (int i = 0; i < _SetZombie[0]; i++) {
		if (rand() % 100 <= _SetZombie[1]) {
			std::vector<int> cords{ rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.') {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
			}
			_Enemys[cube].emplace_back(*new Zombie(cords[0], cords[1]));
		}
	}
}

bool Levle::PlayGame() {
	//char c;
	while (_flag) {
		this->Draw();
		this->MovePlayr();
		//std::cin >> c;
	}
	return 1;
}

void Levle::SetAllChar() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < _Enemys[i].size(); j++) {
			_m.SetSmth(_Enemys[i][j]);
		}
		for (int j = 0; j < _Ammo[i].size(); j++) {
			_m.SetSmth(_Ammo[i][j]);
		}
	}
	_m.SetSmth(_player);
}