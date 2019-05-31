#pragma once
#include <iostream>
#include <string>
#include "Console.h"
#include "Player.h"
class Map
{
public:
	Map();
	int getNumber();
	string getName();
	bool areaControl(vector<Player>&, int);
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