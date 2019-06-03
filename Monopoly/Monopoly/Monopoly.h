#pragma once
#define BOOST_FILESYSTEM_VERSION 3

#include <sstream>
#include <algorithm>
#include <direct.h>
#include <io.h>
#include <cstdlib>
#include <time.h>
#include "Player.h"
#include "Map.h"
#include "Console.h"

class Monopoly
{
public:
	//default constructor
	Monopoly();
	//����ʧ@
	void action(int);
	//�}�l�C��
	void playGame(bool);
	//�]�w���a�H��
	bool setPlayerNum(void);
	//��ܨ���
	bool chooseCharacter(int);
	//Ū��
	void loadInfo(string);
	//����
	void printManual(void);
	//���}�C��
	void exitGame(void);
	//�Y��l
	int dice(int);
	//���aESC���
	int menu(int);
	//�x�s�ɮ�
	void saveFile(void);
	//�]�m�^�X��
	bool setRound(void);
	//��ܹD��
	bool chooseItem(int);
	//�ϥιD��
	bool useItem(int);
	//������l
	bool controlDice(int);
	//����
	bool loadBlock(void);
	//�M������
	bool destroyBlock(void);
	//����ɮ�
	bool chooseFile(void);
	//�e�����
	void mapinitial(void);
	//�ӭt
	void win();
	//���u
	bool bomb();
	void positionChanged();
	void moneyChanged();
	void positionClear(int);
	void stockPriceFlow();
	void atm(Player&);
	void stock(Player&);
private:
	vector<int> stockPrice;
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
	int throughRound = 1;
};