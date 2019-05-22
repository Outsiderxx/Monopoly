#pragma once
#include <vector>
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();
	void setDeposit(int);
	void setLoan_times(int);
	void setInterest(int);
	void setStockPrice(); //內部自行rand()
	void setOwnStock();
	int getDeposit();
	int getLoan_times();
	int getInterest();
	vector<int> getStockPrice();
	vector<int> getOwnStock();
private:
	int deposit;
	int loan_times;
	int interest;
	vector<int> StockPrice;
	vector<int> ownStock;
};