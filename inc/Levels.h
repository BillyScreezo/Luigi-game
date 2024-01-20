/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains level functions declaration
 *
 ***********************************************************************************/

#pragma once
#include "Map.h"
#include "Ground.h"
#include "Foo.h"
#include "Player.h"
#include <vector>
#include <ctime>
#include "Enemy.h"

void playLevel(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, Map &map, const unsigned int, Player &, bool &isstoryend);