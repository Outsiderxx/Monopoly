#pragma once
#include<iostream>
#include<cstdbool>
#include<vector>
#include<ctime>
#include"Player.h"
using namespace std;
class Map
{
public:
	Map();
	~Map();
	int getNumber();
	string getName();
	void areaControl(Player);
	int operator[](int);
	int getNumber();
	string getName();
	void nomralArea();
	void firstArea();
	void chanceArea();
	void fateArea();
private:
	int number;
	string name;
	int owner;
	int level;
	int type;
	bool barrier;
	vector<int> cost;	//go through this area
	int price;			//when buying area
	friend class Monopoly;
};