#include <conio.h>
#include "Monopoly.h"

int main(void)
{
	const string tmp[4] = { "�}�s�C��", "ù�w�j�k" ,"�W�h����" ,"  ���}  " };
	vector<string> menu(tmp, tmp + 4);
	Monopoly game;
	int toDo = 0;
	menuprint();
	while (true)
	{
		if (_kbhit())
		{
			int input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (input == 72)
				{
					up_gotoxy(toDo, 54, 21, 1, menu);
					if (toDo == 0)
						toDo = 3;
					else
						toDo--;
				}
				else if (input == 80)
				{
					down_gotoxy(toDo, 54, 21, 1, menu);
					if (toDo == 3)
						toDo = 0;
					else
						toDo++;
				}
			}
			else if (input == 13)
			{
				game.action(toDo);
				menuprint();
			}
		}
	}
	return 0;
}