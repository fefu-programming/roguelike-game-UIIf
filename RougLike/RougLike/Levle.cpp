#include "Levle.h"
#include <time.h> 

Levle::Levle() : _player(0, 0) {
	srand(time(NULL));
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

	//SetHeal
	_SetHeal[0] = findInfConfig("MaxCountHealInRoom");
	if (_SetHeal[0] == -1) {
		_SetHeal[0] = 5;
	}
	_SetHeal[1] = findInfConfig("ProcentHeal");
	if (_SetHeal[1] == -1) {
		_SetHeal[1] = 20;
	}
	_HealVal = findInfConfig("HealValue");
	if (_HealVal == -1) {
		_HealVal = 3;
	}
	//SetArrow
	_SetArrow[0] = findInfConfig("MaxCountArrowInRoom");
	if (_SetArrow[0] == -1) {
		_SetArrow[0] = 5;
	}
	_SetArrow[1] = findInfConfig("ProcentArrow");
	if (_SetArrow[1] == -1) {
		_SetArrow[1] = 20;
	}
	_ArrowVal = findInfConfig("ArrowValue");
	if (_ArrowVal == -1) {
		_ArrowVal = 3;
	}
	//SetPrincess
	_SetPrincess[0] = findInfConfig("MaxCountPrincessInRoom");
	if (_SetPrincess[0] == -1) {
		_SetPrincess[0] = 1;
	}
	_SetPrincess[1] = findInfConfig("ProcentPrincess");
	if (_SetPrincess[1] == -1) {
		_SetPrincess[1] = 5;
	}

	for (int i = 0; i < 9; i++) {
		_Enemys.push_back(std::vector<Monster>{});
		_Ammo.push_back(std::vector<Projectile>{});
		_Stuff.push_back(std::vector<Stuff>{});
	}
	for (int i = 0; i < 9; i++) {
		if(i != 4)
			this->FullRoom(i);
	}
	this->SetAllChar();
}

void Levle::Draw(){
	while (_IsDrawing) {
		return;
	}
	_IsDrawing = true;
	system("cls");
	std::cout << _message << std::endl;
	_m.Draw(_player.GetPos());
	std::cout << "\nHp: "<<_player.GetHp()<< "  Arrows: " << _player.GetArrows()<<'\n';
	_IsDrawing = false;
}

char Levle::MovePlayr() {
	char dir  = -1, resOfAction;
	//std::cin >> dir;
	//dir = 'd';
	/*switch (dir)
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
	case 'k':
		dir = 5;
		break;
	default:
		dir = 0;
		break;
	}*/

	if (GetKeyState('W') & 0x8000)
	{
		dir = 1;
	}
	if (GetKeyState('D') & 0x8000)
	{
		dir = 2;
	}
	if (GetKeyState('S') & 0x8000)
	{
		dir = 3;
	}
	if (GetKeyState('A') & 0x8000)
	{
		dir = 4;
	}
	if (GetKeyState('K') & 0x8000)
	{
		_PlayerShooting = true;
	}
	//std::cout << int(dir) << '\n';
	if (dir == -1) {
		return 1;
	}
	while (_IsCalculation) { return 1; }
	_IsCalculation = true;
	if (_flag) {
		this->MoveArrows();
		if (!_PlayerShooting) {
			_m.SetSmth(_player, '.');
			resOfAction = _player.Move(_m, dir);
			if (resOfAction < 5) {
				_m.MoveRoom(resOfAction);
				this->MoveMap(resOfAction);
				std::vector<int> Stf = _player.GetPos();
				Stf = this->FindEnemy(Stf[0],Stf[1],2);
				if (Stf[1] != -1) {
					char tmp = _Stuff[Stf[0]][Stf[1]].GetSym();
					if (tmp == '+') {
						_player.TakeHp(_HealVal);
					}
					if (tmp == '=') {
						_player.TakeArrow(_ArrowVal);
					}
					if (tmp == 'P') {
						_flag = false;
					}
					_Stuff[4].erase(_Stuff[4].begin() + Stf[1]);
				}
				//std::cout << _player.GetPos()[0] << ' ' << _player.GetPos()[1] <<' '<<Stf[1] << '\n';
				_m.SetSmth(_player);
			}
			else if (resOfAction == 5) {
				std::vector<int> Enem = _player.GetPos();
				std::vector<int> EnemInVect;
				switch (dir) {
				case 1:
					Enem[1]--;
					break;
				case 2:
					Enem[0]++;
					break;
				case 3:
					Enem[1]++;
					break;
				case 4:
					Enem[0]--;
					break;
				}
				EnemInVect = this->FindEnemy(Enem[0], Enem[1]);
				if (EnemInVect[1] != -1 && _Enemys[EnemInVect[0]][EnemInVect[1]].TakeDmg(_player.GetDmg())) {
					_Enemys[EnemInVect[0]].erase(_Enemys[EnemInVect[0]].begin() + EnemInVect[1]);
					_m.SetSmth(Enem[0], Enem[1], '.');
				}
			}
			_m.SetSmth(_player);
		}
		else {
			resOfAction = _player.Shoot(_m,dir);
			_PlayerShooting = false;
			if (resOfAction != -1) {
				std::vector<int> Enem = _player.GetPos();
				switch (resOfAction) {
				case 1:
					Enem[1]--;
					break;
				case 2:
					Enem[0]++;
					break;
				case 3:
					Enem[1]++;
					break;
				case 4:
					Enem[0]--;
					break;
				case 5:
					Enem[1]--;
					break;
				case 6:
					Enem[0]++;
					break;
				case 7:
					Enem[1]++;
					break;
				case 8:
					Enem[0]--;
					break;
				}
				if (resOfAction > 0 && resOfAction < 5) {
					_Ammo[4].emplace_back(*new Projectile(_player, resOfAction));
					_m.SetSmth(_Ammo[4][_Ammo[4].size() - 1]);
				}
				else if (resOfAction > 4) {
					std::vector<int> EnemInVect;
					EnemInVect = this->FindEnemy(Enem[0], Enem[1]);
					if (EnemInVect[1] != -1 && _Enemys[EnemInVect[0]][EnemInVect[1]].TakeDmg(_player.GetArrowsDmg())) {
						_Enemys[EnemInVect[0]].erase(_Enemys[EnemInVect[0]].begin() + EnemInVect[1]);
						_m.SetSmth(Enem[0], Enem[1], '.');
					}
				}
			}
		}
	}
	_IsCalculation = false;
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
				_Stuff[6 + j - 3 * i] = _Stuff[3 + j - 3 * i];
			}
		}
		for (int i = 0; i < 3; i++) {
			_Enemys[i].clear();
			_Stuff[i].clear();
			this->FullRoom(i);
			_Ammo[i].clear();
		}
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[i + j * 3] = _Enemys[i + j * 3 + 1];
				_Ammo[i + j * 3] = _Ammo[i + j * 3 + 1];
				_Stuff[i + j * 3] = _Stuff[i + j * 3 + 1];
			}
		}
		for (int i = 0; i < 3; i++) {
			_Enemys[3*i+2].clear();
			_Stuff[3 * i + 2].clear();
			this->FullRoom(3*i+2);
			_Ammo[3*i+2].clear();
		}
		break;
	case 3:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[i*3 + j] = _Enemys[3 + i*3 + j];
				_Ammo[j + 3 * i] = _Ammo[3 + j + 3 * i];
				_Stuff[j + 3 * i] = _Stuff[3 + j + 3 * i];
			}
		}
		for (int i = 6; i < 9; i++) {
			_Enemys[i].clear();
			_Stuff[i].clear();
			this->FullRoom(i);
			_Ammo[i].clear();
		}
		break;
	case 4:
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				_Enemys[1 -i + j * 3+1] = _Enemys[1 -i + j * 3];
				_Ammo[1 - i + j * 3 + 1] = _Ammo[1 - i + j * 3];
				_Stuff[1 - i + j * 3 + 1] = _Stuff[1 - i + j * 3];
			}
		}
		for (int i = 0; i < 3; i++) {
			_Enemys[i*3].clear();
			_Stuff[i*3].clear();
			this->FullRoom(i*3);
			_Ammo[i*3].clear();
		}
		break;
	default:
		return;
	}
	this->SetAllChar();
}

void Levle::MoveArrows() {
	char d;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < _Ammo[i].size(); j++) {
			_m.SetSmth(_Ammo[i][j], '.');
			d = _Ammo[i][j].Move(_m);
			if (d == -1) {
				_Ammo[i].erase(_Ammo[i].begin() + j);
			}
			else if (d > 0 && d < 5) {
				std::vector<int> temp = _Ammo[i][j].GetPos();
				temp = this->FindEnemy(temp[0],temp[1]);
				_m.SetSmth(_Ammo[i][j]);
				if (temp[0] != i) {
					_Ammo[temp[0]].push_back(_Ammo[i][j]);
					_Ammo[i].erase(_Ammo[i].begin() + j);
				}
			}
			else if (d > 4 && d < 8) {
				std::vector<int> temp = _Ammo[i][j].GetPos();
				d = _m.GetSmth(temp[0],temp[1]);
				if (_Ammo[i][j].WhosArrow()) {
					if (d == 'Z' || d == 'D') {
						temp = this->FindEnemy(temp[0],temp[1]);
						if (temp[1] != -1) {
							if (_Enemys[temp[0]][temp[1]].TakeDmg(_Ammo[i][j].GetDmg())) {
								_Enemys[temp[0]].erase(_Enemys[temp[0]].begin() + temp[1]);
							}
							_Ammo[i].erase(_Ammo[i].begin() + j);
						}
					}
				}
				else {
					if (d == 'K') {
						if (_player.TakeDmg(_Ammo[i][j].GetDmg())) {
							_flag = 0;
						}
						_Ammo[i].erase(_Ammo[i].begin() + j);
					}
				}
			}
			//std::cout << d << '\n';
		}
	}
}

void Levle::MoveEnem() {
	char d;
	while (_IsCalculation) { return; }
	_IsCalculation = true;
	if (_flag) {
		this->MoveArrows();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < _Enemys[i].size(); j++) {
				_m.SetSmth(_Enemys[i][j], '.');
				d = _Enemys[i][j].Move(_m);
				_m.SetSmth(_Enemys[i][j]);
				if (d == -1) {
					_Enemys[i].erase(_Enemys[i].begin() + j);
				}
				else if (d > 0 && d < 5) {
					std::vector<int> temp = _Enemys[i][j].GetPos();
					temp = this->FindEnemy(temp[0], temp[1]);
					_m.SetSmth(_Enemys[i][j]);
					if (temp[0] != i) {
						_Enemys[temp[0]].push_back(_Enemys[i][j]);
						_Enemys[i].erase(_Enemys[i].begin() + j);
					}
				}
				else if (d == 0) {
					if (_player.TakeDmg(_Enemys[i][j].GetDmg()))
						_flag = false;
				}
				else if (d > 4 && d < 9) {
					std::vector<int> temp = _Enemys[i][j].GetPos();
					_Ammo[temp[0]].emplace_back(*new Projectile(_Enemys[i][j], d - 4));
				}
				else if (d > 8 && d < 13) {
					if (_player.TakeDmg(_Enemys[i][j].GetArrowsDmg()))
						_flag = false;
				}
			}
		}
	}
	_IsCalculation = false;
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
	int x;

 	for (int i = 0; i < _SetDragons[0]; i++) {
		if (rand() % 100 <= _SetDragons[1]) {
			x = 0;
			std::vector<int> cords {rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.' && x < 100) {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
				x++;
			}
			if(x < 100)
				_Enemys[cube].emplace_back(*new Dragon(cords[0],cords[1]));
		}
	}

	for (int i = 0; i < _SetZombie[0]; i++) {
		if (rand() % 100 <= _SetZombie[1]) {
			x = 0;
			std::vector<int> cords{ rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.' && x < 100) {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
				x++;
			}
			if (x < 100)
				_Enemys[cube].emplace_back(*new Zombie(cords[0], cords[1]));
		}
	}

	for (int i = 0; i < _SetHeal[0]; i++) {
		if (rand() % 100 <= _SetHeal[1]) {
			x = 0;
			std::vector<int> cords{ rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.' && x < 100) {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
				x++;
			}
			if (x < 100)
				_Stuff[cube].emplace_back(*new Stuff(cords[0], cords[1],'+'));

		}
	}

	for (int i = 0; i < _SetArrow[0]; i++) {
		if (rand() % 100 <= _SetArrow[1]) {
			x = 0;
			std::vector<int> cords{ rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.' && x < 100) {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
				x++;
			}
			if (x < 100)
				_Stuff[cube].emplace_back(*new Stuff(cords[0], cords[1], '='));
		}
	}

	for (int i = 0; i < _SetPrincess[0]; i++) {
		if (rand() % 100 <= _SetPrincess[1]) {
			x = 0;
			std::vector<int> cords{ rand() % _Width + LeftUpCord[0], rand() % _Height + LeftUpCord[1] };
			while (_m.GetSmth(cords[0], cords[1]) != '.' && x < 100) {
				cords[0] = rand() % _Width + LeftUpCord[0];
				cords[1] = rand() % _Height + LeftUpCord[1];
				x++;
			}
			if (x < 100)
				_Stuff[cube].emplace_back(*new Stuff(cords[0], cords[1], 'P'));
		}
	}

}

void Levle::PlayGame() {
	////char c;
	//this->Draw();
	//while (_flag) {
	//	Sleep(300);
	//	while (this->MovePlayr() == 1) {}
	//	this->MoveEnem();
	//	this->Draw();
	//	//std::cin >> c;
	//	
	//}
	this->Draw();
	
	std::thread en(&Levle::EnemyThread, this);
	std::thread pl(&Levle::PlayThread, this);

	pl.join();
	en.join();

	if (_player.GetHp() > 0) {
		std::cout << "\nYour princess in another castle \n";
	}
	else {
		std::cout << "\nOh nooooooo, my princess collection\n";
	}
}

void Levle::SetAllChar() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < _Enemys[i].size(); j++) {
			_m.SetSmth(_Enemys[i][j]);
		}
		for (int j = 0; j < _Ammo[i].size(); j++) {
			_m.SetSmth(_Ammo[i][j]);
		}
		for (int j = 0; j < _Stuff[i].size(); j++) {
			_m.SetSmth(_Stuff[i][j]);
		}
	}
	_m.SetSmth(_player);
}

void Levle::PlayThread() {
	while (_flag) {
		while (this->MovePlayr() == 1) {}
		this->Draw();
		Sleep(300);
	}
}
void Levle::EnemyThread() {
	while (_flag) {
		this->MoveEnem();
		this->Draw();
		Sleep(1000);
	}
}
//
//void wait(unsigned timeout)
//{
//	timeout += std::clock();
//	while (std::clock() < timeout) continue;
//}

std::vector<int> Levle::FindEnemy(int other_x, int other_y, int c)const {
	std::vector<int> CentrOFMap = _m.GetCentrCords();
	int x = other_x - _Width * CentrOFMap[0] + _Width / 2;
	int y = other_y - _Height * CentrOFMap[1] + _Height / 2;
	int cube = 4;
	int toRet = -1;
	if (c == 1) {
		if (x < 0) {
			cube--;
		}
		else if (x >= _Width) {
			cube++;
		}

		if (y < 0) {
			cube -= 3;
		}
		else if (y >= _Height) {
			cube += 3;
		}
		for (int i = 0; i < _Enemys[cube].size(); i++) {
			if (other_x == _Enemys[cube][i].GetPos()[0] && other_y == _Enemys[cube][i].GetPos()[1]) {
				toRet = i;
				break;
			}
		}
	}
	else if (c == 2) {
		//std::cout << other_x << ' ' << other_y << '\n';
		for (int i = 0; i < _Stuff[4].size(); i++) {
			//std::cout<<_Stuff[4][i].GetPos()[0]<<' ' << _Stuff[4][i].GetPos()[1] <<'\n';
			if (_Stuff[4][i].GetPos()[0] == other_x && _Stuff[4][i].GetPos()[1] == other_y) {
				toRet = i;
				//std::cout << "EEEEEEE\n";
				break;
			}
		}
	}
	
	return std::vector<int>{cube, toRet};
}