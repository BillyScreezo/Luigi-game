/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains declaration of Enemy class
 *
 ***********************************************************************************/

#pragma once

const int gDown = 23;
const unsigned int lTime[] = {400, 400, 300, 300};

// Foo.cpp

const int max_pX = 35;
const int spacedelay = 150;
const float bridgespeed = 0.3f;

// Player

const float fallspeed = 0.3f;
const float walkspeed = 0.5f;
const int pwidth = 2;
const int pheight = 2;
const float jumpforce = 0.9f;
const float maxblocks = 7.0f;

const size_t mushscore = 1000;

// Ground

const float blockspeed = 0.2f;
const float blockspeedy = 0.1f;

#pragma once
#include "Prototype.h"
#include "Ground.h"
#include "Player.h"
#include <vector>
#include "Const.h"

// Unique entity identifier
// Must be reset at each level
static int sID{0};

class Player;

// Entity type
enum class EnemyType
{
	// Regular enemies
	// Mushroom
	GOOMBA,
	// Turtle
	KOOPA,
	// Flying turtle
	FLYKOOPA,
	// Plant
	PLANT,

	// Special Enemies
	// Static Fire
	SFIRE,
	// Fire from boss
	BFIRE,
	// Fire from the player
	PFIRE,

	// Items (for player)
	// Star(invulnerability)
	STAR,
	// Mushroom(increase in size)
	MUSHROOM,
	// Mushroom(+1 life)
	LIVEMUSHROOM,
	// Flower (possibility to shoot)
	FLOWER,
	// Coin
	COIN,
	// Dead body
	DEADBODY,

	BOSS
};

// Type of interaction between entities
enum class Interaction
{
	ONX,
	ONY,
	ONYD,
	NOT
};

using namespace std;

class Enemy : public Prototype
{
private:
	EnemyType m_type;	 // Entity type
	bool m_move;		 // Direction of movement, true - right/up, f - left/down
	bool isFriend{true}; // The entity is friendly (to other entities) or not
	bool canFall;		 // Can an entity fall from its initial Ground
	bool throwFire{true};
	bool isSee{false};
	float yU;		   // Top level when moving PLANT && FLYKOOPA
	float yD;		   // Bottom level when moving PLANT && FLYKOOPA
	int ID;			   // Unique identificator
	int lastGroundNum; // Number of the last Ground in the list where Enemy was located
	int position;	   // Current state for SFIRE (what position it is currently in)

	// Compare two entities
	bool operator==(Enemy &);

	void inVision();

public:
	// Is the entity active
	bool status();
	bool inVis();
	// State functions
	// Is the entity friendly
	bool isFriendF();

	Enemy(float, float, EnemyType, Map &, vector<Ground *> &, bool canFall = true, bool move = false);
	Enemy(float, float, Map &);

	// MapC fun
	void setCoord(float x, float y);
	size_t getType();

	void setType(EnemyType);

	void die(bool type = true);

	// Move the entity when the player moves
	void moveR(float wspeed);

	// Is the entity dead
	virtual bool isDead() override;

	void throwFireB(vector<Enemy *> &ENEMY);

	void reset();

	// Coordinate getters
	float getX() { return x; }
	float getY() { return y; }

	// Set the entity in motion
	void move();

	// Interaction of entities with each other
	void enemyInteraction(vector<Enemy *> &, Player &);

	// Determine the type of interaction between the player and the entity
	Interaction interaction(Player &player);

	// Handle interaction between player and entity
	void processInteraction(Player &, Interaction, vector<Ground *> &);

	virtual void putOnMap() override;

	void physic(vector<Ground *> &space, Player &player);
};

enum class WorkType
{
	ENABLEALL,
	PUTONMAP,
	MOVEL,
	MOVER,
	PTHROW,
	PHYSIC,
	INTERACTION,
	MAX
};

// Check all enemies
// If the enemy is dead, delete him
void enemyCheckAndClear(vector<Enemy *> &);

void enemyModule(vector<Enemy *> &, Player &, vector<Ground *> &, Map &map, WorkType);