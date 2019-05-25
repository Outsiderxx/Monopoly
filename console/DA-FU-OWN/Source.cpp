#include "Console.h"
const string menu[4] = { "開新遊戲", "羅德大法" ,"規則說明" ,"  離開  " };			//選單const全域
const string playernum[4] = { "邊緣單行" ,"雙飛翱翔","三人成虎","四人混戰" };		//人數const全域
const string character[4] = { "女高中生","操盤奸商","荒島傻蛋"," 路人69" };	//角色const全域
int main()
{
	menuprint();
	int gameMode = 0;
	while (true)
	{
		//偵測是否有鍵盤輸入
		if (_kbhit())
		{
			int input = _getch();
			//輸入鍵為方向鍵
			if (input == 224)
			{
				input = _getch();
				//輸入鍵為UP
				if (input == 72)
				{
					up_gotoxy(gameMode, 54, 21, 1,menu);
					if (gameMode == 0)
						gameMode = 3;
					else
						gameMode--;
				}
				//輸入鍵為DOWN
				else if (input == 80)
				{
					down_gotoxy(gameMode, 54, 21, 1,menu);
					if (gameMode == 3)
						gameMode = 0;
					else
						gameMode++;
				}
			}
			//輸入鍵為ENTER
			else if (input == 13)
			{
				selectPlayer();
				gameMode = 0;
				int selectMode = 0;
				while (true)
				{
					//偵測是否有鍵盤輸入
					if (_kbhit())
					{
						int input = _getch();
						//輸入鍵為方向鍵
						if (input == 224)
						{
							input = _getch();
							//輸入鍵為UP
							if (input == 72)
							{
								up_gotoxy(selectMode,54,21,1,playernum);
								if (selectMode == 0)
									selectMode = 3;
								else
									selectMode--;
							}
							//輸入鍵為DOWN
							else if (input == 80)
							{
								down_gotoxy(selectMode,54,21,1,playernum);
								if (selectMode == 3)
									selectMode = 0;
								else
									selectMode++;
							}
						}
						//輸入鍵為ENTER
						else if (input == 13)	//----------------------------選完人數
						{
							system("color 0f");
							system("cls");
							characterprint(selectMode);
							selectMode = 0;
							int c = 0;
							while (true)
							{
								//偵測是否有鍵盤輸入
								if (_kbhit())
								{
									int input = _getch();
									//輸入鍵為方向鍵
									if (input == 224)
									{
										input = _getch();
										//輸入鍵為UP
										if (input == 72)
										{
											up_gotoxy(c, 57, 7, 3, character);
											if (c == 0)
												c = 3;
											else
												c--;
										}
										//輸入鍵為DOWN
										else if (input == 80)
										{
											down_gotoxy(c, 57, 7, 3, character);
											if (c == 3)
												c = 0;
											else
												c++;
										}
									}
									//輸入鍵為ENTER
									else if (input == 13)	//----------------------------選完人數
									{
										previewCharacter(c);
										while (true)
										{
											if (_kbhit())
											{
												input = _getch();
												//確定選擇此棋盤進行遊戲
												if (input == 13)
												{
													system("color 0f");
													system("cls");
													return 1;
												}
												//重新選擇
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
