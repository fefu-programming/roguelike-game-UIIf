#include "Map.h"
#include <iostream>

#define minH 5
#define minW 5

Map::Map(int W,int H,int sW,int sH) {
	if (W < minW) {
		_mapW = minW;
	}
	else {
		_mapW = W;
	}

	if (H < minH) {
		_mapH = minH;
	}
	else {
		_mapH = H;
	}

	if (sW + 1 > _mapW) {
		_drawW = (_mapW - 1) / 2;
	}
	else {
		_drawW = sW;
	}

	if (sH + 1 > _mapH) {
		_drawH = (_mapH - 1) / 2;
	}
	else {
		_drawH = sH;
	}
	
	_arr = new GameObj * *[_mapH];

	for (int i = 0; i < _mapH; i++) {
		_arr[i] = new GameObj * [_mapW];
		for (int j = 0; j < _mapW; j++) {
			_arr[i][j] = new Space(j, i);
		}
		_arr[i][0] = new Wall(0, i);
		_arr[i][_mapW - 1] = new Wall(_mapW - 1, i);
	}

	for (int i = 0; i < _mapW; i++) {
		_arr[0][i] = new Wall(i, 0);
		_arr[_mapH - 1][i] = new Wall(i, _mapH - 1);
	}

}

void Map::Draw(GameObj *k) const {
	std::vector<int> cords = (*k).GetPos();

	int sX = cords[0] - _drawW/2,
		fX = cords[0] + _drawW/2,
		sY = cords[1] - _drawH/2,
		fY = cords[1] + _drawH/2;

	if (sX < 0) {
		fX = _drawW + 1;
		sX = 0;
	}
	else if (fX >= _mapW) {
		sX = _mapW - 2 - _drawW;
		fX = _mapW;
	}

	if (sY < 0) {
		fY = _drawH + 1;
		sY = 0;
	}
	else if (fY >= _mapH) {
		sY = _mapH - 2 - _drawH;
		fY = _mapH;
	}
	for (int i = sX; i < fX + 2; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
	for (int i = sY; i < fY; i++) {
		std::cout << '|';
		for (int j = sX; j < fX; j++) {
			std::cout << (_arr[i][j])->GetSym();
		}
		std::cout << '|' << std::endl;
	}
	for (int i = sX; i < fX + 2; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
}

void Map::SetSmth(int x, int y, GameObj* other) {
	if (x > 0 && x < _mapW - 1 && y > 0 && y < _mapH - 1) {
		_arr[y][x] = other;
	}
}

void Map::SetSmth(std::vector<int> cord, GameObj* other) {
	if (cord[0] > 0 && cord[0] < _mapW - 1 && cord[1] > 0 && cord[1] < _mapH - 1) {
		_arr[cord[1]][cord[0]] = other;
	}
}

int Map::GetHeight() const {
	return _mapH;
}
int Map::GetWidth() const {
	return _mapW;
}

GameObj* Map::GetSmth(int x, int y) const {
	if (x >= 0 && x < _mapW && y >= 0 && y < _mapH) {
		return _arr[y][x];
	}
	return new GameObj;
}
GameObj* Map::GetSmth(std::vector<int> cord) const {
	if (cord[0] >= 0 && cord[0] < _mapW && cord[1] >= 0 && cord[1] < _mapH) {
		return _arr[cord[1]][cord[0]];
	}
	return new GameObj;
}