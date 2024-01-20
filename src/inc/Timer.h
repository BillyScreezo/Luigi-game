/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains declaration of Timer class
 *
 ***********************************************************************************/

#pragma once
#include <ctime>

class Timer
{
private:
	unsigned int time0, time1, delay;
	int secCounter;

public:
	Timer();
	void erase();
	void set();
	void check();
	unsigned int get();
};
