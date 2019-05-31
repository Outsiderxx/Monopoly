#include "map.h"
#include"Monopoly.h"
Map::Map()
{
	owner = -1;
	level = 0;
	barrier = 0;
	cost.resize(4);
}

int Map::getNumber()
{
	return number;
}

string Map::getName()
{
	return name;
}

void Map::areaControl(vector<Player> playerList,int currentPlayer)
{
	Monopoly changeinfo;
	if (type == 1)	//nomral area
	{
		if (owner == -1)
		{
			//print �a�W  �O�_�ʶR-------------------------------------------------������
			int toBuy = 0;
			string tmp[] = { "�O","�_" };
			vector<string> choose(tmp, tmp + 2);
			while (true)
			{
				if (_kbhit())
				{
					int input = _getch();
					if (input == 224)
					{
						input = _getch();
						down_gotoxy(toBuy, 54, 21, 1, choose); //need revise
						toBuy = 1 - toBuy;
					}
					else if (input == 13)
					{
						if (toBuy == 0)
						{
							playerList[currentPlayer].money -= price;		//-----------------------------------cout new map after buying
							owner = currentPlayer;
						}
						break;
					}
				}
			}
		}
		else if (owner == currentPlayer)		//---------------------�ɯ� ������
		{
			if (level < 4)
			{
				level++;
			}
		}
		else                     //--------------------------�I�� ����
		{
			if (!playerList[currentPlayer].skip)
			{
				playerList[currentPlayer].money -= cost[level];
				playerList[owner].money += cost[level];
				//-------------------------------------------------------------------------------------------cout money
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	
				for (int i = 0, j = 1; i < playerList.size(); i++, j = j + 18) {							//���M��
					gotoxy(j, 1);	cout << "                 ";
				}
				for (int i = 0, j = 1; i < playerList.size(); i++, j = j + 18) {
					gotoxy(j, 1);	cout << "$" << playerList[i].getMoney();	
				}
				//-------------------------------------------------------------------------------------------
				playerList[currentPlayer].skip = 0;
			}
		}
	}
	else if (type == -1)			//fate area
	{
		int randomFateCard;
		randomFateCard = rand() % 5;	//if we have 5 fate options
		// do fate part
	}
	else if (type == -2)			//chance area
	{
		int randomChanceCard;
		randomChanceCard = rand() % 5;	//if we have 5 chance options
		//do chance part
	}
	else if (type == 2) //Bank
	{

	}
}