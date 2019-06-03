#include "map.h"
#include"Monopoly.h"

Map::Map()
{
	owner = -1;
	level = 0;
	barrier = 0;
	cost.resize(4);
}

//return true if need dice again
//other situation return false
int Map::areaControl(vector<Player> &playerList, int currentPlayer)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(73, 17);
	cout << "目前地點是: " << name << " ";
	if (type == 1)	//nomral area
	{
		cout << "等級: " << level << " 地主: ";
		if (owner == -1)
		{
			cout << "無";
			gotoxy(75, 19);
			int newPrice = price;
			if (playerList[currentPlayer].character == 0)
				newPrice *= 0.9;
			else if (playerList[currentPlayer].character == 1)
				newPrice *= 1.1;
			cout << "價格: " << newPrice;
			int toBuy = 0;
			string tmp[] = { "是","否" };
			vector<string> choose(tmp, tmp + 2);
			gotoxy(90, 19);
			cout << "是否購買";
			firstPrint(100,19,2,choose);
			while (true)
			{
				if (_kbhit())
				{
					int input = _getch();
					if (input == 224)
					{
						down_gotoxy(toBuy, 100, 19, 2, choose);
						toBuy = 1 - toBuy;
					}
					else if (input == 13)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						if (toBuy == 0)
						{
							if (playerList[currentPlayer].money >= newPrice)
							{
								playerList[currentPlayer].money -= newPrice;
								owner = currentPlayer;
								gotoxy(85, 25);
								cout << "金錢減少 " << newPrice;
							}
							else
							{
								gotoxy(85, 25);
								cout << "錢不夠QQ";
							}
						}
						break;
					}
				}
			}
		}
		else if (owner == currentPlayer)
		{
			cout << "玩家 " << owner + 1;
			gotoxy(85, 23);
			cout << name;
			if (level < 3)
			{
				level++;
				cout << "升到 " << level<<" 級";
			}
			else
			{
				cout << "無法再升級";
			}
		}
		else
		{
			cout << "玩家 " << owner + 1;
			if (playerList[currentPlayer].skip == 0)
			{
				gotoxy(80, 23);
				cout << "乖乖付錢啦 付給玩家" << owner + 1 << " " << cost[level]<<"摳";
				playerList[currentPlayer].money -= cost[level];
				
				if (playerList[currentPlayer].money < 0)
				{
					gotoxy(85, 27);
					cout << "玩家 " << currentPlayer + 1 << " 破產啦QQ";
					playerList[currentPlayer].state = 0;
				}
				playerList[owner].money += cost[level];
			}
			else
			{
				playerList[currentPlayer].skip--;
				gotoxy(80, 23);
				cout << "算你好運 免付過路費次數減一";
			}
		}
	}
	else if (type == -1)			//fate area
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(75, 19);
		cout << "按ENTER查看本次命運";
		pressEnter();
		int randomFateCard, step;
		randomFateCard = rand() % 5;	//if we have 5 fate options
		gotoxy(83, 23);
		switch (randomFateCard)
		{
		case 0:
			step = rand() % 3 + 1;
			cout << "前進 " << step << " 步";
			return step;
		case 1:
			step = rand() % 3 + 1;
			cout << "後退 " << step << " 步";
			return -step;
		case 2:
			cout << "暫停行動一回合";
			playerList[currentPlayer].stop++;
			break;
		case 3:
			cout << "免付過路費次數加一";
			playerList[currentPlayer].skip++;
			break;
		case 4:
			cout << "獲得再骰一次的機會";
			return 0;
		}
	}
	else if (type == -2)			//chance area
	{
		(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(75, 19);
		cout << "按ENTER查看本次機會";
		pressEnter();
		int randomChanceCard;
		randomChanceCard = rand() % 7;
		gotoxy(85, 23);
		switch (randomChanceCard)
		{
		case 0:
			cout << "撿到1000摳";
			playerList[currentPlayer].money += 1000;
			break;
		case 1:
			cout << "弄丟1000摳";
			playerList[currentPlayer].money -= 1000;
			if (playerList[currentPlayer].money < 0)
			{
				gotoxy(85, 27);
				cout << "玩家 " << currentPlayer + 1 << " 破產啦QQ";
				playerList[currentPlayer].state = 0;
			}
			break;
		case 2:
			cout << "獲得遙控骰子 * 1";
			playerList[currentPlayer].item[0]++;
			break;
		case 3:
			cout << "獲得久逃 * 1";
			playerList[currentPlayer].item[1]++;
			break;
		case 4:
			cout << "獲得碎石器 * 1";
			playerList[currentPlayer].item[2]++;
			break;
		case 5:
			cout << "獲得炸彈 * 1";
			playerList[currentPlayer].item[3]++;
			break;
		case 6:
			cout << "向其他人收取500摳";
			for (int loop = 0; loop < playerList.size(); loop++)
			{
				if (loop == currentPlayer)
				{
					playerList[loop].money += 500 * (playerList.size()-1);
				}
				else
				{
					playerList[loop].money -= 500;
					if (playerList[loop].money < 0)
					{
						gotoxy(85, 25 + 2 * loop);
						cout << "玩家 " << currentPlayer << " 破產啦QQ";
						playerList[loop].state = 0;
					}
				}
			}
			break;
		}
	}
	return 4;
}