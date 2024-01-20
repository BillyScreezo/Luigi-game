/***********************************************************************************
 * Copyright (C) 2024 Kirill Turintsev <billiscreezo228@gmail.com>
 * See LICENSE file for licensing details.
 *
 * This file contains defenition of map creator functions
 *
 ***********************************************************************************/

#include "MapCreator.h"

using namespace std;

Ground *addNewObject_g(int x1, int y1, int x2, int y2, size_t type, Map &map)
{
	Ground *ground = new Ground(x1, x2, y1, y2, type, map);
	return ground;
}

Ground *addNewObject_g(int x1, int y1, int x2, int y2, size_t type, size_t range, Map &map)
{
	char buff[50]{0};
	Ground *ground = nullptr;
	if (type == 9)
	{
		if (range == 0)
		{
			do
			{
				system("cls");
				cout << "Enter move range of this ground type: ";
				cin >> buff;
				if (atoi(buff) <= 0)
				{
					cout << "Enter number bigger than 0!\n";
					system("pause");
				}
			} while (atoi(buff) <= 0);
			ground = new Ground(x1, x2, y1, y2, type, map, atoi(buff));
		}
		else
		{
			ground = new Ground(x1, x2, y1, y2, type, map, range);
		}
	}
	return ground;
}

Enemy *addNewObject_e(float x, float y, EnemyType type, Map &map, vector<Ground *> &ground_list)
{
	Enemy *enemy = new Enemy(x, y, type, map, ground_list);
	return enemy;
}

void loadMap(ifstream &fin, vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, Map &map)
{
	string buff, mode;
	char *dig;
	int array[6]{0};
	float arr[2]{0};
	arr[0] = -10100.0f;
	arr[1] = -10100.0f;
	for (int i = 0; i < 5; i++)
		array[i] = 0;
	while (!fin.eof())
	{
		getline(fin, buff);
		if (buff == "g:" || buff == "e:")
		{
			mode = buff;
			continue;
		}
		if (buff != "")
		{
			if (mode == "g:")
			{
				for (size_t i = 0, prev_i = -1, count = 1, c = 0; i <= buff.size(); i++, count++)
				{
					if (buff[i] == ':' || i == buff.size())
					{
						dig = new char[count];
						for (size_t j = prev_i + 1, k = 0; j < i; j++, k++)
							dig[k] = buff[j];
						dig[count - 1] = '\0';
						array[c] = atoi(dig);
						c++;
						count = 0;
						prev_i = i;
						delete[] dig;
					}
				}
				if (array[4] != 9)
					ground_list.push_back(addNewObject_g(array[0], array[2], array[1], array[3], array[4], map));
				else
					ground_list.push_back(addNewObject_g(array[0], array[2], array[1], array[3], array[4], array[5], map));
			}
			else
			{
				for (size_t i = 0, prev_i = -1, count = 1, c = 0; i <= buff.size(); i++, count++)
				{
					if (buff[i] == ':' || i == buff.size())
					{
						dig = new char[count];
						for (size_t j = prev_i + 1, k = 0; j < i; j++, k++)
							dig[k] = buff[j];
						dig[count - 1] = '\0';
						if (arr[0] != -10100.0f && arr[1] != -10100.0f)
						{
							if (strcmp(dig, "GOOMBA") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::GOOMBA, map, ground_list));
							else if (strcmp(dig, "KOOPA") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::KOOPA, map, ground_list));
							else if (strcmp(dig, "FLYKOOPA") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::FLYKOOPA, map, ground_list));
							else if (strcmp(dig, "PLANT") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::PLANT, map, ground_list));
							else if (strcmp(dig, "SFIRE") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::SFIRE, map, ground_list));
							else if (strcmp(dig, "STAR") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::STAR, map, ground_list));
							else if (strcmp(dig, "MUSHROOM") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::MUSHROOM, map, ground_list));
							else if (strcmp(dig, "LIVEMUSHROOM") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::LIVEMUSHROOM, map, ground_list));
							else if (strcmp(dig, "FLOWER") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::FLOWER, map, ground_list));
							else if (strcmp(dig, "COIN") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::COIN, map, ground_list));
							else if (strcmp(dig, "BOSS") == 0)
								enemy_list.push_back(addNewObject_e(arr[0], arr[1], EnemyType::BOSS, map, ground_list));
							arr[0] = -10100.0f;
							arr[1] = -10100.0f;
							count = 0;
							prev_i = i;
							delete[] dig;
							continue;
						}
						if (arr[0] == -10100.0f)
							arr[0] = (float)atoi(dig);
						else
						{
							if (arr[1] == -10100.0f)
								arr[1] = (float)atoi(dig);
							count = 0;
							prev_i = i;
							delete[] dig;
							continue;
						}
						count = 0;
						prev_i = i;
						delete[] dig;
					}
				}
			}
		}
	}
}

void deleteObject_g(vector<Ground *> &ground_list, int index)
{
	delete[] ground_list[index];
	ground_list.erase(ground_list.begin() + index);
}

void deleteObject_e(vector<Enemy *> &enemy_list, int index)
{
	delete[] enemy_list[index];
	enemy_list.erase(enemy_list.begin() + index);
}

void interactMenu(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, Map &map, int pos, int &gin, int &ein, bool &g_change, bool &e_change)
{
	bool isend = false, isend3 = false, isend4 = false;
	char buff[50];
	string str;
	int height, width, g_index = static_cast<int>(ground_list.size()) - 1, g_e = 0, enemy_type = 0, e_index = static_cast<int>(enemy_list.size()) - 1;
	size_t type;
	system("cls");
	while (!isend)
	{
		SetCur(0, 0);
		cout << "1 - Add new object\n2 - Edit object\n3 - Delete object\n4 - Back\n";
		switch (_getch())
		{
		case '1':
			system("cls");
			while (!isend3)
			{
				SetCur(0, 0);
				cout << "What object you want to create: ";
				if (g_e == 0)
					cout << "ground type      \n";
				if (g_e == 1)
					cout << "enemy type       \n";
				if (GetKeyState(VK_RIGHT) < 0)
				{
					g_e++;
					if (g_e == 2)
						g_e = 0;
				}
				if (GetKeyState(VK_LEFT) < 0)
				{
					g_e--;
					if (g_e == -1)
						g_e = 1;
				}
				if (_getch() == 13)
					break;
				Sleep(100);
			}
			switch (g_e)
			{
			case 0:
				system("cls");
				cout << "Enter width, height and ground type: ";
				cin >> buff;
				if (atoi(buff) <= 0)
				{
					cout << "Enter number bigger than 0!\n";
					system("pause");
					system("cls");
				}
				else
				{
					width = atoi(buff);
					cin >> buff;
					if (atoi(buff) <= 0)
					{
						cout << "Enter number bigger than 0!\n";
						system("pause");
						system("cls");
					}
					else
					{
						height = atoi(buff);
						cin >> buff;
						if (atoi(buff) < 0)
						{
							cout << "Enter number bigger than 0!\n";
							system("pause");
							system("cls");
						}
						else
						{
							type = atoi(buff);
							if (type != 9)
								ground_list.push_back(addNewObject_g(0, 0, width, height, type, map));
							else
								ground_list.push_back(addNewObject_g(0, 0, width, height, type, 0, map));
							gin = static_cast<int>(ground_list.size()) - 1;
							if (type == 3 || type == 4)
								ground_list[gin]->setSum('*');
						}
					}
				}
				break;
			case 1:
				system("cls");
				while (!isend3)
				{
					SetCur(0, 0);
					cout << "Choose enemy type: ";
					switch (enemy_type)
					{
					case 0:
						cout << "GOOMBA       \n";
						break;
					case 1:
						cout << "KOOPA        \n";
						break;
					case 2:
						cout << "FLYKOOPA     \n";
						break;
					case 3:
						cout << "PLANT        \n";
						break;
					case 4:
						cout << "SFIRE        \n";
						break;
					case 5:
						cout << "STAR        \n";
						break;
					case 6:
						cout << "MUSHROOM        \n";
						break;
					case 7:
						cout << "LIVEMUSHROOM     \n";
						break;
					case 8:
						cout << "FLOWER       \n";
						break;
					case 9:
						cout << "COIN         \n";
						break;
					case 10:
						cout << "BOSS         \n";
						break;
					}
					if (GetKeyState(VK_RIGHT) < 0)
					{
						if (enemy_type == 10)
							enemy_type = 0;
						else
							enemy_type++;
					}
					if (GetKeyState(VK_LEFT) < 0)
					{
						if (enemy_type == 0)
							enemy_type = 10;
						else
							enemy_type--;
					}
					if (_getch() == 13)
					{
						switch (enemy_type)
						{
						case 0:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::GOOMBA, map, ground_list));
							break;
						case 1:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::KOOPA, map, ground_list));
							break;
						case 2:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::FLYKOOPA, map, ground_list));
							break;
						case 3:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::PLANT, map, ground_list));
							break;
						case 4:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::SFIRE, map, ground_list));
							break;
						case 5:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::STAR, map, ground_list));
							break;
						case 6:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::MUSHROOM, map, ground_list));
							break;
						case 7:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::LIVEMUSHROOM, map, ground_list));
							break;
						case 8:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::FLOWER, map, ground_list));
							break;
						case 9:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::COIN, map, ground_list));
							break;
						case 10:
							enemy_list.push_back(addNewObject_e(0.0f, 0.0f, EnemyType::BOSS, map, ground_list));
							break;
						}
						ein = static_cast<int>(enemy_list.size()) - 1;
						break;
					}
					Sleep(100);
				}
				break;
			}
			isend = true;
			break;
		case '2':
			system("cls");
			isend3 = false;
			g_index = static_cast<int>(ground_list.size()) - 1;
			e_index = static_cast<int>(enemy_list.size()) - 1;
			if (g_index >= 0 || e_index >= 0)
			{
				while (!isend4)
				{
					SetCur(0, 0);
					cout << "What object you want to change: ";
					if (g_e == 0)
						cout << "ground type      \n";
					if (g_e == 1)
						cout << "enemy type       \n";
					if (GetKeyState(VK_RIGHT) < 0)
					{
						g_e++;
						if (g_e == 2)
							g_e = 0;
					}
					if (GetKeyState(VK_LEFT) < 0)
					{
						g_e--;
						if (g_e == -1)
							g_e = 1;
					}
					if (_getch() == 13)
					{
						system("cls");
						break;
					}
					Sleep(100);
				}
				switch (g_e)
				{
				case 0:
					isend3 = false;
					while (!isend3)
					{
						Sleep(100);
						SetCur(0, 0);
						cout << "Which object you want to change?\nSelect: ";
						cout << "gr" << g_index + 1 << "(" << ground_list[g_index]->x1 << ", " << ground_list[g_index]->x2 << ", " << ground_list[g_index]->y1 << ", " << ground_list[g_index]->y2 << ", " << ground_list[g_index]->getType() << ")        ";
						if (GetKeyState(VK_LEFT) < 0)
						{
							if (g_index == 0)
								g_index = static_cast<int>(ground_list.size()) - 1;
							else
								g_index--;
						}
						if (GetKeyState(VK_RIGHT) < 0)
						{
							if (g_index == ground_list.size() - 1)
								g_index = 0;
							else
								g_index++;
						}
						if (_getch() == 13)
						{
							system("cls");
							cout << "Enter width and height: ";
							cin >> buff;
							if (atoi(buff) <= 0)
							{
								cout << "Enter number bigger than 0!\n";
								system("pause");
								system("cls");
							}
							else
							{
								width = atoi(buff);
								cin >> buff;
								if (atoi(buff) <= 0)
								{
									cout << "Enter number bigger than 0!\n";
									system("pause");
									system("cls");
								}
								else
								{
									height = atoi(buff);
									if (ground_list[g_index]->getType() == 9)
									{
										do
										{
											system("cls");
											cout << "Enter range: " << endl;
											cin >> buff;
											if (atoi(buff) <= 0)
											{
												cout << "Enter number bigger than 0!\n";
												system("pause");
											}
										} while (atoi(buff) <= 0);
										ground_list[g_index]->setDiapasoneX(ground_list[g_index]->x1, ground_list[g_index]->x1 + atoi(buff));
									}
									ground_list[g_index]->setCoord(static_cast<float>(ground_list[g_index]->x1), static_cast<float>(ground_list[g_index]->x1 + width), static_cast<float>(ground_list[g_index]->y1), static_cast<float>(ground_list[g_index]->y1 + height));
									g_change = true;
									isend3 = true;
									isend = true;
								}
							}
							isend3 = true;
							gin = g_index;
						}
					}
					break;
				case 1:
					isend3 = false;
					if (enemy_list.size() != 0)
					{
						while (!isend3)
						{
							SetCur(0, 0);
							cout << "Which object you want to change?\nSelect: ";
							cout << "enemy" << e_index + 1 << "(" << enemy_list[e_index]->getX() << ", " << enemy_list[e_index]->getY() << ", ";
							switch (enemy_list[e_index]->getType())
							{
							case 0:
								cout << "GOOMBA)       \n";
								break;
							case 1:
								cout << "KOOPA)        \n";
								break;
							case 2:
								cout << "FLYKOOPA)     \n";
								break;
							case 3:
								cout << "PLANT)        \n";
								break;
							case 4:
								cout << "SFIRE)        \n";
								break;
							case 5:
								cout << "STAR)        \n";
								break;
							case 6:
								cout << "MUSHROOM)        \n";
								break;
							case 7:
								cout << "LIVEMUSHROOM)     \n";
								break;
							case 8:
								cout << "FLOWER)       \n";
								break;
							case 9:
								cout << "COIN)         \n";
								break;
							case 10:
								cout << "BOSS)         \n";
								break;
							}
							Sleep(100);
							if (GetKeyState(VK_LEFT) < 0)
							{
								if (e_index == 0)
									e_index = static_cast<int>(enemy_list.size()) - 1;
								else
									e_index--;
							}
							if (GetKeyState(VK_RIGHT) < 0)
							{
								if (e_index == enemy_list.size() - 1)
									e_index = 0;
								else
									e_index++;
							}
							if (_getch() == 13)
							{
								isend4 = false;
								while (!isend4)
								{
									system("cls");
									cout << "Enter type or enter \'nothing\' in order to change coords: ";
									cin >> buff;
									if (strcmp(buff, "GOOMBA") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::GOOMBA);
										break;
									}
									else if (strcmp(buff, "KOOPA") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::KOOPA);
										break;
									}
									else if (strcmp(buff, "FLYKOOPA") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::FLYKOOPA);
										break;
									}
									else if (strcmp(buff, "PLANT") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::PLANT);
										break;
									}
									else if (strcmp(buff, "SFIRE") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::SFIRE);
										break;
									}
									else if (strcmp(buff, "STAR") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::STAR);
										break;
									}
									else if (strcmp(buff, "MUSHROOM") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::MUSHROOM);
										break;
									}
									else if (strcmp(buff, "LIVEMUSHROOM") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::LIVEMUSHROOM);
										break;
									}
									else if (strcmp(buff, "FLOWER") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::FLOWER);
										break;
									}
									else if (strcmp(buff, "COIN") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::COIN);
										break;
									}
									else if (strcmp(buff, "BOSS") == 0)
									{
										enemy_list[e_index]->setType(EnemyType::BOSS);
										break;
									}
									else if (strcmp(buff, "nothing") == 0)
										break;
									else
									{
										system("cls");
										cout << "This type doesn't exist\n";
										system("pause");
									}
								}
								isend3 = true;
								isend = true;
								ein = e_index;
								e_change = true;
							}
						}
					}
					else
					{
						system("cls");
						cout << "There is no enemy\n";
						system("pause");
					}
					break;
				}
				if (GetKeyState(VK_ESCAPE) < 0)
					isend3 = true;
				Sleep(100);
			}
			else
			{
				cout << "There are no objects\n";
				system("pause");
			}
			system("cls");
			break;
		case '3':
			system("cls");
			isend3 = false;
			g_index = static_cast<int>(ground_list.size()) - 1;
			e_index = static_cast<int>(enemy_list.size()) - 1;
			while (!isend3)
			{
				SetCur(0, 0);
				cout << "What object you want to delete: ";
				if (g_e == 0)
					cout << "ground type      \n";
				if (g_e == 1)
					cout << "enemy type       \n";
				if (GetKeyState(VK_RIGHT) < 0)
				{
					g_e++;
					if (g_e == 2)
						g_e = 0;
				}
				if (GetKeyState(VK_LEFT) < 0)
				{
					g_e--;
					if (g_e == -1)
						g_e = 1;
				}
				if (_getch() == 13)
					break;
				Sleep(100);
			}
			system("cls");
			switch (g_e)
			{
			case 0:
				if (g_index >= 0)
					while (!isend3)
					{
						SetCur(0, 0);
						cout << "Which object you want to delete?\nSelect: ";
						cout << "gr" << g_index + 1 << "(" << ground_list[g_index]->x1 << ", " << ground_list[g_index]->x2 << ", " << ground_list[g_index]->y1 << ", " << ground_list[g_index]->y2 << ", " << ground_list[g_index]->getType() << ")        ";
						if (GetKeyState(VK_LEFT) < 0)
						{
							if (g_index == 0)
								g_index = static_cast<int>(ground_list.size()) - 1;
							else
								g_index--;
						}
						if (GetKeyState(VK_RIGHT) < 0)
						{
							if (g_index == ground_list.size() - 1)
								g_index = 0;
							else
								g_index++;
						}
						if (_getch() == 13)
						{
							deleteObject_g(ground_list, g_index);
							gin = -1;
							isend3 = true;
						}
						if (GetKeyState(VK_ESCAPE) < 0)
							isend3 = true;
						Sleep(100);
					}
				else
				{
					system("cls");
					cout << "There are no grounds\n";
					system("pause");
				}
				break;
			case 1:
				if (g_index >= 0)
					while (!isend3)
					{
						SetCur(0, 0);
						cout << "Which object you want to change?\nSelect: ";
						cout << "enemy" << e_index + 1 << "(" << enemy_list[e_index]->getX() << ", " << enemy_list[e_index]->getY() << ", ";
						switch (enemy_list[e_index]->getType())
						{
						case 0:
							cout << "GOOMBA)       \n";
							break;
						case 1:
							cout << "KOOPA)        \n";
							break;
						case 2:
							cout << "FLYKOOPA)     \n";
							break;
						case 3:
							cout << "PLANT)        \n";
							break;
						case 4:
							cout << "SFIRE)        \n";
							break;
						case 5:
							cout << "STAR)        \n";
							break;
						case 6:
							cout << "MUSHROOM)        \n";
							break;
						case 7:
							cout << "LIVEMUSHROOM)     \n";
							break;
						case 8:
							cout << "FLOWER)       \n";
							break;
						case 9:
							cout << "COIN)         \n";
							break;
						case 10:
							cout << "BOSS)         \n";
							break;
						}
						if (GetKeyState(VK_LEFT) < 0)
						{
							if (e_index == 0)
								e_index = static_cast<int>(enemy_list.size()) - 1;
							else
								e_index--;
						}
						if (GetKeyState(VK_RIGHT) < 0)
						{
							if (e_index == enemy_list.size() - 1)
								e_index = 0;
							else
								e_index++;
						}
						if (_getch() == 13)
						{
							deleteObject_e(enemy_list, e_index);
							isend3 = true;
						}
						if (GetKeyState(VK_ESCAPE) < 0)
							isend3 = true;
						Sleep(100);
					}
				else
				{
					system("cls");
					cout << "There are no enemies\n";
					system("pause");
				}
				break;
			}
			system("cls");
			break;
		case '4':
			isend = true;
			break;
		}
	}
	system("cls");
}

bool visualWorkSpace(vector<Ground *> &ground_list, vector<Enemy *> &enemy_list, int &pos, Map &map)
{
	int g_index = -1, e_index = -1,
		g_prev_index = g_index, e_prev_index = e_index;
	bool isend = false,
		 g_ischange = false, e_ischange = false,
		 flag = false;
	while (!isend)
	{
		SetCur(0, 0);
		map.fillSpace();
		for (size_t i = 0; i < ground_list.size(); i++)
			ground_list[i]->putOnMap();
		for (size_t i = 0; i < enemy_list.size(); i++)
			enemy_list[i]->putOnMap();
		map.printMap();
		if (GetKeyState('Q') < 0 && g_index < 0)
		{
			interactMenu(ground_list, enemy_list, map, pos, g_index, e_index, g_ischange, e_ischange);
			if (g_index <= g_prev_index && !g_ischange)
				g_index = -1;
			g_prev_index = g_index;
			if (e_index <= e_prev_index && !e_ischange)
				e_index = -1;
			e_prev_index = e_index;
			flag = true;
			if (ground_list.size() == 0 && enemy_list.size() == 0)
				flag = false;
		}
		if (g_index >= 0)
		{
			if (GetKeyState('W') < 0)
				ground_list[g_index]->setCoord(ground_list[g_index]->fx1, ground_list[g_index]->fx2, static_cast<float>(ground_list[g_index]->y1 - 1), static_cast<float>(ground_list[g_index]->y2 - 1));
			if (GetKeyState('S') < 0)
				ground_list[g_index]->setCoord(ground_list[g_index]->fx1, ground_list[g_index]->fx2, static_cast<float>(ground_list[g_index]->y1 + 1), static_cast<float>(ground_list[g_index]->y2 + 1));
			if (GetKeyState('A') < 0)
				ground_list[g_index]->setCoord(ground_list[g_index]->fx1 - 1.0f, ground_list[g_index]->fx2 - 1.0f, static_cast<float>(ground_list[g_index]->y1), static_cast<float>(ground_list[g_index]->y2));
			if (GetKeyState('D') < 0)
				ground_list[g_index]->setCoord(ground_list[g_index]->fx1 + 1.0f, ground_list[g_index]->fx2 + 1.0f, static_cast<float>(ground_list[g_index]->y1), static_cast<float>(ground_list[g_index]->y2));
			if (GetKeyState(VK_CONTROL) < 0)
			{
				g_ischange = false;
				g_index = -1;
				e_ischange = false;
				e_index = -1;
			}
			if (GetKeyState(VK_DELETE) < 0)
			{
				deleteObject_g(ground_list, g_index);
				g_index = -1;
			}
		}
		if (e_index >= 0)
		{
			if (GetKeyState('W') < 0)
				enemy_list[e_index]->setCoord(enemy_list[e_index]->getX(), enemy_list[e_index]->getY() - 1);
			if (GetKeyState('S') < 0)
				enemy_list[e_index]->setCoord(enemy_list[e_index]->getX(), enemy_list[e_index]->getY() + 1);
			if (GetKeyState('A') < 0)
				enemy_list[e_index]->setCoord(enemy_list[e_index]->getX() - 1, enemy_list[e_index]->getY());
			if (GetKeyState('D') < 0)
				enemy_list[e_index]->setCoord(enemy_list[e_index]->getX() + 1, enemy_list[e_index]->getY());
			if (GetKeyState(VK_CONTROL) < 0)
			{
				g_ischange = false;
				g_index = -1;
				e_ischange = false;
				e_index = -1;
			}
			if (GetKeyState(VK_DELETE) < 0)
			{
				deleteObject_e(enemy_list, e_index);
				e_index = -1;
			}
		}
		if (GetKeyState(VK_ESCAPE) < 0)
			isend = true;
		if (GetKeyState(VK_LEFT) < 0)
		{
			for (size_t i = 0; i < ground_list.size(); i++)
				ground_list[i]->setCoord(ground_list[i]->fx1 + 1.0f, ground_list[i]->fx2 + 1.0f, static_cast<float>(ground_list[i]->y1), static_cast<float>(ground_list[i]->y2));
			for (size_t i = 0; i < enemy_list.size(); i++)
				enemy_list[i]->setCoord(enemy_list[i]->getX() + 1, enemy_list[i]->getY());
			pos++;
		}
		if (GetKeyState(VK_RIGHT) < 0)
		{
			for (size_t i = 0; i < ground_list.size(); i++)
				ground_list[i]->setCoord(ground_list[i]->fx1 - 1.0f, ground_list[i]->fx2 - 1.0f, static_cast<float>(ground_list[i]->y1), static_cast<float>(ground_list[i]->y2));
			for (size_t i = 0; i < enemy_list.size(); i++)
				enemy_list[i]->setCoord(enemy_list[i]->getX() - 1, enemy_list[i]->getY());
			pos--;
		}
		Sleep(60);
	}
	system("cls");
	return flag;
}

void mapCreator()
{
	int iex = 0;
	string name;
	vector<Ground *> ground_list;
	vector<Enemy *> enemy_list;
	ofstream fout;
	ifstream fin;
	Map map(120, 25);
	int pos = 0, x;
	bool isend = false, flag;
	system("cls");
	while (!isend)
	{
		SetCur(0, 0);
		cout << "Do you want to create new map or import?\n\n1 - Create new\n2 - Import\n3 - Help\n4 - Exit\n";
		switch (_getch())
		{
		case '1':
			ground_list.clear();
			enemy_list.clear();
			pos = 0;
			system("cls");
			flag = visualWorkSpace(ground_list, enemy_list, pos, map);
			if (flag)
			{
				cin.ignore();
				while (name == "")
				{
					system("cls");
					cout << "Enter name of file: ";
					getline(cin, name);
				}
				x = _wmkdir(L"Maps");
				fout.open("Maps/" + name + ".txt");
				if (!fout.is_open())
				{
					cout << name + ".txt wasn't opened\n";
					system("pause");
					system("cls");
				}
				else
				{
					fout << "g:" << endl;
					for (size_t i = 0; i < ground_list.size(); i++)
					{
						ground_list[i]->roundCoords();
						fout << ground_list[i]->x1 - pos << ":" << ground_list[i]->x2 - pos << ":" << ground_list[i]->y1 << ":" << ground_list[i]->y2 << ":" << ground_list[i]->getType();
						if (ground_list[i]->getType() == 9)
							fout << ":" << ground_list[i]->getEX() - ground_list[i]->getSX() << endl;
						else
							fout << endl;
					}
					fout << "e:" << endl;
					for (size_t i = 0; i < enemy_list.size(); i++)
					{
						fout << enemy_list[i]->getX() - pos << ":" << enemy_list[i]->getY() << ":";
						switch (enemy_list[i]->getType())
						{
						case 0:
							fout << "GOOMBA";
							break;
						case 1:
							fout << "KOOPA";
							break;
						case 2:
							fout << "FLYKOOPA";
							break;
						case 3:
							fout << "PLANT";
							break;
						case 4:
							fout << "SFIRE";
							break;
						case 5:
							fout << "STAR";
							break;
						case 6:
							fout << "MUSHROOM";
							break;
						case 7:
							fout << "LIVEMUSHROOM";
							break;
						case 8:
							fout << "FLOWER";
							break;
						case 9:
							fout << "COIN";
							break;
						case 10:
							fout << "BOSS";
							break;
						}
						fout << endl;
					}
					fout.close();
				}
			}
			break;
		case '2':
			ground_list.clear();
			enemy_list.clear();
			pos = 0;
			system("cls");
			cout << "Enter name of file: ";
			getline(cin, name);
			fin.open("Maps/" + name);
			if (!fin.is_open())
			{
				cout << "This file doesn't exist!\n";
				system("pause");
				system("cls");
			}
			else
			{
				loadMap(fin, ground_list, enemy_list, map);
				for (size_t i = 0; i < ground_list.size(); i++)
				{
					if (ground_list[i]->getType() == 3)
						ground_list[i]->setSum('*');
				}
				visualWorkSpace(ground_list, enemy_list, pos, map);
				fin.close();
				fout.open("Maps/" + name);
				fout << "g:" << endl;
				for (size_t i = 0; i < ground_list.size(); i++)
				{
					ground_list[i]->roundCoords();
					fout << ground_list[i]->x1 - pos << ":" << ground_list[i]->x2 - pos << ":" << ground_list[i]->y1 << ":" << ground_list[i]->y2 << ":" << ground_list[i]->getType();
					if (ground_list[i]->getType() == 9)
						fout << ":" << ground_list[i]->getEX() - ground_list[i]->getSX() << endl;
					else
						fout << endl;
				}
				fout << "e:" << endl;
				for (size_t i = 0; i < enemy_list.size(); i++)
				{
					fout << enemy_list[i]->getX() - pos << ":" << enemy_list[i]->getY() << ":";
					switch (enemy_list[i]->getType())
					{
					case 0:
						fout << "GOOMBA";
						break;
					case 1:
						fout << "KOOPA";
						break;
					case 2:
						fout << "FLYKOOPA";
						break;
					case 3:
						fout << "PLANT";
						break;
					case 4:
						fout << "SFIRE";
						break;
					case 5:
						fout << "STAR";
						break;
					case 6:
						fout << "MUSHROOM";
						break;
					case 7:
						fout << "LIVEMUSHROOM";
						break;
					case 8:
						fout << "FLOWER";
						break;
					case 9:
						fout << "COIN";
						break;
					case 10:
						fout << "BOSS";
						break;
					}
					fout << endl;
				}
				fout.close();
			}
			break;
		case '3':
			while (true)
			{
				switch (iex)
				{
				case 0:
					system("cls");
					cout << "Control:\n\nLeft arrow - move left on the map\nRight Arrow - move right on the map\nQ - call an interactive menu for interaction\n\n"
						 << "In the interactive menu, when you select an object type or when prompted to select an object,\n"
						 << "move between types or objects on the right and left arrows\n\n"
						 << "After creating an object, moving the object around the map using the WASD keys\n\n"
						 << "Left CTRL - to save the position of the object on the map, after that you can turn to the interactive menu again\n\n"
						 << "<< Prev(Left arrow)\t\tNext(Right arrow) >>\n\nEnter in order to exit";
					break;
				case 1:
					system("cls");
					cout << "Ground types:\n\n0 - standart ground type\n1 - ? ground type with mushrooms(2x2 size)\n2 - ? ground type with coin(2x2 size)\n"
						 << "3 - invisibility ground type with mushrooms(2x2 size)\n4 - invisibility ground type with coin(2x2 size)\n5 - brick ground type(its dimensions are multiples of 2)\n"
						 << "6 - lava ground\n7 - bridge ground\n8 - handle(to lower the bridge)\n9 - flying horizontally ground\n11 - finish ground\n\n"
						 << "<< Prev\t\tNext >>\n\nEnter in order to exit";
					break;
				case 2:
					system("cls");
					cout << "Enemy types:\n\nGOOMBA\nKOOPA\nFLYKOOPA\nPLANT\nSFIRE\nSTAR\nMUSHROOM\nLIVEMUSHROOM\nFLOWER\nCOIN\nBOSS\n\n"
						 << "<< Prev\t\tNext >>\n\nEnter in order to exit";
					break;
				}
				if (GetKeyState(VK_LEFT) < 0)
					iex--;
				if (GetKeyState(VK_RIGHT) < 0)
					iex++;
				if (_getch() == 13)
					break;
				if (iex < 0)
					iex = 2;
				if (iex > 2)
					iex = 0;
				Sleep(10);
			}
			iex = 0;
			system("cls");
			break;
		case '4':
			isend = true;
			break;
		}
	}
	system("cls");
}