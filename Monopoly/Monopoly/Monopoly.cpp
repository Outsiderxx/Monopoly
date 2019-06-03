#include "Monopoly.h"

//�C���y�{
void Monopoly::playGame(bool chooseBanker)
{
	int banker, initialPlayerNum = player.size();
	//�M�w�_���I
	if (chooseBanker)
	{
		banker = dice(player.size());
		turn = banker;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(80,5);
		cout << "�����C���Ѫ��a " << turn + 1 << " �}�l";
		gotoxy(80, 7);
		cout << "Press ENTER to start!!!";
		pressEnter();
	}
	//��ܵe��
	mapinitial();
	//�Ѿl�^�X�����s
	while (throughRound <= round)
	{
		//�ѻ��i��
		stockPriceFlow();
		//���a�H�Ƥj��1�H
		if (initialPlayerNum != 1)
		{
			//���}���H�ƳѤ@�H����
			int num = 0;
			for (int i = 0; i < player.size(); i++)
			{
				if (player[i].state)
					num++;
			}
			if (num == 1)
				break;
		}
		//���a�H�Ƥ@�H
		else
		{
			//���a�}������
			if (player[0].money < 0)
			{
				break;
			}
		}
		for (int time = 0; time < player.size(); time++, turn++)
		{
			if (turn == player.size())
				turn = 0;
			//���a�O�_�}��
			if (!player[turn].state)
			{
				for (int i = 0; i < map.size(); i++)
				{
					if (map[i].owner == turn)
					{
						map[i].owner = -1;
						map[i].level = 0;
					}
				}
				continue;
			}
			mapinitial();
			//���a�O�_�Q�Ȱ�
			if (player[turn].stop != 0)
			{
				gotoxy(80, 5);
				cout << "���^�X�Ȱ����QQ �Ȱ����ƴ�@";
				player[turn].stop--;
				continue;
			}
			if (player[turn].character == 2)
			{
				gotoxy(80, 5);
				if (rand() % 2)
				{
					cout << "�̤H���̺� �ߨ�500��";
					player[turn].money += 500;
				}
				else
				{
					cout << "�����^�� �˥�500��QQ";
					player[turn].money -= 500;
				}
				gotoxy(80, 7);
				cout << "Press ENTER to continue";
				pressEnter();
				mapinitial();
			}
			if (player[turn].character == 3)
			{
				gotoxy(80, 5);
				cout << "�����o�j�]";
				gotoxy(80, 7);
				cout << "Press ENTER to continue";
				pressEnter();
				mapinitial();
			}
			gotoxy(80, 3);		 cout << "�{�b���� ���a" << player[turn].number + 1 << " ���K�M��";
			gotoxy(80, 5);		 cout << "��enter���Y��l!!!!";		gotoxy(117, 30);
			while (true)
			{
				if (_kbhit())
				{
					int input = _getch();
					//���a��ENTER
					if (input == 13)
					{
						//�Y��l
						int step = dice(6) + 1;
						gotoxy(80, 7);		
						cout << "�A��� " << step << " �I";
						while (true)
						{
							positionClear(turn);
							//�P�_���~���O�_���[�k
							for (int i = 1; i <= step; i++)
							{
								//�Q����
								if (map[(player[turn].position + i) % 28].barrier)
								{
									gotoxy(80, 13);
									cout << "�Q�[�k�̭�QQ";
									map[(player[turn].position + i) % 28].barrier = 0;
									step = i;
									break;
								}
							}
							//�e�i�g�L�_�I��o1000��
							if ((player[turn].position + step) > 27)  
							{
								gotoxy(80, 11);
								cout << "���a" << player[turn].number + 1 << "�q�L�_�I��o1000�����y";
								player[turn].money += 1000;
								player[turn].position = (player[turn].position + step) % map.size();
								positionChanged();
							}
							//��h�g�L�_�I(�R�Bcase)
							else if ((player[turn].position + step) < 0)
							{
								player[turn].position += 28 + player[turn].position - step;
								positionChanged();
							}
							//���`�e�i
							else
							{
								player[turn].position += step;
								positionChanged();
							}
							gotoxy(80, 9);
							cout << "���ʦ�m�� " << map[player[turn].position].name;
							//�ƥ�P�_
							int flag = map[player[turn].position].areaControl(player, turn);
							//�A��@��
							if (flag == 0)
							{
								time--;
								if (turn == 0)
									turn = player.size() - 1;
								else
									turn--;
								break;
							}
							//���`�ƥ�
							else if (flag == 4)
							{
								break;
							}
							//�e�i��h
							else
							{
								step = flag;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
								gotoxy(94, 30);
								cout << "Press ENTER to continue";
								pressEnter();
								menuClear();
							}
						}
						break;
					}
					//���a��ESC�A�s�X���
					else if (input == 27)
					{
						int flag = menu(turn);
						mapinitial();
						gotoxy(80, 3);		 cout << "�{�b���� ���a" << player[turn].number + 1 << " ���K�M��";
						gotoxy(80, 5);		 cout << "��enter���Y��l!!!!";		gotoxy(117, 30);
						if (flag == 1)
							break;
						else if (flag == 2)
						{
							goto end;
						}
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(94, 30);
			cout << "Press ENTER to continue";
			pressEnter();
			hintClear();
		}
		throughRound++;
		//���ܸg�L�^�X��
		mapinitial();
	}
	end:
	//�P�_�ӭt
	win();
}

//�����ܰʧ@: �s�� �§� ���� ���}
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

//��ܪ��a�H��
bool Monopoly::setPlayerNum(void)
{
	const string tmp[4] = { "��t���" ,"��������","�T�H����","�|�H�V��" };
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

//��ܨ���
bool Monopoly::chooseCharacter(int num)
{
	const string tmp[4] = { "�k������","�޽L�l��","��q�̳J"," ���H69" };
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

//���J���
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
			{
				ss >> tmp.item[j];
			}
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
	}
	inputFile.close();
	if(mapFile!="initial.txt")
		_chdir("..\\");
}

//��ܻ���
void Monopoly::printManual(void)
{
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
		cout << "�W�h�����ɿ�" << endl;
	}
	manualFile.close();
	system("pause");
}

//���}�C��
void Monopoly::exitGame(void)
{
	//print �����e��
	exit(1);
}

//�Y��l
int Monopoly::dice(int range)
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

// ���: �~�� �ϥιD�� ������l �s�� ���}
int Monopoly::menu(int whichPlayer)
{
	const string tmp[] = { "�~��","�Ȧ�","�ϥιD��","������l","�s��","�^�D�e��","���}" };
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
					const string tmp[] = { "ATM","�Ѳ����" };
					vector<string> bank(tmp, tmp + 2);
					gotoxy(73, 17);
					cout << "��ܭn�ϥΪ��\��";
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
								//�Ѳ�
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
					//�ϥλ�����l�A���i�b�륿�`��l
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
						cout << "�D�㤣��";
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

//�s��
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
		outputFile << mapName << " " << round - throughRound << " " << player.size() << endl;
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
			if (player[i].state)
			{
				outputFile << player[i].number << " " << player[i].character << " " << player[i].position << " " << player[i].money << " ";
				outputFile << player[i].stop << " " << player[i].skip;
				for (int j = 0; j < player[i].item.size(); j++)
				{
					outputFile << " " << player[i].item[j];
				}
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
		}
	}
	else
	{
		cout << "�ɮ׶}�ҥ���" << endl;
	}
	outputFile.close();
	_chdir("..");
}

//��ܭn�i�檺�^�X��
bool Monopoly::setRound(void)
{
	const string tmp[] = { "10","20","30","40","50" };
	vector<string> roundDecision(tmp, tmp + 5);
	gotoxy(17, 19);
	cout << "��ܭn�C�����^�X��:";
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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

//��ܭn�ϥΪ��D��
bool Monopoly::chooseItem(int currentPlayer)
{
	const string tmp[] = {"�[�k","�l�l","���u"};
	vector<string> item(tmp, tmp + 3);
	firstPrint(86, 18, 2, item);
	for (int i = 0; i < item.size(); i++)
	{
		gotoxy(91, 18 + 2 * i);
		cout << " * " << player[currentPlayer].item[i + 1];
	}
	gotoxy(117,30);
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
					cout << "�D�㤣��";
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

//�ϥιD��
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

//������l
bool Monopoly::controlDice(int whichPlayer)
{
	const string tmp[] = { "1�I","2�I" ,"3�I" ,"4�I" ,"5�I" ,"6�I" };
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
				cout << "�A��� " << toMove + 1 << " �I";
				if ((player[turn].position + toMove + 1) / map.size() != 0)  //�g�L�_�I��o1000��
				{
					gotoxy(75, 11);
					cout << "���a" << player[turn].number + 1 << "�q�L�_�I��o1000�����y";
					player[turn].money += 1000;
				}
				player[turn].position = (player[turn].position + toMove + 1) % map.size();
				gotoxy(75, 9);
				cout << "���ʦ�m�� " << map[player[turn].position].name;
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

//�]�m����
bool Monopoly::loadBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(98, 18);
	cout << "��J�a�I: ";
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
					cout << "�D�k�a��";
					inputClear();
					break;
				}
				else
				{
					if (map[i].barrier == 1)
					{
						cout << "���a�Ϥw���[�k";
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
			cout << "�d�L���a";
			inputClear();
		}
	}
}

//�}�a����
bool Monopoly::destroyBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(98, 18);
	cout << "��J�a�I: ";
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
					cout << "�D�k�a��";
					inputClear();
					break;
				}
				else
				{
					if (map[i].barrier == 0)
					{
						cout << "���a�ϨS���[�k";
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
			cout << "�d�L���a";
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(98, 18);
	cout << "��J�a�I: ";
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
					cout << "�D�k�a��";
					inputClear();
					break;
				}
				else
				{
					if (map[i].owner == -1)
					{
						cout << "���a�ϨS���ؿv";
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
			cout << "�d�L���a";
			inputClear();
		}
	}
}

//�n�ϥΪ��a��
bool Monopoly::chooseFile(void)
{
	system("color 0f");
	system("cls");
	_chdir(".\\map");
	vector<string> mapFileName;
	struct _finddata_t fileName;
	//Ū���ɦW
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
	//-------------------------------------------------------------------------------------------------------------�}��W��
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
	//-------------------------------------------------------------------------------------------------------------��l��+�����+�^�X��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	moneyChanged();
	gotoxy(1, 4);		cout << turn + 1;		gotoxy(70, 4);	cout << throughRound;
	positionChanged();
	//-------------------------------------------------------------------------------------------------------------�a��
	for (int i = 0, j = 7; i < 7; i++, j = j + 3)	//����
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
	for (int i = 7, j = 1; i < 14; i++, j = j + 9)	//�U��
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
	for (int i = 14, j = 28; i < 21; i++, j = j - 3)	//�k��
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
	for (int i = 21, j = 64; i < 28; i++, j = j - 9)	//�W��
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
	cout << "�C�����p���";
	gotoxy(73, 1);
	cout << "---------------------------------------------";
	gotoxy(73, 15);
	cout << "���";
	gotoxy(73, 16);
	cout << "---------------------------------------------";
	//-------------------------------------------------------------------------------------------------------------------------�Ҧb��m
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
		if (max < player[i].money)
		{
			max = player[i].money;
			tag = i;
		}
	}
	if (max == -1)
		cout << "���x�ШS";
	else
	{
		int num = 0;
		for (int i = 0; i < player.size(); i++)
		{
			if (player[i].money == max)
			{
				gotoxy(80, 7 + num * 2);
				cout << "���a " << player[i].number + 1 << " ���!!!";
				num++;
			}
		}
	}
	gotoxy(80, 15);
	cout << "Press ENTER to continue";
	pressEnter();
	player.clear();
	map.clear();
}

void Monopoly::moneyChanged()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {       //���M��
		gotoxy(j, 1); cout << "                 ";
	}
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		gotoxy(j, 1); cout << "$" << player[i].money;
	}
}

void Monopoly::positionChanged()
{
	switch ((player[0].position / 7))
	{
	case 0: {
		gotoxy(1, 8 + (player[0].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);  cout << "1";  break;
	}
	case 1: {
		gotoxy(1 + (player[0].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);  cout << "1";  break;
	}
	case 2: {
		gotoxy(64, 29 - (player[0].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);  cout << "1";  break;
	}
	case 3: {
		gotoxy(64 - (player[0].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);  cout << "1";  break;
	}
	}
	if (player.size() >= 2)
	{
		switch ((player[1].position / 7))
		{
		case 0: {
			gotoxy(3, 8 + (player[1].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);  cout << "2";  break;
		}
		case 1: {
			gotoxy(3 + (player[1].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);  cout << "2";  break;
		}
		case 2: {
			gotoxy(66, 29 - (player[1].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);  cout << "2";  break;
		}
		case 3: {
			gotoxy(66 - (player[1].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);  cout << "2";  break;
		}
		}
	}
	if (player.size() >= 3)
	{
		switch ((player[2].position / 7))
		{
		case 0: {
			gotoxy(6, 8 + (player[2].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);  cout << "3";  break;
		}
		case 1: {
			gotoxy(6 + (player[2].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);  cout << "3";  break;
		}
		case 2: {
			gotoxy(69, 29 - (player[2].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);  cout << "3";  break;
		}
		case 3: {
			gotoxy(69 - (player[2].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);  cout << "3";  break;
		}
		}
	}
	if (player.size() >= 4)
	{
		switch ((player[3].position / 7))
		{
		case 0: {
			gotoxy(8, 8 + (player[3].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  cout << "4";  break;
		}
		case 1: {
			gotoxy(8 + (player[3].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  cout << "4";  break;
		}
		case 2: {
			gotoxy(71, 29 - (player[3].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  cout << "4";  break;
		}
		case 3: {
			gotoxy(71 - (player[3].position % 7) * 9, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  cout << "4";  break;
		}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Monopoly::positionClear(int curplayer)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	switch (curplayer)  //�u��curplayer��m
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
	for (int i = 0; i < 3; i++)
	{
		if (rand() % 2)
		{
			stockPrice[i] *= (1 + 0.001*(rand() % 100 + 1));
		}
		else
		{
			stockPrice[i] *= (1 - 0.001*(rand() % 100 + 1));
		}
	}
}

void Monopoly::stock(Player &person)
{
	const string tmp[] = { "�O�W50","x��","�xx�q" };
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
				cout << stock[toDo] << ": " << stockPrice[toDo] << " ��/�i";
				gotoxy(95, 19);
				cout << "�A���s��: " << person.deposit;
				gotoxy(95, 21);
				cout << "�A�֦����i��: " << person.ownStock[toDo] << " �i";
				const string tmp[] = { "�R","��" };
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
								cout << "��J�i��: ";
								cin >> num;
								gotoxy(100, 25);
								if (num == -1)
								{
									break;
								}
								else if (num < 0)
								{
									cout << "�D�k�Ʀr";
									gotoxy(110, 23);
									cout << "       ";
								}
								//�R
								if (operate)
								{
									if (person.ownStock[toDo] < num)
									{
										cout << "�Ѳ��i�Ƥ���";
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
										cout << "�A���s��: " << person.deposit;
										gotoxy(95, 21);
										cout << "�A�֦����i��: " << person.ownStock[toDo] << " �i";
										break;
									}
								}
								//��
								else
								{
									if (person.deposit < num*stockPrice[toDo])
									{
										cout << "�s�ڤ���";
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
										cout << "�A���s��: " << person.deposit;
										gotoxy(95, 21);
										cout << "�A�֦����i��: " << person.ownStock[toDo] << " �i";
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
	gotoxy(95, 17);
	cout << "�A���s��: " << person.deposit;
	const string tmp[] = { "�s��","����" };
	vector<string> thing(tmp, tmp + 2);
	firstPrint(85, 20, 2, thing);
	bool toDo = 0;
	while (true)
	{
		if (_kbhit())
		{
			int input = _getch();
			if (input == 224)
			{
				down_gotoxy(toDo, 85, 20, 2, thing);
				toDo = 1 - toDo;
			}
			else if (input == 13)
			{
				//����
				if (toDo)
				{
					gotoxy(95, 17);
					cout << "�A���s��: " << person.deposit;
					while (true)
					{
						int num;
						gotoxy(95, 20);
						cout << "��J���B: ";
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
							cout << "�D�k�Ʀr";
							gotoxy(105, 20);
							cout << "         ";
						}
						else if (num > person.deposit)
						{
							cout << "�s�ڤ���";
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
							cout << "�A���s��: " << person.deposit;
							moneyChanged();
							for (int i = 20; i < 31; i++)
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
				//�s��
				else
				{
					gotoxy(95, 17);
					cout << "�A���s��: " << person.deposit;
					while (true)
					{
						int num;
						gotoxy(95, 20);
						cout << "��J���B: ";
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
							cout << "�D�k�Ʀr";
							gotoxy(105, 20);
							cout << "         ";
						}
						else if (num > person.money)
						{
							cout << "�{������";
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
							cout << "�A���s��: " << person.deposit;
							moneyChanged();
							for (int i = 20; i < 31; i++)
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
	for (int i = 0; i < 3; i++)
	{
		stockPrice[i] = 1000;
	}
}