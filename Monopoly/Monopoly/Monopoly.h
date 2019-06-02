#pragma once
#define BOOST_FILESYSTEM_VERSION 3

#include <sstream>
#include <algorithm>
#include <direct.h>
#include <io.h>
#include "Player.h"
#include "Map.h"
#include "Bank.h"
#include "Console.h"

class Monopoly
{
public:
	//default constructor
	Monopoly() {}
	//執行動作
	void action(int);
	//開始遊戲
	void playGame(bool);
	//設定玩家人數
	bool setPlayerNum(void);
	//選擇角色
	bool chooseCharacter(int);
	//讀檔
	void loadInfo(string);
	//說明
	void printManual(void);
	//離開遊戲
	void exitGame(void);
	//擲骰子
	int dice(int);
	//玩家ESC選單
	bool menu(int);
	//儲存檔案
	void saveFile(void);
	//設置回合數
	bool setRound(void);
	//選擇道具
	bool chooseItem(int);
	//使用道具
	bool useItem(int);
	//遙控骰子
	bool controlDice(int);
	//路障
	bool loadBlock(void);
	//清除路障
	bool destroyBlock(void);
	//選擇檔案
	bool chooseFile(void);
	//畫面顯示
	void mapinitial();
	//勝負
	void win();
	//炸彈
	bool bomb();
	void positionChanged();
	void moneyChanged();
private:
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
	int throughRound = 1;
};