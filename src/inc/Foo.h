/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains declaration of general functions
 *
 ***********************************************************************************/

#pragma once
#include <Windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <cstring>
#include <conio.h>
#include "Ground.h"
#include "Map.h"
#include "Timer.h"

class Player;
class Enemy;
void SetCur(int x, int y);
void HideCursor();
time_t getTime();
void control(Map &map, Player &player, vector<Ground *> &ground_list, vector<Enemy *> &ENEMY, bool &isend, bool &isstoryend);
void playMenu();
void printStat(Player &player, Timer &timer, const int endTime);
void spawnMushroom(Player &player, vector<Ground *> &ground_list, size_t index, vector<Enemy *> &enemy_list, Map &map);
void groundCheck(vector<Ground *> &ground_list, Player &player);
void storyMode();
void openOrWrite(int lNumber, ifstream &file);
void spawnCoin(Player &player, vector<Ground *> &ground_list, size_t index, vector<Enemy *> &enemy_list, Map &map);
void pauseMenu(bool &isend, bool &isstoryend);
void setStdCoords(Player &player);