#include "Console.h"

#define initialx 54
#define initialy 21

const string menu[4] = { "�}�s�C��", "ù�w�j�k" ,"�W�h����" ,"  ���}  " };			//���const����
const string playernum[4] = { "��t���" ,"��������","�T�H����","�|�H�V��" };		//�H��const����
const string character[4] = { "�k������","�޽L�l��","��q�̳J"," ���H69" };	//����const����

void gotoxy(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void menuprint()		//------------------------------------------------------------------------�i�O�e��
{
	PlaySound(TEXT("Dance The Night Away (Instrumental).wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);				//background music
	system("mode con cols=118 lines=31");			//set console size
	for (int i = 0; i < 18; i++) { gotoxy(8, 0 + i);	cout << "|"; }
	for (int i = 0; i < 18; i++) { gotoxy(110, 0 + i);	cout << "|"; }
	system("color 0e");
	gotoxy(20, 2); cout << "[44m                                                                             [1;35m  [m" << '\n';
	gotoxy(20, 3); cout << "[44m  [40m                                                                           [1;35;44m  [m" << '\n';
	gotoxy(20, 4); cout << "[44m  [1;35;40m �~ �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w ��   [44m  [m" << '\n';
	gotoxy(20, 5); cout << "[44m  [1;35;40m �x [33;42m�� �� �� �� �� �� �� �� [40m�� [42m�� �� [40m��     [42m�� �� [40m�� [42m�� �� �� �� [40m��   [42m�� �� �� �� [40m�� [42m�� �� �� �� �� [40m�� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 6); cout << "[44m  [1;35;40m �x [33;42m��               [40m�� [42m��   [40m��     [42m��   [40m�� [42m��       [40m�� [42m�� ��       [40m�� [42m��         [40m�� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 7); cout << "[44m  [1;35;40m �x [33m�� �� �� [42m��   [40m�� �� �� �� [42m��   [40m��     [42m��   [40m�� �� [42m��   [40m�� �� [42m��   [40m�� [42m��   [40m�� [42m��  [40m �� �� �� �� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 8); cout << "[44m  [1;35;40m �� �w �w [37;50m�� [33;42m��   [40m�� [35m�~ �w �� [33;42m��   �� [40m�� [42m�� ��   [40m��   [42m��   [40m��   [42m��   [40m�� �� �� �� [42m��   �� �� �� [40m�� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 9); cout << "[44m  [40m      [1;35m[37;50m �x [33;42m��   [40m�� [35m�x   �x [33m�� [42m��   [40m�� [42m��   [40m�� ��   [42m��   [40m��   [42m��   [40m��       [42m��         [40m�� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 10); cout << "[44m  [40m      [1;35m[37;50m �x [33;42m��   [40m�� [35m�x   �� �� [33;42m��   �� ��   [40m��     [42m��   [40m��   [42m��   [40m�� [42m�� �� [40m�� [42m��  [40m �� �� �� �� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 11); cout << "[44m  [40m      [1;35m[37;50m �x [33;42m��   [40m�� [35m�x     �x [33;42m��         [40m��   [42m�� ��   �� [40m�� [42m��   �� ��   [40m�� [42m��   �� �� �� [40m�� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 12); cout << "[44m  [40m      [1;35m[37;50m �x [33;42m��   [40m�� [35m�x     �x [33m�� [42m�� [40m�� [42m�� [40m�� ��   [42m��       [40m�� �� [42m��       [40m�� [42m��         [40m�� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 13); cout << "[44m  [40m      [1;35m[37;50m �x [33m�� �� �� [35m�x     �� �� [33m�� �� �� ��     �� �� �� �� ��   �� �� �� �� �� �� �� �� �� �� �� [35m�x   [44m  [m" << '\n';
	gotoxy(20, 14); cout << "[44m  [40m      [1;35m �� �w �w �w ��       �� �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w �w ��   [44m  [m" << '\n';
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
void selectPlayer()		//-----------------------------------------------��ܤH��
{
	gotoxy(initialx, initialy);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << playernum[0];
	gotoxy(initialx, initialy + 1);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	cout << playernum[1];
	gotoxy(initialx, initialy + 2);		cout << playernum[2];
	gotoxy(initialx, initialy + 3);		cout << playernum[3];
	gotoxy(117, 30);
}
void characterprint(int num)		//--------------------------------------------�﨤
{
	PlaySound(TEXT("GOLDEN LEGEND.wav"), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);		//background music
	const int row = 29, column = 116;
	//-------------------�~��-----------------------------------
	gotoxy(0, 0);		cout << "�z";
	for (int i = 1; i < column; i++)	cout << "�w";		cout << "�{";
	for (int i = 1; i < row; i++)
	{
		gotoxy(0, i);	cout << "�x";
		gotoxy(column, i);	cout << "�x";
	}
	gotoxy(0, row);		cout << "�|";
	for (int i = 1; i < column; i++)	cout << "�w";		cout << "�}";
	gotoxy(10, 2);	cout << "------Select your character------";
	gotoxy(47, 2);	cout << "------Character Preview------";
	gotoxy(5, 26);	cout << "Press ���� ��ܭn�w��������";
	gotoxy(35, 26);	cout << "Press Enter �w������/�i�J�C��";
	gotoxy(67, 26);		cout << "Press 'q' ��ܨ�L����";
	gotoxy(92, 26);		cout << "Press Esc �^��D�e��";
	gotoxy(57, 7);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); cout << "�k������";
	gotoxy(57, 10);		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); cout << "�޽L�l��";
	gotoxy(57, 13);		cout << "��q�̳J";	gotoxy(57, 16);		cout << " ���H69";
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
void initialgame()			//---------------------------------------------�C���e��
{
	cout << "|1                |2                |3                |4                |" << endl;				//------------blank*16
	cout << "|$50000           |$50000           |$50000           |$50000           |" << endl;	//------------blank*11
	cout << "|-----------------------------------------------------------------------|" << endl;
	cout << "|�ثe�C����                                                   ��e�^�X��|" << endl;
	cout << "|                                                                     n |" << endl;
	cout << "|_______________________________________________________________________|" << endl;
	cout << "|";	for (int i = 0; i < 71; i++)	cout << "*";		cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|  �_�I  ";	cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|1|2||3|4";	cout << "|" << endl;
	cout << "|_______________________________________________________________________|" << endl;
	for (int i = 0; i < 6; i++) {
		cout << "|  �_�I  |                                                     |  �_�I  |" << endl;	cout << "|1|2||3|4|                                                     |1|2||3|4|" << endl;
		if (i != 5)	cout << "|________|                                                     |________|" << endl;
	}
	cout << "|_______________________________________________________________________|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|  �_�I  ";	cout << "|" << endl;
	for (int i = 0; i < 8; i++)	cout << "|1|2||3|4";	cout << "|" << endl;
}

void up_gotoxy(int num, int x, int y, int blank, const vector<string> str)
{
	COORD pointup;
	pointup.X = x;  pointup.Y = y + num * blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//����k��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	pointup.X = x;
	if (num == 0)
		pointup.Y = y + (str.size()-1) * blank;
	else
		pointup.Y = y + (num - 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointup);			//���ϥ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == 0)
		cout << str[str.size() - 1];
	else
		cout << str[num - 1];
	gotoxy(117, 30);
}
void down_gotoxy(int num, int x, int y, int blank, const vector<string> str)
{
	COORD point;
	point.X = x; point.Y = y + num * blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//����k��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << str[num];
	point.X = x;
	if (num == str.size()-1)
		point.Y = y;
	else
		point.Y = y + (num + 1)*blank;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);					//���ϥ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	if (num == str.size() - 1)
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
		gotoxy(90, 2);	cout << "  [1;33m [;34m���i�i�i��[37m";
		gotoxy(93, 3);	cout << "    [34;43m�i�������i[37;40m";
		gotoxy(89, 4);	cout << "    [34;43m�p[30m�Z   �Z [34m�i[37;40m";
		gotoxy(88, 5);	cout << "[1;36m�@   [;34;43m�p  [31m��  [34m�i[37;40m";
		gotoxy(88, 6);	cout << "  [1;36m�@ [;34;47m��[37m[45;50m�m[1;37;45m��[;34m[37;47;50m�i[34m��[37;40m";
		gotoxy(89, 7);	cout << "    [34m�i[37m[45;50m�m[1m�Y [47m [;34m�i[37m";
		gotoxy(85, 10);		cout << "���ݦa�� : �_�찪��";
		gotoxy(85, 13);		cout << "��O : �i���a�]-->�L���O8��";
		gotoxy(85, 16);		cout << "�Ƨ@�� : ���v�ʦ]���K�h�ҹL��";
		gotoxy(94, 17);		cout << "�𮧤@�^";
		gotoxy(117, 30);	break;
	}
	case 1:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(92, 2);	cout << " [1;34m���i�i�i�� [m";
		gotoxy(92, 3);	cout << " [1;34;43m��  [;30;43m��   [1;34;40m�m[m";
		gotoxy(92, 4);	cout << "[43m [30m�w ��w ��-[37m";
		gotoxy(93, 5);	cout << " [43m    [30m��   [40m  [37m";
		gotoxy(93, 6);	cout << "[30;43m��  �` ��[40m  [37m";
		gotoxy(93, 7);	cout << "[33m��[47m  [1;31m�n  [;33m��[37m";
		gotoxy(85, 10);		cout << "���ݦa�� : �EX����";
		gotoxy(85, 13);		cout << "��O : �Ѥl����-->��l���B+1w";
		gotoxy(85, 16);		cout << "�Ƨ@�� : ���Ӧh,�L���O���p��";
		gotoxy(94, 17);		cout << "�h���L�H�@�i�p�B��";
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
		gotoxy(85, 10);		cout << "���ݦa�� : �u�����s";
		gotoxy(85, 13);		cout << "��O : ���BS-->��n�o �ߨ�100�k";
		gotoxy(85, 16);		cout << "�Ƨ@�� : ����E- ���ǳQ����???";
		gotoxy(94, 17);		cout << "���v����............";
		gotoxy(94, 18);		cout << "....................��";
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
		gotoxy(98, 5);	cout << "******   ���۬�";		gotoxy(99, 3);	cout << "*     *";	gotoxy(100, 4);	cout << "*   *";
		gotoxy(100, 6);	cout << "*   *  �O�ݬn��";		gotoxy(99, 7);	cout << "*     *";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(85, 10);		cout << "���ݦa�� : �֨Ӭ��|";
		gotoxy(85, 13);		cout << "��O : �C�^�X�����v�����o�j�]";
		gotoxy(85, 16);		cout << "�Ƨ@�� : ���v�X�{��~�o�{....";
		gotoxy(94, 17);		cout << "....................";
		gotoxy(94, 18);		cout << "��........�n���S����";
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
