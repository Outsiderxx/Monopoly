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
	void setPlayerNum(void);
	//��ܨ���
	void chooseCharacter(int);
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
	//���o�a�ϦW��
	string getMapName(void);
	//���o��e���a
	int getTurn(void);
	//���o�g�L�^�X��
	int getThroughRound(void);
	//�]�m�^�X��
	void setRound(void);
	//���o���a�H��
	int getPlayerNum(void);
	//��ܹD��
	bool chooseItem(int);
	//�ϥιD��
	void useItem(int);
	//������l
	bool controlDice(int);
	//����
	void loadBlock(void);
	//�M������
	void destroyBlock(void);
	//����ɮ�
	void chooseFile(void);
	//�e�����
	void mapintitial();
private:
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
	int throughRound = 1;
};