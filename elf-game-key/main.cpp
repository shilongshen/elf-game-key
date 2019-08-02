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
	initWindow("elf-game", DEFAULT, DEFAULT, winwidth, winheight);//��ʼ������
	//loadImage(tom, &img);//����ͼƬ
	loadImage("tom.bmp", &img);//����ͼƬ����һ��Ϊ�ļ������ڶ���Ϊָ���ļ��ĵ�ַ
	//registerTimerEvent(timerEvent);//ע�ᶨʱ������ʱ������������ʱ��timerEvent
	//startTimer(id, timerinterval);//������ʱ��,id��������ͬ�Ķ�ʱ����timerintervalΪ��ʱ�������ļ��
	registerKeyboardEvent(keyEvent);
	//x = rand() % winwidth;
	//y = rand() % winheight;
	paint();//��ͼ
	return 0;
}

/*void timerEvent(int id)
{
	if (id == 0)
	{
		x += dist;//tom�ƶ�
		if (x > winwidth - tomwidth || x <= 0)//tom�����߿򷴵�
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

void paint()//��ͼ
{
	beginPaint();//��ʼ��ͼ
	clearDevice();//����
	putImageScale(&img, x, y, tomwidth, tomheight);//���û�ͼ��λ���Լ�ͼƬ�Ŀ�Ⱥ͸߶�
	endPaint();//������ͼ
}