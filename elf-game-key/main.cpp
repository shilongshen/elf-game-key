#include "acllib.h"
#include <time.h>
const int winwidth = 640, winheight = 480;
ACL_Image img;
const char *tom = "tom.bmp";
int tomwidth = 100, tomheight = 100;
//void timerEvent(int id);
void keyEvent(int key, int e);
int id = 0, timerinterval = 20;
int  dist = 5;
int x = 10, y = 10;
void paint();



int Setup()
{
	//srand((unsigned)time(NULL));
	initWindow("elf-game", DEFAULT, DEFAULT, winwidth, winheight);//初始化窗口
	//loadImage(tom, &img);//加载图片
	loadImage("tom.bmp", &img);//加载图片，第一个为文件名，第二个为指向文件的地址
	//registerTimerEvent(timerEvent);//注册定时器，定时器触发后发生的时间timerEvent
	//startTimer(id, timerinterval);//启动定时器,id用于区别不同的定时器，timerinterval为定时器触发的间隔
	registerKeyboardEvent(keyEvent);
	//x = rand() % winwidth;
	//y = rand() % winheight;
	paint();//画图
	return 0;
}

/*void timerEvent(int id)
{
	if (id == 0)
	{
		x += dist;//tom移动
		if (x > winwidth - tomwidth || x <= 0)//tom遇到边框反弹
		{
			dist *= -1;
		}
		paint();

	}
}
*/

void keyEvent(int key, int e)
{
	if (e != KEY_DOWN)return;
	switch (key)
	{
	case VK_UP:
		y -= dist;
		if (y <= 0)
		{
			y = 0;
		}
		break;
	case VK_DOWN:
		y += dist;
		if (y >= winheight - tomheight)
		{
			y = winheight - tomheight;
		}
		break;
	case VK_LEFT:
		x -= dist;
		if (x <= 0)
		{
			x = 0;
		}
		break;
	case VK_RIGHT:
		x += dist;
		if (x >= winwidth - tomwidth)
		{
			x = winwidth - tomwidth;
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
	putImageScale(&img, x, y, tomwidth, tomheight);//设置画图的位置以及图片的宽度和高度
	endPaint();//结束画图
}