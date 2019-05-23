#pragma once
#include <string>
#include <vector>
using namespace std;

class Map
{
public:
	Map();
	~Map();
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
	vector<int> cost;	//go through this area
	int price;	//when buying area
	friend class Monopoly;
};