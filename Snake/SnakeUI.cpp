#include "SnakeUI.h"
#include <time.h>
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <stdio.h>
#include "SnakeFile.h"

static IMAGE bomb;
static IMAGE weed;
static IMAGE food;
static IMAGE background;

void DrawSnake(game Game)
{
	snake s = Game->head;
	while (s != NULL)
	{
		circle(s->posi->X, s->posi->Y, R);
		setfillcolor(BLACK);
		fillcircle(s->posi->X, s->posi->Y, R);
		s = s->next;
	}
}

void InitGraph()
{
	initgraph(CHOOSE_WIDTH, CHOOSE_HEIGHT, SHOWCONSOLE);   // ������ͼ���ڣ���СΪ 640x480 ����
	setbkcolor(BLACK);
	cleardevice();
	
}

void DrawChoose()
{
	Resize(NULL, CHOOSE_WIDTH, CHOOSE_HEIGHT);
	cleardevice();
	settextcolor(WHITE);
	int points[] = { 0, 70,  638, 70,  638, 350, 0, 350 };
	drawpoly(4, points);
	RECT begin = { 0,70,CHOOSE_WIDTH,140 };
	RECT record = { 0,140,CHOOSE_WIDTH, 210 };
	RECT level = { 0,210,CHOOSE_WIDTH, 280 };
	RECT continue_ = { 0,280,CHOOSE_WIDTH, 350 };
	drawtext(_T("��ʼ��Ϸ"), &begin, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("��ʷ��¼"), &record, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("��Ϸ����"), &level, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("������Ϸ"), &continue_, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	int scene = 1;
	int is_repaint = 0;
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.x > 0 && msg.mkLButton)
			{
				int n = msg.y / 70;
				switch (n)
				{
				case 0:
					break;
				case 1:
					GetMouseMsg();
					is_repaint = 1;
					DrawGameWindow(1, scene, 1);
					//����ʼ��Ϸ
					break;
				case 2:
					GetMouseMsg();
					is_repaint = 1;
					DrawRank();
					//������ʷ��¼
					break;
				case 3:
					GetMouseMsg();
					is_repaint = 1;
					scene = DrawScene();
					GetMouseMsg();
					//������Ϸ����
					break;
				case 4:
					GetMouseMsg();
					is_repaint = 1;
					DrawGameWindow(1, scene, 0);
					//���������Ϸ
					break;
				default:
					break;
				}
				if (is_repaint == 1)
				{
					Resize(NULL, CHOOSE_WIDTH, CHOOSE_HEIGHT);
					cleardevice();
					settextcolor(WHITE);
					is_repaint = 0;
					int points[] = { 0, 70,  638, 70,  638, 350, 0, 350 };
					drawpoly(4, points);
					RECT begin = { 0,70,CHOOSE_WIDTH,140 };
					RECT record = { 0,140,CHOOSE_WIDTH, 210 };
					RECT level = { 0,210,CHOOSE_WIDTH, 280 };
					RECT continue_ = { 0,280,CHOOSE_WIDTH, 350 };
					drawtext(_T("��ʼ��Ϸ"), &begin, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("��ʷ��¼"), &record, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("��Ϸ����"), &level, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("������Ϸ"), &continue_, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
	}
}


void DrawGameInfo(game Game)
{
	settextcolor(WHITE);
	RECT length = { 900, 0, 1200, 80 };
	RECT score = { 900, 80, 1200, 160 };
	RECT level = { 900, 160, 1200, 240 };
	RECT next = { 900, 400, 1200, 500 };
	RECT regame = { 900, 500, 1200, 600 };
	RECT back = { 900, 600, 1200, 700 };
	TCHAR length_char[10];
	TCHAR score_char[10];
	TCHAR level_char[10];
	swprintf_s(length_char, _T("���ڳ��ȣ�%d"), Game->length);
	swprintf_s(score_char, _T("���ڵ÷֣�%d"), Game->score);
	swprintf_s(level_char, _T("��ǰ�ؿ���%d"), Game->difficulty);

	printf("%d\n", Game->difficulty);
	drawtext(length_char, &length, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(score_char, &score, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(level_char, &level, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	drawtext(_T("��һ��"), &next, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("���¿�ʼ"), &regame, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("�˳���Ϸ"), &back, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


}
void DrawPoisonousWeeds(poisonousWeeds PoisonousWeeds)
{
	while (PoisonousWeeds != NULL)
	{
		putimage(PoisonousWeeds->posi->X - 8, PoisonousWeeds->posi->Y - 8, &weed);
		PoisonousWeeds = PoisonousWeeds->next;
	}
}
void DrawFoods(foods Foods)
{
	while (Foods != NULL)
	{
		putimage(Foods->posi->X - 8, Foods->posi->Y - 8, &food);
		Foods = Foods->next;
	}
}

void DrawBooms(booms Booms)
{
	
	while (Booms != NULL)
	{
		putimage(Booms->posi->X - 8, Booms->posi->Y - 8, &bomb);
		Booms = Booms->next;
	}
}

void DrawGameWindow(int difficulty, int scene, int is_new)
{
	int DrawWeed = 1;
	Resize(NULL, 1200, 700);
	game Game; 
	if(is_new)
		Game = Begin(difficulty, scene);
	else
	{
		Game = getGameInfo();
	}
	if (Game->scene == 1)
	{
		setbkcolor(BLACK);
	}
	else if(Game->scene == 2)
	{
		setbkcolor(GREEN);
	}
	else
	{
		setbkcolor(BLUE);
	}
	cleardevice();
	//������Դ
	loadingImage(&bomb, &weed, &food, &background, Game->scene);
	//��ʼ������ͼ
	BeginBatchDraw();
	setcliprgn(NULL);
	//����
	putimage(0, 0, &background);
	//����
	line(900, 0, 900, 700);
	//����Ϸ��Ϣ
	DrawGameInfo(Game);
	//���òü���
	HRGN Snake_RGN = CreateRectRgn(0, 0, 898, 700);
	setcliprgn(Snake_RGN);
	HRGN Info_RGN = CreateRectRgn(902, 0, 1200, 300);
	//����
	DrawSnake(Game);
	//������
	DrawPoisonousWeeds(Game->Weeds);
	//��ʳ��
	DrawFoods(Game->Foods);
	//��ը��
	DrawBooms(Game->Booms);
	//����������ͼ
	FlushBatchDraw();
	//��ʱ��
	DWORD Last_time, Now_time;
	Last_time = GetTickCount();

	FlushMouseMsgBuffer();
	while (1)
	{
		//�����Ӧ
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton == 1)
			{
				//�������Ϸ���水��
				if (msg.x < 900 && Game->is_on)
				{
					struct position temp = { msg.x, msg.y };

					setNextDirc(&temp, Game->head->posi);
					SetDirect(Game, &temp);
				}
				//��һ��
				else if (1000 < msg.x && msg.x < 1100 && 430 < msg.y && msg.y < 470)
				{
					Game->difficulty++;
					printf("%d\n", Game->difficulty);
					changeBooms(Game);
					changeWeeds(Game);
					changeFoods(Game);
					//���´�����ʾ
					setcliprgn(Info_RGN);
					clearcliprgn();
					DrawGameInfo(Game);
					setcliprgn(Snake_RGN);
				}
				//���¿�ʼ
				else if (1000 < msg.x && msg.x < 1100 && 530 < msg.y && msg.y < 570)
				{
					Die(Game);
					Game = Begin(1, 1);
					clearcliprgn();
					BeginBatchDraw();
					//����
					putimage(0, 0, &background);
					//����
					DrawSnake(Game);
					//����
					line(900, 0, 900, 700);
					//������
					if (DrawWeed)
					{
						DrawPoisonousWeeds(Game->Weeds);
						DrawWeed = 0;
					}
					else
					{
						DrawWeed = 1;
					}
					//��ʳ��
					DrawFoods(Game->Foods);
					//��ը��
					EndBatchDraw();
					//����Ϸ��Ϣ
					setcliprgn(Info_RGN);
					clearcliprgn();
					DrawGameInfo(Game);
					setcliprgn(Snake_RGN);
				}
				//�˳���Ϸ
				else if (1000 < msg.x && msg.x < 1100 && 630 < msg.y && msg.y < 670)
				{
					//��Ϸ����������÷�
					printf("here\n");
					storeGameInfo(Game);
					Die(Game);
					return;
				}
			}
		}
		//ʱ�䶨ʱ
		if (Game->is_on)
		{
			Now_time = GetTickCount();
			if ((int)(Now_time - Last_time) > Game->time)
			{
				clearcliprgn();
				//���ƶ�
				Move(Game);
				//����
				putimage(0, 0, &background);
				//����
				BeginBatchDraw();
				DrawSnake(Game);
				//���ʳ���Ƿ񱻳�
				if (CheckFoods(Game->head->posi, Game->Foods))
				{
					Grow(Game);
					setcliprgn(Info_RGN);
					clearcliprgn();
					DrawGameInfo(Game);
					setcliprgn(Snake_RGN);
				}
				//��ʳ��
				DrawFoods(Game->Foods);
				//��鶾��
				if (CheckWeeds(Game->head->posi, Game->Weeds))
				{
					Game->is_on = 0;
					DrawGameOver();
					DrawPoisonousWeeds(Game->Weeds);
				}
				//������
				if (DrawWeed)
				{
					DrawPoisonousWeeds(Game->Weeds);
					DrawWeed = 0;
				}
				else
				{
					DrawWeed = 1;
				}
				//���ը��
				if (CheckBooms(Game->head->posi, Game->Booms))
				{
					if (SplitHalf(Game) == 1)
					{
						//��Ϸ����
						Game->is_on = 0;
						DrawGameOver();
						DrawPoisonousWeeds(Game->Weeds);
					};
					setcliprgn(Info_RGN);
					clearcliprgn();
					DrawGameInfo(Game);
					setcliprgn(Snake_RGN);
				}
				//��ը��
				DrawBooms(Game->Booms);
				EndBatchDraw();
				//����Ƿ�ײǽ
				if (CheckWall(Game->head->posi) == 1)
				{
					Game->is_on = 0;
					DrawGameOver();
					DrawPoisonousWeeds(Game->Weeds);
				}

				Last_time = Now_time;
			}
		}
	}
}


void DrawRank()
{
	int s[5] = { 0,0,0,0,0 };
	getScore(s);
	Resize(NULL, 480, 400);
	cleardevice();
	settextcolor(WHITE);
	RECT first = { 0,30,480,110 };
	RECT second = { 0,110,480, 180 };
	RECT third = { 0,180,480, 250 };
	RECT fourth = { 0,250,480, 320 };
	RECT fifth = { 0, 320, 480, 390 };
	RECT back = { 400, 350, 480, 400 };

	TCHAR word1[10];
	TCHAR word2[10];
	TCHAR word3[10];
	TCHAR word4[10];
	TCHAR word5[10];


	swprintf_s(word1, _T("��һ����%d"), s[0]);
	swprintf_s(word2, _T("�ڶ�����%d"), s[1]);
	swprintf_s(word3, _T("��������%d"), s[2]);
	swprintf_s(word4, _T("��������%d"), s[3]);
	swprintf_s(word5, _T("��������%d"), s[4]);

	drawtext(word1, &first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(word2, &second, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(word3, &third, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(word4, &fourth, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(word5, &fifth, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("����"), &back, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton)
			{
				if (420 < msg.x && msg.x < 460 && 360 < msg.y < 390)
				{
					return;
				}
			}
		}
	}
}

void DrawGameOver()
{
	settextcolor(WHITE);
	RECT gameover = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	drawtext(_T("Game Over!"), &gameover, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
}
int DrawScene()
{
	Resize(NULL, 480, 400);
	cleardevice();
	settextcolor(WHITE);
	RECT first = { 0,50,480,130 };
	RECT second = { 0,130,480, 200 };
	RECT third = { 0,200,480, 270 };
	RECT back = { 400, 350, 480, 400 };

	drawtext(_T("����һ"), &first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("������"), &second, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("������"), &third, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("����"), &back, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton)
			{
				if (200 < msg.x && msg.x < 280 && 50 < msg.y && msg.y< 130)
				{
					return 1;
				}
				else if (200 < msg.x && msg.x < 280 && 130 < msg.y && msg.y < 200)
				{
					return 2;
				}
				else if (200 < msg.x && msg.x < 280 && 200 < msg.y && msg.y < 270)
				{
					return 3;
				}
				else if (420 < msg.x && msg.x < 460 && 360 < msg.y && msg.y < 390)
				{
					return 1;
				}
			}




		
		}
	}
}