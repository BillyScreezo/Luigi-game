/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition of Prototype class
 *
 ***********************************************************************************/

#include "Prototype.h"

void Prototype::putOnMap()
{
    roundCoords();
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

void Prototype::die() {}
bool Prototype::isDead() { return health == 0; }
char Prototype::getMarker() { return sym; }
void Prototype::jump() { y -= 4; }
int Prototype::getScore() { return score; }

void Prototype::roundCoords()
{
    ix = (int)round(x);
    iy = (int)round(y);
}

unsigned int Prototype::getTime() { return m_time; }
void Prototype::setTime() { m_time = clock(); }