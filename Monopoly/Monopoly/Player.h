#pragma once
#include"Bank.h"
#include<vector>
#include <utility>
using namespace std;
class Player
{
public:
	Player(int);
	int getMoney();
	int getPosition();
	Bank getAccount();
private:
	int item[2];			// 2 items each player
	int money;
	int position;
	int stop;
	int character; //¨¤¦â
	vector<pair<int,int>> house;
	Bank account;
	friend class Map;
	friend class Monopoly;
};