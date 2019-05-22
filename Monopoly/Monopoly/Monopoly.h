#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "Map.h"
#include "Bank.h"

class Monopoly
{
public:
	//default constructor
	Monopoly() {}
	//執行動作
	void action(int);
	//開始遊戲
	void playGame(void);
	//設定角色玩家人數回合數
	void setup(void);
	//讀檔
	void loadInfo(string);
	//說明
	void printManual(void);
	//離開遊戲
	void exitGame(void);
	//擲骰子
	int dice(int);
	//玩家ESC選單
	int menu(void);
	//儲存檔案
	void saveFile(void);
	//取得地圖名稱
	string getMapName(void);
	//取得當前玩家
	int getTurn(void);
	//取得當前剩下回合數
	int getRound(void);
private:
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
};