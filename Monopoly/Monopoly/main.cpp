#include <conio.h>
#include "Monopoly.h"

int main(void)
{
	//toDo 0:new game,1:old game,2:manual,3:exit
	Monopoly game;
	int toDo = 0;
	//print�D�e��
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
			//�^��D�e���A��s���
		}
	}
	return 0;
}