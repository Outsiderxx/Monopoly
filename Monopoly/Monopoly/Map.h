#pragma once
#include <iostream>
#include <string>
#include "Player.h"
class Map
{
public:
	Map();
	int getNumber();
	string getName();
	void areaControl(Player);
	void areaControl(Player, Player);
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