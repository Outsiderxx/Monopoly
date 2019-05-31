#include "Monopoly.h"

//�C��
void Monopoly::playGame(bool chooseBanker)
{
	if (chooseBanker)
		turn = dice(player.size());

	while (round > 0 && player.size() > 0)	
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
				player[i].stop = 0;
				continue;
			}
			gotoxy(88, 3);		 cout << "�{�b���� " << i + 1 << " ���K�M��";
			gotoxy(89, 5);		cout << "��enter���Y��l!!!!";		gotoxy(117, 30);
			while (true)
			{
				if(_kbhit())
				{
					int input = _getch();
					//���a��ENTER
					if (input == 13)
					{
						hintclear();		//---------���T�M��
						positionclear(i);
						//�Y��l
						int point = dice(6) + 1;
						gotoxy(90, 3);		cout << "�A��� "<<point;		gotoxy(117, 30);		//------------------------------------	�I��???
						if ((player[i].position + point) % map.size() != 0)  //�g�L�_�I��o1000��
							player[i].money += 1000;
						player[i].position = (player[i].position + point) % map.size();	//-----------------���ܦ�m��T
						positinchanged(i);
						gotoxy(90, 5);		cout << i + 1 << " �{�b�b " << map[player[i].position].name;	gotoxy(117, 30);//----------------
						map[player[i].position].areaControl(player,i);
						break;
					}
					//���a��ESC�A�s�X���
					else if (input == 27)
					{
						int flag = menu(i);
						if (flag)
							break;
					}
				}
			}
		}
		hintclear();
		round--;
	}
}

//�����ܰʧ@: �s�� �§� ���� ���}
void Monopoly::action(int toDo)
{
	switch (toDo)
	{
	case 0:
		loadInfo("initial.txt", 1);
		gameMode = 1;
		setPlayerNum();
		mapintitial();
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
void Monopoly::loadInfo(string mapFile, bool isNew)
{
	ifstream inputFile(mapFile);
	int playerNum;
	string str;
	inputFile >> mapName >> round >> playerNum;
	for (int i = 0; i < 28; i++)
	{
		Map tmpMap;
		inputFile >> tmpMap.number;
		if (tmpMap.number == 0 || tmpMap.number == 6 || tmpMap.number == 16)
		{
			inputFile >> tmpMap.name >> tmpMap.type;
		}
		else
		{
			inputFile >> tmpMap.name >> tmpMap.type >> tmpMap.owner >> tmpMap.level >> tmpMap.barrier >> tmpMap.price;
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
			ss >> num >> tmp.character >> tmp.position >> tmp.money >> tmp.stop >> tmp.skip;
			for (int j = 0; j < tmp.item.size(); j++)
				ss >> tmp.item[j];
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
int Monopoly::dice(int range)	//------------------------------------------------------print+1������
{
	srand(time(NULL));
	int result = rand() % range;
	return result;
}

// ���: �~�� �ϥιD�� ������l �s�� ���}
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

//�x��
void Monopoly::saveFile(void)
{

}

//��ܭn�i�檺�^�X��
void Monopoly::setRound(void)
{
	const string tmp[] = { "10","20","30","40","50" };
	vector<string> roundDecision(tmp, tmp + 5);
	gotoxy(17, 19);
	cout << "��ܭn�C�����^�X��:";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	gotoxy(40, 19);
	cout << roundDecision[0];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 1; i < 5; i++)
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
	}
}

//������l
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
				map[player[whichPlayer].position].areaControl(player, whichPlayer);
				break;
			}
		}
	}
}

//�]�m����
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
					cout << "���a�ϨS����ê��";
			}
		}
	}
}

//�n�ϥΪ��a��
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
int Monopoly::getRound(void)
{
	return round;
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
	case 1:{
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";	break; }
	case 2:{
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";
		gotoxy(19, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p               ";	break; }
	case 3:{
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";
		gotoxy(19, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p               ";
		gotoxy(37, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	cout << "3p               ";	break; }
	case 4:{
		gotoxy(1, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p               ";
		gotoxy(19, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p               ";
		gotoxy(37, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	cout << "3p               ";
		gotoxy(55, 0);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	cout << "4p               ";	break; }
	}
	//-------------------------------------------------------------------------------------------------------------��l��+��l��m+�����+�^�X��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		gotoxy(j, 1);	cout << "$" << player[i].getMoney();
	}
	gotoxy(1, 4);		cout << getTurn();		gotoxy(70, 4);	cout << getRound();
	gotoxy(1, 8);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	cout << "1";
	gotoxy(3, 8);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);	cout << "2";
	gotoxy(6, 8);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);	cout << "3";
	gotoxy(8, 8);		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);	cout << "4";
	//-------------------------------------------------------------------------------------------------------------�a��
	for (int i = 0, j = 7 ; i < 7; i++, j = j + 3)	//����
	{
		switch (map[i].owner)
		{
		case -1:{
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	lenprint(map[i].getName());	break; }
		case 0:{
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	lenprint(map[i].getName());	break;}
		case 1:{
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	lenprint(map[i].getName());	break;}
		case 2:{
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	lenprint(map[i].getName());	break;}
		case 3:{
			gotoxy(1, j);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	lenprint(map[i].getName()); break;}
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(117, 30);
}
void Monopoly::moneychanged()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {							//���M��
		gotoxy(j, 1);	cout << "                 ";
	}
	for (int i = 0, j = 1; i < player.size(); i++, j = j + 18) {
		gotoxy(j, 1);	cout << "$" << player[i].getMoney();
	}
}
void Monopoly::positinchanged(int curplayer)	
{
	switch (curplayer)		//�u��curplayer��m
	{
	case 0:{	//(1,8)
		switch ((player[curplayer].position/7))
		{
		case 0:{
			gotoxy(1, 8 + (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);		cout << "1";		break;
		}
		case 1:{
			gotoxy(1 + (player[curplayer].position % 7) * 9, 29);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);		cout << "1";		break;
		}
		case 2:{
			gotoxy(64, 29 - (player[curplayer].position % 7) * 3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);		cout << "1";		break;
		}
		case 3:{
			gotoxy(64 - (player[curplayer].position % 7) * 9, 8);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);		cout << "1";		break;
		}
		}	break;
	}
	case 1:{	//(3,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(3, 8 + (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);		cout << "2";		break;
		}
		case 1: {
			gotoxy(3 + (player[curplayer].position % 7) * 9, 29);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);		cout << "2";		break;
		}
		case 2: {
			gotoxy(66, 29 - (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);		cout << "2";		break;
		}
		case 3: {
			gotoxy(66 - (player[curplayer].position % 7) * 9, 8);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);		cout << "2";		break;
		}
		}	break;
	}
	case 2:{	//(6,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(6, 8 + (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);		cout << "3";		break;
		}
		case 1: {
			gotoxy(6 + (player[curplayer].position % 7) * 9, 29); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);		cout << "3";		break;
		}
		case 2: {
			gotoxy(69, 29 - (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);		cout << "3";		break;
		}
		case 3: {
			gotoxy(69 - (player[curplayer].position % 7) * 9, 8);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);		cout << "3";		break;
		}
		}	break;
	}
	case 3:{	//(8,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(8, 8 + (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		cout << "4";		break;
		}
		case 1: {
			gotoxy(8 + (player[curplayer].position % 7) * 9, 29);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		cout << "4";		break;
		}
		case 2: {
			gotoxy(71, 29 - (player[curplayer].position % 7) * 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		cout << "4";		break;
		}
		case 3: {
			gotoxy(71 - (player[curplayer].position % 7) * 9, 8);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		cout << "4";		break;
		}
		}	break;
	}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Monopoly::positionclear(int curplayer)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	switch (curplayer)		//�u��curplayer��m
	{
	case 0: {	//(1,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(1, 8 + (player[curplayer].position % 7) * 3);	cout << " ";		break;
		}
		case 1: {
			gotoxy(1 + (player[curplayer].position % 7) * 9, 29);		cout << " ";		break;
		}
		case 2: {
			gotoxy(64, 29 - (player[curplayer].position % 7) * 3); 	cout << " ";		break;
		}
		case 3: {
			gotoxy(64 - (player[curplayer].position % 7) * 9, 8);		cout << " ";		break;
		}
		}	break;
	}
	case 1: {	//(3,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(3, 8 + (player[curplayer].position % 7) * 3);		cout << " ";		break;
		}
		case 1: {
			gotoxy(3 + (player[curplayer].position % 7) * 9, 29);		cout << " ";		break;
		}
		case 2: {
			gotoxy(66, 29 - (player[curplayer].position % 7) * 3);		cout << " ";		break;
		}
		case 3: {
			gotoxy(66 - (player[curplayer].position % 7) * 9, 8);		cout << " ";		break;
		}
		}	break;
	}
	case 2: {	//(6,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(6, 8 + (player[curplayer].position % 7) * 3);		cout << " ";		break;
		}
		case 1: {
			gotoxy(6 + (player[curplayer].position % 7) * 9, 29);		cout << " ";		break;
		}
		case 2: {
			gotoxy(69, 29 - (player[curplayer].position % 7) * 3);		cout << " ";		break;
		}
		case 3: {
			gotoxy(69 - (player[curplayer].position % 7) * 9, 8);		cout << " ";		break;
		}
		}	break;
	}
	case 3: {	//(8,8)
		switch ((player[curplayer].position / 7))
		{
		case 0: {
			gotoxy(8, 8 + (player[curplayer].position % 7) * 3);		cout << " ";		break;
		}
		case 1: {
			gotoxy(8 + (player[curplayer].position % 7) * 9, 29);		cout << " ";		break;
		}
		case 2: {
			gotoxy(71, 29 - (player[curplayer].position % 7) * 3);		cout << " ";		break;
		}
		case 3: {
			gotoxy(71 - (player[curplayer].position % 7) * 9, 8);		cout << " ";		break;
		}
		}
	}	break;
	}
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

