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
	for (int i = 0; i < numOfStocks; ++i)
	{
		minStockPrice[i] = StockPrice[i] * 0.88;
		maxStockPrice[i] = StockPrice[i] * 1.12;
	}
	lastTime = time(NULL);
	nowTime = time(NULL);
	flowTimes = 0;
}
Bank::~Bank() {}

void Bank::setDeposit(int dep) { deposit = dep; }
void Bank::setLoan_times(int times) { loan_times = times; }
void Bank::setInterest(int inter) { interest = inter; }
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
			range = 0.95 + (float(rand()) / RAND_MAX) * 0.1; //�C���i�ʴT�׬����t5%(��ѻ� * (0.95~1.05))
			if (StockPrice[i] * range >= maxStockPrice[i]) //����
			{
				StockPrice[i] = maxStockPrice[i];
				upDownLimit[i] = 1;
			}
			else if (StockPrice[i] * range <= minStockPrice[i]) // �^��
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
		if (flowTimes == 6) // �C�i�ʤ�����s�����з�
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
void Bank::saveMoney(int dep) // �s��
{
	if (dep > 0/*�{�����B*/)
	{
		//�s�ڵL��
	}
	else
	{
		deposit += dep;
		//�{�����B -= dep;
	}
}
void Bank::withdrawMoney(int wd) // ����
{
	if (wd > deposit)
	{
		//���ڵL��
	}
	else
	{
		deposit -= wd;
		//�{�����B += wd;
	}
}
int Bank::getDeposit() { return deposit; }
int Bank::getLoan_times() { return loan_times; }
int Bank::getInterest() { return interest; }
vector<float> Bank::getStockPrice() { return StockPrice; }
vector<int> Bank::getOwnStock() { return ownStock; }
vector<int> Bank::getUpDownLimit() { return upDownLimit; }
