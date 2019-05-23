#pragma once
#include"Bank.h"
#include<vector>
#include <utility>
using namespace std;
class Player
{
public:
	Player(int);
	~Player();
	pair<int, int> getHouseInfo();
	int getMoney();
	int getPosition();
	Bank getAccount();
	vector<int> getHouse();
private:
	int item[2];			// 2 items each player
	int money;
	int position;
	int stop;
	int character; //¨¤¦â
	vector<pair<int,int>> house;
	Bank account;
	friend class Monopoly;
};