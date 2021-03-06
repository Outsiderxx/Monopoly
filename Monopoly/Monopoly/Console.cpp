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
	gotoxy(20, 5); cout << "[44m  [1;35;40m │ [33;42m�� �� �� �� �� �� �� �� [40m�� [42m�� �� [40m��     [42m�� �� [40m�� [42m�� �� �� �� [40m��   [42m�� �� �� �� [40m�� [42m�� �� �� �� �� [40m�� [35m│   [44m  [m" << '\n';
	gotoxy(20, 6); cout << "[44m  [1;35;40m │ [33;42m��               [40m�� [42m��   [40m��     [42m��   [40m�� [42m��       [40m�� [42m�� ��       [40m�� [42m��         [40m�� [35m│   [44m  [m" << '\n';
	gotoxy(20, 7); cout << "[44m  [1;35;40m │ [33m�� �� �� [42m��   [40m�� �� �� �� [42m��   [40m��     [42m��   [40m�� �� [42m��   [40m�� �� [42m��   [40m�� [42m��   [40m�� [42m��  [40m �� �� �� �� [35m│   [44m  [m" << '\n';
	gotoxy(20, 8); cout << "[44m  [1;35;40m ╰ ─ ─ [37;50m╮ [33;42m��   [40m�� [35m╭ ─ ╮ [33;42m��   �� [40m�� [42m�� ��   [40m��   [42m��   [40m��   [42m��   [40m�� �� �� �� [42m��   �� �� �� [40m�� [35m│   [44m  [m" << '\n';
	gotoxy(20, 9); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m��   [40m�� [35m│   │ [33m�� [42m��   [40m�� [42m��   [40m�� ��   [42m��   [40m��   [42m��   [40m��       [42m��         [40m�� [35m│   [44m  [m" << '\n';
	gotoxy(20, 10); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m��   [40m�� [35m│   ╰ ╮ [33;42m��   �� ��   [40m��     [42m��   [40m��   [42m��   [40m�� [42m�� �� [40m�� [42m��  [40m �� �� �� �� [35m│   [44m  [m" << '\n';
	gotoxy(20, 11); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m��   [40m�� [35m│     │ [33;42m��         [40m��   [42m�� ��   �� [40m�� [42m��   �� ��   [40m�� [42m��   �� �� �� [40m�� [35m│   [44m  [m" << '\n';
	gotoxy(20, 12); cout << "[44m  [40m      [1;35m[37;50m │ [33;42m��   [40m�� [35m│     │ [33m�� [42m�� [40m�� [42m�� [40m�� ��   [42m��       [40m�� �� [42m��       [40m�� [42m��         [40m�� [35m│   [44m  [m" << '\n';
	gotoxy(20, 13); cout << "[44m  [40m      [1;35m[37;50m │ [33m�� �� �� [35m│     ╰ ╮ [33m�� �� �� ��     �� �� �� �� ��   �� �� �� �� �� �� �� �� �� �� �� [35m│   [44m  [m" << '\n';
	gotoxy(20, 14); cout << "[44m  [40m      [1;35m ╰ ─ ─ ─ ╯       ╰ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ╯   [44m  [m" << '\n';
	gotoxy(20, 15); cout << "[44m                                                                             [1;35m  [m" << '\n';
	gotoxy(0, 17);	cout << "----------------------------------------------------------------------------------------------------------------------";
	gotoxy(2, 20);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		cout << "*         *       **       *      *       **                      ******         **        *         *     *    **";
	gotoxy(2, 21);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		cout << "**       **     *    *     **     *     *    *                   *      *      *    *      *         *     *    **";
	gotoxy(2, 22);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		cout << "* *     * *    *      *    * *    *    *      *                  *       *    *      *     *          *   *     **";
	gotoxy(2, 23);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		cout << "*  *   *  *   *        *   *  *   *   *        *                 **     *    *        *    *           * *      **";
	gotoxy(2, 24);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		cout << "*   * *   *    *      *    *   *  *    *      *                  * *****      *      *     *            *       **";
	gotoxy(2, 25);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		cout << "*    *    *     *    *     *    * *     *    *                   *             *    *      *            *   ";
	gotoxy(2, 26);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		cout << "*         *       **       *     **       **                     *               **        *******      *       **";
	//------------------------------------------------------------------------------------------------------------------------------------------------
	gotoxy(initialx, initialy);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);	cout << menu[0];
	gotoxy(initialx, initialy + 1);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	cout << menu[1];
	gotoxy(initialx, initialy + 2); cout << menu[2];
	gotoxy(initialx, initialy + 3);	cout << menu[3];
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

void mapbasic()			//---------------------------------------------遊戲畫面
{
	system("color 0f");
	system("cls");
	cout << "|                 |                 |                 |                 |" << endl;				//------------blank*16
	cout << "|                 |                 |                 |                 |" << endl;	//------------blank*11
	cout << "|-----------------------------------------------------------------------|" << endl;
	cout << "|目前遊戲者                                                   當前回合數|" << endl;
	cout << "|                                                                       |" << endl;
	cout << "|_______________________________________________________________________|" << endl;
	cout << "|";	for (int i = 0; i < 71; i++)	cout << "*";		cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|        ";	cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "| | || | ";	cout << "|" << endl;
	cout << "|_______________________________________________________________________|" << endl;
	for (int i = 0; i < 6; i++) {
		cout << "|        |                                                     |        |" << endl;	cout << "| | || | |                                                     | | || | |" << endl;
		if (i != 5)	cout << "|________|                                                     |________|" << endl;
	}
	cout << "|_______________________________________________________________________|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|        ";	cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "| | || | ";	cout << "|" << endl;
}

void up_gotoxy(int num, int x, int y, int blank, const vector<string> str)
{
	COORD pointup;
	pointup.X = x;  pointup.Y = y + num * blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//原位歸還
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	pointup.X = x;
	if (num == 0)
		pointup.Y = y + (str.size()-1) * blank;
	else
		pointup.Y = y + (num - 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//到位反白
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == 0)
		cout << str[str.size() - 1];
	else
		cout << str[num - 1];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(117, 30);
}
void down_gotoxy(int num, int x, int y, int blank, const vector<string> str)
{
	COORD point;
	point.X = x; point.Y = y + num * blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//原位歸還
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	point.X = x;
	if (num == str.size()-1)
		point.Y = y;
	else
		point.Y = y + (num + 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//到位反白
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == str.size() - 1)
		cout << str[0];
	else
		cout << str[num + 1];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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
		gotoxy(85, 13);		cout << "能力 : 學生方案 買房價格-10趴";
		gotoxy(85, 16);		cout << "副作用 : 窮包 錢少5000摳";
		gotoxy(117, 30);	break;
	}
	case 1:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(92, 2);	cout << " [1;34m◢███◣ [m";
		gotoxy(92, 3);	cout << " [1;34;43m◤  [;30;43m≡   [1;34;40m▌[m";
		gotoxy(92, 4);	cout << "[43m [30m─ ☉─ ☉-[37m";
		gotoxy(93, 5);	cout << " [43m    [30m皿   [40m  [37m";
		gotoxy(93, 6);	cout << "[30;43m◣  ︶ ◢[40m  [37m";
		gotoxy(93, 7);	cout << "[33m◢[47m  [1;31m爽  [;33m◣[37m";
		gotoxy(85, 10);		cout << "隸屬地區 : 鴻X集團";
		gotoxy(85, 13);		cout << "能力 : 老子有錢 錢多5000摳";
		gotoxy(85, 16);		cout << "副作用 : 錢太多 買房價格+10趴";
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
		gotoxy(85, 13);		cout << "能力 : 幸運S-->曹爽得 撿到500餒";
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

void firstPrint(int x_axis, int y_axis, int space , vector<string> text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	gotoxy(x_axis, y_axis);
	cout << text[0];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 1; i < text.size(); i++)
	{
		gotoxy(x_axis, y_axis + i*space);
		cout << text[i];
	}
	gotoxy(117, 30);
}

void hintClear()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 2; i < 30; i++)
	{
		gotoxy(73, i);	cout << "                                             ";
	}
	gotoxy(117, 30);
}

void lenPrint(string str)                    //---------------------------排版置中用
{
	switch (str.length())
	{
	case 4:
		cout << "  " << str << "  ";	break;
	case 6:
		cout << " " << str << " ";		break;
	case 8:
		cout << str;	break;
	}
}

void menuClear()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 17; i < 31; i++)
	{
		gotoxy(73, i);	cout << "                                             ";
	}
}

void pressEnter()
{
	gotoxy(117, 30);
	while (true)
	{
		if (_kbhit())
		{
			int input = _getch();
			if (input == 13)
			{
				break;
			}
		}
	}
}

void inputClear()
{
	gotoxy(108, 18);
	cout << "         ";
	gotoxy(108, 18);
}

void exitprint()
{
	PlaySound(TEXT("ROUNDABOUT.wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	system("cls");
	system("color 0f");
	gotoxy(22, 4); cout << "[47m      [40m◤                   [33m▁▂▁                               [37m◥[47m              [40m" << endl;
	gotoxy(22, 5); cout << "[47m    [40m◤               [30m[33;50m▂▅▇[43m        [40m▆▄[30;50m▂                         [37m◥[47m            [40m" << endl;
	gotoxy(22, 6); cout << "[47m  [40m◤              [30m[33;50m▂[43;50m▅            [30m/／╱  [33m[40;50m▆[30;50m▃                        [37m◥[47m          [40m" << endl;
	gotoxy(22, 7); cout << "◤              [33m◢[43m               [37;50m▇▆▅▄[33;50m▂[40;50m▄              [1m跳         [m◥[47m        [40m" << endl;
	gotoxy(22, 8); cout << "              [30m[33;50m◢[43m                [47m▊         [37;43m[33;50m▄[40;50m▄                         [37m◥[47m      [40m" << endl;
	gotoxy(22, 9); cout << "              [30;43m▎                 [47m            [37;43m[33;50m▄[40;50m▄         [1mGAME            [m◥[47m    [40m" << endl;
	gotoxy(22, 10); cout << "              [43m [30m/               [33;47m▋             [37;43m▍[33;40m▊                          [37m◥[47m  [40m" << endl;
	gotoxy(22, 11); cout << "            [30;43m▊[33m[30;50m∥              [33;47m▊     [30m╱  〝[37m[30;50m︷﹏ [37;43m▎[33;40m▋        [1m沒                 [m◥" << endl;
	gotoxy(22, 12); cout << "             [43m [30m｜    ▏       ▁[47m‵︸′       ▁▂[43m  [33;40m▍[37m                            " << endl;
	gotoxy(22, 13); cout << "            [30;43m▎[33m[30;50m∥    ▏     [33;40m▄[37;50m▅▃[30;47m▆[37;50m︻     [40m◤▃▅[43m▏[33;40m▋[37m▁▂[30;50m▁ [1;33m有[m                   " << endl;
	gotoxy(22, 14); cout << "      ▁▂▃[43m▄▄▃▂[30m▏       [47;50m▅[37;40m▂▆[47m       [40m▅▂[30;47m▅[37;43m▎ [33;47m▎   [30m[40;50m◢[37m                      " << endl;
	gotoxy(22, 15); cout << "     [47;50m●       [30m[37;50m︸[30;50m︿ [37;43m▍       [33;46m▎[36;47m▏[37mψ            [36m▉[37;43m▎ [33;47m▍ [30m◢[40m   [1;33m妹[m                   " << endl;
	gotoxy(22, 16); cout << "     [30m[47;50m▆[37;50m▃       [30m(〝[37;43m▍       [46m  [47m    [30m,~︷﹏▁__  [37;46m▎[43m▍[33;47m▉[30m◢[37;40m                          " << endl;
	gotoxy(22, 17); cout << "       [30m[47;50m▇[33;50m▅[30;50m▃▁  ︸[37;43m▍      [33;46m▎[36;47m▍ [31m◢[41m[47;50m▆▅▄▅▆[41m [47m [37;46m▍[36;47m[43;50m▏[33;40m▊       [1m妹[m                   " << endl;
	gotoxy(22, 18); cout << "          [30;43m◣[33;40m[30;50m▄ [47m[33;50m▇▆[40m[43;50m▎      [37;46m▍[36;47m▏[37;41m▍          [31;47m▉  [46m [37;43m▍[33;40m▋[37m                            " << endl;
	gotoxy(22, 19); cout << "            [30;43m◣[33;40m[30;50m▄[43m \ [33;50m∥      [47m  [46m [36;47m▎[37;41m▎          [31;47m▋ [37;46m▋[43m▏[33;40m▍       [1m                   [;30;47m◤[37;40m" << endl;
	gotoxy(22, 20); cout << "              [30;43m▊  ╲ ▏ [33m[37;50m▄[47m [46m▉[36;47m▉[37;40m▉[41m◣▁   ▁▂[31;47m[37;50m◤ [43m[36;50m◤[33m[30;50m▄[40m                          [47m◤  [37;40m" << endl;
	gotoxy(22, 21); cout << "               [30;43m▏   \  [33m[37;50m︼[33;47m▃[37;50m▂[46m [36;47m▎ [30m╲_  _,~︸〞 [37;43m◤[30m▃[40m                          [47m◤    [37;40m" << endl;
	gotoxy(22, 22); cout << "               [43m     [33m[30;50mλ   \ [33;47m[46;50m◣[36;47m▏     [37;40m▇[47m [33m▁▄[30;40;50m▆                            [47m◤      [37;40m" << endl;
	gotoxy(22, 23); cout << "[30;47m◥[40m            [43m▍     [32m▍  [33m[32;50m▇▆[31;47m▁   [37m[33;50m▄▆[40m◤[43m  [40m▎                          [30;47m◤        [37;40m" << endl;
	gotoxy(22, 24); cout << "[47m  [30m◥[40m         [43m▋   [33m[32;50m▄[42m  [43m◣ [42;50m◢[41m▊     [31m[42;50m��   [32;40m◣[30;43m▎[40m                          [47m◤          [37;40m" << endl;
	gotoxy(22, 25); cout << "[47m    [30m◥[40m       [43m▍ [33m[32;50m▂[42;50m▆   [43m▋◥[47m▋[37;41m▇▆▇[42m    [32m[33;50m◢[43m [40m[30;50m◣  [33m#NYKD54 (MAN_Chat)[30m  [47m◤            [37;40m" << endl;
	gotoxy(22, 26); cout << "[47m      [30m◥[40m    [32m[43;50m▁▃[42;50m▆      [43m▎[33;42m▋[32;47m◣    [37;42m▋   [32;43m▍ [33;40m▋    ig : k7_00626   [30;47m◤              [37;40m" << endl;
	gotoxy(90, 28);	cout << "To be continued---->";
	gotoxy(117, 30);
	Sleep(10000);
}