/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition of levels functions
 *
 ***********************************************************************************/

#include "MapCreator.h"
#include "Levels.h"
#include "Timer.h"
#include "Foo.h"
#include "Const.h"

void playLevel(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, Map &map, const unsigned int endTime, Player &player, bool &isstoryend)
{
	bool isend = false, isgameend = false;
	clock_t t1 = 0, t2 = 0;

	enemyModule(enemy_list, player, ground_list, map, WorkType::ENABLEALL);

	Timer timer;
	timer.set();

	player.ctrl = true;

	if (player.isDead())
		player.resetPlayer();

	while (!isend)
	{
		SetCur(0, 0);

		map.fillSpace();

		for (size_t i = 0; i < ground_list.size(); i++)
			ground_list[i]->putOnMap();

		enemyModule(enemy_list, player, ground_list, map, WorkType::PUTONMAP);

		player.putOnMap();

		map.printMap();

		player.physic(enemy_list, 1);
		control(map, player, ground_list, enemy_list, isend, isstoryend);

		enemyModule(enemy_list, player, ground_list, map, WorkType::PHYSIC);
		enemyModule(enemy_list, player, ground_list, map, WorkType::INTERACTION);

		groundCheck(ground_list, player);

		printStat(player, timer, endTime);
		Sleep(15);

		t2 = clock();
		if (player.checkDown() || (player.isEndLevel(ground_list, t1) && t2 - t1 >= 250))
		{
			isend = true;
		}
	}
	if (!isstoryend && !player.isDead())
	{
		timer.check();
		int timeLeft = endTime - timer.get();
		int tempS = 0;
		for (int i{0}; i <= timeLeft; ++i)
		{
			SetCur(0, 0);
			map.fillSpace();
			for (size_t i = 0; i < ground_list.size(); i++)
				ground_list[i]->putOnMap();

			player.putOnMap();

			enemyModule(enemy_list, player, ground_list, map, WorkType::PUTONMAP);

			map.printMap();

			player.addScore(10);
			cout << "Time: " << timeLeft - i << ' ';
			cout << "\nLives: " << pLives << ' ';
			cout << "\nScore: " << player.getScore();
			cout << "\n        ";
			Sleep(10);
		}

		Sleep(2000);
	}
	system("cls");
}