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
	vector<int> item;
	int money;
	int position;
	bool stop;
	int character; 
	bool skip;
	Bank account;
	friend class Map;
	friend class Monopoly;
};