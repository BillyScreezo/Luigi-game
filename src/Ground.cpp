/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition of Ground class
 *
 ***********************************************************************************/

#include "Ground.h"

Ground::Ground()
{
	fx1 = 0.0f;
	fx2 = 0.0f;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
	type = 0;
	sym = '&';
	startx = 0.f;
	endx = 0.f;
	starty = 0.f;
	endy = 0.f;
	map = nullptr;
}
Ground::Ground(int x1, int x2, int y1, int y2, size_t type, Map &map)
{
	this->fx1 = (float)x1;
	this->fx2 = (float)x2;
	this->x1 = (int)round(fx1);
	this->x2 = (int)round(fx2);
	this->fy1 = (float)y1;
	this->fy2 = (float)y2;
	this->type = type;
	switch (type)
	{
	case 0:
		this->sym = '#';
		break;
	case 1:
		this->sym = '?';
		this->fx2 = this->fx1 + 2.0f;
		this->x2 = (int)round(fx2);
		this->fy2 = this->fy1 + 2.0f;
		this->mode = true;
		break;
	case 2:
		this->sym = '?';
		this->fx2 = this->fx1 + 2.0f;
		this->x2 = (int)round(fx2);
		this->fy2 = this->fy1 + 2.0f;
		this->mode = true;
		this->moneycount = 4;
		break;
	case 3:
		this->sym = ' ';
		this->fx2 = this->fx1 + 2.0f;
		this->x2 = (int)round(fx2);
		this->fy2 = this->fy1 + 2.0f;
		this->mode = true;
		break;
	case 4:
		this->sym = ' ';
		this->fx2 = this->fx1 + 2.0f;
		this->x2 = (int)round(fx2);
		this->fy2 = this->fy1 + 2;
		this->mode = true;
		this->moneycount = 4;
		break;
	case 5:
		this->sym = '=';
		if ((int)(this->fx2 - this->fx1) % 2 != 0)
			this->fx2 += 1.0f;
		if ((this->y2 - this->y1) % 2 != 0)
			this->fy2 += 1.0f;
		break;
	case 6:
		this->sym = '^';
		this->fx1 = (float)x1;
		this->fx2 = (float)x2;
		this->fy1 = (float)y1;
		this->fy2 = (float)y2;
		break;
	case 7:
		this->sym = '-';
		this->fx1 = (float)x1;
		this->fx2 = (float)x2;
		this->fy1 = (float)y1;
		this->fy2 = (float)y1 + 1.0f;
		break;
	case 8:
		this->sym = '!';
		this->fx1 = (float)x1;
		this->fx2 = (float)x1 + 1.0f;
		this->fy1 = (float)fy1;
		this->fy2 = (float)(y1 + 1);
		mode = false;
		break;
	case 9:
		this->sym = 'm';
		this->fx1 = (float)x1;
		this->fx2 = (float)x1 + 6.0f;
		this->fy1 = (float)y1;
		this->fy2 = (float)(y1 + 1);
		this->x1 = (int)round(fx1);
		this->x2 = (int)round(fx2);
		setDiapasoneX(this->x1, this->x1 + 30);
		break;
	case 10:
		this->sym = 'm';
		this->fx1 = (float)x1;
		this->fx2 = (float)x1 + 6.0f;
		this->fy1 = (float)y1;
		this->fy2 = (float)(y1 + 1);
		setDiapasoneY(this->y1, this->y2 + 25);
		break;
	case 11:
		this->sym = '|';
		this->fx1 = (float)x1;
		this->fx2 = (float)x1 + 1.0f;
		this->fy1 = (float)y1;
		this->fy2 = (float)y2;
		break;
	default:
		this->sym = '&';
	}
	roundCoords();
	this->map = &map;
	if (y2 < 0)
		this->y2 = map.getHeight() - 1;
	if (this->y1 > this->y2)
		swap(this->y1, this->y2);
	if (this->y2 >= map.getHeight())
		this->y2 = map.getHeight() - 1;
}
Ground::Ground(int x1, int x2, int y1, int y2, size_t type, Map &map, size_t range)
{
	this->sym = 'm';
	this->fx1 = (float)x1;
	this->fx2 = (float)x2;
	this->fy1 = (float)y1;
	this->fy2 = (float)(y1 + 1);
	this->x1 = (int)round(fx1);
	this->x2 = (int)round(fx2);
	this->type = type;
	roundCoords();
	this->map = &map;
	if (y2 < 0)
		this->y2 = map.getHeight() - 1;
	if (this->y1 > this->y2)
		swap(this->y1, this->y2);
	if (this->y2 >= map.getHeight())
		this->y2 = map.getHeight() - 1;
	setDiapasoneX(this->x1, this->x1 + static_cast<int>(range));
}
void Ground::putOnMap()
{
	roundCoords();
	int start_x = x1, end_x = x2, start_y = y1, end_y = y2;
	if (y1 < 0)
		start_y = 0;
	else
		start_y = y1;
	if (y2 > map->getHeight() - 1)
		end_y = map->getHeight() - 1;
	else
		end_y = y2;
	if (x2 > map->getWidth() - 1)
		end_x = map->getWidth() - 1;
	else
		end_x = x2;
	if (x1 < 0)
		start_x = 0;
	if (x1 < map->getWidth())
	{
		for (int i = start_y; i < end_y; i++)
			for (int j = start_x; j < end_x; j++)
				map->field[i][j] = sym;
	}
}
size_t Ground::getType()
{
	return type;
}
void Ground::setSum(char sym)
{
	this->sym = sym;
}
void Ground::setCoord(float x1, float x2, float y1, float y2)
{
	this->fx1 = x1;
	this->fx2 = x2;
	if (this->type == 5)
	{
		if ((int)(this->fx2 - this->fx1) % 2 != 0)
			this->fx2 += 1.0f;
		if ((this->y2 - this->y1) % 2 != 0)
			this->y2++;
	}
	this->x1 = (int)round(fx1);
	this->x2 = (int)round(fx2);
	this->fy1 = y1;
	this->fy2 = y2;
}
void Ground::setDiapasoneX(int x1, int x2)
{
	this->startx = (float)x1;
	this->endx = (float)x2;
}
void Ground::setDiapasoneY(int y1, int y2)
{
	if (type == 10)
	{
		this->starty = (float)y1;
		this->endy = (float)y2;
	}
}
int Ground::getSX()
{
	if (type == 9)
		return (int)round(this->startx);
	else
		return -12345;
}
int Ground::getEX()
{
	if (type == 9)
		return (int)round(this->endx);
	else
		return -12345;
}
int Ground::getSY()
{
	if (type == 9)
		return (int)round(this->starty);
	else
		return -12345;
}
int Ground::getEY()
{
	if (type == 9)
		return (int)round(this->endy);
	else
		return -12345;
}
void Ground::roundCoords()
{
	x1 = (int)round(fx1);
	x2 = (int)round(fx2);
	y1 = (int)round(fy1);
	y2 = (int)round(fy2);
}
void Ground::changeWalkCoords(float walkspeed)
{
	startx -= walkspeed;
	endx -= walkspeed;
}