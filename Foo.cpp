/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition menu, cmd, control functions
 *
 ***********************************************************************************/

#include "Foo.h"
#include "Player.h"
#include "Levels.h"
#include "MapCreator.h"
#include "Enemy.h"
#include "Const.h"

using namespace std;

void SetCur(int x, int y)
{
	COORD coord{static_cast<short>(x), static_cast<short>(y)};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

time_t getTime()
{
	time_t tm = time(NULL);
	return tm;
}

void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void control(Map &map, Player &player, vector<Ground *> &ground_list, vector<Enemy *> &ENEMY, bool &isend, bool &isstoryend)
{
	clock_t t1 = clock();
	if (!player.isDead())
	{
		if (player.ctrl)
		{
			if (GetKeyState(VK_ESCAPE) < 0)
				pauseMenu(isend, isstoryend);
			if (GetKeyState('A') < 0 && player.ismove_l)
			{
				player.side = false;
				if (player.ix >= 0)
					player.x -= player.wspeed;
				player.physic(ENEMY, 0);
			}
			if (GetKeyState('D') < 0 && player.ismove_r)
			{
				player.side = true;

				if (player.ix >= max_pX)
				{
					for (size_t i = 0; i < ground_list.size(); i++)
					{
						ground_list[i]->setCoord(ground_list[i]->fx1 - player.wspeed, ground_list[i]->fx2 - player.wspeed, static_cast<float>(ground_list[i]->y1), static_cast<float>(ground_list[i]->y2));
						if (ground_list[i]->getType() == 9)
						{
							ground_list[i]->changeWalkCoords(player.wspeed);
						}
					}
					enemyModule(ENEMY, player, ground_list, map, WorkType::MOVER);
				}
				else
					player.x += player.wspeed;
				player.physic(ENEMY, 0);
			}
			if ((GetKeyState(VK_SPACE) < 0 && player.onground && (t1 - player.timeonground >= spacedelay)) || player.isjump)
			{
				if (!player.isjump)
				{
					player.isjump = true;
					player.startJump = player.y;
				}
				player.jump(ground_list, ENEMY);
			}
			if (GetKeyState(VK_LSHIFT) < 0)
			{
				player.wspeed = 1.0f;
				static unsigned int count = 0;
				static unsigned int delay = clock();
				if ((clock() - delay >= 300) && (player.getLevel() == 3))
				{
					if (count != 2)
					{
						++count;
						if (player.getLevel() == 3)
							enemyModule(ENEMY, player, ground_list, map, WorkType::PTHROW);
					}
					else
					{
						if (clock() - delay >= 1000)
							count = 0;
						return;
					}
					delay = clock();
				}
			}
			else
			{
				player.wspeed = player.stdspeed;
			}
		}
	}
}

void openOrWrite(int lNumber, ifstream &file)
{
	int x = _wmkdir(L"Maps");
	string lName = "Maps/story_";
	switch (lNumber)
	{
	case 1:
		lName += "1";
		break;
	case 2:
		lName += "2";
		break;
	case 3:
		lName += "3";
		break;
	case 4:
		lName += "4";
		break;
	}
	lName += ".txt";
	file.open(lName);
	if (!file.is_open())
	{
		ofstream writeFile(lName);
		switch (lNumber)
		{
		case 1:
		{
			writeFile << "g:\n"
					  << "0:90:20:24:0\n"
					  << "83 : 87 : 17 : 20 : 0\n"
					  << "90 : 180 : 20 : 24 : 0\n"
					  << "103 : 107 : 15 : 20 : 0\n"
					  << "126 : 130 : 13 : 20 : 0\n"
					  << "152 : 156 : 13 : 20 : 0\n"
					  << "189 : 239 : 20 : 24 : 0\n"
					  << "251 : 341 : 20 : 24 : 0\n"
					  << "341 : 431 : 20 : 24 : 0\n"
					  << "414 : 422 : 18 : 20 : 0\n"
					  << "416 : 422 : 16 : 18 : 0\n"
					  << "406 : 414 : 18 : 20 : 0\n"
					  << "410 : 416 : 16 : 18 : 0\n"
					  << "414 : 422 : 14 : 16 : 0\n"
					  << "418 : 422 : 12 : 14 : 0\n"
					  << "431 : 471 : 20 : 24 : 0\n"
					  << "432 : 448 : 18 : 20 : 0\n"
					  << "432 : 444 : 16 : 18 : 0\n"
					  << "432 : 440 : 14 : 16 : 0\n"
					  << "432 : 436 : 12 : 14 : 0\n"
					  << "471 : 487 : 18 : 20 : 0\n"
					  << "475 : 487 : 16 : 18 : 0\n"
					  << "471 : 487 : 20 : 24 : 0\n"
					  << "479 : 487 : 14 : 16 : 0\n"
					  << "483 : 487 : 12 : 14 : 0\n"
					  << "487 : 491 : 12 : 24 : 0\n"
					  << "501 : 505 : 12 : 14 : 0\n"
					  << "501 : 509 : 14 : 16 : 0\n"
					  << "501 : 513 : 16 : 18 : 0\n"
					  << "501 : 517 : 18 : 20 : 0\n"
					  << "501 : 561 : 20 : 24 : 0\n"
					  << "536 : 540 : 16 : 20 : 0\n"
					  << "582 : 586 : 16 : 20 : 0\n"
					  << "561 : 651 : 20 : 24 : 0\n"
					  << "589 : 625 : 18 : 20 : 0\n"
					  << "593 : 625 : 16 : 18 : 0\n"
					  << "597 : 625 : 14 : 16 : 0\n"
					  << "601 : 625 : 12 : 14 : 0\n"
					  << "605 : 625 : 10 : 12 : 0\n"
					  << "609 : 625 : 8 : 10 : 0\n"
					  << "613 : 625 : 6 : 8 : 0\n"
					  << "651 : 691 : 20 : 24 : 0\n"
					  << "61 : 63 : 13 : 15 : 5\n"
					  << "57 : 59 : 13 : 15 : 5\n"
					  << "55 : 57 : 13 : 15 : 1\n"
					  << "53 : 55 : 13 : 15 : 5\n"
					  << "44 : 46 : 13 : 15 : 2\n"
					  << "57 : 59 : 7 : 9 : 2\n"
					  << "264 : 266 : 8 : 10 : 2\n"
					  << "258 : 264 : 8 : 10 : 5\n"
					  << "264 : 266 : 14 : 16 : 5\n"
					  << "229 : 247 : 8 : 10 : 5\n"
					  << "227 : 229 : 14 : 16 : 1\n"
					  << "223 : 227 : 14 : 16 : 5\n"
					  << "281 : 285 : 14 : 16 : 5\n"
					  << "301 : 303 : 14 : 16 : 2\n"
					  << "308 : 310 : 14 : 16 : 2\n"
					  << "315 : 317 : 14 : 16 : 2\n"
					  << "308 : 310 : 8 : 10 : 1\n"
					  << "344 : 346 : 14 : 16 : 5\n"
					  << "356 : 362 : 8 : 10 : 5\n"
					  << "369 : 371 : 8 : 10 : 5\n"
					  << "371 : 375 : 14 : 16 : 5\n"
					  << "371 : 373 : 8 : 10 : 2\n"
					  << "373 : 375 : 8 : 10 : 2\n"
					  << "375 : 377 : 8 : 10 : 5\n"
					  << "550 : 554 : 14 : 16 : 5\n"
					  << "556 : 558 : 14 : 16 : 5\n"
					  << "554 : 556 : 14 : 16 : 2\n"
					  << "59 : 61 : 13 : 15 : 2\n"
					  << "170 : 172 : 14 : 16 : 3\n"
					  << "168 : 170 : 14 : 16 : 4\n"
					  << "655 : 656 : 5 : 20 : 11\n"
					  << "e:\n"
					  << "57:18:GOOMBA\n"
					  << "116:18:GOOMBA\n"
					  << "141 : 18 :GOOMBA\n"
					  << "138 : 18 :GOOMBA\n"
					  << "231 : 6 :GOOMBA\n"
					  << "235 : 6 :GOOMBA\n"
					  << "264 : 18 :GOOMBA\n"
					  << "268 : 18 :GOOMBA\n"
					  << "298 : 17 :KOOPA\n"
					  << "316 : 18 :GOOMBA\n"
					  << "320 : 18 :GOOMBA\n"
					  << "338 : 18 :GOOMBA\n"
					  << "348 : 18 :GOOMBA\n"
					  << "354 : 18 :GOOMBA\n"
					  << "358 : 18 :GOOMBA\n"
					  << "558 : 18 :GOOMBA\n"
					  << "563 : 18 :GOOMBA\n";
			break;
		}
		case 2:
		{
			writeFile << "g:\n"
					  << "0 : 90 : 20 : 24 : 0\n"
					  << "68 : 70 : 18 : 20 : 0\n"
					  << "74 : 76 : 16 : 20 : 0\n"
					  << "86 : 88 : 12 : 20 : 0\n"
					  << "80 : 82 : 14 : 20 : 0\n"
					  << "92 : 94 : 12 : 20 : 0\n"
					  << "90 : 180 : 20 : 24 : 0\n"
					  << "98 : 100 : 14 : 20 : 0\n"
					  << "110 : 112 : 14 : 20 : 0\n"
					  << "116 : 118 : 16 : 20 : 0\n"
					  << "180 : 270 : 20 : 24 : 0\n"
					  << "280 : 370 : 20 : 24 : 0\n"
					  << "377 : 381 : 20 : 24 : 0\n"
					  << "388 : 428 : 20 : 24 : 0\n"
					  << "408 : 428 : 18 : 20 : 0\n"
					  << "412 : 428 : 16 : 18 : 0\n"
					  << "416 : 428 : 14 : 16 : 0\n"
					  << "420 : 428 : 12 : 14 : 0\n"
					  << "1610 : 1670 : -10 : 24 : 0\n"
					  << "329 : 333 : 16 : 20 : 0\n"
					  << "341 : 345 : 12 : 20 : 0\n"
					  << "353 : 357 : 16 : 20 : 0\n"
					  << "454 : 494 : 20 : 24 : 0\n"
					  << "509 : 569 : 20 : 24 : 0\n"
					  << "0 : 2 : -2 : 20 : 5\n"
					  << "39 : 41 : 14 : 16 : 1\n"
					  << "41 : 43 : 14 : 16 : 2\n"
					  << "43 : 45 : 14 : 16 : 2\n"
					  << "45 : 47 : 14 : 16 : 2\n"
					  << "47 : 49 : 14 : 16 : 2\n"
					  << "15 : 105 : 0 : 2 : 5\n"
					  << "104 : 106 : 10 : 12 : 5\n"
					  << "105 : 195 : 0 : 2 : 5\n"
					  << "194 : 284 : 0 : 2 : 5\n"
					  << "132 : 134 : 10 : 16 : 5\n"
					  << "138 : 140 : 10 : 16 : 5\n"
					  << "134 : 138 : 14 : 16 : 5\n"
					  << "140 : 144 : 10 : 12 : 5\n"
					  << "144 : 146 : 10 : 16 : 5\n"
					  << "146 : 150 : 14 : 16 : 5\n"
					  << "150 : 152 : 10 : 16 : 5\n"
					  << "178 : 182 : 13 : 17 : 5\n"
					  << "174 : 178 : 8 : 14 : 5\n"
					  << "178 : 182 : 2 : 10 : 5\n"
					  << "188 : 200 : 1 : 5 : 5\n"
					  << "196 : 200 : 5 : 15 : 5\n"
					  << "188 : 200 : 15 : 17 : 5\n"
					  << "262 : 270 : 15 : 17 : 5\n"
					  << "262 : 270 : 7 : 9 : 5\n"
					  << "248 : 252 : 9 : 17 : 5\n"
					  << "222 : 232 : 2 : 6 : 5\n"
					  << "224 : 226 : 6 : 12 : 5\n"
					  << "224 : 230 : 12 : 14 : 5\n"
					  << "230 : 232 : 10 : 14 : 5\n"
					  << "284 : 374 : 0 : 2 : 5\n"
					  << "282 : 296 : 11 : 15 : 5\n"
					  << "130 : 132 : 10 : 12 : 5\n"
					  << "377 : 381 : 16 : 20 : 5\n"
					  << "368 : 428 : 0 : 2 : 5\n"
					  << "464 : 484 : 12 : 14 : 5\n"
					  << "445 : 447 : 9 : 10 : 0\n"
					  << "498 : 500 : 7 : 8 : 0\n"
					  << "509 : 549 : 16 : 20 : 5\n"
					  << "539 : 549 : 6 : 16 : 5\n"
					  << "509 : 539 : 4 : 6 : 5\n"
					  << "509 : 537 : 0 : 2 : 5\n"
					  << "537 : 539 : 0 : 2 : 4\n"
					  << "539 : 549 : 0 : 6 : 5\n"
					  << "484 : 486 : 12 : 14 : 3\n"
					  << "537 : 539 : 0 : 2 : 2\n"
					  << "529 : 530 : 6 : 16 : 11\n"
					  << "443 : 445 : 9 : 10 : 0\n"
					  << "501 : 503 : 16 : 17 : 0\n"
					  << "e:\n"
					  << "49 : 18 :GOOMBA\n"
					  << "45 : 18 :GOOMBA\n"
					  << "104 : 18 :GOOMBA\n"
					  << "136 : 13 :COIN\n"
					  << "148 : 13 :COIN\n"
					  << "142 : 8 :COIN\n"
					  << "140 : 8 :COIN\n"
					  << "138 : 8 :COIN\n"
					  << "144 : 8 :COIN\n"
					  << "152 : 17 :KOOPA\n"
					  << "156 : 17 :KOOPA\n"
					  << "195 : 13 :COIN\n"
					  << "193 : 13 :COIN\n"
					  << "191 : 13 :COIN\n"
					  << "189 : 13 :COIN\n"
					  << "204 : 17 :KOOPA\n"
					  << "209 : 18 :GOOMBA\n"
					  << "213 : 18 :GOOMBA\n"
					  << "250 : 7 :GOOMBA\n"
					  << "264 : 5 :GOOMBA\n"
					  << "268 : 5 :GOOMBA\n"
					  << "324 : 18 :GOOMBA\n"
					  << "320 : 18 :GOOMBA\n"
					  << "316 : 18 :GOOMBA\n"
					  << "283 : 9 :COIN\n"
					  << "285 : 9 :COIN\n"
					  << "287 : 9 :COIN\n"
					  << "289 : 9 :COIN\n"
					  << "291 : 9 :COIN\n"
					  << "293 : 9 :COIN\n"
					  << "330 : 16 :PLANT\n"
					  << "342 : 12 :PLANT\n"
					  << "354 : 16 :PLANT\n";
			break;
		}
		case 3:
		{
			writeFile << "g:\n"
					  << "0 : 40 : 20 : 24 : 0\n"
					  << "48 : 52 : 20 : 24 : 0\n"
					  << "47 : 53 : 18 : 20 : 0\n"
					  << "63 : 75 : 16 : 24 : 0\n"
					  << "62 : 76 : 14 : 16 : 0\n"
					  << "65 : 73 : 8 : 10 : 0\n"
					  << "81 : 83 : 20 : 24 : 0\n"
					  << "80 : 84 : 18 : 20 : 0\n"
					  << "90 : 96 : 15 : 24 : 0\n"
					  << "89 : 97 : 13 : 15 : 0\n"
					  << "104 : 114 : 10 : 24 : 0\n"
					  << "103 : 115 : 8 : 10 : 0\n"
					  << "128 : 130 : 20 : 24 : 0\n"
					  << "127 : 131 : 18 : 20 : 0\n"
					  << "141 : 147 : 20 : 24 : 0\n"
					  << "140 : 148 : 18 : 20 : 0\n"
					  << "128 : 130 : 8 : 9 : 0\n"
					  << "141 : 147 : 6 : 8 : 0\n"
					  << "154 : 160 : 20 : 24 : 0\n"
					  << "153 : 161 : 18 : 20 : 0\n"
					  << "165 : 167 : 16 : 24 : 0\n"
					  << "164 : 168 : 14 : 16 : 0\n"
					  << "178 : 186 : 10 : 24 : 0\n"
					  << "177 : 187 : 8 : 10 : 0\n"
					  << "219 : 223 : 16 : 24 : 0\n"
					  << "218 : 224 : 14 : 16 : 0\n"
					  << "202 : 204 : 8 : 9 : 0\n"
					  << "234 : 246 : 11 : 24 : 0\n"
					  << "233 : 247 : 9 : 11 : 0\n"
					  << "256 : 258 : 18 : 24 : 0\n"
					  << "255 : 259 : 16 : 18 : 0\n"
					  << "266 : 270 : 16 : 24 : 0\n"
					  << "265 : 271 : 14 : 16 : 0\n"
					  << "281 : 285 : 16 : 24 : 0\n"
					  << "280 : 286 : 14 : 16 : 0\n"
					  << "305 : 395 : 20 : 24 : 0\n"
					  << "344 : 368 : 18 : 20 : 0\n"
					  << "344 : 368 : 12 : 18 : 0\n"
					  << "352 : 368 : 9 : 13 : 0\n"
					  << "360 : 368 : 6 : 10 : 0\n"
					  << "382 : 442 : 20 : 24 : 0\n"
					  << "140 : 142 : 12 : 14 : 1\n"
					  << "140 : 141 : 6 : 8 : 0\n"
					  << "259 : 260 : 16 : 18 : 0\n"
					  << "292 : 298 : 10 : 11 : 9 : 40\n"
					  << "177 : 178 : 10 : 24 : 0\n"
					  << "176 : 177 : 8 : 10 : 0\n"
					  << "397 : 398 : 5 : 20 : 11\n"
					  << "e:\n"
					  << "69 : 7 :COIN\n"
					  << "67 : 7 :COIN\n"
					  << "71 : 7 :COIN\n"
					  << "65 : 5 :KOOPA\n"
					  << "82 : 17 :COIN\n"
					  << "100 : 6 :COIN\n"
					  << "98 : 6 :COIN\n"
					  << "106 : 6 :GOOMBA\n"
					  << "110 : 6 :GOOMBA\n"
					  << "123 : 5 :COIN\n"
					  << "121 : 5 :COIN\n"
					  << "146 : 5 :COIN\n"
					  << "144 : 5 :COIN\n"
					  << "142 : 5 :COIN\n"
					  << "140 : 5 :COIN\n"
					  << "171 : 8 :FLYKOOPA\n"
					  << "185 : 6 :GOOMBA\n"
					  << "193 : 5 :COIN\n"
					  << "195 : 5 :COIN\n"
					  << "210 : 5 :COIN\n"
					  << "212 : 5 :COIN\n"
					  << "239 : 6 :KOOPA\n"
					  << "255 : 15 :COIN\n"
					  << "257 : 15 :COIN\n"
					  << "259 : 15 :COIN\n"
					  << "274 : 11 :COIN\n"
					  << "276 : 11 :COIN\n"
					  << "256 : 8 :FLYKOOPA\n"
					  << "323 : 17 :KOOPA\n";
			break;
		}
		case 4:
		{
			writeFile << "g:\n"
					  << "0 : 60 : 20 : 24 : 0\n"
					  << "0 : 20 : 18 : 20 : 0\n"
					  << "0 : 16 : 16 : 18 : 0\n"
					  << "0 : 12 : 14 : 16 : 0\n"
					  << "-1 : 89 : 0 : 2 : 0\n"
					  << "60 : 64 : 20 : 24 : 6\n"
					  << "64 : 94 : 20 : 24 : 0\n"
					  << "49 : 89 : 2 : 12 : 0\n"
					  << "85 : 89 : 12 : 14 : 0\n"
					  << "94 : 98 : 20 : 24 : 6\n"
					  << "98 : 108 : 20 : 24 : 0\n"
					  << "102 : 104 : 14 : 16 : 1\n"
					  << "87 : 89 : 14 : 16 : 5\n"
					  << "89 : 179 : 0 : 6 : 0\n"
					  << "108 : 112 : 20 : 24 : 6\n"
					  << "112 : 172 : 16 : 24 : 0\n"
					  << "112 : 172 : 6 : 12 : 0\n"
					  << "118 : 120 : 12 : 14 : 5\n"
					  << "143 : 145 : 12 : 14 : 5\n"
					  << "170 : 172 : 12 : 14 : 5\n"
					  << "172 : 212 : 16 : 24 : 0\n"
					  << "172 : 212 : 0 : 12 : 0\n"
					  << "197 : 199 : 12 : 14 : 5\n"
					  << "212 : 302 : 18 : 24 : 0\n"
					  << "212 : 302 : 0 : 8 : 0\n"
					  << "225 : 227 : 16 : 18 : 5\n"
					  << "238 : 240 : 10 : 12 : 5\n"
					  << "238 : 240 : 8 : 10 : 0\n"
					  << "245 : 247 : 16 : 18 : 5\n"
					  << "254 : 256 : 8 : 10 : 0\n"
					  << "254 : 256 : 10 : 12 : 5\n"
					  << "263 : 265 : 16 : 18 : 5\n"
					  << "302 : 342 : 22 : 24 : 0\n"
					  << "302 : 342 : 0 : 2 : 0\n"
					  << "342 : 350 : 18 : 24 : 0\n"
					  << "350 : 354 : 22 : 24 : 0\n"
					  << "354 : 370 : 18 : 24 : 0\n"
					  << "342 : 422 : 0 : 2 : 0\n"
					  << "354 : 370 : 2 : 10 : 0\n"
					  << "416 : 422 : 2 : 10 : 0\n"
					  << "410 : 422 : 16 : 24 : 0\n"
					  << "370 : 410 : 20 : 24 : 6\n"
					  << "370 : 410 : 18 : 19 : 7\n"
					  << "411 : 412 : 15 : 16 : 8\n"
					  << "379 : 385 : 13 : 14 : 9 : 30\n"
					  << "422 : 462 : 22 : 24 : 0\n"
					  << "422 : 462 : 0 : 2 : 0\n"
					  << "455 : 456 : 7 : 22 : 11\n"
					  << "462 : 464 : -1 : 23 : 0\n"
					  << "e:\n"
					  << "102 : 20 :SFIRE\n"
					  << "245 : 16 :SFIRE\n"
					  << "254 : 11 :SFIRE\n"
					  << "143 : 12 :SFIRE\n"
					  << "170 : 12 :SFIRE\n"
					  << "197 : 12 :SFIRE\n"
					  << "225 : 16 :SFIRE\n"
					  << "405 : 15 :BOSS\n";

			break;
		}
		}
		writeFile.close();
		file.open(lName);
	}
}

void storyMode()
{
	pLives = 3;
	bool isstoryend = false;
	Map *map = new Map(120, 25);
	vector<Ground *> ground_list;
	vector<Enemy *> enemy_list;
	Player player(15, 2, pwidth, pheight, walkspeed, fallspeed, '@', *map, ground_list);
	ifstream file;
	int pLivesTemp;
	for (int i{1}; i <= 4; ++i)
	{
		openOrWrite(i, file);
		loadMap(file, ground_list, enemy_list, *map);
		file.close();
		pLivesTemp = pLives;
		setStdCoords(player);

		playLevel(ground_list, enemy_list, *map, lTime[i - 1], player, isstoryend);
		if (isstoryend)
			break;

		ground_list.clear();
		enemy_list.clear();

		if (pLives == 0)
			break;
		if (pLivesTemp != pLives)
		{
			--i;
			continue;
		}
	}

	system("cls");

	if (pLives == 0)
	{
		cout << "\nGame over!\n\n";
		cout << "\nTotal score: " << player.getScore() << "\n\n";
		system("pause");
	}
	else
	{
		if (!isstoryend)
		{
			cout << "\nYou have passed the story mode of the game, congratulations!\n\n";
			cout << "\nTotal score: " << player.getScore() << "\n\n";
			system("pause");
			system("cls");
			cout << "\nTry also creating your own world with MapCreatorand playing in it!\n\n";
			system("pause");
		}
	}
}

void spawnCoin(Player &player, vector<Ground *> &ground_list, size_t index, vector<Enemy *> &enemy_list, Map &map)
{
	Enemy *coin = new Enemy(ground_list[index]->fx1, ground_list[index]->fy1 - 1.0f, EnemyType::COIN, map, ground_list, false, false);
	enemy_list.push_back(coin);
}

void playMenu()
{
	bool isend = false, isend2 = false;
	string str;
	Map *map = new Map(120, 25);
	vector<Ground *> ground_list;
	vector<Enemy *> enemy_list;
	Player player(15, 2, 2, 2, walkspeed, fallspeed, '@', *map, ground_list);
	ifstream fin;
	while (!isend)
	{
		system("cls");
		cout << "Main Menu\n\n1 - Story mode\n2 - Load your map\n3 - Control\n4 - Back";
		switch (_getch())
		{
		case '1':
			storyMode();
			isend = true;
			break;
		case '2':
			system("cls");
			cout << "Enter file name: ";
			getline(cin, str);
			fin.open("Maps/" + str);
			if (!fin.is_open())
			{
				cout << "Error! This file doesn't exist!\n";
				system("pause");
			}
			else
			{
				pLives = 3;
				loadMap(fin, ground_list, enemy_list, *map);
				fin.close();
				playLevel(ground_list, enemy_list, *map, 320u, player, isend2);
				ground_list.clear();
				enemy_list.clear();
				isend = true;
			}
			break;
		case '3':
			system("cls");
			cout << "Control:\n\nA - walk left\nD - walk right\nLeft Shift - run/shoot\nSpace - jump\nESC - pause\n\nEnter - back to main menu";
			while (_getch() != 13)
				;
			break;
		case '4':
			isend = true;
			break;
		}
	}
	system("cls");
}

void printStat(Player &player, Timer &timer, const int endTime)
{
	timer.check();
	static unsigned int delayS = -1;
	unsigned int sec = timer.get();
	cout << "Time: " << endTime - sec << ' ';
	cout << "\nLives: " << pLives << ' ';
	cout << "\nScore: " << player.getScore();
	if (player.useStar())
	{
		if (delayS == -1)
			delayS = sec;
		cout << "\nStar: " << (unsigned int)10 - (sec - delayS) << ' ';
	}
	else
	{
		delayS = -1;
		cout << "\n        ";
	}
}

void spawnMushroom(Player &player, vector<Ground *> &ground_list, size_t index, vector<Enemy *> &enemy_list, Map &map)
{
	Enemy *mush;
	if (player.getLevel() == 1)
		mush = new Enemy(ground_list[index]->fx1, ground_list[index]->y1 - 1.0f, EnemyType::MUSHROOM, map, ground_list, true, true);
	else
		mush = new Enemy(ground_list[index]->fx1, ground_list[index]->y1 - 1.0f, EnemyType::FLOWER, map, ground_list, false, false);
	enemy_list.push_back(mush);
}

void groundCheck(vector<Ground *> &ground_list, Player &player)
{
	for (size_t i = 0; i < ground_list.size(); i++)
	{
		if (ground_list[i]->getType() == 8 && player.iy + player.height - 1 == ground_list[i]->y1 &&
			((player.ix >= ground_list[i]->x1 && player.ix < ground_list[i]->x2) || (player.ix + player.width >= ground_list[i]->x1 &&
																					 player.ix + player.width < ground_list[i]->x2)))
		{
			ground_list[i]->mode = true;
		}
		if (ground_list[i]->getType() == 8 && ground_list[i]->mode == true)
		{
			for (size_t j = 0; j < ground_list.size(); j++)
			{
				ground_list[j]->x1 = (int)round(ground_list[j]->fx1);
				ground_list[j]->x2 = (int)round(ground_list[j]->fx2);
				if (ground_list[j]->getType() == 7)
				{
					if (ground_list[j]->x1 != ground_list[j]->x2)
						ground_list[j]->fx2 -= bridgespeed;
					else
					{
						delete[] ground_list[j];
						ground_list.erase(ground_list.begin() + j);
					}
				}
			}
		}
		if (ground_list[i]->getType() == 9)
		{
			if (ground_list[i]->side == false)
			{
				ground_list[i]->setCoord(ground_list[i]->fx1 + blockspeed, ground_list[i]->fx2 + blockspeed, static_cast<float>(ground_list[i]->y1), static_cast<float>(ground_list[i]->y2));
			}
			else
			{
				ground_list[i]->setCoord(ground_list[i]->fx1 - blockspeed, ground_list[i]->fx2 - blockspeed, static_cast<float>(ground_list[i]->y1), static_cast<float>(ground_list[i]->y2));
			}
			ground_list[i]->roundCoords();
			if (ground_list[i]->x1 == ground_list[i]->getSX())
				ground_list[i]->side = false;
			if (ground_list[i]->x1 == ground_list[i]->getEX())
				ground_list[i]->side = true;
			for (int j = 0; j < static_cast<int>(ground_list.size()); j++)
				if ((ground_list[i]->x2 == ground_list[j]->x1 &&
					 ground_list[i]->y1 >= ground_list[j]->y1 && ground_list[i]->y2 < ground_list[j]->y2) ||
					(ground_list[i]->x1 - 1 == ground_list[j]->x2 &&
					 ground_list[i]->y1 >= ground_list[j]->y1 && ground_list[i]->y2 < ground_list[j]->y2))
					ground_list[i]->side = !ground_list[i]->side;
			if (player.onground && player.iy + player.height == ground_list[i]->y1 && ((player.ix >= ground_list[i]->x1 && player.ix < ground_list[i]->x2) || (player.ix + player.width >= ground_list[i]->x1 && player.ix + player.width < ground_list[i]->x2)))
			{
				if (ground_list[i]->side)
				{
					player.x -= blockspeed;
				}
				else
				{
					player.x += blockspeed;
				}
			}
		}
		if (ground_list[i]->getType() == 11)
		{
			player.ix = (int)round(player.x);
			player.iy = (int)round(player.y);
			if (player.iy + player.height >= ground_list[i]->y1 && player.iy + player.height < ground_list[i]->y2 &&
				(player.ix == ground_list[i]->x1 || player.ix + player.width - 1 == ground_list[i]->x1))
			{
				player.ctrl = false;
				if (player.onground == false)
					player.y += blockspeed / 3;
			}
		}
		if (ground_list[i]->getType() == 10)
		{
			if (ground_list[i]->side == false)
			{
				ground_list[i]->setCoord(ground_list[i]->fx1, ground_list[i]->fx2, ground_list[i]->fy1 + blockspeedy, ground_list[i]->fy2 + blockspeedy);
			}
			else
			{
				ground_list[i]->setCoord(ground_list[i]->fx1, ground_list[i]->fx2, ground_list[i]->fy1 - blockspeedy, ground_list[i]->fy2 - blockspeedy);
			}
			if (player.onground && player.iy + player.height == ground_list[i]->y1 && ((player.ix >= ground_list[i]->x1 && player.ix < ground_list[i]->x2) || (player.ix + player.width >= ground_list[i]->x1 && player.ix + player.width < ground_list[i]->x2)))
			{
				if (ground_list[i]->side)
					player.y += blockspeedy;
				else
					player.y -= blockspeedy;
			}
		}
	}
}

void pauseMenu(bool &isend, bool &isstoryend)
{
	bool ispause = true;
	while (ispause)
	{
		system("cls");
		cout << "Pause\n\n1 - Back\n2 - Control\n3 - Exit\n";
		switch ((char)_getch())
		{
		case '1':
			ispause = false;
			system("cls");
			break;
		case '2':
			system("cls");
			cout << "Control:\n\nA - walk left\nD - walk right\nLeft Shift - run/shoot\nSpace - jump\n\nEnter - back to pause menu";
			while (_getch() != 13)
				;
			break;
		case '3':
			ispause = false;
			isend = true;
			isstoryend = true;
			break;
		}
	}
	system("cls");
}

void setStdCoords(Player &player)
{
	player.x = 15.0f;
	player.y = 2.0f;
}