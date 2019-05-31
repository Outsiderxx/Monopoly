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

//return true if need dice again
//other situation return false
bool Map::areaControl(vector<Player> &playerList, int currentPlayer)
{
	if (type == 1)	//nomral area
	{
		if (owner == -1)
		{
			int toBuy = 0;
			string tmp[] = { "是","否" };
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
		switch (randomFateCard)
		{
		case 0:
			playerList[currentPlayer].position += (rand() % 3) + 1;

			areaControl(playerList, currentPlayer);
			break;
		case 1:
			playerList[currentPlayer].position -= (rand() % 3) + 1;
			areaControl(playerList, currentPlayer);
			break;
		case 2:
			playerList[currentPlayer].stop = 1;
			break;
		case 3:
			playerList[currentPlayer].position = rand() % 28/*mapSize*/;
			break;
		case 4:
			return true;
			break;
		}
	}
	else if (type == -2)			//chance area
	{
		int randomChanceCard;
		randomChanceCard = rand() % 5;
		switch (randomChanceCard)
		{
		case 0:
			playerList[currentPlayer].money += 1000;
			break;
		case 1:
			playerList[currentPlayer].money -= 1000;
			break;
		case 2:
			playerList[currentPlayer].stop = 1;
			break;
		case 3:
			playerList[currentPlayer].skip = 1;
			break;
		case 4:
			for (int loop = 0; loop < playerList.size(); loop++)
			{
				if (loop == currentPlayer)
				{
					playerList[loop].money += 500 * playerList.size();
				}
				else
				{
					playerList[loop].money -= 500;
				}
			}
			break;

		}
	}
	else if (type == 2) //Bank
	{

	}
	return false;
}