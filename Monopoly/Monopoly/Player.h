#pragma once
#include "Console.h"

class Player
{
public:
	Player() {};
	Player(int);
	
private:
	vector<int> item;
	int number;
	int money;
	int position;
	int stop;
	int character; 
	int skip;
	bool state;
	int deposit;
	vector<int> ownStock;
	friend class Map;
	friend class Monopoly;
};