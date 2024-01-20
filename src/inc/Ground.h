/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains declaration of Ground class
 *
 ***********************************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;
class Ground // class of type "surface"
{
private:
	char sym{0};
	size_t type;
	float startx{0.f}, endx{0.f};
	float starty{0.f}, endy{0.f};

public:
	Map *map = nullptr;
	int y1{0}, y2{0};
	float fx1{0.f}, fx2{0.f};
	float fy1{0.f}, fy2{0.f};
	int x1{0}, x2{0};
	size_t moneycount = 0;
	bool mode = false;
	bool side = false;
	Ground();
	Ground(int x1, int x2, int y1, int y2, size_t type, Map &map);
	Ground(int x1, int x2, int y1, int y2, size_t type, Map &map, size_t range);
	void setCoord(float x1, float x2, float y1, float y2);
	size_t getType();
	void setSum(char sym);
	void putOnMap();
	void setDiapasoneX(int x1, int x2);
	void setDiapasoneY(int y1, int y2);
	void roundCoords();
	int getSX();
	int getEX();
	int getSY();
	int getEY();
	void changeWalkCoords(float walkspeed);
};