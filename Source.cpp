/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains Main function
 *
 ***********************************************************************************/

#include "Levels.h"
#include "Foo.h"
#include "MapCreator.h"
#include <vector>

extern int pLives = 3;
using namespace std;

int main()
{
	HideCursor();
	bool isend = false;
	while (!isend)
	{
		SetCur(0, 0);
		cout << "Main Menu\n\n1 - Play\n2 - Map Creator\n3 - Exit\n";
		switch (_getch())
		{
		case '1':
			playMenu();
			break;
		case '2':
			system("cls");
			mapCreator();
			break;
		case '3':
			isend = true;
			break;
		default:
			cout << "There is no action\n";
			system("pause");
			system("cls");
		}
	}
	return 0;
}