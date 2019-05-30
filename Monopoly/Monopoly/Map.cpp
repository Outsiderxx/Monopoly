#include "map.h"

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

void Map::areaControl(vector<Player> &playerList,int currentPlayer)
{
	if (type == 1)	//nomral area
	{
		if (owner == -1)
		{
			int toBuy = 0;
			string tmp[] = { "¬O","§_" };
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
							playerList[currentPlayer].money -= price;
							owner = currentPlayer;
						}
						break;
					}
				}
			}
		}
		else if (owner == currentPlayer)
		{
			if (level < 4)
			{
				level++;
			}
		}
		else
		{
			if (!playerList[currentPlayer].skip)
			{
				playerList[currentPlayer].money -= cost[level];
				playerList[owner].money += cost[level];
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