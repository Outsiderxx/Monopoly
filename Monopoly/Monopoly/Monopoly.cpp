#include "Monopoly.h"

//遊戲流程
void Monopoly::playGame(bool chooseBanker)
{
	int banker, initialPlayerNum = player.size();
	const string zanzu[4] = { "安美肌防賽乳","娘家滴肌精","單身俱樂部","30公分好棒棒" };
	//決定起手點
	if (chooseBanker)
	{
		banker = dice(player.size());
		turn = banker;
		gotoxy(80,5);
		cout << "本局遊戲由玩家 " << turn + 1 << " 開始";
		gotoxy(80, 9);
		cout << "Press ENTER to start!!!";
		gotoxy(85, 17);
		int zan = rand() % 4;
		if (zan == 0)
			cout << "感謝" << zanzu[0] << "冠名贊助";
		else if (zan == 1)
			cout << "感謝" << zanzu[1] << "冠名贊助";
		else if (zan == 2)
			cout << "感謝" << zanzu[2] << "冠名贊助";
		else if (zan == 3)
			cout << "感謝" << zanzu[3] << "冠名贊助";
		pressEnter();
	}
	//顯示畫面
	mapinitial();
	//剩餘回合不為零
	int flag = 0;
	if (chooseBanker)
		flag = 1;
	while (throughRound <= round)
	{
		if (throughRound == round)
		{
			gotoxy(80, 5);
			cout << "最後一回合囉 ";
			gotoxy(80, 7);	cout << "現金最多才是老大啦 ";
			gotoxy(92, 9);	cout << "小朋友才+銀行股票!!!";
			gotoxy(94, 14);	cout << "Press ENTER to continue";
			pressEnter();
			mapinitial();
		}
		//股價波動
		if(flag)
			stockPriceFlow();
		flag = 1;
		for (int time = 0; time < player.size(); time++, turn++)
		{
			moneyChanged();
			//玩家人數大於1人
			if (initialPlayerNum != 1)
			{
				//為破產人數剩一人結束
				int num = 0;
				for (int i = 0; i < player.size(); i++)
				{
					if (player[i].state)
						num++;
				}
				if (num == 1)
					goto end;
			}
			//玩家人數一人
			else
			{
				//玩家破產結束
				if (player[0].money < 0)
				{
					goto end;
				}
			}
			if (turn == player.size())
				turn = 0;
			if (player[turn].isLoan)
			{
				player[turn].loanTime--;
				if (player[turn].loanTime == 1)
				{
					gotoxy(80, 5);
					cout << "準備還錢囉";
					gotoxy(85, 7);
					cout << "Press ENTER to continue";
					pressEnter();
				}
				else if (player[turn].loanTime == 0)
				{
					player[turn].isLoan = 0;
					gotoxy(80, 5);
					cout << "還錢囉 金錢減10000摳";
					player[turn].money -= 10000;
					moneyChanged();
					if (player[turn].money < 0)
					{
						gotoxy(80, 9);
						cout << "玩家 " << turn + 1 << " 破產啦QQ";
						player[turn].state = 0;
					}
					gotoxy(80, 7);
					cout << "Press ENTER to continue";
					pressEnter();
				}
			}
			for (int i = 0; i < map.size(); i++)
			{
				if (map[i].owner != -1)
				{
					if (!player[map[i].owner].state)
					{
						map[i].owner = -1;
						map[i].level = 0;
					}
				}
			}
			//玩家是否破產
			if (!player[turn].state)
			{
				positionClear(turn);
				continue;
			}
			//玩家是否被暫停
			if (player[turn].stop != 0)
			{
				gotoxy(80, 5);
				cout << "媽的SOD還要演" << (player[turn].stop) << "次";
				player[turn].stop--;
				gotoxy(80, 7);
				cout << "Press ENTER to 暫停次數減一";
				pressEnter();
				continue;
			}
			mapinitial();
			if (player[turn].character == 2)
			{
				gotoxy(80, 5);
				int ran = rand() % 5;
				if (ran ==0)
				{
					cout << "朝爽德~ 撿到500快哩~";
					player[turn].money += 500;
					gotoxy(80, 9);
					cout << "Press ENTER to continue";
					pressEnter();
				}
				else if(ran == 1)
				{
					cout << "看 ! 哪個咩偷幹我..";
					gotoxy(80, 7);	cout << ".............500摳謀起阿 ! !";
					player[turn].money -= 500;
					gotoxy(80, 9);
					cout << "Press ENTER to continue";
					pressEnter();
				}
				mapinitial();
			}
			if (player[turn].character == 3)
			{
				if (rand() % 5 == 0)		//-------------------------------------機率調整
				{
					gotoxy(82, 5);	cout << "路人69的技能發動了zzz";
					gotoxy(82, 7);	cout << "漱公魔法卡-->高雄發大財";
					gotoxy(82, 9);	cout << "然而.............";
					gotoxy(82, 10);	cout << ".................什麼事都沒發生";
					gotoxy(82, 12);	cout << "Press ENTER to continue";
					pressEnter();
				}
				mapinitial();
			}
			gotoxy(80, 3);		 cout << "現在輪到 玩家" << player[turn].number + 1 << " 骰西八刀阿";
			gotoxy(80, 5);		 cout << "按enter投擲骰子!!!!";		gotoxy(117, 30);
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
						gotoxy(80, 7);		
						cout << "你骰到 " << step << " 點";
						if (step == 1)
						{
							gotoxy(90, 7); cout << "逼機啦 ~ ~";
						}
						while (true)
						{
							positionClear(turn);
							//判斷路途中是否有久逃
							for (int i = 1; i <= step; i++)
							{
								//被阻擋
								if (map[(player[turn].position + i) % 28].barrier)
								{
									gotoxy(80, 13);
									cout << "阿怎麼路上也有捕人夾 ? ?";
									map[(player[turn].position + i) % 28].barrier = 0;
									step = i;
									break;
								}
							}
							//前進經過起點獲得1000摳
							if ((player[turn].position + step) > 27)  
							{
								gotoxy(80, 11);
								cout << "玩家" << player[turn].number + 1 << "通過起點獲得1000元獎勵";
								player[turn].money += 1000;
								player[turn].position = (player[turn].position + step) % map.size();
								positionChanged();
							}
							//後退經過起點(命運case)
							else if ((player[turn].position + step) < 0)
							{
								player[turn].position += 28 + player[turn].position - step;
								positionChanged();
							}
							//正常前進
							else
							{
								player[turn].position += step;
								positionChanged();
							}
							gotoxy(80, 9);
							cout << "移動到 " << map[player[turn].position].name;
							//事件判斷
							int flag = map[player[turn].position].areaControl(player, turn);
							//正常事件
							if (flag == 4)
							{
								break;
							}
							//前進後退
							else 
							{
								step = flag;
								gotoxy(94, 30);
								cout << "Press ENTER to continue";
								pressEnter();
								menuClear();
							}
						}
						break;
					}
					//玩家按ESC，叫出選單
					else if (input == 27)
					{
						int flag = menu(turn);
						if (flag == 1)
						{
							break;
						}
						else if (flag == 2)
						{
							goto end;
						}
						else
						{
							mapinitial();
							gotoxy(80, 3);		 cout << "現在輪到 玩家" << player[turn].number + 1 << " 骰西八刀阿";
							gotoxy(80, 5);		 cout << "按enter投擲骰子!!!!";		gotoxy(117, 30);
						}
					}
				}
			}
			gotoxy(94, 30);
			cout << "Press ENTER to continue";
			pressEnter();
			hintClear();
		}
		throughRound++;
		//改變經過回合數
		mapinitial();
	}
	end:
	//判斷勝負
	win();
}

//執行選擇動作: 新局 舊局 說明 離開
void Monopoly::action(int toDo)
{
	int flag;
	switch (toDo)
	{
	case 0:
		loadInfo("initial.txt");
		flag = setPlayerNum();
		if (flag)
		{
			playGame(1);
		}
		break;
	case 1:
		flag = chooseFile();
		if (flag)
		{
			hintClear();
			playGame(0);
		}
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
bool Monopoly::setPlayerNum(void)
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
				int flag = chooseCharacter(playerNum);
				if (flag)
					return 1;
				playerNum = 0;
				menuprint();
				selectPlayer();
			}
			else if (input == 27)
				return 0;
		}
	}
}

//選擇角色
bool Monopoly::chooseCharacter(int num)
{
	const string tmp[4] = { "女高中生","操盤奸商","荒島傻蛋"," 路人69" };
	vector<string> character(tmp, tmp + 4);
	while (true)
	{
		characterprint(num);
		int characterType = 0;
		for (int i = 0; i <= num; i++)
		{
			while (true)
			{
				if (_kbhit())
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
							else if (input == 27)
							{
								player.clear();
								return 0;
							}
						}
						if (haveChoose)
							break;
					}
					else if (input == 27)
					{
						player.clear();
						return 0;
					}
				}
			}
		}
		int flag = setRound();
		if (flag)
			return 1;
	}
}

//載入資料
void Monopoly::loadInfo(string mapFile)
{	
	bool isNew = 0;
	if (mapFile == "initial.txt")
		isNew = 1;
	else
		_chdir(".\\map");
	ifstream inputFile(mapFile);
	int playerNum;
	string str;
	inputFile >> mapName >> round >> playerNum;
	for (int i = 0; i < 28; i++)
	{
		Map tmpMap;
		inputFile >> tmpMap.number >> tmpMap.name >> tmpMap.type;
		if (tmpMap.type == 1)
		{
			inputFile >> tmpMap.barrier >> tmpMap.price;
			for (int i = 0; i < 4; i++)
				inputFile >> tmpMap.cost[i];
		}
		map.push_back(tmpMap);
	}
	if (!isNew)
	{
		upLimit.resize(3);
		downLimit.resize(3);
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
			ss >> tmp.number >> tmp.character >> tmp.state >> tmp.position >> tmp.money >> tmp.stop >> tmp.skip;
			for (int j = 0; j < tmp.item.size(); j++)
			{
				ss >> tmp.item[j];
			}
			ss >> tmp.deposit >> tmp.isLoan >> tmp.loanTime;
			for (int i = 0; i < 3; i++)
			{
				ss >> tmp.ownStock[i];
			}
			player[i] = tmp;
			while (!ss.eof())
			{
				int number, level;
				ss >> number >> level;
				map[number].owner = player[i].number;
				map[number].level = level;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			inputFile >> stockPrice[i];
		}
		for (int i = 0; i < 3; i++)
		{
			bool num;
			inputFile >> num;
			upLimit[i] = num;
		}
		for (int i = 0; i < 3; i++)
		{
			bool num;
			inputFile >> num;
			downLimit[i] = num;
		}
	}
	inputFile.close();
	if(mapFile!="initial.txt")
		_chdir("..");
}

//顯示說明
void Monopoly::printManual(void)
{
	system("cls");
	system("mode con cols=118 lines=31");
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
			system("pause");
			system("cls");
		}
	}
	else
	{
		cout << "規則說明檔遺失" << endl;
	}
	manualFile.close();
}

//離開遊戲
void Monopoly::exitGame(void)
{
	//print 結束畫面
	exitprint();
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
int Monopoly::menu(int whichPlayer)
{
	const string tmp[] = { "繼續","銀行","使用道具","遙控骰子","存檔","回主畫面","離開" };
	vector<string> menuText(tmp, tmp + 7);
	firstPrint(75, 17, 2, menuText);
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
					up_gotoxy(toDo, 75, 17, 2, menuText);
					if (toDo == 0)
						toDo = 6;
					else
						toDo--;
				}
				else if (input == 80)
				{
					down_gotoxy(toDo, 75, 17, 2, menuText);
					if (toDo == 6)
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
					menuClear();
					const string tmp[] = { "ATM","股票交易" };
					vector<string> bank(tmp, tmp + 2);
					gotoxy(73, 17);
					cout << "選擇要使用的功能";
					firstPrint(75, 19, 5, bank);
					bool goTo = 0;
					while (true)
					{
						if (_kbhit())
						{
							int input = _getch();
							if (input == 224)
							{
								input = _getch();
								down_gotoxy(goTo, 75, 19, 5, bank);
								goTo = 1 - goTo;
							}
							else if (input == 13)
							{
								//股票
								if (goTo)
								{
									stock(player[turn]);
								}
								//ATM
								else
								{
									atm(player[turn]);
								}
							}
							else if (input == 'q')
							{
								menuClear();
								toDo = 0;
								firstPrint(75, 17, 2, menuText);
								break;
							}
						}
					}
				}
				else if (toDo == 2)
				{
					int flag= chooseItem(whichPlayer);
					if (flag)
						return 0;
				}
				else if (toDo == 3)
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
				else if (toDo == 4)
				{
					saveFile();
					return 0;
				}
				else if (toDo == 5)
				{
					return 2;
				}
				else if (toDo == 6)
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
	_chdir(".\\map");
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
		outputFile << mapName << " " << round - throughRound + 1 << " " << player.size() << endl;
		for (int i = 0; i < map.size(); i++)
		{
			if (map[i].type == 1)
			{
				outputFile << map[i].number << " " << map[i].name << " " << map[i].type << " ";
				outputFile << map[i].barrier << " " << map[i].price << " ";
				outputFile << map[i].cost[0] << " " << map[i].cost[1] << " " << map[i].cost[2] << " " << map[i].cost[3] << endl;
			}
			else
			{
				outputFile << map[i].number << " " << map[i].name << " " << map[i].type << endl;
			}
		}
		outputFile << "playerstate " << turn << endl;
		for (int i = 0; i < player.size(); i++)
		{
			outputFile << player[i].number << " " << player[i].character << " " << player[i].state << " " << player[i].position << " " << player[i].money << " ";
			outputFile << player[i].stop << " " << player[i].skip;
			for (int j = 0; j < player[i].item.size(); j++)
			{
				outputFile << " " << player[i].item[j];
			}
			outputFile << " " << player[i].deposit << " " << player[i].isLoan << " " << player[i].loanTime;
			for (int j = 0; j < 3; j++)
			{
				outputFile << " " << player[i].ownStock[j];
			}
			for (int j = 0; j < map.size(); j++)
			{
				if (map[j].owner == i)
				{
					outputFile << " " << map[j].number << " " << map[j].level;
				}
			}
			outputFile << endl;
		}
		for (int i = 0; i < 3; i++)
		{
			outputFile << stockPrice[i] << " ";
		}
		for (int i = 0; i < 3; i++)
		{
			outputFile << upLimit[i] << " ";
		}
		for (int i = 0; i < 3; i++)
		{
			outputFile << downLimit[i] << " ";
		}
		outputFile << endl;
	}
	else
	{
		cout << "檔案開啟失敗" << endl;
	}
	outputFile.close();
	_chdir("..");
}

//選擇要進行的回合數
bool Monopoly::setRound(void)
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
				return 1;
			}
			else if (input == 27)
			{
				for (int i = 19; i < 29; i++)
				{
					gotoxy(17, i);
					cout << "                         ";
				}
				return 0;
			}
		}
	}
}

//選擇要使用的道具
bool Monopoly::chooseItem(int currentPlayer)
{
	const string tmp[] = {"捕人夾","拆夾工","炸彈"};
	vector<string> item(tmp, tmp + 3);
	firstPrint(86, 18, 2, item);
	for (int i = 0; i < item.size(); i++)
	{
		gotoxy(92, 18 + 2 * i);
		cout << " * " << player[currentPlayer].item[i + 1];
	}
	gotoxy(117,30);
	int toUse = 0;
	while (true)
	{
		if(_kbhit())
		{
			gotoxy(105, 18);
			cout << "        ";
			gotoxy(117, 30);
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(toUse, 86, 18, 2, item);
					if (toUse == 0)
						toUse = player[currentPlayer].item.size()-2;
					else
						toUse--;
				}
				else if (input == 80)
				{
					down_gotoxy(toUse, 86, 18, 2, item);
					if (toUse == player[currentPlayer].item.size() - 2)
						toUse = 0;
					else
						toUse++;
				}
			}
			else if (input == 13)
			{
				if (player[currentPlayer].item[toUse + 1] != 0)
				{
					int flag = useItem(toUse);
					if (flag)
					{
						player[currentPlayer].item[toUse + 1]--;
						menuClear();
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
			else if (input == 'q')
			{
				for (int i = 18; i < 31; i++)
				{
					gotoxy(86, i);	cout << "                                ";
				}
				return 0;
			}
		}
	}
}

//使用道具
bool Monopoly::useItem(int useWhich)
{
	bool flag;
	switch (useWhich)
	{
	case 0:
		flag = loadBlock();
		return flag;
	case 1:
		flag = destroyBlock();
		return flag;
	case 2:
		flag = bomb();
		return flag;
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
				menuClear();
				int step = toMove + 1;
				gotoxy(80, 7);
				cout << "你選擇移動 " << step << " 步";
				while (true)
				{
					positionClear(turn);
					//判斷路途中是否有久逃
					for (int i = 1; i <= step; i++)
					{
						//被阻擋
						if (map[(player[turn].position + i) % 28].barrier)
						{
							gotoxy(80, 13);
							cout << "阿怎麼路上也有捕人夾 ? ?";
							map[(player[turn].position + i) % 28].barrier = 0;
							step = i;
							break;
						}
					}
					//前進經過起點獲得1000摳
					if ((player[turn].position + step) > 27)
					{
						gotoxy(80, 11);
						cout << "玩家" << player[turn].number + 1 << "通過起點獲得1000元獎勵";
						player[turn].money += 1000;
						player[turn].position = (player[turn].position + step) % map.size();
						positionChanged();
					}
					//後退經過起點(命運case)
					else if ((player[turn].position + step) < 0)
					{
						player[turn].position += 28 + player[turn].position - step;
						positionChanged();
					}
					//正常前進
					else
					{
						player[turn].position += step;
						positionChanged();
					}
					gotoxy(80, 9);
					cout << "移動到 " << map[player[turn].position].name;
					//事件判斷
					int flag = map[player[turn].position].areaControl(player, turn);
					//正常事件
					if (flag == 4)
					{
						break;
					}
					//前進後退
					else
					{
						step = flag;
						gotoxy(94, 30);
						cout << "Press ENTER to continue";
						pressEnter();
						menuClear();
					}
				}
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
bool Monopoly::loadBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	gotoxy(98, 18);
	cout << "輸入地點: ";
	string area;
	while (cin >> area)
	{
		if (area == "q")
		{
			for (int i = 17; i < 31; i++)
			{
				gotoxy(98, i);
				cout << "                 ";
			}
			return 0;
		}
		gotoxy(98, 20);
		int i;
		for (i = 0; i < map.size(); i++)
		{
			if (map[i].name == area)
			{
				if (map[i].type != 1)
				{
					cout << "非法地區";
					inputClear();
					break;
				}
				else
				{
					if (map[i].barrier == 1)
					{
						cout << "此地區已有捕人夾";
						inputClear();
						break;
					}
					else
					{
						map[i].barrier = 1;
						return 1;
					}
				}
			}
		}
		if (i == map.size())
		{
			cout << "查無此地";
			inputClear();
		}
	}
}

//破壞路障
bool Monopoly::destroyBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	gotoxy(98, 18);
	cout << "輸入地點: ";
	string area;
	while (cin >> area)
	{
		if (area == "q")
		{
			for (int i = 17; i < 31; i++)
			{
				gotoxy(98, i);
				cout << "                 ";
			}
			return 0;
		}
		gotoxy(98, 20);
		int i;
		for (i = 0; i < map.size(); i++)
		{
			if (map[i].name == area)
			{
				if (map[i].type != 1)
				{
					cout << "非法地區";
					inputClear();
					break;
				}
				else
				{
					if (map[i].barrier == 0)
					{
						cout << "此地區沒有捕人夾";
						inputClear();
						break;
					}
					else
					{
						map[i].barrier = 0;
						return 1;
					}
				}
			}
		}
		if (i == map.size())
		{
			cout << "查無此地";
			inputClear();
		}
	}
}

bool Monopoly::bomb()
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	gotoxy(98, 18);
	cout << "輸入地點: ";
	string area;
	while (cin >> area)
	{
		if (area == "q")
		{
			for (int i = 17; i < 31; i++)
			{
				gotoxy(98, i);
				cout << "                 ";
			}
			return 0;
		}
		gotoxy(98, 20);
		int i;
		for (i = 0; i < map.size(); i++)
		{
			if (map[i].name == area)
			{
				if (map[i].type != 1)
				{
					cout << "非法地區";
					inputClear();
					break;
				}
				else
				{
					if (map[i].owner == -1)
					{
						cout << "此地區沒有建築";
						inputClear();
						break;
					}
					else
					{
						map[i].owner = -1;
						map[i].level = 0;
						return 1;
					}
				}
			}
		}
		if (i == map.size())
		{
			cout << "查無此地";
			inputClear();
		}
	}
}

//要使用的地圖
bool Monopoly::chooseFile(void)
{
	system("color 0f");
	system("cls");
	_chdir(".\\map");
	vector<string> mapFileName;
	struct _finddata_t fileName;
	//讀取檔名
	unsigned long long hfile = _findfirst("*.txt", &fileName);
	do
	{
		mapFileName.push_back(fileName.name);
	} while (hfile != -1 && _findnext(hfile, &fileName) == 0);
	_chdir("..");
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
				return 1;
			}
			else if (input == 27)
			{
				return 0;
			}
		}
	}
} 

void Monopoly::mapinitial()
{
	mapbasic();
	const string tmp[4] = { "女高中生","操盤奸商","荒島傻蛋"," 路人69" };
	//-------------------------------------------------------------------------------------------------------------腳色名稱
	int playernum = player.size();
	switch (playernum)
	{
	case 1: {
		gotoxy(1, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); cout << playernum << "p " << tmp[player[playernum - 1].character] << "      "; break; }
	case 2: {
		gotoxy(1, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); cout << (playernum - 1) << "p " << tmp[player[playernum - 2].character] << "      ";
		gotoxy(19, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39); cout << playernum << "p " << tmp[player[playernum - 1].character] << "      ";  break; }
	case 3: {
		gotoxy(1, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); cout << (playernum - 2) << "p " << tmp[player[playernum - 3].character] << "      ";
		gotoxy(19, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39); cout << (playernum - 1) << "p " << tmp[player[playernum - 2].character] << "      ";
		gotoxy(37, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55); cout << playernum << "p " << tmp[player[playernum - 1].character] << "      "; break; }
	case 4: {
		gotoxy(1, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); cout << (playernum - 3) << "p " << tmp[player[playernum - 4].character] << "      ";
		gotoxy(19, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39); cout << (playernum - 2) << "p " << tmp[player[playernum - 3].character] << "      ";
		gotoxy(37, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55); cout << (playernum - 1) << "p " << tmp[player[playernum - 2].character] << "      ";
		gotoxy(55, 0);   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71); cout << playernum << "p " << tmp[player[playernum - 1].character] << "      "; break; }
	}
	//-------------------------------------------------------------------------------------------------------------初始錢+輪到誰+回合數
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	moneyChanged();
	gotoxy(1, 4);		cout << turn + 1;		gotoxy(70, 4);	cout << throughRound;
	positionChanged();
	//-------------------------------------------------------------------------------------------------------------地圖
	for (int i = 0, j = 7; i < 7; i++, j = j + 3)	//左邊
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].name);	break; }
		case 0: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].name);	break; }
		case 1: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].name);	break; }
		case 2: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].name);	break; }
		case 3: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].name); break; }
		}
	}
	for (int i = 7, j = 1; i < 14; i++, j = j + 9)	//下面
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].name);	break; }
		case 0: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].name);	break; }
		case 1: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].name);	break; }
		case 2: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].name);	break; }
		case 3: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].name); break; }
		}
	}
	for (int i = 14, j = 28; i < 21; i++, j = j - 3)	//右邊
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].name);	break; }
		case 0: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].name);	break; }
		case 1: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].name);	break; }
		case 2: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].name);	break; }
		case 3: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].name); break; }
		}
	}
	for (int i = 21, j = 64; i < 28; i++, j = j - 9)	//上面
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenPrint(map[i].name);	break; }
		case 0: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenPrint(map[i].name);	break; }
		case 1: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenPrint(map[i].name);	break; }
		case 2: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenPrint(map[i].name);	break; }
		case 3: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenPrint(map[i].name); break; }
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
	gotoxy(18, 13); cout << "[44m  [1m─ ┬ ─   ─ ┼ ─   │  ┼ ┼ ╮  ─ ┼ ─   [m" << endl;
	gotoxy(18, 14); cout << "[1;44m    │       │     ┼  │ │ │    │     [m" << endl;
	gotoxy(18, 15); cout << "[30;42m  [1;37m─ ┼ ─ [;30;42m    [1;37m│     │  │ │ ╯    │     [m" << endl;
	gotoxy(18, 16); cout << "[30;42m  [1;37m╭ ╯ ╮   ╭ ╯ ╮   │  │      ╭ ╯ ╮   [m" << endl;
	gotoxy(18, 17); cout << "[1;42m  │   │ [;30;42m  [1;37m│ [;30;42m  [1;37m│ [;30;42m  [1;37m╱  ╰ ─ ╯  │   │   [m" << endl;
	gotoxy(18, 18); cout << "[33m  [34m          [1;30m DA-FU-OWN[;34m            [33m  [37m" << endl;
	gotoxy(18, 19); cout << "[34m  [1;33;45m   ╱         ╯   ╲ │   ─ ┼ ─    [;34m  [37m" << endl;
	gotoxy(18, 20); cout << "[36m  [1;33;45m  ╰ ─ ─ ╲    ┼   ╲ │     │      [;36m  [37m" << endl;
	gotoxy(18, 21); cout << "[1m  [33;45m  ╭ ─ ─ ╮    │   ─ ┼     │      [;34m  [37m" << endl;
	gotoxy(18, 22); cout << "[34m  [1;33;45m  │     │  ▕│ ▏  │   ╭ ╯ ╮    [;34m  [37m" << endl;
	gotoxy(18, 23); cout << "[34m  [1;33;45m  ╰ ─ ─ ╯    │     │   │   │    [;34m  [37m" << endl;
	gotoxy(117, 30);
}

void Monopoly::win()
{
	hintClear();
	gotoxy(80, 5);
	cout << "GAME OVER";
	int max = -1, tag;
	for (int i = 0; i < player.size(); i++)
	{
		if (player[i].isLoan)
			player[i].money -= 1000;
	}
	for (int i = 0; i < player.size(); i++)
	{
		if (max < player[i].money)
		{
			max = player[i].money;
			tag = i;
		}
	}
	if (max == -1)
		cout << "全軍覆沒";
	else
	{
		int num = 0;
		for (int i = 0; i < player.size(); i++)
		{
			if (player[i].money == max)
			{
				gotoxy(80, 7 + num * 2);
				cout << "玩家 " << player[i].number + 1 << " 獲勝!!!";
				num++;
			}
		}
	}
	gotoxy(80, 15);
	cout << "Press ENTER to continue";
	pressEnter();
	player.clear();
	map.clear();
	throughRound = 1;
}

void Monopoly::moneyChanged()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {       //原位清除
		gotoxy(j, 1); cout << "                 ";
	}
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		if (player[i].state == 1)
		{
			gotoxy(j, 1); cout << "$" << player[i].money;
		}
		else
		{
			gotoxy(j, 1);	cout << "破 產";
		}
	}
}

void Monopoly::positionChanged()
{
	if (player[0].state == 1)
	{
		switch ((player[0].position / 7))
		{
		case 0: {
			gotoxy(1, 8 + (player[0].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);  cout << "1";  break;
		}
		case 1: {
			gotoxy(1 + (player[0].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);  cout << "1";  break;
		}
		case 2: {
			gotoxy(64, 29 - (player[0].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);  cout << "1";  break;
		}
		case 3: {
			gotoxy(64 - (player[0].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);  cout << "1";  break;
		}
		}
	}
	if (player.size() >= 2)
	{
		if (player[1].state == 1)
		{
			switch ((player[1].position / 7))
			{
			case 0: {
				gotoxy(3, 8 + (player[1].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  cout << "2";  break;
			}
			case 1: {
				gotoxy(3 + (player[1].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  cout << "2";  break;
			}
			case 2: {
				gotoxy(66, 29 - (player[1].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  cout << "2";  break;
			}
			case 3: {
				gotoxy(66 - (player[1].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  cout << "2";  break;
			}
			}
		}
	}
	if (player.size() >= 3)
	{
		if (player[2].state == 1)
		{
			switch ((player[2].position / 7))
			{
			case 0: {
				gotoxy(6, 8 + (player[2].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  cout << "3";  break;
			}
			case 1: {
				gotoxy(6 + (player[2].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  cout << "3";  break;
			}
			case 2: {
				gotoxy(69, 29 - (player[2].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  cout << "3";  break;
			}
			case 3: {
				gotoxy(69 - (player[2].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  cout << "3";  break;
			}
			}
		}
	}
	if (player.size() >= 4)
	{
		if (player[3].state == 1)
		{
			switch ((player[3].position / 7))
			{
			case 0: {
				gotoxy(8, 8 + (player[3].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  cout << "4";  break;
			}
			case 1: {
				gotoxy(8 + (player[3].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  cout << "4";  break;
			}
			case 2: {
				gotoxy(71, 29 - (player[3].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  cout << "4";  break;
			}
			case 3: {
				gotoxy(71 - (player[3].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  cout << "4";  break;
			}
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Monopoly::positionClear(int curplayer)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	switch (curplayer)  //只改curplayer位置
	{
	case 0: { //(1,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(1, 8 + (player[curplayer].position % 7) * 3); cout << " ";  break;
		}
		case 1: {
			gotoxy(1 + (player[curplayer].position % 7) * 9, 29);  cout << " ";  break;
		}
		case 2: {
			gotoxy(64, 29 - (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 3: {
			gotoxy(64 - (player[curplayer].position % 7) * 9, 8);  cout << " ";  break;
		}
		} break;
	}
	case 1: { //(3,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(3, 8 + (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 1: {
			gotoxy(3 + (player[curplayer].position % 7) * 9, 29);  cout << " ";  break;
		}
		case 2: {
			gotoxy(66, 29 - (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 3: {
			gotoxy(66 - (player[curplayer].position % 7) * 9, 8);  cout << " ";  break;
		}
		} break;
	}
	case 2: { //(6,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(6, 8 + (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 1: {
			gotoxy(6 + (player[curplayer].position % 7) * 9, 29);  cout << " ";  break;
		}
		case 2: {
			gotoxy(69, 29 - (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 3: {
			gotoxy(69 - (player[curplayer].position % 7) * 9, 8);  cout << " ";  break;
		}
		} break;
	}
	case 3: { //(8,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(8, 8 + (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 1: {
			gotoxy(8 + (player[curplayer].position % 7) * 9, 29);  cout << " ";  break;
		}
		case 2: {
			gotoxy(71, 29 - (player[curplayer].position % 7) * 3);  cout << " ";  break;
		}
		case 3: {
			gotoxy(71 - (player[curplayer].position % 7) * 9, 8);  cout << " ";  break;
		}
		}
	} break;
	}
}

void Monopoly::stockPriceFlow()
{
	srand(time(NULL));
	for (int j = 0; j < 3; j++)
	{
		upLimit[j] = 0;
		downLimit[j] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		int rate = rand() % 80 + 1;
		if (rand() % 2)
		{
			if (rate > 70)
			{
				rate = 70;
				upLimit[i] = 1;
			}
			stockPrice[i] *= (1 + 0.001*rate);
		}
		else
		{
			if (rate > 70)
			{
				rate = 70;
				downLimit[i] = 1;
			}
			stockPrice[i] *= (1 - 0.001*rate);
		}
	}
}
void Monopoly::stock(Player &person)
{
	const string tmp[] = { "鈊象電子","佛心公司","統神電台" };
	vector<string> stock(tmp, tmp + 3);
	firstPrint(85, 21, 3, stock);
	int toDo = 0;
	while (true)
	{
		if (_kbhit())
		{
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(toDo, 85, 21, 3, stock);
					if (toDo == 0)
						toDo = 2;
					else
						toDo--;
				}
				else if (input==80)
				{
					down_gotoxy(toDo, 85, 21, 3, stock);
					if (toDo == 2)
						toDo = 0;
					else
						toDo++;
				}
			}
			else if (input == 13)
			{
				gotoxy(95, 17);
				cout << stock[toDo] << ": ";
				if (upLimit[toDo] == 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				}
				if (downLimit[toDo] == 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				}
				cout << stockPrice[toDo];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << " 摳/張";
				gotoxy(95, 19);
				cout << "你的存款: " << person.deposit;
				gotoxy(95, 21);
				cout << "你擁有的張數: " << person.ownStock[toDo] << " 張";
				const string tmp[] = { "買","賣" };
				vector<string> thing(tmp, tmp + 2);
				firstPrint(95,23, 3, thing);
				bool operate = 0;
				while (true)
				{
					if (_kbhit())
					{
						int input = _getch();
						if (input == 224)
						{
							down_gotoxy(operate, 95, 23, 3, thing);
							operate = 1 - operate;
						}
						else if (input == 13)
						{
							while (true)
							{
								int num;
								gotoxy(100, 23);
								cout << "輸入張數: ";
								cin >> num;
								gotoxy(100, 25);
								if (num == -1)
								{
									break;
								}
								else if (num < 0)
								{
									cout << "非法數字";
									gotoxy(110, 23);
									cout << "       ";
								}
								//買
								if (operate)
								{
									if (person.ownStock[toDo] < num)
									{
										cout << "股票張數不足";
										gotoxy(110, 23);
										cout << "       ";
									}
									else
									{
										person.deposit += num * stockPrice[toDo];
										person.ownStock[toDo] -= num;
										gotoxy(105, 19);
										cout << "           ";
										gotoxy(109, 21);
										cout << "        ";
										gotoxy(95, 19);
										cout << "你的存款: " << person.deposit;
										gotoxy(95, 21);
										cout << "你擁有的張數: " << person.ownStock[toDo] << " 張";
										break;
									}
								}
								//賣
								else
								{
									if (person.deposit < num*stockPrice[toDo])
									{
										cout << "存款不足";
										gotoxy(110, 23);
										cout << "       ";
									}
									else
									{
										person.deposit -= num * stockPrice[toDo];
										person.ownStock[toDo] += num;
										gotoxy(105, 19);
										cout << "           ";
										gotoxy(109, 21);
										cout << "        ";
										gotoxy(95, 19);
										cout << "你的存款: " << person.deposit;
										gotoxy(95, 21);
										cout << "你擁有的張數: " << person.ownStock[toDo] << " 張";
										break;
									}
								}
								gotoxy(100, 23);
							}
							for (int i = 23; i < 31; i++)
							{
								gotoxy(100, i);
								cout << "                ";
							}
							gotoxy(117, 30);
						}
						else if (input == 'q')
						{
							for (int i = 17; i < 31; i++)
							{
								gotoxy(95, i);
								cout << "                     ";
							}
							break;
						}
					}
				}
			}
			else if (input == 'q')
			{
				for (int i = 21; i < 31; i++)
				{
					gotoxy(85, i);
					cout << "          ";
				}
				gotoxy(117, 30);
				break;
			}
		}
	}
}

void Monopoly::atm(Player& person)
{
	const string tmp[] = { "存款","提款" ,"借款"};
	vector<string> thing(tmp, tmp + 3);
	firstPrint(85, 20, 2, thing);
	int toDo = 0;
	while (true)
	{
		if (_kbhit())
		{
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(toDo, 85, 20, 2, thing);
					if (toDo == 0)
						toDo = 2;
					else
						toDo--;
				}
				else if (input == 80)
				{
					down_gotoxy(toDo, 85, 20, 2, thing);
					if (toDo == 2)
						toDo = 0;
					else
						toDo++;
				}
			}
			else if (input == 13)
			{
				//提款
				if (toDo==1)
				{
					gotoxy(95, 17);
					cout << "你的塞ㄎㄧㄚ: " << person.deposit;
					while (true)
					{
						int num;
						gotoxy(95, 20);
						cout << "輸入金額: ";
						cin >> num;
						gotoxy(95, 22);
						if (num == -1)
						{
							for (int i = 17; i < 31; i++)
							{
								gotoxy(95, i);
								cout << "                     ";
							}
							break;
						}
						else if (num <= 0)
						{
							cout << "非法數字";
							gotoxy(105, 20);
							cout << "         ";
						}
						else if (num > person.deposit)
						{
							cout << "存款不足";
							gotoxy(105, 20);
							cout << "         ";
						}
						else
						{
							person.money += num;
							person.deposit -= num;
							gotoxy(105, 17);
							cout << "            ";
							gotoxy(95, 17);
							cout << "你的存款: " << person.deposit;
							moneyChanged();
							for (int i = 17; i < 31; i++)
							{
								gotoxy(95, i);
								cout << "                   ";
							}
							break;
						}
						gotoxy(105, 20);
					}
					gotoxy(117, 30);
				}
				//存款
				else if(toDo==0)
				{
					gotoxy(95, 17);
					cout << "你的塞ㄎㄧㄚ: "<< person.deposit;
					while (true)
					{
						int num;
						gotoxy(95, 20);
						cout << "輸入金額: ";
						cin >> num;
						gotoxy(95, 22);
						if (num == -1)
						{
							for (int i = 17; i < 31; i++)
							{
								gotoxy(95, i);
								cout << "                     ";
							}
							break;
						}
						else if (num <= 0)
						{
							cout << "非法數字";
							gotoxy(105, 20);
							cout << "         ";
						}
						else if (num > person.money)
						{
							cout << "現金不足";
							gotoxy(105, 20);
							cout << "         ";
						}
						else
						{
							person.money -= num;
							person.deposit += num;
							gotoxy(105, 17);
							cout << "            ";
							gotoxy(95, 17);
							cout << "你的塞ㄎㄧㄚ: " << person.deposit;
							moneyChanged();
							for (int i = 17; i < 31; i++)
							{
								gotoxy(95, i);
								cout << "                   ";
							}
							break;
						}
						gotoxy(105, 20);
					}
					gotoxy(117, 30);
				}
				//借款
				else if (toDo == 2)
				{
					gotoxy(95, 17);
					cout << "借款金額:10000摳";
					if (person.isLoan)
					{
						gotoxy(95, 19);
						cout << "還款期限: " << person.loanTime << " 回合";
					}
					else
					{
						gotoxy(100, 19);
						cout << "尚未借款";
					}
					const string tmp[] = { "是","否" };
					vector<string> choice(tmp, tmp + 2);
					firstPrint(95, 23,3,choice);
					bool toChoose = 0;
					while (true)
					{
						int input = _getch();
						if (input == 224)
						{
							up_gotoxy(toChoose, 95, 23, 3, choice);
							toChoose = 1 - toChoose;
						}
						else if(input==13)
						{
							if (!toChoose)
							{
								if (!person.isLoan)
								{
									gotoxy(100, 22);
									cout << "借款成功";
									person.isLoan = 1;
									person.loanTime = 5;
									person.money += 10000;
									moneyChanged();
								}
								else
								{
									gotoxy(100, 22);
									cout << "你已經借錢了";
								}
							}
							gotoxy(94, 30);
							cout << "Press ENTER to continue";
							pressEnter();
							break;
						}
					}
					for (int i = 17; i < 31; i++)
					{
						gotoxy(94, i);
						cout << "                       ";
					}
					gotoxy(117, 30);
				}
			}
			else if (input == 'q')
			{
				for (int i = 17; i < 31; i++)
				{
					gotoxy(95, i);
					cout << "                     ";
				}
				for (int i = 20; i < 31; i++)
				{
					gotoxy(85, i);
					cout << "      ";
				}
				gotoxy(117, 30);
				break;
			}
		}
	}
}

Monopoly::Monopoly(void)
{
	stockPrice.resize(3);
	upLimit.resize(3);
	downLimit.resize(3);
	for (int i = 0; i < 3; i++)
	{
		stockPrice[i] = 1000;
		upLimit[i] = 0;
		downLimit[i] = 0;
	}
}