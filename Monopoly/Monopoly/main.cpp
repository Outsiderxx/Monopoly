#include <conio.h>
#include "Monopoly.h"

int main(void)
{
	Monopoly game;
	int toDo = 0;
	//print主畫面
	while (_kbhit())
	{
		int input = _getch();
		if (input == 224)
		{
			input = _getch();
			if (input == 72)
			{
				//UP
				if (toDo == 0)
					toDo = 4;
				else
					toDo--;
			}
			else if (input == 80)
			{
				//DOWN
				if (toDo = 4)
					toDo = 0;
				else
					toDo++;
			}
		}
		else if (input == 13)
		{
			game.action(toDo);
			//回到主畫面，刷新顯示
		}
	}
	return 0;
}