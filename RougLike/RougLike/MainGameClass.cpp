#include "MainGameClass.h"

MainGameClass::MainGameClass(int W, int H , int sW , int sH) {
	_room = *(new Map(W,H,sW,sH));
	_GameIsOn = 1;
	this->Generate();
}

void MainGameClass::Generate() {
	_len_of_enemy = rand() % 10 + 5;
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
		_Enemys.push_back(EnemyFactory(x,y));
		_room.SetSmth(x,y,_Enemys[i]);
	}
	while (_room.GetSmth(x, y)->GetSym() != ' ') {
		x = rand() % mapW / 2 + mapW / 2;
		y = rand() % (mapH - 1) + 1;
	}
	_room.SetSmth(x,y,new Princess(x,y));
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
	_GameIsOn = _Player->Enteract(_room,dir);
	for (int i = 0; i < _Enemys.size(); i++) {
		if (!_Enemys[i]->GetHp() < 0) {
			_Enemys.erase(_Enemys.begin() + i);
			i--;
		}
	}
}

void MainGameClass::MoveEnemy() {
	for (int i = 0; i < _Enemys.size(); i++) {
		_Enemys[i]->Move(_room);
	}
}

bool MainGameClass::GetGame() const {
	return _GameIsOn;
}

int MainGameClass::GetHp() const{
	return _Player->GetHp();
}

void MainGameClass::DrawWin() const{
	this->Draw();
	std::cout << std::endl;
	for(int i = 0; i < 10; i++)
		std::cout << "You save the princess\n";
}

void MainGameClass::DrawLose() const {
	this->Draw();
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << "Oh NOOO, MY PRINCESS COLECTION!!!\n";
}