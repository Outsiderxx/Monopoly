#include"Map.h"

Map::Map() { srand(time(NULL)); }

Map::~Map() {}

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
	if (this->type == 0)		//start area
	{
		nowPlayer.money+=1000;	//go through start area can earn money(need adjust)
	}
	else if (this->type == 1)	//nomral area
	{
		if (!this->owner)
		{
			//choose buy or not
			if(1/*buy*/)
			{
				owner = true;
				nowPlayer.money-=price;
				level = 0;
				nowPlayer.house.push_back(make_pair(number, level));
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			bool ownerIsMe = false;
			for (int loop = 0; loop < nowPlayer.house.size(); loop++)
			{
				if (this->number == nowPlayer.house[loop].first)
				{
					ownerIsMe = true;
					break;
				}
			}
			if (ownerIsMe)
			{
				if (level < 4)
				{
					level++;
					nowPlayer.house.push_back(make_pair(number,level));
				}
			}
			else
			{
				nowPlayer.money-=cost[level];
			}
		}
	}
	else if (this->type == -1)			//fate area
	{
		int randomFateCard;
		randomFateCard = rand() % 10;	//if we have 10 fate options
		// do fate part
	}
	else if (this->type == -2)			//chance area
	{
		int randomChanceCard;
		randomChanceCard = rand() % 10;	//if we have 10 chance options
		//do chance part
	}
}