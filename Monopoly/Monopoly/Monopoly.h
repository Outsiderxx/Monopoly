#pragma once
#include <sstream>
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
	void setPlayerNum(void);
	//選擇角色
	void chooseCharacter(int);
	//讀檔
	void loadInfo(string,bool);
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
	//取得地圖名稱
	string getMapName(void);
	//取得當前玩家
	int getTurn(void);
	//取得當前剩下回合數
	int getRound(void);
	//設置回合數
	void setRound(void);
	//取得玩家人數
	int getPlayerNum(void);
	//選擇道具
	void chooseItem(void);
	//使用道具
	void useItem(int);
	//遙控骰子
	void controlDice(int);
	//路障
	void loadBlock(void);
	//清除路障
	void destroyBlock(void);
	//選擇檔案
	void chooseFile(void);
private:
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
	bool gameMode;
};