#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include <vector>
#include <mmsystem.h>		//for music
#pragma comment(lib, "winmm.lib")	//for music
using namespace std;

void gotoxy(int x, int y);				//initial positin execute
void menuprint();						//�D�e�� & ���
void mapbasic();					//�j�I�Ω���
void characterprint(int);			//�﨤�e��
void selectPlayer();					//��H��
void previewCharacter(int num);			//����w��
void characterClear();						//��s�w��
void up_gotoxy(int num, int, int, int,const vector<string>);			//up execute
void down_gotoxy(int num, int, int, int, const vector<string>);		//down execute
void firstPrint(int, int, int, vector<string>);