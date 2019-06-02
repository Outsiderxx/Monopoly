#include"Player.h"

Player::Player(int characterType)
{
	money = 30000;
	position = 0;
	stop = 0;
	character = characterType;
	skip = 0;
	state = 1;
	item.resize(4);
	for (int i = 0; i < item.size(); i++)
		item[i] = 1;
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