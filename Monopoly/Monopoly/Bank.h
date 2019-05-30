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
	//-----------�Ѳ�����------------------
	static vector<float> StockPrice;
	static vector<float> minStockPrice, maxStockPrice; // ��^�X�����^�W�U��
	static vector<int> upDownLimit; // 0:���F���^���O 1:�����O 2:�^���O
	static clock_t lastTime;
	static clock_t nowTime;
	static int flowTimes;

	void stockPriceFlow(); //�����ۦ�rand()
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