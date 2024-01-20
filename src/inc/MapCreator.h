/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains declaration of map creator functions
 *
 ***********************************************************************************/

#pragma once
#include "Map.h"
#include "Ground.h"
#include "Enemy.h"
#include "Foo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <vector>
#include <sys/stat.h>
#include <limits>

Ground *addNewObject_g(int x1, int y1, int x2, int y2, size_t type, Map &map);
void loadMap(ifstream &fin, vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, Map &map);
void deleteObject_g(vector<Ground *> &ground_list, int index);
void interactMenu(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, Map &map, int pos, int &in, bool &g_ischange, bool &e_ischange);
bool visualWorkSpace(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, int &pos, Map &map);
void mapCreator();