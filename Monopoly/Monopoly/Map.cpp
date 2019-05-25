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

void Map::areaControl(Player nowPlayer)
{
	if (type == 0)		//start area
	{
		nowPlayer.money += 1000;	//go through start area can earn money(need adjust)
	}
	else if (type == 1)	//nomral area
	{
		if (owner == -1)
		{
			//choose buy or not
			if (1/*buy*/)
			{
				owner = true;
				nowPlayer.money -= price;
				level = 0;
				//house data update
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			if (owner == nowPlayer.character)
			{
				if (level < 4)
				{
					level++;
					//house data update
				}
			}
			else
			{
				nowPlayer.money -= cost[level];
				//ownerPlayer's money increaseS
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
}