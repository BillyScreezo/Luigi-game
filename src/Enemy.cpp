/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition of Enemy class
 *
 ***********************************************************************************/

#include "Enemy.h"

void Enemy::putOnMap()
{
	roundCoords();
	if (m_type == EnemyType::SFIRE)
	{
		bool cSX{false};
		bool cSY{false};
		bool cEX{false};
		bool cEY{false};
		int start_x = ix - height, end_x = ix + height, start_y = iy - height, end_y = iy + height;
		if (iy < 0)
		{
			start_y = 0;
			cSY = true;
		}
		if (end_y > map->getHeight() - 1)
		{
			end_y = map->getHeight() - 1;
			cEY = true;
		}
		if (end_x > map->getWidth() - 1)
		{
			end_x = map->getWidth() - 1;
			cEX = true;
		}
		if (ix < 0)
		{
			start_x = 0;
			cSX = true;
		}
		if (ix < map->getWidth())
		{
			if (!cSX)
				start_x = ix;
			if (!cSY)
				start_y = iy;
			if (!cEX)
				end_x = ix + height;
			if (!cEY)
				end_y = iy + height;
			for (int i = 0; i < (end_y - start_y); i++)
			{
				for (int j = 0; j < (end_x - start_x); j++)
				{
					if (i == j)
					{
						switch (position)
						{
						case 0:
							map->field[start_y - i][start_x] = sym;
							break;
						case 1:
							map->field[start_y - i][start_x + j] = sym;
							break;
						case 2:
							map->field[start_y][start_x + j] = sym;
							break;
						case 3:
							map->field[start_y + i][start_x + j] = sym;
							break;
						case 4:
							map->field[start_y + i][start_x] = sym;
							break;
						case 5:
							map->field[start_y + i][start_x - j] = sym;
							break;
						case 6:
							map->field[start_y][start_x - j] = sym;
							break;
						case 7:
							map->field[start_y - i][start_x - j] = sym;
							break;
						}
					}
				}
			}
		}
	}
	else if (m_type == EnemyType::DEADBODY)
	{
		int tmp = score;
		int len{0};
		while (tmp != 0)
		{
			++len;
			tmp /= 10;
		}
		tmp = score;

		int start_x = ix, end_x = ix + len, start_y = iy;
		if (iy < 0)
			start_y = 0;
		if (end_x > map->getWidth() - 1)
			end_x = map->getWidth() - 1;
		if (ix < 0)
			start_x = 0;
		if (ix < map->getWidth())
		{
			int tmpSym;
			for (int i{end_x}; i > start_x; --i)
			{
				switch (tmp % 10)
				{
				case 0:
					tmpSym = '0';
					break;
				case 1:
					tmpSym = '1';
					break;
				case 2:
					tmpSym = '2';
					break;
				case 3:
					tmpSym = '3';
					break;
				case 4:
					tmpSym = '4';
					break;
				case 5:
					tmpSym = '5';
					break;
				case 6:
					tmpSym = '6';
					break;
				case 7:
					tmpSym = '7';
					break;
				case 8:
					tmpSym = '8';
					break;
				case 9:
					tmpSym = '9';
					break;
				}
				map->field[start_y][i] = tmpSym;
				tmp /= 10;
			}
		}
	}
	else
	{
		int start_x = ix, end_x = ix + width, start_y = iy, end_y = iy + height;
		if (iy < 0)
			start_y = 0;
		else
			start_y = iy;
		if (iy + height > map->getHeight() - 1)
			end_y = map->getHeight() - 1;
		else
			end_y = iy + height;
		if (ix + width > map->getWidth() - 1)
			end_x = map->getWidth() - 1;
		else
			end_x = ix + width;
		if (ix < 0)
			start_x = 0;
		if (ix < map->getWidth())
		{
			for (int i = start_y; i < end_y; i++)
				for (int j = start_x; j < end_x; j++)
					map->field[i][j] = sym;
		}
	}
}

// Reactivate the entity (turn on/off physics)
void Enemy::move() { isStand = !isStand; }

// Getting the status of the entity (active/inactive)
bool Enemy::status() { return isStand; }

bool Enemy::inVis() { return isSee; }

// Getting the status of the entity (friendly/hostile)
bool Enemy::isFriendF() { return isFriend; }

// Entity displacement when player moves Right
void Enemy::moveR(float wspeed) { x -= wspeed; }

// Getting the status of the entity (alive/dead)
bool Enemy::isDead()
{
	// If the entity is NOT killed or touched
	if (health != 0)
		return false;
	// If the entity itself died
	else if (health == 0 && m_type != EnemyType::DEADBODY)
		return true;
	// If the entity is killed by the player
	else
	{
		// Output score entity during timer
		const int timer = 1000;
		if (clock() - m_time >= timer)
			return true;
		else
			return false;
	}
}

// Compare two entities
bool Enemy::operator==(Enemy &other) { return this->ID == other.ID; }

Enemy::Enemy(float x, float y, EnemyType type, Map &map, vector<Ground *> &space, bool canFall, bool move)
{
	// General initialization
	score = 0;
	yU = 0;
	yD = 0;
	position = 0;
	lastGroundNum = 0;

	// Initialization by parameters
	// Coordinates and map
	this->x = x;
	this->y = y;
	this->map = &map;
	roundCoords();

	// Type and characteristics
	m_type = type;
	setType(m_type);
	if (m_type == EnemyType::PFIRE)
	{
		isStand = false;
		isSee = true;
	}
	else
		isStand = true;

	// Peculiarities
	m_move = move;
	this->canFall = canFall;
	ID = sID++;

	// Determine the Ground where Enemy is located
	if (!(m_type == EnemyType::SFIRE || m_type == EnemyType::PLANT || m_type == EnemyType::BOSS))
	{
		const int size = static_cast<int>(space.size());
		// Last (suitable) Ground
		int last{-1};
		// Number of Enemy "pieces" that are on the ground being checked
		bool member{false};
		// Low point Enemy
		int downDot = iy + height - 1;
		// Traverse all Ground
		for (int g{0}; g < size; ++g)
		{
			// Determine the common parts of Enemy and Ground by X
			for (int i{ix}; i <= ix + width - 1; ++i)
				if ((i >= space[g]->x1) && (i <= space[g]->x2) && (downDot <= space[g]->y1))
				{
					member = true;
					break;
				}

			if (!member)
				continue;
			else
			{
				// If the first one (suitable)
				if (last == -1)
					last = g;

				// Compare last and current
				// Which Ground is more suitable
				else
				{
					if (space[g]->y1 < space[last]->y1)
						last = g;
				}
			}
			member = false;
		}
		lastGroundNum = last;
	}
	m_time = clock();
}

Enemy::Enemy(float x, float y, Map &map)
{
	this->x = x;
	this->y = y;
	this->map = &map;
	ID = sID++;
	isStand = false;
	isSee = true;
	setType(EnemyType::BFIRE);
	roundCoords();
	m_time = clock();
}

// Death of the entity
// true - the entity died because of the player, the player gets points
// false - the entity died on its own, the player does NOT receive points
void Enemy::die(bool type)
{
	if (type)
	{
		m_type = EnemyType::DEADBODY;
		m_time = clock();
	}
	--y;
	health = 0;
}

void Enemy::inVision()
{
	if ((x >= 0) && (x <= 120))
		isSee = true;
}

// Determine the type of interaction between Enemy and Player
Interaction Enemy::interaction(Player &player)
{
	// Player does not interact with DEADBODY and PFIRE
	if (isSee == false || m_type == EnemyType::PFIRE || m_type == EnemyType::DEADBODY)
		return Interaction::NOT;
	roundCoords();
	int pIX = (int)round(player.x);
	int pIY = (int)round(player.y);
	if (m_type != EnemyType::SFIRE)
	{
		// Interaction by X
		for (int pBody{pIY}; pBody <= pIY + player.height - 1; ++pBody)
		{
			for (int eBody{iy}; eBody <= iy + height - 1; ++eBody)
			{
				if (pBody != eBody)
					continue;
				else
				{
					if ((pIX + player.width == ix) || (ix + width == pIX))
						return Interaction::ONX;

					break;
				}
			}
		}
		// Interaction on Y
		for (int pBody{pIX}; pBody <= pIX + player.width - 1; ++pBody)
		{
			for (int eBody{ix}; eBody <= ix + width - 1; ++eBody)
			{
				if (pBody != eBody)
					continue;
				else
				{
					if (pIY + player.height == iy)
						return Interaction::ONY;

					else if (iy + height == pIY)
						return Interaction::ONYD;

					break;
				}
			}
		}
	}
	else
	{
		// Interaction on Y
		for (int pBody{pIX}; pBody <= pIX + player.width - 1; ++pBody)
		{
			if ((map->field[pIY + player.height][pBody] == sym) || (map->field[pIY - 1][pBody] == sym))
				return Interaction::ONY;
		}
		// Interaction on X
		for (int pBody{pIY}; pBody <= pIY + player.height - 1; ++pBody)
		{
			if ((map->field[pBody][pIX + player.width] == sym) || (map->field[pBody][pIX - 1] == sym))
				return Interaction::ONY;
		}
	}

	return Interaction::NOT;
}

void Enemy::processInteraction(Player &player, Interaction type, vector<Ground *> &ground_list)
{
	// The player does not interact with DEADBODY and PFIRE
	switch (type)
	{
	case Interaction::ONY:
	{

		// When jumping on objects, they are picked up by the player
		if (m_type == EnemyType::COIN || m_type == EnemyType::LIVEMUSHROOM || m_type == EnemyType::STAR)
		{
			if (m_type == EnemyType::COIN)
				player.addScore(score);

			else if (m_type == EnemyType::LIVEMUSHROOM)
				player.takeLiveMushroom();

			else if (m_type == EnemyType::STAR)
				player.takeStar(score);

			die(false);
			return;
		}

		if (m_type == EnemyType::MUSHROOM || m_type == EnemyType::FLOWER)
		{
			player.levelUp();
			die();
			return;
		}

		// When jumping on other Enemy
		// Player jumps away
		player.y -= 2.7f;
		// Invulnerability kills everyone
		if (player.useStar())
		{
			player.addScore(score);
			die();
			return;
		}

		// PLANT and SFIRE and BFIRE attack Player on Y
		if (m_type == EnemyType::PLANT || m_type == EnemyType::SFIRE || m_type == EnemyType::BFIRE)
		{
			player.levelDown();
			return;
		}

		// Other Enemies take damage
		--health;
		if (m_type == EnemyType::FLYKOOPA)
		{
			setType(EnemyType::KOOPA);
			return;
		}
		if (m_type == EnemyType::KOOPA)
		{
			switch (health)
			{
			case 2:
				wspeed = 0;
				sym = '0';
				++iy;
				break;
			case 1:
			{

				wspeed = 0.6f;
				isFriend = false;
				m_move = player.side;
			}
			break;
			case 0:
				wspeed = 0;
				health = 2;
				isFriend = true;
				break;
			}
			return;
		}
		if (health == 0)
		{
			player.addScore(score);
			die();
			return;
		}
	}
	break;
	case Interaction::ONX:
	{

		// When jumping on objects, they are picked up by the player
		if (m_type == EnemyType::COIN || m_type == EnemyType::LIVEMUSHROOM || m_type == EnemyType::STAR)
		{
			if (m_type == EnemyType::COIN)
				player.addScore(score);

			else if (m_type == EnemyType::LIVEMUSHROOM)
				player.takeLiveMushroom();

			else if (m_type == EnemyType::STAR)
				player.takeStar(score);

			die(false);
			return;
		}

		if (m_type == EnemyType::MUSHROOM || m_type == EnemyType::FLOWER)
		{
			player.levelUp();
			die();
			return;
		}

		if (player.useStar())
		{
			player.addScore(score);
			die();
			return;
		}
		if (m_type == EnemyType::KOOPA && health == 2)
		{
			wspeed = 0.6f;
			isFriend = false;
			--health;
			m_move = player.side;
			if (m_move)
				x += 2;
			else
				x -= 2;
			return;
		}
		player.y -= 2.7f;
		player.levelDown();
		return;
	}
	break;
	case Interaction::ONYD:
	{

		// When jumping on objects, they are picked up by the player
		if (m_type == EnemyType::COIN || m_type == EnemyType::LIVEMUSHROOM || m_type == EnemyType::STAR)
		{
			if (m_type == EnemyType::COIN)
				player.addScore(score);

			else if (m_type == EnemyType::LIVEMUSHROOM)
				player.takeLiveMushroom();

			else if (m_type == EnemyType::STAR)
				player.takeStar(score);

			die(false);
			return;
		}

		if (m_type == EnemyType::MUSHROOM || m_type == EnemyType::FLOWER)
		{
			player.levelUp();
			die();
			return;
		}
		if (player.useStar())
		{
			player.addScore(score);
			die();
			return;
		}
		player.y -= 2.7f;
		player.levelDown();
		return;
	}
	break;
	case Interaction::NOT:
		return;
		break;
	}
}
void Enemy::throwFireB(vector<Enemy *> &ENEMY)
{
	float fX = x - 1;
	float fY = y;
	Enemy *fire = new Enemy(fX, fY, *map);
	ENEMY.push_back(fire);
}

void Enemy::physic(vector<Ground *> &space, Player &player)
{

	if (m_type == EnemyType::DEADBODY)
	{
		y -= 0.1f;
		return;
	}

	if (!isSee)
		inVision();
	if (isStand && ((m_type == EnemyType::STAR) || (m_type == EnemyType::MUSHROOM) || (m_type == EnemyType::LIVEMUSHROOM) || (m_type == EnemyType::COIN)))
		isStand = false;
	if (!isStand && isSee)
	{
		if (m_type == EnemyType::SFIRE)
		{
			if ((clock() - m_time) >= 1000)
			{
				if (position == 7)
					position = 0;
				else
					++position;
				m_time = clock();
			}
			return;
		}

		roundCoords();

		if (m_type == EnemyType::BFIRE)
		{

			// Delay before throwing
			unsigned int delay = 10;
			if (clock() - m_time <= delay)
				return;

			if (throwFire)
			{
				yD = player.y;
				throwFire = false;
			}
			else
			{
				if (iy < yD)
					y += fspeed;
				else if (iy > yD)
					y -= fspeed;
				x -= wspeed;
				if (ix <= 0)
					die(false);
			}
			return;
		}
		if (m_type == EnemyType::PLANT || m_type == EnemyType::FLYKOOPA || m_type == EnemyType::BOSS)
		{
			if (m_type == EnemyType::PLANT)
			{
				if (map->field[iy - 1][ix] == '#')
					for (int body{ix}; body <= ix + width - 1; ++body)
					{
						if (map->field[iy - 2][body] == player.getMarker())
							return;
					}
			}

			if (m_type == EnemyType::BOSS && canFall)
			{
				for (int i{0}; static_cast<size_t>(i) < space.size(); ++i)
				{
					if ((space[i]->getType() == 8) && (space[i]->mode == true))
					{
						canFall = false;
						break;
					}
				}
			}
			if (m_type == EnemyType::BOSS && !canFall)
			{

				if (iy >= gDown)
					die(false);

				else
					++y;

				return;
			}

			if (m_move && y - 1 <= yU)
				m_move = !m_move;
			else if (!m_move && y + height + 1 >= yD)
				m_move = !m_move;

			if (m_move)
			{
				y -= fspeed;
				if (m_type == EnemyType::BOSS)
					x -= 0.04f;
			}
			else
			{
				y += fspeed;
				if (m_type == EnemyType::BOSS)
					x += 0.04f;
			}

			return;
		}

		if (canFall)
		{
			const int size = static_cast<int>(space.size());
			// Last ground
			int last{-1};
			// Number of "parts" of the mob that are on the ground
			int member{false};
			int downDot = iy + height - 1;
			// Determines the number of the ground on which it is located
			for (int g{0}; g < size; ++g)
			{
				for (int i{ix}; i <= ix + width - 1; ++i)
					if ((i >= space[g]->x1) && (i <= space[g]->x2) && (downDot < space[g]->y1))
					{
						member = true;
						break;
					}

				if (!member)
					continue;
				else
				{
					if (last == -1)
						last = g;

					else
					{

						if (space[g]->y1 < space[last]->y1)
							last = g;
					}
				}
				member = false;
			}
			bool wall = false;
			if (lastGroundNum != -1)
			{
				for (int g{0}; g < size; ++g)
				{
					if ((m_move && (ix + width == space[g]->x1)) || (!m_move && (ix - 1 == space[g]->x2)))
						for (int i{iy}; i <= iy + height - 1; ++i)
						{
							if ((i >= space[g]->y1) && (i <= space[g]->y2))
							{
								m_move = !m_move;
								wall = true;
								break;
							}
						}
					if (wall)
						break;
				}

				if (last == -1)
				{
					if (iy >= gDown)
					{
						die(false);
						return;
					}
					y += fspeed;
					if (!isFriend)
					{
						if (m_move)
							x += wspeed;
						else
							x -= wspeed;
					}
				}
				else
				{
					lastGroundNum = last;

					if (downDot < space[last]->y1 - 1)
					{
						y += fspeed;
						if (!isFriend)
						{

							if (m_move)
								x += wspeed;
							else
								x -= wspeed;
						}
					}
					else
					{
						if (m_move)
							x += wspeed;
						else
							x -= wspeed;
					}
				}

				roundCoords();

				if (m_type == EnemyType::PFIRE)
				{
					for (int i{0}; i < size; ++i)
						if (iy >= space[i]->y1 && iy <= space[i]->y2 && ix >= space[i]->x1 && ix <= space[i]->x2)
							wall = true;

					if (wall)
					{
						die(false);
						return;
					}
					if (last != -1)
					{
						if (clock() - m_time >= 300)
						{
							--y;
							m_time = clock();
						}
					}
				}

				return;
			}
			else
			{
				if (iy >= gDown)
				{
					die(false);
					return;
				}
				y += fspeed;
				return;
			}
		}
		else
		{
			if (iy + height - 1 < space[lastGroundNum]->y1 - 1)
			{
				y += fspeed;
				return;
			}
			if ((ix + width == space[lastGroundNum]->x2) || (ix - 1 == space[lastGroundNum]->x1))
			{
				m_move = !m_move;
			}
			if (m_move)
				x += wspeed;
			else
				x -= wspeed;
		}
	}
}

void Enemy::enemyInteraction(vector<Enemy *> &all, Player &player)
{
	if (isSee == false || m_type == EnemyType::BFIRE || m_type == EnemyType::BOSS || m_type == EnemyType::DEADBODY || m_type == EnemyType::COIN || m_type == EnemyType::SFIRE || m_type == EnemyType::STAR || m_type == EnemyType::MUSHROOM || m_type == EnemyType::LIVEMUSHROOM || m_type == EnemyType::FLOWER || m_type == EnemyType::FLYKOOPA || m_type == EnemyType::PLANT)
		return;

	Interaction type = Interaction::NOT;
	int ixOther;
	int iyOther;
	int otherWidth;
	int otherHeight;
	bool end;
	bool otherIsFriend;
	int otherScore;
	EnemyType otherType;
	for (int i{0}; i < static_cast<int>(all.size()); ++i)
	{
		// Mob died earlier
		if (all[i] == nullptr)
			continue;
		// Mob interaction with itself
		if (*this == *all[i])
			continue;
		otherType = all[i]->m_type;
		otherIsFriend = all[i]->isFriendF();

		if (all[i]->isSee == false || otherType == EnemyType::BFIRE || otherType == EnemyType::BOSS || otherType == EnemyType::DEADBODY || otherType == EnemyType::COIN || otherType == EnemyType::SFIRE || otherType == EnemyType::PFIRE || ((otherIsFriend == false) && (isFriend == true)))
			continue;
		ixOther = (int)round(all[i]->getX());
		iyOther = (int)round(all[i]->getY());
		otherWidth = all[i]->width;
		otherHeight = all[i]->height;
		end = false;
		roundCoords();
		// Interaction by X
		for (int thisBody{iy}; thisBody <= iy + height - 1; ++thisBody)
		{
			for (int otherBody{iyOther}; otherBody <= iyOther + otherHeight - 1; ++otherBody)
			{
				if (thisBody != otherBody)
					continue;
				else
				{
					for (int i{ix}; i <= ix + width - 1; ++i)
					{
						for (int j{ixOther}; j <= ixOther + otherWidth - 1; ++j)
						{
							if (i == j)
							{
								end = true;
								break;
							}
						}
						if (end)
							break;
					}
					if (end)
						break;
					if ((ix + width == ixOther) || (ixOther + otherWidth == ix))
					{
						type = Interaction::ONX;
						end = true;
						break;
					}
				}
			}
			if (end)
				break;
		}

		if (type == Interaction::NOT && end)
			return;

		if (!end)
		{
			// Interaction on Y
			for (int thisBody{ix}; thisBody <= ix + width - 1; ++thisBody)
			{
				for (int otherBody{ixOther}; otherBody <= ixOther + otherWidth - 1; ++otherBody)
				{
					if (thisBody != otherBody)
						continue;
					else
					{
						if ((iy + height == iyOther) || (iy == iyOther + otherHeight))
						{
							// This one falls on the other one
							if (iy + height == iyOther)
								type = Interaction::ONY;
							// The other one falls on this one
							else
								type = Interaction::ONYD;
							end = true;
							break;
						}
					}
				}
				if (end)
					break;
			}
		}

		// There was no interaction
		if (!end)
			continue;

		bool isItem = otherType == EnemyType::STAR || otherType == EnemyType::MUSHROOM || otherType == EnemyType::LIVEMUSHROOM || otherType == EnemyType::FLOWER || otherType == EnemyType::FLYKOOPA || otherType == EnemyType::PLANT;
		otherScore = all[i]->getScore();
		// This one is the player's fire
		if (m_type == EnemyType::PFIRE)
		{
			if (!isItem)
			{
				player.addScore(otherScore);
				all[i]->die();
			}
			die(false);
			return;
		}
		// This one is not a friend, the other one is a friend
		if (!isFriend && !isItem && otherIsFriend)
		{
			player.addScore(otherScore);
			all[i]->die();
			continue;
		}

		// Both are friends or enemies
		if (type == Interaction::ONX)
		{
			bool changeThis{false};
			bool changeOther{false};
			bool &moveOther = all[i]->m_move;
			if (isItem)
			{
				m_move = !m_move;
				changeThis = true;
			}
			else
			{
				// Moved towards each other
				if (m_move != moveOther)
				{
					m_move = !m_move;
					changeThis = true;

					moveOther = !moveOther;
					changeOther = true;
				}
				else
				{
					if (m_move && (ix > ixOther))
					{
						moveOther = !moveOther;
						changeOther = true;
					}
					else if (m_move && (ix < ixOther))
					{
						m_move = !m_move;
						changeThis = true;
					}
					else if (!m_move && (ix > ixOther))
					{
						m_move = !m_move;
						changeThis = true;
					}
					else if (!m_move && (ix < ixOther))
					{
						moveOther = !moveOther;
						changeOther = true;
					}
				}
			}

			if (changeThis)
			{
				if (m_move)
					++x;
				else
					--x;
			}
			else if (changeOther)
			{
				if (moveOther)
					++all[i]->x;
				else
					--all[i]->x;
			}
			return;
		}

		// This one falls on the other one
		if (type == Interaction::ONY)
		{
			fspeed = 0;
		}
		if (type == Interaction::ONYD)
		{
			all[i]->fspeed = 0;
		}
	}
}

void Enemy::reset()
{
	switch (m_type)
	{
	case EnemyType::GOOMBA:
		fspeed = 0.1f;
		break;

	case EnemyType::KOOPA:
		fspeed = 0.1f;
		break;

	case EnemyType::FLYKOOPA:
		fspeed = 0.1f;
		break;

	case EnemyType::PLANT:
		fspeed = 0.01f;
		break;

	case EnemyType::STAR:
		fspeed = 0.1f;
		break;

	case EnemyType::MUSHROOM:
		fspeed = 0.1f;
		break;

	case EnemyType::LIVEMUSHROOM:
		fspeed = 0.1f;
		break;

	case EnemyType::FLOWER:
		fspeed = 0.1f;
		break;

	case EnemyType::BOSS:
		fspeed = 0.02f;
		break;
	}
}

void enemyModule(vector<Enemy *> &ENEMY, Player &player, vector<Ground *> &GROUND, Map &map, WorkType type)
{
	if (type == WorkType::PTHROW)
	{

		bool side = player.side;
		int fX;
		if (side)
			fX = static_cast<int>(player.x) + player.width;
		else
			fX = static_cast<int>(player.x) - 1;
		int fY = static_cast<int>(player.y) + player.height - 1;
		bool canSpawn{true};
		int i = fX;
		if (fX <= 0 || fY <= 0)
			canSpawn = false;
		else
		{
			while (true)
			{
				if (map.field[fY][i] == '#')
				{
					canSpawn = false;
					break;
				}
				if (side)
				{
					if (i - fX == 1)
						break;
					++i;
				}
				else
				{
					if (fX - i == 1)
						break;
					--i;
				}
			}
		}

		if (canSpawn)
		{
			Enemy *pFire = new Enemy(static_cast<float>(fX), static_cast<float>(fY), EnemyType::PFIRE, map, GROUND, true, player.side);
			ENEMY.push_back(pFire);
		}
		return;
	}

	for (int i{0}; i < static_cast<int>(ENEMY.size()); ++i)
	{
		if (ENEMY[i] == nullptr)
			continue;

		if (type == WorkType::ENABLEALL)
			ENEMY[i]->move();

		if (type == WorkType::PUTONMAP)
			ENEMY[i]->putOnMap();

		if (type == WorkType::MOVER)
			ENEMY[i]->moveR(player.wspeed);

		if (type == WorkType::PHYSIC)
		{
			ENEMY[i]->physic(GROUND, player);
			if (!ENEMY[i]->status() && ENEMY[i]->inVis() && (ENEMY[i]->getType() == 10) && ((clock() - ENEMY[i]->getTime()) >= 1500))
			{
				ENEMY[i]->throwFireB(ENEMY);
				ENEMY[i]->setTime();
			}
			ENEMY[i]->reset();
			ENEMY[i]->enemyInteraction(ENEMY, player);
			enemyCheckAndClear(ENEMY);
		}

		if (type == WorkType::INTERACTION)
		{
			if (ENEMY[i] == nullptr)
				continue;
			if (!player.status())
				ENEMY[i]->processInteraction(player, ENEMY[i]->interaction(player), GROUND);
			enemyCheckAndClear(ENEMY);
		}
	}
}

// Check all enemies
// If the enemy is dead, delete him
void enemyCheckAndClear(vector<Enemy *> &all)
{
	for (int i{0}; i < static_cast<int>(all.size()); ++i)
	{
		if (all[i] == nullptr)
			continue;
		if (all[i]->isDead())
		{
			delete all[i];
			all[i] = nullptr;
		}
	}
}

size_t Enemy::getType()
{
	switch (m_type)
	{
		// Enemies
	case EnemyType::GOOMBA:
		return 0;
		break;
	case EnemyType::KOOPA:
		return 1;
		break;
	case EnemyType::FLYKOOPA:
		return 2;
		break;
	case EnemyType::PLANT:
		return 3;
		break;
		// Special enemies
	case EnemyType::SFIRE:
		return 4;
		break; // Static fire
			   // Items
	case EnemyType::STAR:
		return 5;
		break;
	case EnemyType::MUSHROOM:
		return 6;
		break;
	case EnemyType::LIVEMUSHROOM:
		return 7;
		break;
	case EnemyType::FLOWER:
		return 8;
		break;
	case EnemyType::COIN:
		return 9;
		break;
	case EnemyType::BOSS:
		return 10;
		break;
	}
	return -1;
}

void Enemy::setCoord(float x, float y)
{
	this->x = x;
	this->y = y;
	ix = (int)round(x);
	iy = (int)round(y);
}

void Enemy::setType(EnemyType type)
{
	m_type = type;
	switch (type)
	{

	case EnemyType::GOOMBA:
		sym = '1';
		health = 1;
		score = 100;
		width = 2;
		height = 2;
		wspeed = 0.1f;
		fspeed = 0.1f;
		break;

	case EnemyType::KOOPA:
		sym = 'o';
		health = 3;
		score = 200;
		width = 2;
		height = 2;
		wspeed = 0.1f;
		fspeed = 0.1f;
		break;

	case EnemyType::FLYKOOPA:
		sym = 'O';
		health = 4;
		score = 200;
		width = 2;
		height = 2;
		wspeed = 0.0f;
		fspeed = 0.1f;
		//+
		yU = y - 10;
		yD = y + 10;
		break;

	case EnemyType::PLANT:
		sym = '|';
		health = -1;
		score = 250;
		width = 2;
		height = 2;
		wspeed = 0;
		fspeed = 0.01f;
		yU = y - height - 1;
		yD = y + height + 2;
		break;

	case EnemyType::SFIRE:
		sym = 'W';
		health = -1;
		score = 0;
		width = 3;
		height = 3;
		wspeed = 0.0f;
		fspeed = 0.0f;
		//+
		position = 0;
		break;

	case EnemyType::BFIRE:
		sym = '.';
		health = -1;
		score = 0;
		width = 2;
		height = 1;
		wspeed = 0.2f;
		fspeed = 0.2f;
		break;

	case EnemyType::PFIRE:
		sym = ',';
		health = -1;
		score = 0;
		width = 1;
		height = 1;
		wspeed = 0.5f;
		fspeed = 0.5f;
		//+
		isFriend = false;
		break;

	case EnemyType::STAR:
		sym = 'S';
		health = 1;
		score = 1000;
		width = 1;
		height = 1;
		wspeed = 0.1f;
		fspeed = 0.1f;
		break;

	case EnemyType::MUSHROOM:
		sym = '?';
		health = 1;
		score = 1000;
		width = 1;
		height = 1;
		wspeed = 0.1f;
		fspeed = 0.1f;
		break;

	case EnemyType::LIVEMUSHROOM:
		sym = '&';
		health = 1;
		score = 1000;
		width = 1;
		height = 1;
		wspeed = 0.1f;
		fspeed = 0.1f;
		break;

	case EnemyType::FLOWER:
		sym = 'X';
		health = 1;
		score = 1000;
		width = 1;
		height = 1;
		wspeed = 0.1f;
		fspeed = 0.1f;
		break;

	case EnemyType::COIN:
		sym = 'C';
		health = 1;
		score = 100;
		width = 1;
		height = 1;
		wspeed = 0.0f;
		fspeed = 0.0f;
		break;

	case EnemyType::DEADBODY:
		sym = ' ';
		health = -1;
		score = 0;
		width = 0;
		height = 0;
		wspeed = 0.0f;
		fspeed = 0.2f;
		break;
	case EnemyType::BOSS:
		sym = '3';
		health = -1;
		score = 1000;
		width = 3;
		height = 3;
		wspeed = 0.02f;
		fspeed = 0.02f;
		//+
		canFall = true;
		yU = y - 2;
		yD = y + height + 1;
		break;
	}
}