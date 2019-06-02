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
	bool menu(int);
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
	void mapinitial();
	//�ӭt
	void win();
	//���u
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