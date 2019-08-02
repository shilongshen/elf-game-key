#include "acllib.h"
#include <time.h>
const int winwidth = 640, winheight = 480;
ACL_Image tomimg, jerryimg;
const char *tom = "tom.bmp";
const char *jerry = "jerry.bmp";
//int tomwidth = 100, tomheight = 100;
//int jerrywidth = 50, jerryheight = 50;
void timerEvent(int id);
void keyEvent(int key, int e);
int movid = 0, movtimerinterval = 20;//jerry移动定时器
int createid = 1, createimerinterval = 1000;//Jerry产生定时器
//int  dist = 5;
//int x = 10, y = 10;
void paint();
const int maxnum = 10;

struct sprite
{
	//char *name;
	int x, y;
	int width, height;
	int distx, disty;//移动速度

};

struct sprite tomSprite, *jerrySprite[maxnum] = { NULL };//定义指针数组
int jerrynum = 0;


int Setup()
{
	srand((unsigned)time(NULL));//随机种子
	initWindow("elf-game", DEFAULT, DEFAULT, winwidth, winheight);//初始化窗口
	//loadImage(tom, &Img);//加载图片
	loadImage(tom, &tomimg);//加载图片，第一个为文件名，第二个为指向文件的地址
	loadImage(jerry, &jerryimg);
	tomSprite.x = rand() % (winwidth - tomSprite.width);
	tomSprite.y = rand() % (winheight - tomSprite.height);
	tomSprite.width = 100;
	tomSprite.height = 100;
	tomSprite.distx = 10;
	tomSprite.disty = 10;
	jerrySprite[jerrynum] = (struct sprite*)malloc(sizeof(struct sprite));//动态分配内存
	jerrySprite[jerrynum]->x = rand() % (winwidth - jerrySprite[jerrynum]->width);
	jerrySprite[jerrynum]->y = rand() % (winheight - jerrySprite[jerrynum]->height);
	jerrySprite[jerrynum]->width = 50;
	jerrySprite[jerrynum]->height = 50;
	jerrySprite[jerrynum]->distx = 2;
	jerrySprite[jerrynum]->disty = 2;
	registerTimerEvent(timerEvent);//注册定时器，定时器触发后发生的时间timerEvent
	startTimer(movid, movtimerinterval);//启动定时器,id用于区别不同的定时器，timerinterval为定时器触发的间隔
	startTimer(createid, createimerinterval);
	registerKeyboardEvent(keyEvent);//注册键盘处理函数
	paint();//画图
	return 0;
}


void timerEvent(int id)
{
	int i;
	if (id == 0)
	{
		for (i = 0; i < jerrynum; ++i)
		{
			if (jerrySprite[i])
			{
				jerrySprite[i]->x += jerrySprite[i]->distx;//jerry移动
				jerrySprite[i]->y += jerrySprite[i]->disty;
				if (jerrySprite[i]->x >= winwidth - jerrySprite[i]->width || jerrySprite[i]->x <= 0)
					jerrySprite[i]->distx *= -1;
				if (jerrySprite[i]->y >= winheight - jerrySprite[i]->height || jerrySprite[i]->y <= 0)
					jerrySprite[i]->disty *= -1;
			}
		}
	}
	if (id == 1)
	{
		if (jerrynum < maxnum)
			jerrynum++;

		if (jerrynum < maxnum&&jerrySprite[jerrynum] == NULL)
		{

			//jerrySprite[jerrynum] = (struct sprite*)malloc(sizeof(struct sprite));
			jerrySprite[jerrynum] = (struct sprite*)malloc(sizeof(struct sprite));
			jerrySprite[jerrynum]->width = 50;
			jerrySprite[jerrynum]->height = 50;
			jerrySprite[jerrynum]->distx = 2;
			jerrySprite[jerrynum]->disty = 2;
			jerrySprite[jerrynum]->x = rand() % (winwidth - jerrySprite[jerrynum]->width);
			jerrySprite[jerrynum]->y = rand() % (winheight - jerrySprite[jerrynum]->height);
			//注意在调试时将x,y的随机数产生语句放在最后才能正确产生Jerry
		}
	}
	paint();
}




void keyEvent(int key, int e)
{
	if (e != KEY_DOWN)return;
	switch (key)
	{
	case VK_UP:
		tomSprite.y -= tomSprite.disty;
		if (tomSprite.y <= 0)
		{
			tomSprite.y = 0;
		}
		break;
	case VK_DOWN:
		tomSprite.y += tomSprite.disty;
		if (tomSprite.y >= winheight - tomSprite.height)
		{
			tomSprite.y = winheight - tomSprite.height;
		}
		break;
	case VK_LEFT:
		tomSprite.x -= tomSprite.distx;
		if (tomSprite.x <= 0)
		{
			tomSprite.x = 0;
		}
		break;
	case VK_RIGHT:
		tomSprite.x += tomSprite.distx;
		if (tomSprite.x >= winwidth - tomSprite.width)
		{
			tomSprite.x = winwidth - tomSprite.width;
		}
		break;
	default:
		break;
	}
	paint();
}

void paint()//画图
{
	beginPaint();//开始画图
	clearDevice();//清屏
	putImageScale(&tomimg, tomSprite.x, tomSprite.y, tomSprite.width, tomSprite.height);//设置画图的位置以及图片的宽度和高度
	for (int i = 0; i < jerrynum - 1; ++i)
	{
		if (jerrySprite[i])
			putImageScale(&jerryimg, jerrySprite[i]->x, jerrySprite[i]->y, jerrySprite[i]->width, jerrySprite[i]->height);
	}
	endPaint();//结束画[jerrynum]->
}