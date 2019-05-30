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
void menuprint();						//主畫面 & 選單
void mapbasic();					//大富翁底圖
void characterprint(int);			//選角畫面
void selectPlayer();					//選人數
void previewCharacter(int num);			//角色預覽
void characterClear();						//刷新預覽
void up_gotoxy(int num, int, int, int,const vector<string>);			//up execute
void down_gotoxy(int num, int, int, int, const vector<string>);		//down execute
void firstPrint(int, int, int, vector<string>);