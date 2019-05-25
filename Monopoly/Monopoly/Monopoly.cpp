#include "Monopoly.h"
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <sstream>
void gotoxy(int, int);
void down_gotoxy(int , int , int , int , const string [4]);
void up_gotoxy(int, int , int , int , const string [4]);

void Monopoly::playGame(bool chooseBanker)
{
	//決定莊家
	if (chooseBanker)
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
				//玩家按ENTER
				if (input == 13)
				{
					//擲骰子
					player[i].position = (player[i].position + dice(6) + 1) % map.size();
					map[player[i].position].areaControl(player[i]);
					break;
				}
				//玩家按ESC，叫出選單
				else if (input == 27)
				{
					int flag = menu(i);
					if (flag)
						break;
				}
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
		loadInfo("initial.txt", 1);
		gameMode = 1;
		setPlayerNum();
		playGame(1);
		break;
	case 1:
		chooseFile();
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

void Monopoly::setPlayerNum(void)
{
	//遊戲人數
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
			chooseCharacter(playerNum + 1);
			break;
		}
	}
}

void Monopoly::chooseCharacter(int num)
{
	//選擇角色
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
				break;
			}
		}
	}
	setRound();
}

void Monopoly::loadInfo(string mapFile, bool isNew)
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
	if (!isNew)
	{
		inputFile >> str >> turn;
		for (int i = 0; i < playerNum; i++)
		{
			int num;
			Player tmp(0);
			string tmpStr;
			stringstream ss;
			getline(inputFile, tmpStr);
			ss << tmpStr;
			ss >> num >> tmp.position >> tmp.money;
			while (true)
			{
				int number, level;
				ss >> number >> level;
				if (ss.eof())
					break;
				map[number].owner = i;
				map[number].level = level;
			}
		}
		if (gameMode)
		{

		}
	}
}

void Monopoly::printManual(void)
{
	ifstream manualFile("Manual.txt");
}

void Monopoly::exitGame(void)
{
	//print 結束畫面
	exit(1);
}

int Monopoly::dice(int range)
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

// 0.繼續 1.使用道具 2.遙控骰子 3.存檔 4.離開
bool Monopoly::menu(int whichPlayer)
{
	int toDo = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (toDo == 0)
					toDo = 4;
				else
					toDo--;
			}
			else if (input == 80)
			{
				if (toDo == 4)
					toDo = 0;
				else
					toDo++;
			}
		}
		else if (input == 13)
		{
			switch (toDo)
			{
			case 0:
				return;
			case 1:
				int flag = chooseItem();
				if (flag == 0)
					break;
				else
					useItem(flag);
				break;
			case 2:
				controlDice(whichPlayer);
				return 1;
			case 3:
				saveFile(gameMode);
				break;
			}
			break;
		}
	}
	return 0;
}

void Monopoly::saveFile(bool)
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

void Monopoly::setRound(void)
{
	cout << "選擇要遊玩的回合數";
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
			break;
		}
	}
}

int Monopoly::getPlayerNum(void)
{
	return player.size();
}

bool Monopoly::chooseItem(void)
{
	int toUse = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (toUse == 0)
					toUse = 1;
				else
					toUse--;
			}
			else if (input == 80)
			{
				if (toUse == 1)
					toUse = 0;
				else
					toUse++;
			}
		}
		else if (input == 13)
		{
			useItem(toUse);
			break;
		}
	}
}

void Monopoly::useItem(int useWhich)
{
	switch (useWhich)
	{
	case 0:
		loadBlock();
		break;
	}
}

void Monopoly::controlDice(int whichPlayer)
{
	int toMove = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (toMove == 0)
					toMove = 5;
				else
					toMove--;
			}
			else if (input == 80)
			{
				if (toMove == 5)
					toMove = 0;
				else
					toMove++;
			}
		}
		else if (input == 13)
		{
			player[whichPlayer].position = (player[whichPlayer].position + toMove) % map.size();
			map[player[whichPlayer].position].areaControl(player[whichPlayer]);
			break;
		}
	}
}

void Monopoly::loadBlock(void)
{
	int toBlock = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (toBlock == 0)
					toBlock = map.size() - 1;
				else
					toBlock--;
			}
			else if (input == 80)
			{
				if (toBlock == map.size() - 1)
					toBlock = 0;
				else
					toBlock++;
			}
		}
		else if (input == 13)
		{
			if (!map[toBlock].barrier)
			{
				map[toBlock].barrier = 1;
				break;
			}
			else
				cout << "此地區已有障礙物";
		}
	}
}

void Monopoly::destroyBlock(void)
{
	int toDestroy = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (toDestroy == 0)
					toDestroy = map.size() - 1;
				else
					toDestroy--;
			}
			else if (input == 80)
			{
				if (toDestroy == map.size() - 1)
					toDestroy = 0;
				else
					toDestroy++;
			}
		}
		else if (input == 13)
		{
			if (map[toDestroy].barrier)
			{
				map[toDestroy].barrier = 0;
				break;
			}
			else
				cout << "此地區沒有障礙物";
		}
	}
}

void Monopoly::chooseFile(void)
{
	int toLoad = 0;
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				if (toLoad == 0)
					toLoad = map.size() - 1;
				else
					toLoad--;
			}
			else if (input == 80)
			{
				if (toLoad == map.size() - 1)
					toLoad = 0;
				else
					toLoad++;
			}
		}
		else if (input == 13)
		{
			stringstream ss;
			string file;
			ss << toLoad;
			ss >> file;
			file += ".txt";
			loadInfo(file, 0);
		}
	}
}

void up_gotoxy(int num, int x, int y, int blank, const string str[4])
{
	COORD pointup;
	pointup.X = x;  pointup.Y = y + num * blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);   //原位歸還
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	pointup.X = x;
	if (num == 0)
		pointup.Y = y + 3 * blank;
	else
		pointup.Y = y + (num - 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);   //到位反白
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == 0)
		cout << str[3];
	else
		cout << str[num - 1];
	gotoxy(117, 30);
}

void down_gotoxy(int num, int x, int y, int blank, const string str[4])
{
	COORD point;
	point.X = x; point.Y = y + num * blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);     //原位歸還
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	point.X = x;
	if (num == 3)
		point.Y = y;
	else
		point.Y = y + (num + 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);     //到位反白
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == 3)
		cout << str[0];
	else
		cout << str[num + 1];
	gotoxy(117, 30);
}

void gotoxy(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}