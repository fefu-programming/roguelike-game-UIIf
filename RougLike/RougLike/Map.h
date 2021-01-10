#pragma once
#include "GameObj.h"
class Map
{
private:
	int _mapW = 50,
		_mapH = 50,
		_drawW = 40,
		_drawH = 14;
	GameObj ***_arr;
public:
	Map(int W = 50,int H = 50,int sW=34, int sH=14);
	void Draw(GameObj *k) const;

	void SetSmth(int x, int y, GameObj *other);
	void SetSmth(std::vector<int> cord, GameObj* other);

	int GetHeight() const;
	int GetWidth() const;

	GameObj* GetSmth(int x, int y) const;
	GameObj* GetSmth(std::vector<int> cord) const;
};

