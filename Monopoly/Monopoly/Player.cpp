#include"Player.h"

Player::Player(int characterType)
{
	money = 30000;
	position = 0;
	stop = 0;
	character = 3;
	skip = 0;
	item.resize(2);
	for (int i = 0; i < item.size(); i++)
		item[i] = 0;
}

int Player::getMoney()
{
	return money;
}

int Player::getPosition()
{
	return position;
}

/*Bank Player::getAccount()
{
	//control
}*/