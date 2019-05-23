#pragma once
#include <vector>
#include<cstdlib>
#include<time.h>
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();
	void setDeposit(int);
	void setLoan_times(int);
	void setInterest(int);
	void stockPriceFlow(); //�����ۦ�rand()
	void setOwnStock(int, int);
	int getDeposit();
	int getLoan_times();
	int getInterest();
	vector<float> getStockPrice();
	vector<int> getOwnStock();
	vector<int> getUpDownLimit();
private:
	int deposit;
	int loan_times;
	int interest;
	int roundCount;
	vector<float> StockPrice;
	vector<float> minStockPrice, maxStockPrice; // ��^�X�����^�W�U��
	vector<int> ownStock;
	vector<int> upDownLimit; // 0:���F���^���O 1:�����O 2:�^���O
};