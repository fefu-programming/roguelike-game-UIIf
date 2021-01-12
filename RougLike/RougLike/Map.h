#pragma once
#include <vector>
#include <iostream>
#include "Perlin.h"
#include "GameObject.h"

class Map
{
	Perlin _Per;
	std::vector<std::vector<std::vector<char>>> CurMap;
	std::vector<std::vector<std::vector<bool>>> VisMap;
	std::vector<std::vector<std::vector<char>>> AllMap;
	int _MainRoomX, _MainRoomY, _Rooms,_Width,_Height, _Room_offset;
	int Fw, Fh;
	void ReadRooms();
	void StartView();
	std::vector<std::vector<char>> ReturnRoom(int x, int y);
public:
	Map();
	void DrawAll() const;
	void ChoseRoom(int x, int y);
	void MoveRoom(char dir);
	void Draw(std::vector<int> Cord) const;
	void SetSmth(GameObj other,char t = -1);
	void SetSmth(int other_x, int other_y, char sym);
	char GetSmth(int x, int y, int cube = 4);
	bool IsInMidle(GameObj other) const;
};

