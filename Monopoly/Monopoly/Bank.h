#pragma once
#include <vector>
#include<cstdlib>
#include<time.h>
#define numOfStocks 3
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();
	void setDeposit(int);
	void setLoan_times(int);
	void setInterest(int);
	int getDeposit();
	int getLoan_times();
	int getInterest();
	void saveMoney(int);
	void withdrawMoney(int);
	//-----------股票相關------------------
	static vector<float> StockPrice;
	static vector<float> minStockPrice, maxStockPrice; // 當回合的漲跌上下限
	static vector<int> upDownLimit; // 0:未達漲跌停板 1:漲停板 2:跌停板
	static clock_t lastTime;
	static clock_t nowTime;
	static int flowTimes;

	void stockPriceFlow(); //內部自行rand()
	void setOwnStock(int, int);
	vector<float> getStockPrice();
	vector<int> getOwnStock();
	vector<int> getUpDownLimit();
private:
	int deposit;
	int loan_times;
	int interest;
	vector<int> ownStock;
};