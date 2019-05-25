#include "Console.h"

#define initialx 54
#define initialy 21

const string menu[4] = { "開新遊戲", "羅德大法" ,"規則說明" ,"  離開  " };			//選單const全域
const string playernum[4] = { "邊緣單行" ,"雙飛翱翔","三人成虎","四人混戰" };		//人數const全域
const string character[4] = { "女高中生","操盤奸商","荒島傻蛋"," 路人69" };	//角色const全域

void gotoxy(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void menuprint()		//------------------------------------------------------------------------進板畫面
{
	PlaySound(TEXT("Dance The Night Away (Instrumental).wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);				//background music
	system("mode con cols=118 lines=31");			//set console size
	for (int i = 0; i < 18; i++) { gotoxy(8, 0 + i);	cout << "|"; }
	for (int i = 0; i < 18; i++) { gotoxy(110, 0 + i);	cout << "|"; }
	system("color 0e");
	gotoxy(20, 2); cout << "[44m                                                                             [1;35m  [m" << '\n';
	gotoxy(20, 3); cout << "[44m  [40m                                                                           [1;35;44m  [m" << '\n';
	gotoxy(20, 4); cout << "[44m  [1;35;40m ╭ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ╮   [44m  [m" << '\n';
	gotoxy(20, 5); cout << "[44m  [1;35;40m │ [33;42m╔ ═ ═ ═ ═ ═ ═ ═ [40m╗ [42m╔ ═ [40m╗     [42m╔ ═ [40m╗ [42m╔ ═ ═ ═ [40m╗   [42m╔ ═ ═ ═ [40m╗ [42m╔ ═ ═ ═ ═ [40m╗ [35m│   [44m  [m" << '\n';
	gotoxy(20, 6); cout << "[44m  [1;35;40m │ [33;42m║               [40m║ [42m║   [40m║     [42m║   [40m║ [42m║       [40m║ [42m╔ ╝       [40m║ [42m║         [40m║ [35m│   [44m  [m" << '\n';
	gotoxy(20, 7); cout << "[44m  [1;35;40m │ [33m╚ ═ ═ [42m╗   [40m╔ ═ ═ ╝ [42m║   [40m║     [42m║   [40m║ ╚ [42m╗   [40m╔ ╝ [42m║   [40m╔ [42m╗   [40m║ [42m║  [40m ╔ ═ ═ ╝ [35m│   [44m  [m" << '\n';
	gotoxy(20, 8); cout << "[44m  [1;35;40m ╰ ─ ─ [37;50m╮ [33;42m║   [40m║ [35m╭ ─ ╮ [33;42m║   ╚ [40m╗ [42m╔ ╝   [40m║   [42m║   [40m║   [42m║   [40m║ ╚ ═ ╝ [42m║   ╚ ═ ═ [40m╗ [35m│   [44m  [m" << '\n';
	gotoxy(20, 9); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m║   [40m║ [35m│   │ [33m╚ [42m╗   [40m║ [42m║   [40m╔ ╝   [42m║   [40m║   [42m║   [40m║       [42m║         [40m║ [35m│   [44m  [m" << '\n';
	gotoxy(20, 10); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m║   [40m║ [35m│   ╰ ╮ [33;42m║   ╚ ╝   [40m║     [42m║   [40m║   [42m║   [40m║ [42m╔ ═ [40m╗ [42m║  [40m ╔ ═ ═ ╝ [35m│   [44m  [m" << '\n';
	gotoxy(20, 11); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m║   [40m║ [35m│     │ [33;42m║         [40m║   [42m╔ ╝   ╚ [40m╗ [42m║   ╚ ╝   [40m║ [42m║   ╚ ═ ═ [40m╗ [35m│   [44m  [m" << '\n';
	gotoxy(20, 12); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m║   [40m║ [35m│     │ [33m╚ [42m╗ [40m╔ [42m╗ [40m╔ ╝   [42m║       [40m║ ╚ [42m╗       [40m║ [42m║         [40m║ [35m│   [44m  [m" << '\n';
	gotoxy(20, 13); cout << "[44m  [40m      [1;35m[37;50m │ [33m╚ ═ ╝ [35m│     ╰ ╮ [33m╚ ╝ ╚ ╝     ╚ ═ ═ ═ ╝   ╚ ═ ═ ═ ╝ ╚ ═ ═ ═ ═ ╝ [35m│   [44m  [m" << '\n';
	gotoxy(20, 14); cout << "[44m  [40m      [1;35m ╰ ─ ─ ─ ╯       ╰ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ╯   [44m  [m" << '\n';
	gotoxy(20, 15); cout << "[44m                                                                             [1;35m  [m" << '\n';
	gotoxy(0,17);	cout << "----------------------------------------------------------------------------------------------------------------------";
	gotoxy(2, 20);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		cout << "*         *       **       *      *       **                      ******         **        *         *     *    **";
	gotoxy(2, 21);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		cout << "**       **     *    *     **     *     *    *                   *      *      *    *      *         *     *    **";
	gotoxy(2, 22);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		cout << "* *     * *    *      *    * *    *    *      *                  *       *    *      *     *          *   *     **";
	gotoxy(2, 23);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		cout << "*  *   *  *   *        *   *  *   *   *        *                 **     *    *        *    *           * *      **";
	gotoxy(2, 24);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		cout << "*   * *   *    *      *    *   *  *    *      *                  * *****      *      *     *            *       **";
	gotoxy(2, 25);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		cout << "*    *    *     *    *     *    * *     *    *                   *             *    *      *            *   ";
	gotoxy(2, 26);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		cout << "*         *       **       *     **       **                     *               **        *******      *       **";
	//------------------------------------------------------------------------------------------------------------------------------------------------
	gotoxy(initialx, initialy);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);	cout << menu[0];
	gotoxy(initialx, initialy+1);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	cout << menu[1];
	gotoxy(initialx, initialy+2); cout << menu[2];
	gotoxy(initialx, initialy+3);	cout << menu[3];
	gotoxy(117, 30);
}
void selectPlayer()		//-----------------------------------------------選擇人數
{
	gotoxy(initialx, initialy);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << playernum[0];
	gotoxy(initialx, initialy + 1);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	cout << playernum[1];
	gotoxy(initialx, initialy + 2);		cout << playernum[2];
	gotoxy(initialx, initialy + 3);		cout << playernum[3];
	gotoxy(117, 30);
}
void characterprint(int num)		//--------------------------------------------選角
{
	PlaySound(TEXT("GOLDEN LEGEND.wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);		//background music
	const int row = 29, column = 116;
	//-------------------外框-----------------------------------
	gotoxy(0, 0);		cout << "┌";
	for (int i = 1; i < column; i++)	cout << "─";		cout << "┐";
	for (int i = 1; i < row; i++)
	{
		gotoxy(0, i);	cout << "│";
		gotoxy(column, i);	cout << "│";
	}
	gotoxy(0, row);		cout << "└";
	for (int i = 1; i < column; i++)	cout << "─";		cout << "┘";
	gotoxy(10, 2);	cout << "------Select your character------";
	gotoxy(47, 2);	cout << "------Character Preview------";
	gotoxy(5, 26);	cout << "Press ↑↓ 選擇要預覽的角色";
	gotoxy(35, 26);	cout << "Press Enter 預覽角色/進入遊戲";
	gotoxy(67, 26);		cout << "Press 'q' 選擇其他角色";
	gotoxy(92, 26);		cout << "Press Esc 回到主畫面";
	gotoxy(57, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "女高中生";	
	gotoxy(57, 10);		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); cout << "操盤奸商";	
	gotoxy(57, 13);		cout << "荒島傻蛋";	gotoxy(57, 16);		cout << " 路人69";
	//----------------------------------------------------------------------------------
	switch (num)
	{
	case 0:	
	{
		gotoxy(17, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p : ";	gotoxy(117, 30);	 break;
	}
	case 1:
	{
		gotoxy(17, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p : ";
		gotoxy(17, 10);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p : ";	gotoxy(117, 30);	break;
	}
	case 2:
	{
		gotoxy(17, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p : ";
		gotoxy(17, 10);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p : ";
		gotoxy(17, 13);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	cout << "3p : ";	gotoxy(117, 30);	break;
	}
	case 3:
	{
		gotoxy(17, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	cout << "1p : ";
		gotoxy(17, 10);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);	cout << "2p : ";
		gotoxy(17, 13);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 55);	cout << "3p : ";
		gotoxy(17, 16);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);	cout << "4p : ";	gotoxy(117, 30);	break;
	}
	}
}
void initialgame()			//---------------------------------------------遊戲畫面
{
	cout << "|1                |2                |3                |4                |" << endl;				//------------blank*16
	cout << "|$50000           |$50000           |$50000           |$50000           |" << endl;	//------------blank*11
	cout << "|-----------------------------------------------------------------------|" << endl;
	cout << "|目前遊戲者                                                   當前回合數|" << endl;
	cout << "|                                                                     n |" << endl;
	cout << "|_______________________________________________________________________|" << endl;
	cout << "|";	for (int i = 0; i < 71; i++)	cout << "*";		cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|  起點  ";	cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|1|2||3|4";	cout << "|"<< endl; 
	cout << "|_______________________________________________________________________|" << endl;
	for (int i = 0; i < 6; i++) {
		cout << "|  起點  |                                                     |  起點  |" << endl;	cout << "|1|2||3|4|                                                     |1|2||3|4|" << endl; 
		if (i != 5)	cout << "|________|                                                     |________|"<< endl; }
	cout << "|_______________________________________________________________________|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|  起點  ";	cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|1|2||3|4";	cout << "|" << endl;
}

void up_gotoxy(int num, int x, int y, int blank, const string str[4])
{
	COORD pointup;
	pointup.X = x;  pointup.Y = y + num*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//原位歸還
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	pointup.X = x;
	if (num == 0)
		pointup.Y = y + 3*blank;
	else
		pointup.Y = y + (num - 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//到位反白
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == 0)
		cout << str[3];
	else
		cout << str[num - 1];
	gotoxy(117, 30);
}
void down_gotoxy(int num, int x, int y, int blank, const string str[4])
{
	COORD point;
	point.X = x; point.Y = y + num*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//原位歸還
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	point.X = x;
	if (num == 3)
		point.Y = y;
	else
		point.Y = y + (num + 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//到位反白
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == 3)
		cout << str[0];
	else
		cout << str[num + 1];
	gotoxy(117, 30);
}
void previewCharacter(int num)
{
	switch (num)
	{
	case 0:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(90, 2);	cout << "  [1;33m [;34m◢███◣[37m";
		gotoxy(93, 3);	cout << "    [34;43m█◤◤◥█[37;40m";
		gotoxy(89, 4);	cout << "    [34;43m▉[30m╴   ╴ [34m█[37;40m";
		gotoxy(88, 5);	cout << "[1;36m＼   [;34;43m▉  [31m▼  [34m█[37;40m";
		gotoxy(88, 6);	cout << "  [1;36m＼ [;34;47m◤[37m[45;50m▌[1;37;45m／[;34m[37;47;50m█[34m◥[37;40m";
		gotoxy(89, 7);	cout << "    [34m█[37m[45;50m▌[1m︳ [47m [;34m█[37m";
		gotoxy(85, 10);		cout << "隸屬地區 : 北科高中";
		gotoxy(85, 13);		cout << "能力 : 可憐窮包-->過路費8折";
		gotoxy(85, 16);		cout << "副作用 : 機率性因早八疲勞過度";
		gotoxy(94, 17);		cout << "休息一回";	
		gotoxy(117, 30);	break;
	}
	case 1:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(92, 2);	cout << " [1;34m◢███◣ [m";
		gotoxy(92, 3);	cout << " [1;34;43m◤  [;30;43m≡   [1;34;40m▌[m";
		gotoxy(92, 4);	cout << "[43m [30m─ ⊙─ ⊙-[37m";
		gotoxy(93, 5);	cout << " [43m    [30m皿   [40m  [37m";
		gotoxy(93, 6);	cout << "[30;43m◣  ︶ ◢[40m  [37m";
		gotoxy(93, 7);	cout << "[33m◢[47m  [1;31m爽  [;33m◣[37m";
		gotoxy(85, 10);		cout << "隸屬地區 : 鴻X集團";
		gotoxy(85, 13);		cout << "能力 : 老子有錢-->初始金額+1w";
		gotoxy(85, 16);		cout << "副作用 : 錢太多,過路費不小心";
		gotoxy(94, 17);		cout << "多給他人一張小朋友";
		gotoxy(117, 30); break;
	}
	case 2:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(94, 2);	cout << "[1;33m (o)(o)    ???[m";
		gotoxy(93, 3);	cout << "[1;33mw*      *w[m";
		gotoxy(92, 4);	cout << "[1;33mW  -====-  W[m";
		gotoxy(93, 5);	cout << "[1;33m*w      w*[m";
		gotoxy(92, 6);	cout << "[1;33mw**********w[m";
		gotoxy(91, 7);	cout << "[1;33mW            W[m";
		gotoxy(85, 10);		cout << "隸屬地區 : 真●天龍";
		gotoxy(85, 13);		cout << "能力 : 幸運S-->曹爽得 撿到100餒";
		gotoxy(85, 16);		cout << "副作用 : 智商E- 內褲被偷還???";
		gotoxy(94, 17);		cout << "機率掉錢............";
		gotoxy(94, 18);		cout << "....................嗎";
		gotoxy(117, 30); break;
	}
	case 3:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		gotoxy(90, 2);	cout << "*";	gotoxy(90, 3);	cout << "*";
		gotoxy(90, 4);	cout << "*";	gotoxy(90, 5);	cout << "******";
		gotoxy(90, 6);	cout << "*    *";	gotoxy(90, 7);	cout << "******";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(92, 2);	cout << "******";	gotoxy(92, 3);	cout << "*    *";
		gotoxy(92, 4);	cout << "******";	gotoxy(97, 5);	cout << "*";
		gotoxy(97, 6);	cout << "*";	gotoxy(97, 7);	cout << "*";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(98, 5);	cout << "******   側著看";		gotoxy(99, 3);	cout << "*     *";	gotoxy(100, 4);	cout << "*   *";
		gotoxy(100, 6);	cout << "*   *  別看歪阿";		gotoxy(99, 7);	cout << "*     *";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(85, 10);		cout << "隸屬地區 : 誰來約會";
		gotoxy(85, 13);		cout << "能力 : 每回合有機率高雄發大財";
		gotoxy(85, 16);		cout << "副作用 : 機率出現後才發現....";
		gotoxy(94, 17);		cout << "....................";
		gotoxy(94, 18);		cout << "欸........好像沒有用";
		gotoxy(117, 30);	break;
	}
	}
}
void characterClear()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 2; i < 21; i++)
	{
		gotoxy(84, i);	cout << "                               ";
	}
	gotoxy(117, 30);
}
