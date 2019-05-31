#include "Monopoly.h"

//遊戲
void Monopoly::playGame(bool chooseBanker)
{
	int banker, initialPlayerNum = player.size();
	if (chooseBanker)
	{
		banker = dice(player.size());
		turn = banker;
	}
	mapintitial();
	while (throughRound <= round)
	{
		if (initialPlayerNum != 1)
		{
			if (player.size() == 1)
			{
				break;
			}
		}
		else
		{

		}
		for (int time = 0; time < 4; time++, turn++)
		{
			if (turn == player.size())
				turn = 0;
			if (player[turn].stop != 0)
			{
				player[turn].stop = 0;
				continue;
			}
			hintClear();
			mapintitial();
			gotoxy(75, 3);		 cout << "現在輪到 玩家" << player[turn].number + 1 << " 骰西八刀阿";
			gotoxy(75, 5);		 cout << "按enter投擲骰子!!!!";		gotoxy(117, 30);
			while (true)
			{
				if (_kbhit())
				{
					int input = _getch();
					//玩家按ENTER
					if (input == 13)
					{
						//擲骰子
						int step = dice(6) + 1;
						gotoxy(75, 7);		
						cout << "你骰到 " << step << " 點";
						if ((player[turn].position + step) / map.size() != 0)  //經過起點獲得1000摳
						{
							gotoxy(75, 11);
							cout << "玩家" << player[turn].number + 1 << "通過起點獲得1000元獎勵";
							player[turn].money += 1000;
						}
						player[turn].position = (player[turn].position + step) % map.size();
						gotoxy(75, 9);		
						cout << "移動位置到 " << map[player[turn].position].name;
						gotoxy(117, 30);
						map[player[turn].position].areaControl(player, turn);
						break;
					}
					//玩家按ESC，叫出選單
					else if (input == 27)
					{
						int flag = menu(turn);
						menuClear(); 
						if (flag)
							break;
					}
				}
			}
		}
		throughRound++;
	}
}

//執行選擇動作: 新局 舊局 說明 離開
void Monopoly::action(int toDo)
{
	switch (toDo)
	{
	case 0:
		_chdir("D:\\My file\\Github\\Monopoly\\Monopoly\\Monopoly");
		loadInfo("initial.txt");
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

//選擇玩家人數
void Monopoly::setPlayerNum(void)
{
	const string tmp[4] = { "邊緣單行" ,"雙飛翱翔","三人成虎","四人混戰" };
	vector<string> number(tmp, tmp + 4);
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

//選擇角色
void Monopoly::chooseCharacter(int num)
{
	const string tmp[4] = { "女高中生","操盤奸商","荒島傻蛋"," 路人69" };
	vector<string> character(tmp, tmp + 4);
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
							player[player.size() - 1].number = player.size() - 1;
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

//載入資料
void Monopoly::loadInfo(string mapFile)
{
	bool isNew = 0;
	if (mapFile == "initial.txt")
		isNew = 1;
	ifstream inputFile(mapFile);
	int playerNum;
	string str;
	inputFile >> mapName >> round >> playerNum;
	for (int i = 0; i < 28; i++)
	{
		Map tmpMap;
		inputFile >> tmpMap.number >> tmpMap.name >> tmpMap.type;
		if (tmpMap.number != 0 && tmpMap.number != 6 && tmpMap.number != 16)
		{
			inputFile >> tmpMap.barrier >> tmpMap.price;
			for (int i = 0; i < 4; i++)
				inputFile >> tmpMap.cost[i];
		}
		map.push_back(tmpMap);
	}
	if (!isNew)
	{
		player.resize(playerNum);
		inputFile >> str >> turn;	
		inputFile.get();
		for (int i = 0; i < playerNum; i++)
		{
			Player tmp(0);
			string tmpStr;
			stringstream ss;
			getline(inputFile, tmpStr);
			ss << tmpStr;
			ss >> tmp.number >> tmp.character >> tmp.position >> tmp.money >> tmp.stop >> tmp.skip;
			for (int j = 0; j < tmp.item.size(); j++)
				ss >> tmp.item[j];
			player[i] = tmp;
			while (!ss.eof())
			{
				int number, level;
				ss >> number >> level;
				map[number].owner = player[i].number;
				map[number].level = level;
			}
		}
	}
}

//顯示說明
void Monopoly::printManual(void)
{
	_chdir("D:\\My file\\Github\\Monopoly\\Monopoly\\Monopoly");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("mode con cols=120 lines=30");
	ifstream manualFile("Manual.txt");
	if (manualFile.is_open())
	{
		string buffer;
		while (!manualFile.eof())
		{
			for (int i = 0; i < 31 && getline(manualFile, buffer); i++)
			{
				cout << buffer << endl;
			}
		}
	}
	else
	{
		cout << "規則說明檔遺失" << endl;
	}
	manualFile.close();
	system("pause");
}

//離開遊戲
void Monopoly::exitGame(void)
{
	//print 結束畫面
	exit(1);
}

//擲骰子
int Monopoly::dice(int range)
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

// 菜單: 繼續 使用道具 遙控骰子 存檔 離開
bool Monopoly::menu(int whichPlayer)
{
	const string tmp[] = { "繼續","使用道具","遙控骰子","存檔","離開" };
	vector<string> menuText(tmp, tmp + 5);
	firstPrint(75, 18, 2, menuText);
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
					up_gotoxy(toDo, 75, 18, 2, menuText);
					if (toDo == 0)
						toDo = 4;
					else
						toDo--;
				}
				else if (input == 80)
				{
					down_gotoxy(toDo, 75, 18, 2, menuText);
					if (toDo == 4)
						toDo = 0;
					else
						toDo++;
				}
			}
			else if (input == 13)
			{
				if (toDo == 0)
				{
					return 0;
				}
				else if (toDo == 1)
				{
					int flag= chooseItem(whichPlayer);
					if (flag)
						return 0;
				}
				else if (toDo == 2)
				{
					//使用遙控骰子，不可在骰正常骰子
					if (player[whichPlayer].item[0] != 0)
					{
						bool flag = controlDice(whichPlayer);
						if (flag)
						{
							player[whichPlayer].item[0]--;
							return 1;
						}
					}
					else
					{
						gotoxy(105, 18);
						cout << "道具不足";
						gotoxy(117, 30);
					}
				}
				else if (toDo == 3)
				{
					saveFile();
					return 0;
				}
				else if (toDo == 4)
				{
					exitGame();
				}
			}
		}
	}
}

//存檔
void Monopoly::saveFile(void)
{
	_chdir("D:\\My file\\Github\\Monopoly\\Monopoly\\Monopoly\\map");
	time_t myTime;
	myTime = time(NULL);
	string timeStr = ctime(&myTime);
	replace(timeStr.begin(), timeStr.end(), ':', ' ');
	timeStr.pop_back();
	timeStr += ".txt";
	fstream outputFile;
	outputFile.open(timeStr,ios::out);
	if (outputFile.is_open())
	{
		outputFile << mapName << " " << round - throughRound << " " << player.size() << endl;
		for (int i = 0; i < map.size(); i++)
		{
			if (map[i].type == 1)
			{
				outputFile << map[i].number << " " << map[i].name << " " << map[i].type << " ";
				outputFile << map[i].owner << " " << map[i].level << " " << map[i].barrier << " " << map[i].price << " ";
				outputFile << map[i].cost[0] << " " << map[i].cost[1] << " " << map[i].cost[2] << " " << map[i].cost[3] << endl;
			}
			else
			{
				outputFile << map[i].number << " " << map[i].name << " " << map[i].type << endl;
			}
		}
		outputFile << "playerstate" << turn << endl;
		for (int i = 0; i < player.size(); i++)
		{
			outputFile << player[i].number << " " << player[i].character << " " << player[i].position << " " << player[i].money << " ";
			outputFile << player[i].stop << " " << player[i].skip << " ";
			for (int j = 0; j < player[i].item.size(); j++)
			{
				outputFile << player[i].item[j] << " ";
			}
			for (int j = 0; j < map.size(); j++)
			{
				if (map[i].owner == i)
				{
					outputFile << map[i].number << " " << map[i].level;
				}
			}
			outputFile << endl;
		}
	}
	else
	{
		cout << "檔案開啟失敗" << endl;
	}
}

//選擇要進行的回合數
void Monopoly::setRound(void)
{
	const string tmp[] = { "10","20","30","40","50" };
	vector<string> roundDecision(tmp, tmp + 5);
	gotoxy(17, 19);
	cout << "選擇要遊玩的回合數:";
	firstPrint(40, 19, 1, roundDecision);
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
						roundNum = 4;
					else
						roundNum--;
				}
				else if (input == 80)
				{
					down_gotoxy(roundNum, 40, 19, 1, roundDecision);
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
}

//選擇要使用的道具
bool Monopoly::chooseItem(int currentPlayer)
{
	const string tmp[] = {"久逃","槌子" };
	vector<string> item(tmp, tmp + 2);
	firstPrint(90, 18, 2, item);
	int toUse = 0;
	while (true)
	{
		if(_kbhit())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(105, 18);
			cout << "        ";
			gotoxy(117, 30);
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(toUse, 90, 18, 2, item);
					if (toUse == 0)
						toUse = player[currentPlayer].item.size()-2;
					else
						toUse--;
				}
				else if (input == 80)
				{
					down_gotoxy(toUse, 90, 18, 2, item);
					if (toUse == player[currentPlayer].item.size() - 2)
						toUse = 0;
					else
						toUse++;
				}
			}
			else if (input == 13)
			{
				if (player[currentPlayer].item[toUse] != 0)
				{
					player[currentPlayer].item[toUse]--;
					useItem(toUse);
					menuClear();
					return 1;
				}
				else
				{
					gotoxy(105, 18); 
					cout << "道具不足";
					gotoxy(117, 30);
				}
			}
			else if (input == 'q')
			{
				for (int i = 18; i < 31; i++)
				{
					gotoxy(90, i);	cout << "                            ";
				}
				return 0;
			}
		}
	}
}

//使用道具
void Monopoly::useItem(int useWhich)
{
	switch (useWhich)
	{
	case 0:
		loadBlock();
		break;
	case 1:
		destroyBlock();
		break;
	}
}

//遙控骰子
bool Monopoly::controlDice(int whichPlayer)
{
	const string tmp[] = { "1點","2點" ,"3點" ,"4點" ,"5點" ,"6點" };
	vector<string> walk(tmp, tmp + 6);
	firstPrint(90, 18, 2, walk);
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
					up_gotoxy(toMove, 90, 18, 2, walk);
					if (toMove == 0)
						toMove = 5;
					else
						toMove--;
				}
				else if (input == 80)
				{
					down_gotoxy(toMove, 90, 18, 2, walk);
					if (toMove == 5)
						toMove = 0;
					else
						toMove++;
				}
			}
			else if (input == 13)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				menuClear();
				gotoxy(75, 7);
				cout << "你骰到 " << toMove + 1 << " 點";
				if ((player[turn].position + toMove + 1) / map.size() != 0)  //經過起點獲得1000摳
				{
					gotoxy(75, 11);
					cout << "玩家" << player[turn].number + 1 << "通過起點獲得1000元獎勵";
					player[turn].money += 1000;
				}
				player[turn].position = (player[turn].position + toMove + 1) % map.size();
				gotoxy(75, 9);
				cout << "移動位置到 " << map[player[turn].position].name;
				gotoxy(117, 30);
				map[player[turn].position].areaControl(player, turn);
				return 1;
			}
			else if (input == 'q')
			{
				for (int i = 18; i < 31; i++)
				{
					gotoxy(90, i);	cout << "                            ";
				}
				return 0;
			}
		}
	}
}

//設置路障
void Monopoly::loadBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(98, 18);
	cout << "輸入地點: ";
	string area;
	while (cin >> area)
	{
		gotoxy(98, 20);
		int i;
		for (i = 0; i < map.size(); i++)
		{
			if (map[i].name == area)
			{
				if (map[i].barrier == 1)
				{
					cout << "此地區已有久逃";
					gotoxy(108, 18);
					break;
				}
				else
				{
					map[i].barrier = 1;
					return;
				}
			}
		}
		if (i == map.size())
		{
			cout << "查無此地";
			gotoxy(108, 18);
			cout << "         ";
			gotoxy(108, 18);
		}
	}
}

//破壞路障
void Monopoly::destroyBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(98, 18);
	cout << "輸入地點: ";
	string area;
	while (cin >> area)
	{
		gotoxy(98, 20);
		int i;
		for (i = 0; i < map.size(); i++)
		{
			if (map[i].name == area)
			{
				if (map[i].barrier == 0)
				{
					cout << "此地區沒有久逃";
					gotoxy(108, 18);
					break;
				}
				else
				{
					map[i].barrier = 0;
					return;
				}
			}
		}
		if (i == map.size())
		{
			cout << "查無此地";
			gotoxy(108, 18);
			cout << "         ";
			gotoxy(108, 18);
		}
	}
}

//要使用的地圖
void Monopoly::chooseFile(void)
{
	system("color 0f");
	system("cls");
	_chdir("D:\\My file\\Github\\Monopoly\\Monopoly\\Monopoly\\map");
	vector<string> mapFileName;
	struct _finddata_t fileName;
	//讀取檔名

	unsigned long long hfile = _findfirst("*.txt", &fileName);
	do
	{
		mapFileName.push_back(fileName.name);
	} while (hfile != -1 && _findnext(hfile, &fileName) == 0);
	mapbasic();
	firstPrint(80, 2, 2, mapFileName);
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
					up_gotoxy(toLoad, 80, 2, 2, mapFileName);
					if (toLoad == 0)
						toLoad = mapFileName.size() - 1;
					else
						toLoad--;
				}
				else if (input == 80)
				{
					down_gotoxy(toLoad, 80, 2, 2, mapFileName);
					if (toLoad == mapFileName.size() - 1)
						toLoad = 0;
					else
						toLoad++;
				}
			}
			else if (input == 13)
			{
				loadInfo(mapFileName[toLoad]);
				break;
			}
		}
	}
} 

//取得地圖名稱
string Monopoly::getMapName(void)
{
	return mapName;
}

//取得莊家
int Monopoly::getTurn(void)
{
	return turn;
}

//取得回合數
int Monopoly::getThroughRound(void)
{
	return throughRound;
}

//取得玩家人數
int Monopoly::getPlayerNum(void)
{
	return player.size();
}

void Monopoly::mapintitial()
{
	mapbasic();
	//-------------------------------------------------------------------------------------------------------------腳色名稱
	switch (player.size())
	{
	case 1: {
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";	break; }
	case 2: {
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";
		gotoxy(19, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p               ";	break; }
	case 3: {
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";
		gotoxy(19, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p               ";
		gotoxy(37, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	cout << "3p               ";	break; }
	case 4: {
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";
		gotoxy(19, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p               ";
		gotoxy(37, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	cout << "3p               ";
		gotoxy(55, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	cout << "4p               ";	break; }
	}
	//-------------------------------------------------------------------------------------------------------------初始錢+輪到誰+回合數
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {							//原位清除
	//	gotoxy(j, 1);	cout << "                 ";
	//}
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		gotoxy(j, 1);	cout << "$" << player[i].money;
	}
	gotoxy(1, 4);		cout << turn;		gotoxy(70, 4);	cout << throughRound;
	//-------------------------------------------------------------------------------------------------------------地圖
	for (int i = 0, j = 7; i < 7; i++, j = j + 3)	//左邊
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].getName());	break; }
		case 0: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].getName());	break; }
		case 1: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].getName());	break; }
		case 2: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].getName());	break; }
		case 3: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].getName()); break; }
		}
	}
	for (int i = 7, j = 1; i < 14; i++, j = j + 9)	//下面
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].getName());	break; }
		case 0: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].getName());	break; }
		case 1: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].getName());	break; }
		case 2: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].getName());	break; }
		case 3: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].getName()); break; }
		}
	}
	for (int i = 14, j = 28; i < 21; i++, j = j - 3)	//右邊
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].getName());	break; }
		case 0: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].getName());	break; }
		case 1: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].getName());	break; }
		case 2: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].getName());	break; }
		case 3: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].getName()); break; }
		}
	}
	for (int i = 21, j = 64; i < 28; i++, j = j - 9)	//上面
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].getName());	break; }
		case 0: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].getName());	break; }
		case 1: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].getName());	break; }
		case 2: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].getName());	break; }
		case 3: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].getName()); break; }
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(73, 0);
	cout << "遊戲狀況顯示";
	gotoxy(73, 1);
	cout << "---------------------------------------------";
	gotoxy(73, 15);
	cout << "選單";
	gotoxy(73, 16);
	cout << "---------------------------------------------";
	//-------------------------------------------------------------------------------------------------------------------------所在位置
	gotoxy(117, 30);
}
