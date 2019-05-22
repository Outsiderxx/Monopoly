#pragma once
#include"Bank.h"
#include<vector>
using namespace std;
class Player
{
public:
	Player();
	~Player();
	void setItem(int);
	void setMoney(int);
	void setPosition(int);
	void setStop(int);
	void setAccount(const Bank&);
	void setHouse(int);
	int getItem();
	int getMoney();
	int getPosition();
	int getStop();
	Bank getAccount();
	vector<int> getHouse();
private:
	int item[2];			// 2 items each player
	int money;
	int position;
	int stop;
	vector<int> house;
	Bank account;
	friend class Monopoly;
};