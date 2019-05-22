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
	void setNumber(int);
	void setOwner(int);
	void setLevel(int);
	void setType(int);
	void setCost(int);
	void setPrice(int);
	int getNumber();
	int getOwner();
	int getLevel();
	int getType();
	int getCost();
	int getPrice();
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