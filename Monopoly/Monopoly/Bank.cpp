#include "bank.h"
#define numOfStocks 3
Bank::Bank()
{
	srand(time(NULL));
	deposit = 10000;
	loan_times = 0;
	interest = 0;
	StockPrice.resize(numOfStocks);
	ownStock.resize(numOfStocks);
	upDownLimit.resize(numOfStocks);
	for (int i = 0; i < numOfStocks; ++i)
	{
		StockPrice[i] = 20 + 10 * (float(rand()) / RAND_MAX);
		ownStock[i] = 0;
		upDownLimit[i] = 0;
	}
}
Bank::~Bank() {}

void Bank::setDeposit(int dep) { deposit = dep; }
void Bank::setLoan_times(int times) { loan_times = times; }
void Bank::setInterest(int inter) { interest = inter; }
void Bank::stockPriceFlow()
{
	roundCount++;
	float range;
	if (roundCount = 1)
	{
		for (int i = 0; i < numOfStocks; ++i)
		{
			minStockPrice[i] = StockPrice[i] * 0.88;
			maxStockPrice[i] = StockPrice[i] * 1.12;
		}
	}
	for (int i = 0; i < numOfStocks; ++i)
	{
		range = (float(rand()) / RAND_MAX) * 0.05;
		if (StockPrice[i] * range >= maxStockPrice[i]) //º¦°±
		{
			StockPrice[i] = maxStockPrice[i];
			upDownLimit[i] = 1;
		}
		else if (StockPrice[i] * range <= minStockPrice[i]) // ¶^°±
		{
			StockPrice[i] = minStockPrice[i];
			upDownLimit[i] = 2;
		}
		else
		{
			StockPrice[i] *= range;
			upDownLimit[i] = 0;
		}
	}
	if (roundCount == 4) roundCount = 0;
}
void Bank::setOwnStock(int StockId, int num) { ownStock[StockId] = num; }
int Bank::getDeposit() { return deposit; }
int Bank::getLoan_times() { return loan_times; }
int Bank::getInterest() { return interest; }
vector<float> Bank::getStockPrice() { return StockPrice; }
vector<int> Bank::getOwnStock() { return ownStock; }
vector<int> Bank::getUpDownLimit() { return upDownLimit; }
