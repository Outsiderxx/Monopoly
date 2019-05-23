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
	//����ʧ@
	void action(int);
	//�}�l�C��
	void playGame(bool);
	//�]�w���a�H��
	bool setPlayerNum(void);
	//��ܨ���
	bool chooseCharacter(int);
	//Ū��
	void loadInfo(string,bool);
	//����
	void printManual(void);
	//���}�C��
	void exitGame(void);
	//�Y��l
	int dice(int);
	//���aESC���
	int menu(void);
	//�x�s�ɮ�
	void saveFile(void);
	//���o�a�ϦW��
	string getMapName(void);
	//���o��e���a
	int getTurn(void);
	//���o��e�ѤU�^�X��
	int getRound(void);
	//�]�m�^�X��
	bool setRound(void);
	//���o���a�H��
	int getPlayerNum(void);
private:
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
};