#include "Console.h"

#define initialx 54
#define initialy 21

const string menu[4] = { "¶}·s¹CÀ¸", "Ã¹¼w¤jªk" ,"³W«h»¡©ú" ,"  Â÷¶}  " };			//¿ï³æconst¥þ°ì
const string playernum[4] = { "Ãä½t³æ¦æ" ,"Âù­¸¿¬µ¾","¤T¤H¦¨ªê","¥|¤H²V¾Ô" };		//¤H¼Æconst¥þ°ì
const string character[4] = { "¤k°ª¤¤¥Í","¾Þ½L¦l°Ó","¯î®q¶Ì³J"," ¸ô¤H69" };	//¨¤¦âconst¥þ°ì

void gotoxy(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void menuprint()		//------------------------------------------------------------------------¶iªOµe­±
{
	PlaySound(TEXT("Dance The Night Away (Instrumental).wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);				//background music
	system("mode con cols=118 lines=31");			//set console size
	for (int i = 0; i < 18; i++) { gotoxy(8, 0 + i);	cout << "|"; }
	for (int i = 0; i < 18; i++) { gotoxy(110, 0 + i);	cout << "|"; }
	system("color 0e");
	gotoxy(20, 2); cout << "[44m                                                                             [1;35m  [m" << '\n';
	gotoxy(20, 3); cout << "[44m  [40m                                                                           [1;35;44m  [m" << '\n';
	gotoxy(20, 4); cout << "[44m  [1;35;40m ¢~ ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢¡   [44m  [m" << '\n';
	gotoxy(20, 5); cout << "[44m  [1;35;40m ¢x [33;42mùÝ ùù ùù ùù ùù ùù ùù ùù [40mùß [42mùÝ ùù [40mùß     [42mùÝ ùù [40mùß [42mùÝ ùù ùù ùù [40mùß   [42mùÝ ùù ùù ùù [40mùß [42mùÝ ùù ùù ùù ùù [40mùß [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 6); cout << "[44m  [1;35;40m ¢x [33;42mùø               [40mùø [42mùø   [40mùø     [42mùø   [40mùø [42mùø       [40mùø [42mùÝ ùå       [40mùø [42mùø         [40mùø [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 7); cout << "[44m  [1;35;40m ¢x [33mùã ùù ùù [42mùß   [40mùÝ ùù ùù ùå [42mùø   [40mùø     [42mùø   [40mùø ùã [42mùß   [40mùÝ ùå [42mùø   [40mùÝ [42mùß   [40mùø [42mùø  [40m ùÝ ùù ùù ùå [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 8); cout << "[44m  [1;35;40m ¢¢ ¢w ¢w [37;50m¢¡ [33;42mùø   [40mùø [35m¢~ ¢w ¢¡ [33;42mùø   ùã [40mùß [42mùÝ ùå   [40mùø   [42mùø   [40mùø   [42mùø   [40mùø ùã ùù ùå [42mùø   ùã ùù ùù [40mùß [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 9); cout << "[44m  [40m      [1;35m[37;50m ¢x [33;42mùø   [40mùø [35m¢x   ¢x [33mùã [42mùß   [40mùø [42mùø   [40mùÝ ùå   [42mùø   [40mùø   [42mùø   [40mùø       [42mùø         [40mùø [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 10); cout << "[44m  [40m      [1;35m[37;50m ¢x [33;42mùø   [40mùø [35m¢x   ¢¢ ¢¡ [33;42mùø   ùã ùå   [40mùø     [42mùø   [40mùø   [42mùø   [40mùø [42mùÝ ùù [40mùß [42mùø  [40m ùÝ ùù ùù ùå [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 11); cout << "[44m  [40m      [1;35m[37;50m ¢x [33;42mùø   [40mùø [35m¢x     ¢x [33;42mùø         [40mùø   [42mùÝ ùå   ùã [40mùß [42mùø   ùã ùå   [40mùø [42mùø   ùã ùù ùù [40mùß [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 12); cout << "[44m  [40m      [1;35m[37;50m ¢x [33;42mùø   [40mùø [35m¢x     ¢x [33mùã [42mùß [40mùÝ [42mùß [40mùÝ ùå   [42mùø       [40mùø ùã [42mùß       [40mùø [42mùø         [40mùø [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 13); cout << "[44m  [40m      [1;35m[37;50m ¢x [33mùã ùù ùå [35m¢x     ¢¢ ¢¡ [33mùã ùå ùã ùå     ùã ùù ùù ùù ùå   ùã ùù ùù ùù ùå ùã ùù ùù ùù ùù ùå [35m¢x   [44m  [m" << '\n';
	gotoxy(20, 14); cout << "[44m  [40m      [1;35m ¢¢ ¢w ¢w ¢w ¢£       ¢¢ ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢w ¢£   [44m  [m" << '\n';
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
void selectPlayer()		//-----------------------------------------------¿ï¾Ü¤H¼Æ
{
	gotoxy(initialx, initialy);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << playernum[0];
	gotoxy(initialx, initialy + 1);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	cout << playernum[1];
	gotoxy(initialx, initialy + 2);		cout << playernum[2];
	gotoxy(initialx, initialy + 3);		cout << playernum[3];
	gotoxy(117, 30);
}
void characterprint(int num)		//--------------------------------------------¿ï¨¤
{
	PlaySound(TEXT("GOLDEN LEGEND.wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);		//background music
	const int row = 29, column = 116;
	//-------------------¥~®Ø-----------------------------------
	gotoxy(0, 0);		cout << "¢z";
	for (int i = 1; i < column; i++)	cout << "¢w";		cout << "¢{";
	for (int i = 1; i < row; i++)
	{
		gotoxy(0, i);	cout << "¢x";
		gotoxy(column, i);	cout << "¢x";
	}
	gotoxy(0, row);		cout << "¢|";
	for (int i = 1; i < column; i++)	cout << "¢w";		cout << "¢}";
	gotoxy(10, 2);	cout << "------Select your character------";
	gotoxy(47, 2);	cout << "------Character Preview------";
	gotoxy(5, 26);	cout << "Press ¡ô¡õ ¿ï¾Ü­n¹wÄýªº¨¤¦â";
	gotoxy(35, 26);	cout << "Press Enter ¹wÄý¨¤¦â/¶i¤J¹CÀ¸";
	gotoxy(67, 26);		cout << "Press 'q' ¿ï¾Ü¨ä¥L¨¤¦â";
	gotoxy(92, 26);		cout << "Press Esc ¦^¨ì¥Dµe­±";
	gotoxy(57, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "¤k°ª¤¤¥Í";
	gotoxy(57, 10);		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); cout << "¾Þ½L¦l°Ó";
	gotoxy(57, 13);		cout << "¯î®q¶Ì³J";	gotoxy(57, 16);		cout << " ¸ô¤H69";
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

void mapbasic()			//---------------------------------------------¹CÀ¸µe­±
{
	system("color 0f");
	system("cls");
	cout << "|                 |                 |                 |                 |" << endl;				//------------blank*16
	cout << "|                 |                 |                 |                 |" << endl;	//------------blank*11
	cout << "|-----------------------------------------------------------------------|" << endl;
	cout << "|¥Ø«e¹CÀ¸ªÌ                                                   ·í«e¦^¦X¼Æ|" << endl;
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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//­ì¦ìÂkÁÙ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	pointup.X = x;
	if (num == 0)
		pointup.Y = y + (str.size()-1) * blank;
	else
		pointup.Y = y + (num - 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//¨ì¦ì¤Ï¥Õ
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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//­ì¦ìÂkÁÙ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	point.X = x;
	if (num == str.size()-1)
		point.Y = y;
	else
		point.Y = y + (num + 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//¨ì¦ì¤Ï¥Õ
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
		gotoxy(90, 2);	cout << "  [1;33m [;34m¢¨¢i¢i¢i¢©[37m";
		gotoxy(93, 3);	cout << "    [34;43m¢i¢«¢«¢ª¢i[37;40m";
		gotoxy(89, 4);	cout << "    [34;43m¢p[30m¡Z   ¡Z [34m¢i[37;40m";
		gotoxy(88, 5);	cout << "[1;36m¢@   [;34;43m¢p  [31m¡¿  [34m¢i[37;40m";
		gotoxy(88, 6);	cout << "  [1;36m¢@ [;34;47m¢«[37m[45;50m¢m[1;37;45m¡þ[;34m[37;47;50m¢i[34m¢ª[37;40m";
		gotoxy(89, 7);	cout << "    [34m¢i[37m[45;50m¢m[1m¡Y [47m [;34m¢i[37m";
		gotoxy(85, 10);		cout << "ÁõÄÝ¦a°Ï : ¥_¬ì°ª¤¤";
		gotoxy(85, 13);		cout << "¯à¤O : ¾Ç¥Í¤è®× ¶R©Ð»ù®æ-10­w";
		gotoxy(85, 16);		cout << "°Æ§@¥Î : ½a¥] ¿ú¤Ö5000áà";
		gotoxy(117, 30);	break;
	}
	case 1:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(92, 2);	cout << " [1;34m¢¨¢i¢i¢i¢© [m";
		gotoxy(92, 3);	cout << " [1;34;43m¢«  [;30;43m¡Ý   [1;34;40m¢m[m";
		gotoxy(92, 4);	cout << "[43m [30m¢w ¡ó¢w ¡ó-[37m";
		gotoxy(93, 5);	cout << " [43m    [30m¥×   [40m  [37m";
		gotoxy(93, 6);	cout << "[30;43m¢©  ¡` ¢¨[40m  [37m";
		gotoxy(93, 7);	cout << "[33m¢¨[47m  [1;31m²n  [;33m¢©[37m";
		gotoxy(85, 10);		cout << "ÁõÄÝ¦a°Ï : ÂEX¶°¹Î";
		gotoxy(85, 13);		cout << "¯à¤O : ¦Ñ¤l¦³¿ú ¿ú¦h5000áà";
		gotoxy(85, 16);		cout << "°Æ§@¥Î : ¿ú¤Ó¦h ¶R©Ð»ù®æ+10­w";
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
		gotoxy(85, 10);		cout << "ÁõÄÝ¦a°Ï : ¯u¡´¤ÑÀs";
		gotoxy(85, 13);		cout << "¯à¤O : ©¯¹BS-->±ä²n±o ¾ß¨ì500¾k";
		gotoxy(85, 16);		cout << "°Æ§@¥Î : ´¼°ÓE- ¤º¿Ç³Q°½ÁÙ???";
		gotoxy(94, 17);		cout << "¾÷²v±¼¿ú............";
		gotoxy(94, 18);		cout << "....................¶Ü";
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
		gotoxy(98, 5);	cout << "******   °¼µÛ¬Ý";		gotoxy(99, 3);	cout << "*     *";	gotoxy(100, 4);	cout << "*   *";
		gotoxy(100, 6);	cout << "*   *  §O¬Ý¬nªü";		gotoxy(99, 7);	cout << "*     *";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(85, 10);		cout << "ÁõÄÝ¦a°Ï : ½Ö¨Ó¬ù·|";
		gotoxy(85, 13);		cout << "¯à¤O : ¨C¦^¦X¦³¾÷²v°ª¶¯µo¤j°]";
		gotoxy(85, 16);		cout << "°Æ§@¥Î : ¾÷²v¥X²{«á¤~µo²{....";
		gotoxy(94, 17);		cout << "....................";
		gotoxy(94, 18);		cout << "ÕÙ........¦n¹³¨S¦³¥Î";
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

void lenPrint(string str)                    //---------------------------±Æª©¸m¤¤¥Î
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
	gotoxy(22, 4); cout << "[47m      [40m¢«                   [33m¢b¢c¢b                               [37m¢ª[47m              [40m" << endl;
	gotoxy(22, 5); cout << "[47m    [40m¢«               [30m[33;50m¢c¢f¢h[43m        [40m¢g¢e[30;50m¢c                         [37m¢ª[47m            [40m" << endl;
	gotoxy(22, 6); cout << "[47m  [40m¢«              [30m[33;50m¢c[43;50m¢f            [30m/¢A¢¬  [33m[40;50m¢g[30;50m¢d                        [37m¢ª[47m          [40m" << endl;
	gotoxy(22, 7); cout << "¢«              [33m¢¨[43m               [37;50m¢h¢g¢f¢e[33;50m¢c[40;50m¢e              [1m¸õ         [m¢ª[47m        [40m" << endl;
	gotoxy(22, 8); cout << "              [30m[33;50m¢¨[43m                [47m¢o         [37;43m[33;50m¢e[40;50m¢e                         [37m¢ª[47m      [40m" << endl;
	gotoxy(22, 9); cout << "              [30;43m¢k                 [47m            [37;43m[33;50m¢e[40;50m¢e         [1mGAME            [m¢ª[47m    [40m" << endl;
	gotoxy(22, 10); cout << "              [43m [30m/               [33;47m¢n             [37;43m¢l[33;40m¢o                          [37m¢ª[47m  [40m" << endl;
	gotoxy(22, 11); cout << "            [30;43m¢o[33m[30;50m¡ü              [33;47m¢o     [30m¢¬  ¡©[37m[30;50m¡c¡\ [37;43m¢k[33;40m¢n        [1m¨S                 [m¢ª" << endl;
	gotoxy(22, 12); cout << "             [43m [30m¡U    ¢j       ¢b[47m¡«¡d¡¬       ¢b¢c[43m  [33;40m¢l[37m                            " << endl;
	gotoxy(22, 13); cout << "            [30;43m¢k[33m[30;50m¡ü    ¢j     [33;40m¢e[37;50m¢f¢d[30;47m¢g[37;50m¡k     [40m¢«¢d¢f[43m¢j[33;40m¢n[37m¢b¢c[30;50m¢b [1;33m¦³[m                   " << endl;
	gotoxy(22, 14); cout << "      ¢b¢c¢d[43m¢e¢e¢d¢c[30m¢j       [47;50m¢f[37;40m¢c¢g[47m       [40m¢f¢c[30;47m¢f[37;43m¢k [33;47m¢k   [30m[40;50m¢¨[37m                      " << endl;
	gotoxy(22, 15); cout << "     [47;50m¡´       [30m[37;50m¡d[30;50m¡s [37;43m¢l       [33;46m¢k[36;47m¢j[37m£r            [36m¢p[37;43m¢k [33;47m¢l [30m¢¨[40m   [1;33m©f[m                   " << endl;
	gotoxy(22, 16); cout << "     [30m[47;50m¢g[37;50m¢d       [30m(¡©[37;43m¢l       [46m  [47m    [30m,~¡c¡\¢b__  [37;46m¢k[43m¢l[33;47m¢p[30m¢¨[37;40m                          " << endl;
	gotoxy(22, 17); cout << "       [30m[47;50m¢h[33;50m¢f[30;50m¢d¢b  ¡d[37;43m¢l      [33;46m¢k[36;47m¢l [31m¢¨[41m[47;50m¢g¢f¢e¢f¢g[41m [47m [37;46m¢l[36;47m[43;50m¢j[33;40m¢o       [1m©f[m                   " << endl;
	gotoxy(22, 18); cout << "          [30;43m¢©[33;40m[30;50m¢e [47m[33;50m¢h¢g[40m[43;50m¢k      [37;46m¢l[36;47m¢j[37;41m¢l          [31;47m¢p  [46m [37;43m¢l[33;40m¢n[37m                            " << endl;
	gotoxy(22, 19); cout << "            [30;43m¢©[33;40m[30;50m¢e[43m \ [33;50m¡ü      [47m  [46m [36;47m¢k[37;41m¢k          [31;47m¢n [37;46m¢n[43m¢j[33;40m¢l       [1m                   [;30;47m¢«[37;40m" << endl;
	gotoxy(22, 20); cout << "              [30;43m¢o  ¢­ ¢j [33m[37;50m¢e[47m [46m¢p[36;47m¢p[37;40m¢p[41m¢©¢b   ¢b¢c[31;47m[37;50m¢« [43m[36;50m¢«[33m[30;50m¢e[40m                          [47m¢«  [37;40m" << endl;
	gotoxy(22, 21); cout << "               [30;43m¢j   \  [33m[37;50m¡l[33;47m¢d[37;50m¢c[46m [36;47m¢k [30m¢­_  _,~¡d¡ª [37;43m¢«[30m¢d[40m                          [47m¢«    [37;40m" << endl;
	gotoxy(22, 22); cout << "               [43m     [33m[30;50m£f   \ [33;47m[46;50m¢©[36;47m¢j     [37;40m¢h[47m [33m¢b¢e[30;40;50m¢g                            [47m¢«      [37;40m" << endl;
	gotoxy(22, 23); cout << "[30;47m¢ª[40m            [43m¢l     [32m¢l  [33m[32;50m¢h¢g[31;47m¢b   [37m[33;50m¢e¢g[40m¢«[43m  [40m¢k                          [30;47m¢«        [37;40m" << endl;
	gotoxy(22, 24); cout << "[47m  [30m¢ª[40m         [43m¢n   [33m[32;50m¢e[42m  [43m¢© [42;50m¢¨[41m¢o     [31m[42;50mùø   [32;40m¢©[30;43m¢k[40m                          [47m¢«          [37;40m" << endl;
	gotoxy(22, 25); cout << "[47m    [30m¢ª[40m       [43m¢l [33m[32;50m¢c[42;50m¢g   [43m¢n¢ª[47m¢n[37;41m¢h¢g¢h[42m    [32m[33;50m¢¨[43m [40m[30;50m¢©  [33m#NYKD54 (MAN_Chat)[30m  [47m¢«            [37;40m" << endl;
	gotoxy(22, 26); cout << "[47m      [30m¢ª[40m    [32m[43;50m¢b¢d[42;50m¢g      [43m¢k[33;42m¢n[32;47m¢©    [37;42m¢n   [32;43m¢l [33;40m¢n    ig : k7_00626   [30;47m¢«              [37;40m" << endl;
	gotoxy(90, 28);	cout << "To be continued---->";
	gotoxy(117, 30);
	Sleep(10000);
}