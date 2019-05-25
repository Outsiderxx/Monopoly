#include "Monopoly.h"

void gotoxy(int, int);
void down_gotoxy(int , int , int , int , const string [4]);
void up_gotoxy(int, int , int , int , const string [4]);

void Monopoly::playGame(bool chooseBanker)
{
	system("color 0f");
	system("cls");
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
			while (true)
			{
				if(_kbhit())
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
	const string number[4] = { "邊緣單行" ,"雙飛翱翔","三人成虎","四人混戰" };
	selectPlayer();
	int playerNum = 0;
	while (true)
	{
		if(_kbhit())
		{
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(playerNum, 54, 21, 1, number);
					if (playerNum == 0)
						playerNum = 3;
					else
						playerNum--;
				}
				else if (input == 80)
				{
					down_gotoxy(playerNum, 54, 21, 1, number);
					if (playerNum == 3)
						playerNum = 0;
					else
						playerNum++;
				}
			}
			else if (input == 13)
			{
				system("color 0f");
				system("cls");
				chooseCharacter(playerNum);
				break;
			}
		}
	}
}

void Monopoly::chooseCharacter(int num)
{
	const string character[4] = { "女高中生","操盤奸商","荒島傻蛋"," 路人69" };
	characterprint(num);
	int characterType = 0;
	for (int i = 0; i <= num; i++)
	{
		while (true)
		{
			if(_kbhit())
			{
				int input = _getch();
				if (input == 224)
				{
					input = _getch();
					if (input == 72)
					{
						up_gotoxy(characterType, 57, 7, 3, character);
						if (characterType == 0)
							characterType = 3;
						else
							characterType--;
					}
					else if (input == 80)
					{
						down_gotoxy(characterType, 57, 7, 3, character);
						if (characterType == 3)
							characterType = 0;
						else
							characterType++;
					}
				}
				else if (input == 13)
				{
					previewCharacter(characterType);
					bool haveChoose = 0;
					while (true)
					{
						int input = _getch();
						if (input == 13)
						{
							characterClear();
							haveChoose = 1;
							player.push_back(Player(characterType));
							gotoxy(25, 7 + 3 * i);
							cout << character[characterType];
							gotoxy(117, 30);
							break;
						}
						else if (input == 'q')
						{
							characterClear();
							gotoxy(117, 30);
							break;
						}
					}
					if (haveChoose)
						break;
				}
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
	while(true)
	{ 
		if(_kbhit())
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
				if (toDo == 1)
					chooseItem();
				else if (toDo == 2)
				{
					controlDice(whichPlayer);
					return 1;
				}
				else if (toDo == 3)
					saveFile();
				return 0;
			}
		}
	}
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

void Monopoly::setRound(void)
{
	const string roundDecision[] = { "10","20","30","40" };
	gotoxy(17, 19);
	cout << "選擇要遊玩的回合數:";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	gotoxy(40, 19);
	cout << roundDecision[0];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 1; i < 4; i++)
	{
		gotoxy(40, 19 + i);
		cout << roundDecision[i];
	}
	gotoxy(117, 30);
	int roundNum = 0;
	while (true)
	{
		if(_kbhit())
		{
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(roundNum, 40, 19, 1, roundDecision);
					if (roundNum == 0)
						roundNum = 3;
					else
						roundNum--;
				}
				else if (input == 80)
				{
					down_gotoxy(roundNum, 40, 19, 1, roundDecision);
					if (roundNum == 3)
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
}

int Monopoly::getPlayerNum(void)
{
	return player.size();
}

void Monopoly::chooseItem(void)
{
	int toUse = 0;
	while (true)
	{
		if(_kbhit())
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
	while (true)
	{
		if(_kbhit())
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
}

void Monopoly::loadBlock(void)
{
	int toBlock = 0;
	while (true)
	{
		if(_kbhit())
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
}

void Monopoly::destroyBlock(void)
{
	int toDestroy = 0;
	while (true)
	{
		if(_kbhit())
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
}

void Monopoly::chooseFile(void)
{
	int toLoad = 0;
	while (true)
	{
		if(_kbhit())
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
}



