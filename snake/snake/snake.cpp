#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#define SNAKE_NUM 500//�ߵ�������
enum DIR//�ߵķ���
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//�ߵĽṹ
struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coor[SNAKE_NUM];//����
}snake;
//ʳ��ṹ
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;
//���ݵĳ�ʼ��
void GameInit()
{
	//init��ʼ�� graphͼ�δ���
	initgraph(640, 480/*,SHOWCONSOLE*/);
	//�������������
	srand(GetTickCount());
	//��ʼ����
	snake.size=3;
	snake.speed = 10;
	snake.dir=RIGHT;
	for (int i = 0; i<snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//��ʼ��ʳ�rand��������һ��������������û������������ӣ���ô�������ǹ̶�����
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;
	food.r = rand() % 10 + 5;
}
void GameDraw()
{
	//˫�����ͼ
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(174, 141, 59));
	cleardevice();
	//������
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
//�ƶ���
void snakeMove()
{
	//���������ͷ��
	for (int i = snake.size-1; i >0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//�ƶ��ı�
	switch (snake.dir)
		{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y <= 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y+=snake.speed;
		if (snake.coor[0].y >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-=snake.speed;
		if (snake.coor[0].x <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
		}
}
//ͨ�������ı��ߵķ���
void keyControl()
{
	//�ж���û�а���
	if (_kbhit())//����а����򷵻�һ����
	{
		//72 80 75 77 �������Ҽ�ֵ
		switch (_getch())
		{
		case'w':
		case'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			
			break;
		case's':
		case'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			
			break;
		case'a':
		case'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			
			break;
		case'd':
		case'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			
			break;
		}
	}
	
}
void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x < food.x + food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].y < food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	//���ʳ�ﱻ�Ե� ��������һ��
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
		food.r = rand() % 10 + 5;
	}
}
//��Ϸ��ͣ
void Stop()
{
	if (_kbhit())
	{
		if (_getch() == ' ')
		{
			while (_getch()!= ' ');
		}
	}
}
int main()
{
	GameInit();
	while (1)
	{
		GameDraw();
		snakeMove();
		keyControl();
		EatFood();
		Stop();
		Sleep(150);
	}
	return 0;
}