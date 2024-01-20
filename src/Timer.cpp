/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition of Timer class
 *
 ***********************************************************************************/

#include "Timer.h"

Timer::Timer()
{
	time0 = 0;
	time1 = 0;
	delay = 0;
	secCounter = 0;
}
void Timer::erase()
{
	time0 = 0;
	time1 = 0;
	delay = 0;
	secCounter = 0;
}

void Timer::set()
{
	time0 = clock();
}

void Timer::check()
{
	time1 = clock();
	delay = time1 - time0;
	if (delay >= 1000)
	{
		secCounter += delay / 1000;
		time0 = clock();
	}
}

unsigned int Timer::get() { return secCounter; }