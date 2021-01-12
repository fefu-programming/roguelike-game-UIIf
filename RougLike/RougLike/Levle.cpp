#include "Levle.h"

Levle::Levle() : _player(0,0){
	_m.SetSmth(_player);
	for (int i = 0; i < 9; i++) {
		_Enemys.push_back(std::vector<Monster>{});
		_Ammo.push_back(std::vector<Projectile>{});
	}
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
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[i + j * 3] = _Enemys[i + j * 3 + 1];
				_Ammo[i + j * 3] = _Ammo[i + j * 3 + 1];
			}
		}
		break;
	case 3:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[j + 3 * i] = _Enemys[3 + j + 3 * i];
				_Ammo[j + 3 * i] = _Ammo[3 + j + 3 * i];
			}
		}
		break;
	case 4:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[1 -i + j * 3+1] = _Enemys[1 -i + j * 3];
				_Ammo[1 - i + j * 3 + 1] = _Ammo[1 - i + j * 3];
			}
		}
		break;
	default:
		return;
	}
}

void FullRoom(int cube) {

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

		}
	}
}