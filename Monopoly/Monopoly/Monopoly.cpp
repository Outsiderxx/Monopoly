#include "Monopoly.h"
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <conio.h>

void Monopoly::playGame(bool chooseBanker)
{
	//�M�w���a
	if(chooseBanker)
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
					player[i].position = dice(6) + 1;
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
		loadInfo("initial.txt",0);
		int flag= setPlayerNum();
		if(flag)
			playGame(1);
		break;
	case 1:
		loadInfo("basemap.txt",1);
		playGame(0);
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

bool Monopoly::setPlayerNum(void)
{
	//�C���H��
	int playerNum = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (playerNum == 0)
					playerNum = 4;
				else
					playerNum--;
			}
			else if (input == 80)
			{
				if (playerNum == 4)
					playerNum = 0;
				else
					playerNum++;
			}
		}
		else if (input == 13)
		{
			int flag = chooseCharacter(playerNum + 1);
			if (flag)
				return 1;
		}
		else if (input == 'q')
		{
			return 0;
		}
	}
}

bool Monopoly::chooseCharacter(int num)
{
	//��ܨ���
	while (true)
	{
		for (int i = 0; i < num; i++)
		{
			int characterType = 0;
			while (_kbhit())
			{
				int input = _getch();
				if (input == 224)
				{
					input = _getch();
					if (input == 72)
					{
						if (characterType == 0)
							characterType = 3;
						else
							characterType--;
					}
					else if (input == 80)
					{
						if (characterType == 3)
							characterType = 0;
						else
							characterType++;
					}
				}
				else if (input == 13)
				{
					player.push_back(Player(characterType));
				}
				else if (input == 'q')
					return 0;
			}
		}
		int flag = setRound();
		if (flag)
			return 1;
	}
}

void Monopoly::loadInfo(string mapFile,bool special)
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
	if (!special)
	{
		inputFile >> str >> turn;
		for (int i = 0; i < playerNum; i++)
		{
			int num;
			inputFile >> num >> player[i].position >> player[i].money;
			//�Цa��
		}
	}
}

void Monopoly::printManual(void)
{
	ifstream manualFile("Manual.txt");
}

void Monopoly::exitGame(void)
{
	//print �����e��
	exit(1);
}

int Monopoly::dice(int range)
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

int Monopoly::menu(void)
{
	//�ݰѦҳ]�w��m
	return 0;
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

bool Monopoly::setRound(void)
{
	cout << "��ܭn�C�����^�X��";
	int roundNum = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (roundNum == 0)
					roundNum = 4;
				else
					roundNum--;
			}
			else if (input == 80)
			{
				if (roundNum == 4)
					roundNum = 0;
				else
					roundNum++;
			}
		}
		else if (input == 13)
		{
			round = (roundNum + 1) * 10;
			return 1;
		}
		else if (input == 'q')
		{
			//�^�W�@���A����
			return 0;
		}
	}
}

int Monopoly::getPlayerNum(void)
{
	return player.size();
}