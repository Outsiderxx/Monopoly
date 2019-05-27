#include "bank.h"
Bank::Bank()
{
	srand(time(NULL));
	deposit = 10000;
	loan_times = 0;
	interest = 0;
	ownStock.resize(numOfStocks);
	/*
	StockPrice.resize(numOfStocks);
	upDownLimit.resize(numOfStocks);
	*/
	for (int i = 0; i < numOfStocks; ++i)
	{
		StockPrice[i] = 20 + 10 * (float(rand()) / RAND_MAX);
		ownStock[i] = 0;
		upDownLimit[i] = 0;
	}
	for (int i = 0; i < numOfStocks; ++i)
	{
		minStockPrice[i] = StockPrice[i] * 0.88;
		maxStockPrice[i] = StockPrice[i] * 1.12;
	}
	/*
	lastTime = time(NULL);
	nowTime = time(NULL);
	flowTimes = 0;
	*/
}
Bank::~Bank() {}

void Bank::setDeposit(int dep) { deposit = dep; }
void Bank::setLoan_times(int times) { loan_times = times; }
void Bank::setInterest(int inter) { interest = inter; }
int Bank::getDeposit() { return deposit; }
int Bank::getLoan_times() { return loan_times; }
int Bank::getInterest() { return interest; }
void Bank::saveMoney(int dep) // 存款
{
	if (dep > 0/*現有金額*/)
	{
		//存款無效
	}
	else
	{
		deposit += dep;
		//現有金額 -= dep;
	}
}
void Bank::withdrawMoney(int wd) // 提款
{
	if (wd > deposit)
	{
		//提款無效
	}
	else
	{
		deposit -= wd;
		//現有金額 += wd;
	}
}

void Bank::stockPriceFlow()
{
	nowTime = time(NULL);
	if (nowTime - lastTime >= 10)
	{
		lastTime = nowTime;
		flowTimes++;
		float range;
		for (int i = 0; i < numOfStocks; ++i)
		{
			range = 0.95 + (float(rand()) / RAND_MAX) * 0.1; //每次波動幅度為正負5%(原股價 * (0.95~1.05))
			if (StockPrice[i] * range >= maxStockPrice[i]) //漲停
			{
				StockPrice[i] = maxStockPrice[i];
				upDownLimit[i] = 1;
			}
			else if (StockPrice[i] * range <= minStockPrice[i]) // 跌停
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
		if (flowTimes == 6) // 每波動六次更新漲停標準
		{
			flowTimes = 0;
			for (int i = 0; i < numOfStocks; ++i)
			{
				minStockPrice[i] = StockPrice[i] * 0.88;
				maxStockPrice[i] = StockPrice[i] * 1.12;
			}
		}
	}
}
void Bank::setOwnStock(int StockId, int num) { ownStock[StockId] = num; }


vector<float> Bank::getStockPrice() { return StockPrice; }
vector<int> Bank::getOwnStock() { return ownStock; }
vector<int> Bank::getUpDownLimit() { return upDownLimit; }

//--------------static varible initial--------------------
vector<float> Bank::StockPrice(numOfStocks, 0);
vector<float> Bank::minStockPrice(numOfStocks, 0), Bank::maxStockPrice(numOfStocks, 0); // 當回合的漲跌上下限
vector<int> Bank::upDownLimit(numOfStocks, 0); // 0:未達漲跌停板 1:漲停板 2:跌停板
clock_t Bank::lastTime = time(NULL);
clock_t Bank::nowTime = time(NULL);
int Bank::flowTimes = 0;