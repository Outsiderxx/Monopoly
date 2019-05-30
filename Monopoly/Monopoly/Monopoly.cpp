#include "Monopoly.h"

//�C��
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
			mapintitial();
			hintclear();
			gotoxy(80, 3);		 cout << "�{�b���� " << player[turn].number + 1 << " ���K�M��";
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
						cout << "�A��� " << step << "�I";
						if ((player[turn].position + step) / map.size() != 0)  //�g�L�_�I��o1000��
						{
							gotoxy(80, 11);
							cout << "���a" << player[turn].number + 1 << "�q�L�_�I��o1000�����y";
							player[turn].money += 1000;
						}
						player[turn].position = (player[turn].position + step) % map.size();
						gotoxy(80, 9);		
						cout << "�{�b��m�b " << map[player[turn].position].name;
						gotoxy(117, 30);
						map[player[turn].position].areaControl(player, turn);
						break;
					}
					//���a��ESC�A�s�X���
					else if (input == 27)
					{
						int flag = menu(turn);
						if (flag)
							break;
					}
				}
			}
		}
		throughRound++;
	}
}

//�����ܰʧ@: �s�� �§� ���� ���}
void Monopoly::action(int toDo)
{
	switch (toDo)
	{
	case 0:
		loadInfo(".\\map\\initial.txt");
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

//��ܪ��a�H��
void Monopoly::setPlayerNum(void)
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
				chooseCharacter(playerNum);
				break;
			}
		}
	}
}

//��ܨ���
void Monopoly::chooseCharacter(int num)
{
	const string tmp[4] = { "�k������","�޽L�l��","��q�̳J"," ���H69" };
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

//���J���
void Monopoly::loadInfo(string mapFile)
{
	bool isNew = 0;
	if (mapFile == ".\\map\\initial.txt")
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
			while (true)
			{
				int number, level;
				ss >> number >> level;
				if (ss.eof())
					break;
				map[number].owner = player[i].number;
				map[number].level = level;
			}
		}
	}
}

//��ܻ���
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
bool Monopoly::menu(int whichPlayer)
{
	const string tmp[] = { "�~��","�ϥιD��","������l","�s��","���}" };
	vector<string> menuText(tmp, tmp + 5);
	firstPrint(58, 15, 2, menuText);
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
					up_gotoxy(toDo, 58, 15, 2, menuText);
					if (toDo == 0)
						toDo = 4;
					else
						toDo--;
				}
				else if (input == 80)
				{
					down_gotoxy(toDo, 58, 15, 2, menuText);
					if (toDo == 4)
						toDo = 0;
					else
						toDo++;
				}
			}
			else if (input == 13)
			{
				if (toDo == 1)
				{
					int flag= chooseItem(whichPlayer);
					if(flag)
						break;
				}
				else if (toDo == 2)
				{
					//�ϥλ�����l�A���i�b�륿�`��l
					if (player[whichPlayer].item[0] != 0)
					{
						player[whichPlayer].item[0]--;
						controlDice(whichPlayer);
						return 1;
					}
					else
					{
						gotoxy(100, 25); //need revise
						cout << "�D�㤣��";
					}
				}
				else if (toDo == 3)
				{
					saveFile();
					break;
				}
			}
		}
	}
	return 0;
}

//�s��
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
				outputFile << player[i].item[j];
			}
			for (int j = 0; j < map.size(); j++)
			{
				if (map[i].owner == i)
				{
					outputFile << " " << map[i].number << " " << map[i].level;
				}
			}
			outputFile << endl;
		}
	}
	else
	{
		cout << "�ɮ׶}�ҥ���" << endl;
	}
}

//��ܭn�i�檺�^�X��
void Monopoly::setRound(void)
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
				break;
			}
		}
	}
}

//��ܭn�ϥΪ��D��
bool Monopoly::chooseItem(int currentPlayer)
{
	const string tmp[] = { "������l","�[�k","�l�l" };
	vector<string> item(tmp, tmp + 3);
	firstPrint(40, 19, 1, item);
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
					up_gotoxy(toUse, 40, 19, 1, item);
					if (toUse == 0)
						toUse = 1;
					else
						toUse--;
				}
				else if (input == 80)
				{
					down_gotoxy(toUse, 40, 19, 1, item);
					if (toUse == 1)
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
					return 1;
				}
				else
				{
					gotoxy(100, 25); //need revise
					cout << "�D�㤣��";
				}
			}
			else if (input == 'q')
			{
				//�M��
				return 0;
			}
		}
	}
}

//�ϥιD��
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

//������l
void Monopoly::controlDice(int whichPlayer)
{
	const string tmp[] = { "1�I","2�I" ,"3�I" ,"4�I" ,"5�I" ,"6�I" };
	vector<string> walk(tmp, tmp + 6);
	firstPrint(40, 19, 1, walk);
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
					up_gotoxy(toMove, 40, 19, 1, walk);
					if (toMove == 0)
						toMove = 5;
					else
						toMove--;
				}
				else if (input == 80)
				{
					down_gotoxy(toMove, 40, 19, 1, walk);
					if (toMove == 5)
						toMove = 0;
					else
						toMove++;
				}
			}
			else if (input == 13)
			{
				player[whichPlayer].position = (player[whichPlayer].position + toMove) % map.size();
				map[player[whichPlayer].position].areaControl(player, whichPlayer);
				break;
			}
		}
	}
}

//�]�m����
void Monopoly::loadBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(40, 16);
	cout << "��ܧA�n��m�[�k���a��";
	firstPrint(40, 19, 1, areaName);
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
					up_gotoxy(toBlock, 40, 19, 1, areaName);
					if (toBlock == 0)
						toBlock = map.size() - 1;
					else
						toBlock--;
				}
				else if (input == 80)
				{
					down_gotoxy(toBlock, 40, 19, 1, areaName);
					if (toBlock == map.size() - 1)
						toBlock = 0;
					else
						toBlock++;
				}
			}
			else if (input == 13)
			{
				if (!map[toBlock].barrier && map[toBlock].type == 1)
				{
					map[toBlock].barrier = 1;
					break;
				}
				else
					cout << "���a�Ϥ��i��m���٩Τw����ê��";
			}
		}
	}
}

//�}�a����
void Monopoly::destroyBlock(void)
{
	vector<string> areaName;
	for (int i = 0; i < map.size(); i++)
	{
		areaName.push_back(map[i].name);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(40, 16);
	cout << "��ܧA�n�R���[�k���a��";
	firstPrint(40, 19, 1, areaName);
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
					up_gotoxy(toDestroy, 40, 19, 1, areaName);
					if (toDestroy == 0)
						toDestroy = map.size() - 1;
					else
						toDestroy--;
				}
				else if (input == 80)
				{
					down_gotoxy(toDestroy, 40, 19, 1, areaName);
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
					cout << "���a�ϨS����ê��";
			}
		}
	}
}

//�n�ϥΪ��a��
void Monopoly::chooseFile(void)
{
	system("color 0f");
	system("cls");
	_chdir("D:\\My file\\Github\\Monopoly\\Monopoly\\Monopoly\\map");
	vector<string> mapFileName;
	struct _finddata_t fileName;
	//Ū���ɦW

	unsigned long long hfile = _findfirst("*.txt", &fileName);
	do
	{
		mapFileName.push_back(fileName.name);
	} while (hfile != -1 && _findnext(hfile, &fileName) == 0);
	gotoxy(15, 5);	
	firstPrint(15, 5, 2, mapFileName);
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
					up_gotoxy(toLoad, 15, 5, 2, mapFileName);//need revise
					if (toLoad == 0)
						toLoad = mapFileName.size() - 1;
					else
						toLoad--;
				}
				else if (input == 80)
				{
					down_gotoxy(toLoad, 15, 5, 2, mapFileName);//need revise
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

//���o�a�ϦW��
string Monopoly::getMapName(void)
{
	return mapName;
}

//���o���a
int Monopoly::getTurn(void)
{
	return turn;
}

//���o�^�X��
int Monopoly::getThroughRound(void)
{
	return throughRound;
}

//���o���a�H��
int Monopoly::getPlayerNum(void)
{
	return player.size();
}

void Monopoly::mapintitial()
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
	//for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {							//���M��
	//	gotoxy(j, 1);	cout << "                 ";
	//}
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		gotoxy(j, 1);	cout << "$" << player[i].money;
	}
	gotoxy(1, 4);		cout << turn;		gotoxy(70, 4);	cout << throughRound;
	//-------------------------------------------------------------------------------------------------------------�a��
	for (int i = 0, j = 7; i < 7; i++, j = j + 3)	//����
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenprint(map[i].getName());	break; }
		case 0: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenprint(map[i].getName());	break; }
		case 1: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenprint(map[i].getName());	break; }
		case 2: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenprint(map[i].getName());	break; }
		case 3: {
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenprint(map[i].getName()); break; }
		}
	}
	for (int i = 7, j = 1; i < 14; i++, j = j + 9)	//�U��
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenprint(map[i].getName());	break; }
		case 0: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenprint(map[i].getName());	break; }
		case 1: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenprint(map[i].getName());	break; }
		case 2: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenprint(map[i].getName());	break; }
		case 3: {
			gotoxy(j, 28);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenprint(map[i].getName()); break; }
		}
	}
	for (int i = 14, j = 28; i < 21; i++, j = j - 3)	//�k��
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenprint(map[i].getName());	break; }
		case 0: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenprint(map[i].getName());	break; }
		case 1: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenprint(map[i].getName());	break; }
		case 2: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenprint(map[i].getName());	break; }
		case 3: {
			gotoxy(64, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenprint(map[i].getName()); break; }
		}
	}
	for (int i = 21, j = 64; i < 28; i++, j = j - 9)	//�W��
	{
		switch (map[i].owner)
		{
		case -1: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenprint(map[i].getName());	break; }
		case 0: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenprint(map[i].getName());	break; }
		case 1: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenprint(map[i].getName());	break; }
		case 2: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenprint(map[i].getName());	break; }
		case 3: {
			gotoxy(j, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenprint(map[i].getName()); break; }
		}
	}
	//-------------------------------------------------------------------------------------------------------------------------�Ҧb��m
	gotoxy(117, 30);
}
void Monopoly::lenprint(string str)//---------------------------�ƪ��m����
{
	switch (str.length())
	{
	case 4:
		cout << "  " << str << "  ";	break;
	case 6:
		cout << " " << str << " ";		break;
	case 8:
		cout << str;	break;
	}
}
void Monopoly::hintclear()//-----------------------��s�k�����
{
	for (int i = 2; i < 30; i++)
	{
		gotoxy(73, i);	cout << "                                             ";
	}
	gotoxy(117, 30);
}