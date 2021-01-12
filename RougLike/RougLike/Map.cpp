#include "Map.h"
#include <fstream>

Map::Map() {
	_Room_offset = rand() % 20;
	this->ReadRooms();
	Fw = findInfConfig("FildOfViewW");
	if (Fw == -1) {
		Fw = _Width ;
	}
	if (Fw > _Width * 2 - 1) {
		Fw = _Width * 2 - 1;
	}
	if (!Fw % 2)
		Fw++;
	Fh = findInfConfig("FildOfViewH");
	if (Fh == -1) {
		Fh = _Height ;
	}
	if (Fh > _Height * 2 - 1) {
		Fh = _Height * 2 - 1;
	}
	if (!Fh % 2)
		Fh++;
	for (int i = 0; i < 9; i++) {
		CurMap.push_back(std::vector<std::vector<char>>{});
	}
	_MainRoomX = -100;
	_MainRoomY = -100;
	this->ChoseRoom(0, 0);
	this->StartView();
}

void Map::ReadRooms() {
	std::ifstream fin("RoomTiles.txt");
	fin >> _Rooms >> _Width >> _Height;
	char tmp;
	for (int i = 0; i < _Rooms; i++) {
		AllMap.push_back(std::vector<std::vector<char>>{});
		for (int y = 0; y < _Height; y++) {
			AllMap[i].push_back(std::vector<char>{});
			for (int x = 0; x < _Width; x++) {
				fin >> tmp;
				AllMap[i][y].push_back(tmp);
			}
		}
	}
	fin.close();
}

void Map::StartView() {
	VisMap.clear();
	for (int i = 0; i < 9; i++) {
		VisMap.push_back(std::vector<std::vector<bool>>{});
		for (int y = 0; y < _Height; y++) {
			VisMap[i].push_back(std::vector<bool> {});
			for (int x = 0; x < _Width; x++) {
				VisMap[i][y].push_back(true);
			}
		}
	}
}

std::vector<std::vector<char>> Map::ReturnRoom(int x, int y) {
	return AllMap[int(20 * _Per.Noise(x+50000<0?-x:x+50000, y+50000<0?-y:y+50000) + _Room_offset) % 20];
}

void Map::DrawAll() const {
	for (int i = 0; i < _Rooms; i++) {
		for (int y = 0; y < _Height; y++) {
			for (int x = 0; x < _Width; x++) {
				std::cout << AllMap[i][y][x];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

void Map::ChoseRoom(int x, int y) {
	CurMap[0] = ReturnRoom(x - 1, y - 1);
	CurMap[1] = ReturnRoom(x, y - 1);
	CurMap[2] = ReturnRoom(x + 1, y - 1);
	CurMap[3] = ReturnRoom(x - 1, y);
	CurMap[4] = ReturnRoom(x, y);
	CurMap[5] = ReturnRoom(x + 1, y);
	CurMap[6] = ReturnRoom(x - 1, y + 1);
	CurMap[7] = ReturnRoom(x, y + 1);
	CurMap[8] = ReturnRoom(x + 1, y + 1);

	_MainRoomX = x;
	_MainRoomY = y;
}
void Map::MoveRoom(char dir) {
	switch (dir)
	{
	case 1:
		_MainRoomY--;
		break;
	case 2:
		_MainRoomX++;
		break;
	case 3:
		_MainRoomY++;
		break;
	case 4:
		_MainRoomX--;
		break;
	default:
		return;
	}
	this->ChoseRoom(_MainRoomX,_MainRoomY);
}

void Map::Draw(std::vector<int> Cord) const{

	int x = Cord[0] - _Width * _MainRoomX + _Width/2;
	int y = Cord[1] - _Height * _MainRoomY + _Height/2;
	//std::cout << x<<'\n';
	int draw_x = _Width + x - Fw/2;
	int draw_y = _Height + y - Fh/2;
	std::cout << char(201);
	for (int i = 0; i < Fw; i++) {
		std::cout << char(205);
	}
	std::cout << char(187)<<std::endl;
	for (int i = 0; i < 3; i++) {
		for (int y = draw_y > _Height * i?draw_y: _Height * i; y >= _Height*i && y < _Height * (i+1) && y < draw_y + Fh; y++) {
			std::cout << char(186);
			for (int col = 0; col < 3; col++) {
				for (int x = draw_x > _Width * col? draw_x: _Width * col; x >= _Width * col && x < _Width * (col + 1) && x < draw_x + Fw; x++) {
					std::cout << CurMap[i * 3 + col][y - _Height*i][x - _Width * col];
				}
			}
			std::cout <<char(186)<< std::endl;
		}
	}
	std::cout << char(200);
	for (int i = 0; i < Fw; i++) {
		std::cout << char(205);
	}
	std::cout << char(188) << std::endl;
	//BackUpDrawOfMap
	//std::cout << "\n";
	//for (int i = 0; i < 3; i++) {
	//	for (int y = 0; y < _Height ; y++) {
	//		//std::cout << char(186);
	//		for (int col = 0; col < 3; col++) {
	//			for (int x = 0; x < _Width ; x++) {
	//				std::cout << CurMap[i * 3 + col][y][x];
	//			}
	//		}
	//		std::cout << "\n";
	//		//std::cout << char(186) << std::endl;
	//	}
	//}

}

void Map::SetSmth(GameObj other, char t) {
	int x = other.GetPos()[0] - _Width * _MainRoomX + _Width / 2;
	int y = other.GetPos()[1] - _Height * _MainRoomY + _Height / 2;
	if (t == -1) {
		t = other.GetSym();
	}
	this->SetSmth(other.GetPos()[0],other.GetPos()[1],t);
}

void Map::SetSmth(int other_x, int other_y, char sym) {
	int x = other_x - _Width * _MainRoomX + _Width / 2;
	int y = other_y - _Height * _MainRoomY + _Height / 2;
	int cube = 4;
	if (x < 0) {
		cube--;
		x += _Width;
	}
	else if (x >= _Width) {
		cube++;
		x -= _Width;
	}

	if (y < 0) {
		cube -= 3;
		y += _Height;
	}
	else if (y >= _Height) {
		cube += 3;
		y -= _Height;
	}

	CurMap[cube][y][x] = sym;
	//std::cout << "x y " << x << ' ' << y;
	//std::cout << "\nK " << CurMap[4][y][x];
}

char Map::GetSmth(int other_x, int other_y) {
	int x = other_x - _Width * _MainRoomX + _Width / 2;
	int y = other_y - _Height * _MainRoomY + _Height / 2;
	int cube = 4;
	if (x < 0) {
		cube--;
		x += _Width;
	} else if (x >= _Width) {
		cube++;
		x -= _Width;
	}

	if (y < 0) {
		cube-=3;
		y += _Height;
	} else if (y >= _Height) {
		cube += 3;
		y -= _Height;
	}		

	//std::cout << '\n' << x <<' '<< y<<'\n';
	if (cube < 9 && cube >= 0 && x >= 0 && x < _Width && y >= 0 && y < _Height) {
		return CurMap[cube][y][x];
	}
	return -1;
}

bool Map::IsInMidle(GameObj other) const {
	int x = other.GetPos()[0] - _Width * (_MainRoomX) + _Width *1.5;
	int y = other.GetPos()[1] - _Height * (_MainRoomY) + _Height * 1.5;
	return x >= _Width && x <= _Width * 2 - 1 && y >= _Height && y <= _Height * 2 -1 ;
}

int Map::GetWidth() {
	return _Width;
}
int Map::GetHeight() {
	return _Height;
}

std::vector<int> Map::GetCentrCords() {
	return std::vector<int>{ _MainRoomX,_MainRoomY };
}