#include"Player.h"

Player::Player(int characterType)
{
	if (characterType == 0)
		money = 25000;
	else if (characterType == 1)
		money = 35000;
	else
		money = 30000;
	position = 0;
	stop = 0;
	character = characterType;
	skip = 0;
	state = 1;
	item.resize(4);
	for (int i = 0; i < item.size(); i++)
		item[i] = 1;
	deposit = 10000;
	ownStock.resize(3);
	for (int i = 0; i < 3; i++)
	{
		ownStock[i] = 0;
	}
}


