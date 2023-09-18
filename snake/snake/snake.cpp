#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#define SNAKE_NUM 500//蛇的最大节数
enum DIR//蛇的方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//蛇的结构
struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coor[SNAKE_NUM];//坐标
}snake;
//食物结构
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;
//数据的初始化
void GameInit()
{
	//init初始化 graph图形窗口
	initgraph(640, 480/*,SHOWCONSOLE*/);
	//设置随机数种子
	srand(GetTickCount());
	//初始化蛇
	snake.size=3;
	snake.speed = 10;
	snake.dir=RIGHT;
	for (int i = 0; i<snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//初始化食物，rand（）产生一个随机整数，如果没有设置随机种子，那么产生的是固定的数
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;
	food.r = rand() % 10 + 5;
}
void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(174, 141, 59));
	cleardevice();
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
//移动蛇
void snakeMove()
{
	//让身体跟着头动
	for (int i = snake.size-1; i >0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//移动改变
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
//通过按键改变蛇的方向
void keyControl()
{
	//判断有没有按键
	if (_kbhit())//如果有按键则返还一个真
	{
		//72 80 75 77 上下左右键值
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
	//如果食物被吃掉 重新生成一个
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
		food.r = rand() % 10 + 5;
	}
}
//游戏暂停
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