#include "Console.h"
const string menu[4] = { "�}�s�C��", "ù�w�j�k" ,"�W�h����" ,"  ���}  " };			//���const����
const string playernum[4] = { "��t���" ,"��������","�T�H����","�|�H�V��" };		//�H��const����
const string character[4] = { "�k������","�޽L�l��","��q�̳J"," ���H69" };	//����const����
int main()
{
	menuprint();
	int gameMode = 0;
	while (true)
	{
		//�����O�_����L��J
		if (_kbhit())
		{
			int input = _getch();
			//��J�䬰��V��
			if (input == 224)
			{
				input = _getch();
				//��J�䬰UP
				if (input == 72)
				{
					up_gotoxy(gameMode, 54, 21, 1,menu);
					if (gameMode == 0)
						gameMode = 3;
					else
						gameMode--;
				}
				//��J�䬰DOWN
				else if (input == 80)
				{
					down_gotoxy(gameMode, 54, 21, 1,menu);
					if (gameMode == 3)
						gameMode = 0;
					else
						gameMode++;
				}
			}
			//��J�䬰ENTER
			else if (input == 13)
			{
				selectPlayer();
				gameMode = 0;
				int selectMode = 0;
				while (true)
				{
					//�����O�_����L��J
					if (_kbhit())
					{
						int input = _getch();
						//��J�䬰��V��
						if (input == 224)
						{
							input = _getch();
							//��J�䬰UP
							if (input == 72)
							{
								up_gotoxy(selectMode,54,21,1,playernum);
								if (selectMode == 0)
									selectMode = 3;
								else
									selectMode--;
							}
							//��J�䬰DOWN
							else if (input == 80)
							{
								down_gotoxy(selectMode,54,21,1,playernum);
								if (selectMode == 3)
									selectMode = 0;
								else
									selectMode++;
							}
						}
						//��J�䬰ENTER
						else if (input == 13)	//----------------------------�粒�H��
						{
							system("color 0f");
							system("cls");
							characterprint(selectMode);
							selectMode = 0;
							int c = 0;
							while (true)
							{
								//�����O�_����L��J
								if (_kbhit())
								{
									int input = _getch();
									//��J�䬰��V��
									if (input == 224)
									{
										input = _getch();
										//��J�䬰UP
										if (input == 72)
										{
											up_gotoxy(c, 57, 7, 3, character);
											if (c == 0)
												c = 3;
											else
												c--;
										}
										//��J�䬰DOWN
										else if (input == 80)
										{
											down_gotoxy(c, 57, 7, 3, character);
											if (c == 3)
												c = 0;
											else
												c++;
										}
									}
									//��J�䬰ENTER
									else if (input == 13)	//----------------------------�粒�H��
									{
										previewCharacter(c);
										while (true)
										{
											if (_kbhit())
											{
												input = _getch();
												//�T�w��ܦ��ѽL�i��C��
												if (input == 13)
												{
													system("color 0f");
													system("cls");
													return 1;
												}
												//���s���
												else if (input == 'q')
												{
													characterClear();
													gotoxy(117, 30);
													break;
												}
											}
										}
									}
								}
							}
						}
					}
				}
				break;
			}
		}
	}
}
