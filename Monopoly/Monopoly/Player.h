#pragma once
#include"Bank.h"

class Player
{
public:
	Player(int);
	int getMoney();
	int getPosition();
	Bank getAccount();
private:
	int item[2];
	int money;
	int position;
	int stop;
	int character; 
	Bank account;
	friend class Map;
	friend class Monopoly;
};