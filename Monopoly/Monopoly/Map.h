#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include"Player.h"
using namespace std;
class Map
{
public:
	Map();
	int getNumber();
	string getName();
	void areaControl(Player);
private:
	int number;
	string name;
	int owner;
	int level;
	int type;
	bool barrier;	
	vector<int> cost;
	int price;	
	friend class Monopoly;
};