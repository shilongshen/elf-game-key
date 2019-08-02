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
int movid = 0, movtimerinterval = 20;//jerry�ƶ���ʱ��
int createid = 1, createimerinterval = 1000;//Jerry������ʱ��
//int  dist = 5;
//int x = 10, y = 10;
void paint();
const int maxnum = 10;

struct sprite
{
	//char *name;
	int x, y;
	int width, height;
	int distx, disty;//�ƶ��ٶ�

};

struct sprite tomSprite, *jerrySprite[maxnum] = { NULL };//����ָ������
int jerrynum = 0;


int Setup()
{
	srand((unsigned)time(NULL));//�������
	initWindow("elf-game", DEFAULT, DEFAULT, winwidth, winheight);//��ʼ������
	//loadImage(tom, &Img);//����ͼƬ
	loadImage(tom, &tomimg);//����ͼƬ����һ��Ϊ�ļ������ڶ���Ϊָ���ļ��ĵ�ַ
	loadImage(jerry, &jerryimg);
	tomSprite.x = rand() % (winwidth - tomSprite.width);
	tomSprite.y = rand() % (winheight - tomSprite.height);
	tomSprite.width = 100;
	tomSprite.height = 100;
	tomSprite.distx = 10;
	tomSprite.disty = 10;
	jerrySprite[jerrynum] = (struct sprite*)malloc(sizeof(struct sprite));//��̬�����ڴ�
	jerrySprite[jerrynum]->x = rand() % (winwidth - jerrySprite[jerrynum]->width);
	jerrySprite[jerrynum]->y = rand() % (winheight - jerrySprite[jerrynum]->height);
	jerrySprite[jerrynum]->width = 50;
	jerrySprite[jerrynum]->height = 50;
	jerrySprite[jerrynum]->distx = 2;
	jerrySprite[jerrynum]->disty = 2;
	registerTimerEvent(timerEvent);//ע�ᶨʱ������ʱ������������ʱ��timerEvent
	startTimer(movid, movtimerinterval);//������ʱ��,id��������ͬ�Ķ�ʱ����timerintervalΪ��ʱ�������ļ��
	startTimer(createid, createimerinterval);
	registerKeyboardEvent(keyEvent);//ע����̴�����
	paint();//��ͼ
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
				jerrySprite[i]->x += jerrySprite[i]->distx;//jerry�ƶ�
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
			//ע���ڵ���ʱ��x,y�������������������������ȷ����Jerry
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

void paint()//��ͼ
{
	beginPaint();//��ʼ��ͼ
	clearDevice();//����
	putImageScale(&tomimg, tomSprite.x, tomSprite.y, tomSprite.width, tomSprite.height);//���û�ͼ��λ���Լ�ͼƬ�Ŀ�Ⱥ͸߶�
	for (int i = 0; i < jerrynum - 1; ++i)
	{
		if (jerrySprite[i])
			putImageScale(&jerryimg, jerrySprite[i]->x, jerrySprite[i]->y, jerrySprite[i]->width, jerrySprite[i]->height);
	}
	endPaint();//������[jerrynum]->
}