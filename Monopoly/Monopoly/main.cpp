#include <conio.h>
#include "Monopoly.h"

int main(void)
{
	const string menu[4] = { "�}�s�C��", "ù�w�j�k" ,"�W�h����" ,"  ���}  " };
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
				system("color 0f");
				system("cls");
			}
		}
	}
	return 0;
}