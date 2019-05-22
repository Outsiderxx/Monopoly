#include "Monopoly.h"
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <conio.h>

void Monopoly::playGame(void)
{
	//�M�w���a
	turn = dice(player.size());
	while (round > 0 && player.size() > 1)
	{
		int time = 0;
		for (int i = turn;; i++)
		{
			if (++time > player.size())
				break;
			if (i == player.size())
				i = 0;
			if (player[i].stop != 0)
			{
				player[i].stop--;
				continue;
			}
			while (_kbhit())
			{
				int input = _getch();
				//���a��ENTER
				if (input == 13)
				{
					//�Y��l
					player[i].setPosition(dice(6) + 1);
					//�P�_�ت��a
					break;
				}
				//���a��ESC�A�s�X���
				else if (input == 27)
					menu();
			}
		}
		round--;
	}
}

void Monopoly::action(int toDo)
{
	switch (toDo)
	{
	case 0:
		loadInfo("basemap.txt");
		playGame();
		break;
	case 1:
		loadInfo("special.txt");
		playGame();
		break;
	case 2:
		printManual();
		break;
	case 3:
		exitGame();
		break;
	default:
		break;
	}
}

void Monopoly::setup(void)
{

}

void Monopoly::loadInfo(string mapFile)
{
	ifstream inputFile(mapFile);
	int playerNum;
	string str;
	inputFile >> mapName >> round >> playerNum;
	for (int i = 0; i < 28; i++)
	{
		Map tmpMap;
		tmpMap.number = i;
		if (tmpMap.number == 0 || tmpMap.number == 6 || tmpMap.number == 16)
		{
			inputFile >> tmpMap.name >> tmpMap.type;
		}
		else
		{
			inputFile >> tmpMap.name >> tmpMap.type >> tmpMap.price;
			for (int i = 0; i < 4; i++)
				inputFile >> tmpMap.cost[i];
		}
		map.push_back(tmpMap);
	}
	inputFile >> str >> turn;
	for (int i = 0; i < playerNum; i++)
	{
		int num;
		inputFile >> num >> player[i].position >> player[i].money;//>>�Цa��
	}
}

void Monopoly::printManual(void)
{
	ifstream manualFile("Manual.txt");
}

void Monopoly::exitGame(void)
{
	//print �����e��
}

int Monopoly::dice(int range)
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

int Monopoly::menu(void)
{

}

void Monopoly::saveFile(void)
{

}

string Monopoly::getMapName(void)
{
	return mapName;
}

int Monopoly::getTurn(void)
{
	return turn;
}

int Monopoly::getRound(void)
{
	return round;
}