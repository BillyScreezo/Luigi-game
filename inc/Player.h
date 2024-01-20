/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains declaration of Player class
 *
 ***********************************************************************************/

#pragma once
#include "Prototype.h"
#include "Ground.h"
#include "Map.h"
#include "Enemy.h"
#include "Foo.h"
#include <cmath>
#include <Windows.h>
#include <ctime>
#include <vector>

extern int pLives;

using namespace std;
class Player : public Prototype
{
private:
	bool isStand{false};
	bool star{false};
	unsigned int timeS;
	size_t level = 1;
	size_t prevlevel = level;

public:
	clock_t timeonground = 0;
	float startJump = 0.0f;
	float stdspeed;
	bool status();
	bool isjump = false, ctrl = true;
	bool ismove_r = true, ismove_l = true, onground = false, underground = false;
	bool side = 0;
	vector<Ground *> ground_list;
	Player(float x, float y, int width, int height, float wspeed, float fspeed, char sym, Map &map, vector<Ground *> &ground_list);

	void physic(vector<Enemy *> &enemy_list, bool mode);
	virtual void die() override;
	void resetPlayer();
	void resetScore();

	bool useStar();
	void takeLiveMushroom();
	void takeStar(int);
	void addScore(int);

	virtual bool isDead() override;
	void jump(vector<Ground *> &ground_list);
	void jump(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list);

	bool checkDown();

	size_t getLevel();
	void levelUp();
	void levelDown();

	bool isEndLevel(vector<Ground *> &space, clock_t &t1);
};
