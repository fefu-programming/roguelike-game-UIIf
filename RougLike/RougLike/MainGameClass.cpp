#include "MainGameClass.h"

MainGameClass::MainGameClass(int W, int H , int sW , int sH) {
	_room = *(new Map(W,H,sW,sH));
	_GameIsOn = 1;
	this->Generate();
}

void MainGameClass::Generate() {
	_len_of_enemy = rand() % 10 + 5;
	_Enemys = new Monster*[_len_of_enemy];
	int mapH = _room.GetHeight(), mapW = _room.GetWidth();
	for (int i = 0; i < rand() % 10 + 10; i++) {
		int x = rand() % (mapW-5), y = rand() % (mapH-5);
		if (rand() % 2) {
			for (int j = 0; j < 5; j++) {
				_room.SetSmth(x+j,y,new Wall(x+j,y));
			}
		}
		else {
			for (int j = 0; j < 5; j++) {
				_room.SetSmth(x, y + j, new Wall(x, y+j));
			}
		}
	}

	int x = rand()%(mapW/2)+1, y = mapH/2;
	_Player = new Knight(x,y);
	_room.SetSmth(x,y,_Player);

	for (int i = 0; i < _len_of_enemy; i++) {
		while (_room.GetSmth(x, y)->GetSym() != ' ') {
			x = rand() % mapW/2 + mapW / 2;
			y = rand() % (mapH - 1) + 1;
		}
		_Enemys[i] = (EnemyFactory(x,y));
		_room.SetSmth(x,y,_Enemys[i]);
	}
}

void MainGameClass::Draw() const {
	system("cls");
	std::cout << _message << std::endl;
	_room.Draw(_Player);
	std::cout << "\nHP: " << _Player->GetHp()<<std::endl;
}

void MainGameClass::EnteractPlayer() {
	char dir;
	std::cin >> dir;
	switch (dir) {
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
	case ' ':
		dir = 5;
		break;
	default:
		dir = 0;
	}
	_Player->Enteract(_room,dir);
}

bool MainGameClass::GetGame() const {
	return _GameIsOn;
}