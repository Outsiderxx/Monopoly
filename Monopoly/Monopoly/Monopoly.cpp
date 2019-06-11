#include "Monopoly.h"

//¹CÀ¸¬yµ{
void Monopoly::playGame(bool chooseBanker)
{
	int banker, initialPlayerNum = player.size();
	const string zanzu[4] = { "¦w¬ü¦Ù¨¾ÁÉ¨Å","®Q®aºw¦Ùºë","³æ¨­­Ñ¼Ö³¡","30¤½¤À¦n´Î´Î" };
	//¨M©w°_¤âÂI
	if (chooseBanker)
	{
		banker = dice(player.size());
		turn = banker;
		gotoxy(80,5);
		cout << "¥»§½¹CÀ¸¥Ñª±®a " << turn + 1 << " ¶}©l";
		gotoxy(80, 9);
		cout << "Press ENTER to start!!!";
		gotoxy(85, 17);
		int zan = rand() % 4;
		if (zan == 0)
			cout << "·PÁÂ" << zanzu[0] << "«a¦WÃÙ§U";
		else if (zan == 1)
			cout << "·PÁÂ" << zanzu[1] << "«a¦WÃÙ§U";
		else if (zan == 2)
			cout << "·PÁÂ" << zanzu[2] << "«a¦WÃÙ§U";
		else if (zan == 3)
			cout << "·PÁÂ" << zanzu[3] << "«a¦WÃÙ§U";
		pressEnter();
	}
	//Åã¥Üµe­±
	mapinitial();
	//³Ñ¾l¦^¦X¤£¬°¹s
	int flag = 0;
	if (chooseBanker)
		flag = 1;
	while (throughRound <= round)
	{
		if (throughRound == round)
		{
			gotoxy(80, 5);
			cout << "³Ì«á¤@¦^¦XÅo ";
			gotoxy(80, 7);	cout << "²{ª÷³Ì¦h¤~¬O¦Ñ¤j°Õ ";
			gotoxy(92, 9);	cout << "¤pªB¤Í¤~+»È¦æªÑ²¼!!!";
			gotoxy(94, 14);	cout << "Press ENTER to continue";
			pressEnter();
			mapinitial();
		}
		//ªÑ»ùªi°Ê
		if(flag)
			stockPriceFlow();
		flag = 1;
		for (int time = 0; time < player.size(); time++, turn++)
		{
			moneyChanged();
			//ª±®a¤H¼Æ¤j©ó1¤H
			if (initialPlayerNum != 1)
			{
				//¬°¯}²£¤H¼Æ³Ñ¤@¤Hµ²§ô
				int num = 0;
				for (int i = 0; i < player.size(); i++)
				{
					if (player[i].state)
						num++;
				}
				if (num == 1)
					goto end;
			}
			//ª±®a¤H¼Æ¤@¤H
			else
			{
				//ª±®a¯}²£µ²§ô
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
					cout << "·Ç³ÆÁÙ¿úÅo";
					gotoxy(85, 7);
					cout << "Press ENTER to continue";
					pressEnter();
				}
				else if (player[turn].loanTime == 0)
				{
					player[turn].isLoan = 0;
					gotoxy(80, 5);
					cout << "ÁÙ¿úÅo ª÷¿ú´î10000áà";
					player[turn].money -= 10000;
					moneyChanged();
					if (player[turn].money < 0)
					{
						gotoxy(80, 9);
						cout << "ª±®a " << turn + 1 << " ¯}²£°ÕQQ";
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
			//ª±®a¬O§_¯}²£
			if (!player[turn].state)
			{
				positionClear(turn);
				continue;
			}
			//ª±®a¬O§_³Q¼È°±
			if (player[turn].stop != 0)
			{
				gotoxy(80, 5);
				cout << "¶ýªºSODÁÙ­nºt" << (player[turn].stop) << "¦¸";
				player[turn].stop--;
				gotoxy(80, 7);
				cout << "Press ENTER to ¼È°±¦¸¼Æ´î¤@";
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
					cout << "´Â²n¼w~ ¾ß¨ì500§Ö­ù~";
					player[turn].money += 500;
					gotoxy(80, 9);
					cout << "Press ENTER to continue";
					pressEnter();
				}
				else if(ran == 1)
				{
					cout << "¬Ý ! ­þ­Ó«§°½·F§Ú..";
					gotoxy(80, 7);	cout << ".............500áà¿Ñ°_ªü ! !";
					player[turn].money -= 500;
					gotoxy(80, 9);
					cout << "Press ENTER to continue";
					pressEnter();
				}
				mapinitial();
			}
			if (player[turn].character == 3)
			{
				if (rand() % 5 == 0)		//-------------------------------------¾÷²v½Õ¾ã
				{
					gotoxy(82, 5);	cout << "¸ô¤H69ªº§Þ¯àµo°Ê¤Fzzz";
					gotoxy(82, 7);	cout << "º¤¤½Å]ªk¥d-->°ª¶¯µo¤j°]";
					gotoxy(82, 9);	cout << "µM¦Ó.............";
					gotoxy(82, 10);	cout << ".................¤°»ò¨Æ³£¨Sµo¥Í";
					gotoxy(82, 12);	cout << "Press ENTER to continue";
					pressEnter();
				}
				mapinitial();
			}
			gotoxy(80, 3);		 cout << "²{¦b½ü¨ì ª±®a" << player[turn].number + 1 << " »ë¦è¤K¤Mªü";
			gotoxy(80, 5);		 cout << "«öenter§ëÂY»ë¤l!!!!";		gotoxy(117, 30);
			while (true)
			{
				if (_kbhit())
				{
					int input = _getch();
					//ª±®a«öENTER
					if (input == 13)
					{
						//ÂY»ë¤l
						int step = dice(6) + 1;
						gotoxy(80, 7);		
						cout << "§A»ë¨ì " << step << " ÂI";
						if (step == 1)
						{
							gotoxy(90, 7); cout << "¹G¾÷°Õ ~ ~";
						}
						while (true)
						{
							positionClear(turn);
							//§PÂ_¸ô³~¤¤¬O§_¦³¤[°k
							for (int i = 1; i <= step; i++)
							{
								//³Qªý¾×
								if (map[(player[turn].position + i) % 28].barrier)
								{
									gotoxy(80, 13);
									cout << "ªü«ç»ò¸ô¤W¤]¦³®·¤H§¨ ? ?";
									map[(player[turn].position + i) % 28].barrier = 0;
									step = i;
									break;
								}
							}
							//«e¶i¸g¹L°_ÂIÀò±o1000áà
							if ((player[turn].position + step) > 27)  
							{
								gotoxy(80, 11);
								cout << "ª±®a" << player[turn].number + 1 << "³q¹L°_ÂIÀò±o1000¤¸¼úÀy";
								player[turn].money += 1000;
								player[turn].position = (player[turn].position + step) % map.size();
								positionChanged();
							}
							//«á°h¸g¹L°_ÂI(©R¹Bcase)
							else if ((player[turn].position + step) < 0)
							{
								player[turn].position += 28 + player[turn].position - step;
								positionChanged();
							}
							//¥¿±`«e¶i
							else
							{
								player[turn].position += step;
								positionChanged();
							}
							gotoxy(80, 9);
							cout << "²¾°Ê¨ì " << map[player[turn].position].name;
							//¨Æ¥ó§PÂ_
							int flag = map[player[turn].position].areaControl(player, turn);
							//¥¿±`¨Æ¥ó
							if (flag == 4)
							{
								break;
							}
							//«e¶i«á°h
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
					//ª±®a«öESC¡A¥s¥X¿ï³æ
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
							gotoxy(80, 3);		 cout << "²{¦b½ü¨ì ª±®a" << player[turn].number + 1 << " »ë¦è¤K¤Mªü";
							gotoxy(80, 5);		 cout << "«öenter§ëÂY»ë¤l!!!!";		gotoxy(117, 30);
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
		//§ïÅÜ¸g¹L¦^¦X¼Æ
		mapinitial();
	}
	end:
	//§PÂ_³Ó­t
	win();
}

//°õ¦æ¿ï¾Ü°Ê§@: ·s§½ ÂÂ§½ »¡©ú Â÷¶}
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

//¿ï¾Üª±®a¤H¼Æ
bool Monopoly::setPlayerNum(void)
{
	const string tmp[4] = { "Ãä½t³æ¦æ" ,"Âù­¸¿¬µ¾","¤T¤H¦¨ªê","¥|¤H²V¾Ô" };
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

//¿ï¾Ü¨¤¦â
bool Monopoly::chooseCharacter(int num)
{
	const string tmp[4] = { "¤k°ª¤¤¥Í","¾Þ½L¦l°Ó","¯î®q¶Ì³J"," ¸ô¤H69" };
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

//¸ü¤J¸ê®Æ
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

//Åã¥Ü»¡©ú
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
		cout << "³W«h»¡©úÀÉ¿ò¥¢" << endl;
	}
	manualFile.close();
}

//Â÷¶}¹CÀ¸
void Monopoly::exitGame(void)
{
	//print µ²§ôµe­±
	exitprint();
	exit(1);
}

//ÂY»ë¤l
int Monopoly::dice(int range)
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

// µæ³æ: Ä~Äò ¨Ï¥Î¹D¨ã »»±±»ë¤l ¦sÀÉ Â÷¶}
int Monopoly::menu(int whichPlayer)
{
	const string tmp[] = { "Ä~Äò","»È¦æ","¨Ï¥Î¹D¨ã","»»±±»ë¤l","¦sÀÉ","¦^¥Dµe­±","Â÷¶}" };
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
					const string tmp[] = { "ATM","ªÑ²¼¥æ©ö" };
					vector<string> bank(tmp, tmp + 2);
					gotoxy(73, 17);
					cout << "¿ï¾Ü­n¨Ï¥Îªº¥\¯à";
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
								//ªÑ²¼
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
					//¨Ï¥Î»»±±»ë¤l¡A¤£¥i¦b»ë¥¿±`»ë¤l
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
						cout << "¹D¨ã¤£¨¬";
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

//¦sÀÉ
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
		cout << "ÀÉ®×¶}±Ò¥¢±Ñ" << endl;
	}
	outputFile.close();
	_chdir("..");
}

//¿ï¾Ü­n¶i¦æªº¦^¦X¼Æ
bool Monopoly::setRound(void)
{
	const string tmp[] = { "10","20","30","40","50" };
	vector<string> roundDecision(tmp, tmp + 5);
	gotoxy(17, 19);
	cout << "¿ï¾Ü­n¹Cª±ªº¦^¦X¼Æ:";
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

//¿ï¾Ü­n¨Ï¥Îªº¹D¨ã
bool Monopoly::chooseItem(int currentPlayer)
{
	const string tmp[] = {"®·¤H§¨","©î§¨¤u","¬µ¼u"};
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
					cout << "¹D¨ã¤£¨¬";
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

//¨Ï¥Î¹D¨ã
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

//»»±±»ë¤l
bool Monopoly::controlDice(int whichPlayer)
{
	const string tmp[] = { "1ÂI","2ÂI" ,"3ÂI" ,"4ÂI" ,"5ÂI" ,"6ÂI" };
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
				cout << "§A¿ï¾Ü²¾°Ê " << step << " ¨B";
				while (true)
				{
					positionClear(turn);
					//§PÂ_¸ô³~¤¤¬O§_¦³¤[°k
					for (int i = 1; i <= step; i++)
					{
						//³Qªý¾×
						if (map[(player[turn].position + i) % 28].barrier)
						{
							gotoxy(80, 13);
							cout << "ªü«ç»ò¸ô¤W¤]¦³®·¤H§¨ ? ?";
							map[(player[turn].position + i) % 28].barrier = 0;
							step = i;
							break;
						}
					}
					//«e¶i¸g¹L°_ÂIÀò±o1000áà
					if ((player[turn].position + step) > 27)
					{
						gotoxy(80, 11);
						cout << "ª±®a" << player[turn].number + 1 << "³q¹L°_ÂIÀò±o1000¤¸¼úÀy";
						player[turn].money += 1000;
						player[turn].position = (player[turn].position + step) % map.size();
						positionChanged();
					}
					//«á°h¸g¹L°_ÂI(©R¹Bcase)
					else if ((player[turn].position + step) < 0)
					{
						player[turn].position += 28 + player[turn].position - step;
						positionChanged();
					}
					//¥¿±`«e¶i
					else
					{
						player[turn].position += step;
						positionChanged();
					}
					gotoxy(80, 9);
					cout << "²¾°Ê¨ì " << map[player[turn].position].name;
					//¨Æ¥ó§PÂ_
					int flag = map[player[turn].position].areaControl(player, turn);
					//¥¿±`¨Æ¥ó
					if (flag == 4)
					{
						break;
					}
					//«e¶i«á°h
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

//³]¸m¸ô»Ù
bool Monopoly::loadBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	gotoxy(98, 18);
	cout << "¿é¤J¦aÂI: ";
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
					cout << "«Dªk¦a°Ï";
					inputClear();
					break;
				}
				else
				{
					if (map[i].barrier == 1)
					{
						cout << "¦¹¦a°Ï¤w¦³®·¤H§¨";
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
			cout << "¬dµL¦¹¦a";
			inputClear();
		}
	}
}

//¯}Ãa¸ô»Ù
bool Monopoly::destroyBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	gotoxy(98, 18);
	cout << "¿é¤J¦aÂI: ";
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
					cout << "«Dªk¦a°Ï";
					inputClear();
					break;
				}
				else
				{
					if (map[i].barrier == 0)
					{
						cout << "¦¹¦a°Ï¨S¦³®·¤H§¨";
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
			cout << "¬dµL¦¹¦a";
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
	cout << "¿é¤J¦aÂI: ";
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
					cout << "«Dªk¦a°Ï";
					inputClear();
					break;
				}
				else
				{
					if (map[i].owner == -1)
					{
						cout << "¦¹¦a°Ï¨S¦³«Ø¿v";
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
			cout << "¬dµL¦¹¦a";
			inputClear();
		}
	}
}

//­n¨Ï¥Îªº¦a¹Ï
bool Monopoly::chooseFile(void)
{
	system("color 0f");
	system("cls");
	_chdir(".\\map");
	vector<string> mapFileName;
	struct _finddata_t fileName;
	//Åª¨úÀÉ¦W
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
	const string tmp[4] = { "¤k°ª¤¤¥Í","¾Þ½L¦l°Ó","¯î®q¶Ì³J"," ¸ô¤H69" };
	//-------------------------------------------------------------------------------------------------------------¸}¦â¦WºÙ
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
	//-------------------------------------------------------------------------------------------------------------ªì©l¿ú+½ü¨ì½Ö+¦^¦X¼Æ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	moneyChanged();
	gotoxy(1, 4);		cout << turn + 1;		gotoxy(70, 4);	cout << throughRound;
	positionChanged();
	//-------------------------------------------------------------------------------------------------------------¦a¹Ï
	for (int i = 0, j = 7; i < 7; i++, j = j + 3)	//¥ªÃä
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
	for (int i = 7, j = 1; i < 14; i++, j = j + 9)	//¤U­±
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
	for (int i = 14, j = 28; i < 21; i++, j = j - 3)	//¥kÃä
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
	for (int i = 21, j = 64; i < 28; i++, j = j - 9)	//¤W­±
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
	cout << "¹CÀ¸ª¬ªpÅã¥Ü";
	gotoxy(73, 1);
	cout << "---------------------------------------------";
	gotoxy(73, 15);
	cout << "¿ï³æ";
	gotoxy(73, 16);
	cout << "---------------------------------------------";
	//-------------------------------------------------------------------------------------------------------------------------©Ò¦b¦ì¸m
	gotoxy(18, 13); cout << "[44m  [1m¢w ¢s ¢w   ¢w ¢q ¢w   ¢x  ¢q ¢q ¢¡  ¢w ¢q ¢w   [m" << endl;
	gotoxy(18, 14); cout << "[1;44m    ¢x       ¢x     ¢q  ¢x ¢x ¢x    ¢x     [m" << endl;
	gotoxy(18, 15); cout << "[30;42m  [1;37m¢w ¢q ¢w [;30;42m    [1;37m¢x     ¢x  ¢x ¢x ¢£    ¢x     [m" << endl;
	gotoxy(18, 16); cout << "[30;42m  [1;37m¢~ ¢£ ¢¡   ¢~ ¢£ ¢¡   ¢x  ¢x      ¢~ ¢£ ¢¡   [m" << endl;
	gotoxy(18, 17); cout << "[1;42m  ¢x   ¢x [;30;42m  [1;37m¢x [;30;42m  [1;37m¢x [;30;42m  [1;37m¢¬  ¢¢ ¢w ¢£  ¢x   ¢x   [m" << endl;
	gotoxy(18, 18); cout << "[33m  [34m          [1;30m DA-FU-OWN[;34m            [33m  [37m" << endl;
	gotoxy(18, 19); cout << "[34m  [1;33;45m   ¢¬         ¢£   ¢­ ¢x   ¢w ¢q ¢w    [;34m  [37m" << endl;
	gotoxy(18, 20); cout << "[36m  [1;33;45m  ¢¢ ¢w ¢w ¢­    ¢q   ¢­ ¢x     ¢x      [;36m  [37m" << endl;
	gotoxy(18, 21); cout << "[1m  [33;45m  ¢~ ¢w ¢w ¢¡    ¢x   ¢w ¢q     ¢x      [;34m  [37m" << endl;
	gotoxy(18, 22); cout << "[34m  [1;33;45m  ¢x     ¢x  ¢y¢x ¢j  ¢x   ¢~ ¢£ ¢¡    [;34m  [37m" << endl;
	gotoxy(18, 23); cout << "[34m  [1;33;45m  ¢¢ ¢w ¢w ¢£    ¢x     ¢x   ¢x   ¢x    [;34m  [37m" << endl;
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
		cout << "¥þ­xÂÐ¨S";
	else
	{
		int num = 0;
		for (int i = 0; i < player.size(); i++)
		{
			if (player[i].money == max)
			{
				gotoxy(80, 7 + num * 2);
				cout << "ª±®a " << player[i].number + 1 << " Àò³Ó!!!";
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
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {       //­ì¦ì²M°£
		gotoxy(j, 1); cout << "                 ";
	}
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		if (player[i].state == 1)
		{
			gotoxy(j, 1); cout << "$" << player[i].money;
		}
		else
		{
			gotoxy(j, 1);	cout << "¯} ²£";
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
	switch (curplayer)  //¥u§ïcurplayer¦ì¸m
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
	const string tmp[] = { "Üc¶H¹q¤l","¦ò¤ß¤½¥q","²Î¯«¹q¥x" };
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
				cout << " áà/±i";
				gotoxy(95, 19);
				cout << "§Aªº¦s´Ú: " << person.deposit;
				gotoxy(95, 21);
				cout << "§A¾Ö¦³ªº±i¼Æ: " << person.ownStock[toDo] << " ±i";
				const string tmp[] = { "¶R","½æ" };
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
								cout << "¿é¤J±i¼Æ: ";
								cin >> num;
								gotoxy(100, 25);
								if (num == -1)
								{
									break;
								}
								else if (num < 0)
								{
									cout << "«Dªk¼Æ¦r";
									gotoxy(110, 23);
									cout << "       ";
								}
								//¶R
								if (operate)
								{
									if (person.ownStock[toDo] < num)
									{
										cout << "ªÑ²¼±i¼Æ¤£¨¬";
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
										cout << "§Aªº¦s´Ú: " << person.deposit;
										gotoxy(95, 21);
										cout << "§A¾Ö¦³ªº±i¼Æ: " << person.ownStock[toDo] << " ±i";
										break;
									}
								}
								//½æ
								else
								{
									if (person.deposit < num*stockPrice[toDo])
									{
										cout << "¦s´Ú¤£¨¬";
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
										cout << "§Aªº¦s´Ú: " << person.deposit;
										gotoxy(95, 21);
										cout << "§A¾Ö¦³ªº±i¼Æ: " << person.ownStock[toDo] << " ±i";
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
	const string tmp[] = { "¦s´Ú","´£´Ú" ,"­É´Ú"};
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
				//´£´Ú
				if (toDo==1)
				{
					gotoxy(95, 17);
					cout << "§Aªº¶ë£}£¸£«: " << person.deposit;
					while (true)
					{
						int num;
						gotoxy(95, 20);
						cout << "¿é¤Jª÷ÃB: ";
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
							cout << "«Dªk¼Æ¦r";
							gotoxy(105, 20);
							cout << "         ";
						}
						else if (num > person.deposit)
						{
							cout << "¦s´Ú¤£¨¬";
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
							cout << "§Aªº¦s´Ú: " << person.deposit;
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
				//¦s´Ú
				else if(toDo==0)
				{
					gotoxy(95, 17);
					cout << "§Aªº¶ë£}£¸£«: "<< person.deposit;
					while (true)
					{
						int num;
						gotoxy(95, 20);
						cout << "¿é¤Jª÷ÃB: ";
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
							cout << "«Dªk¼Æ¦r";
							gotoxy(105, 20);
							cout << "         ";
						}
						else if (num > person.money)
						{
							cout << "²{ª÷¤£¨¬";
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
							cout << "§Aªº¶ë£}£¸£«: " << person.deposit;
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
				//­É´Ú
				else if (toDo == 2)
				{
					gotoxy(95, 17);
					cout << "­É´Úª÷ÃB:10000áà";
					if (person.isLoan)
					{
						gotoxy(95, 19);
						cout << "ÁÙ´Ú´Á­­: " << person.loanTime << " ¦^¦X";
					}
					else
					{
						gotoxy(100, 19);
						cout << "©|¥¼­É´Ú";
					}
					const string tmp[] = { "¬O","§_" };
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
									cout << "­É´Ú¦¨¥\";
									person.isLoan = 1;
									person.loanTime = 5;
									person.money += 10000;
									moneyChanged();
								}
								else
								{
									gotoxy(100, 22);
									cout << "§A¤w¸g­É¿ú¤F";
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