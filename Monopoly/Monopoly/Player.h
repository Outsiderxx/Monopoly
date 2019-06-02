#pragma once
#include"Bank.h"

class Player
{
public:
	Player() {}
	Player(int);
	int getMoney();
	int getPosition();
	Bank getAccount();
private:
	vector<int> item;
	int number;
	int money;
	int position;
	int stop;
	int character; 
	int skip;
	bool state;
	Bank account;
	friend class Map;
	friend class Monopoly;
};