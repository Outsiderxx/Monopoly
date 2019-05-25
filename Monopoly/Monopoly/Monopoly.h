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
	//����ʧ@
	void action(int);
	//�}�l�C��
	void playGame(bool);
	//�]�w���a�H��
	void setPlayerNum(void);
	//��ܨ���
	void chooseCharacter(int);
	//Ū��
	void loadInfo(string,bool);
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
	//���o��e�ѤU�^�X��
	int getRound(void);
	//�]�m�^�X��
	void setRound(void);
	//���o���a�H��
	int getPlayerNum(void);
	//��ܹD��
	void chooseItem(void);
	//�ϥιD��
	void useItem(int);
	//������l
	void controlDice(int);
	//����
	void loadBlock(void);
	//�M������
	void destroyBlock(void);
	//����ɮ�
	void chooseFile(void);
private:
	vector<Player> player;
	vector<Map> map;
	string mapName;
	int turn;
	int round;
	bool gameMode;
};