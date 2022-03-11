#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h >
#include<math.h>
#include<windows.h>
#include<mmsystem.h> 
#pragma warning(disable:4996)
#pragma comment(lib,"Winmm.lib")
int a[8][10], score = 0, step;
IMAGE img[7];
bool bottom1,bottom2;
char str1[20], str2[20];///留出2行2列做缓冲区 有效范围为中间6行8列
void lev0(), lev1(), lev2(), renew(), print_score(),music1(),music2(),save1(),save2(),readsave1(),readsave2();
int  isout(int x, int y), judge_1();
void  print(), print_new();
void eliminate_a(int x, int y, int m, int n), eliminate_b(int x, int y, int m, int n);
int main()
{
	loadimage(&img[0], _T("..\\icom\\2\\0.png"), 80, 80);
	loadimage(&img[1], _T("..\\icon\\2\\1.png"), 80, 80);
	loadimage(&img[2], _T("..\\icon\\2\\2.png"), 80, 80);
	loadimage(&img[3], _T("..\\icon\\2\\3.png"), 80, 80);
	loadimage(&img[4], _T("..\\icon\\2\\4.png"), 80, 80);
	loadimage(&img[5], _T("..\\icon\\2\\5.png"), 80, 80);
	loadimage(&img[6], _T("..\\icon\\2\\6.png"), 80, 80);
	lev0();
	return 0;
}
void lev0()///加载初始界面
{
	initgraph(800, 500);
	IMAGE img1;
	loadimage(&img1, _T("..\\background\\4.png"), 800, 550);///把图像导入并拉伸放入img中，(宽，高)
	putimage(0, 0, &img1);///屏幕上输出位图

	///第一个矩形坐标
	rectangle(45, 54, 290, 125);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 0, "开始新游戏");
	outtextxy(60, 67, "开始新游戏");

	/// 第二个矩形坐标
	rectangle(45, 168, 270, 239);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 0, "继续第一关");
	outtextxy(60, 185, "继续第一关");

	rectangle(45, 330, 270, 400);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 0, "继续第二关");
	outtextxy(60, 345, "继续第二关");

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, "Ps:若无存档，请勿点击上面两个按钮");
	outtextxy(20, 425, "Ps:若无存档，请勿点击上面两个按钮");

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, "注：第二关请保存存档，否则只能从第一关进入");
	outtextxy(20, 450, "注：第二关请保存存档，否则只能从第一关进入");

	MOUSEMSG m;
	while (!_kbhit())///有键盘输入返回1，非键盘输入返回0；
	{
		if (MouseHit())///如果存在鼠标消息，返回 true；否则返回 false
		{
			m = GetMouseMsg();
			switch (m.uMsg)///对鼠标消息进行分类
			{
			case WM_LBUTTONDOWN:///鼠标左键
				if ((m.x >= 45 && m.x <= 304) && (m.y >= 54 && m.y <= 125))///开始新游戏
				{
					bottom1 = true;
					score = 0;
					step = 20;
					music1();
					renew();
					lev1();
				}
				if ((m.x >= 45 && m.x <= 270) && (m.y >= 170 && m.y <= 240))///继续第一关
				{
					bottom1 = true;
					music1();
					readsave1();
					lev1();
				}
				if ((m.x >= 45 && m.x <= 270) && (m.y >= 330 && m.y <= 400))///继续第二关
				{
					bottom2 = true;
					music2();
					readsave2();
					lev2();
				}
				break;
			}
		}
	}
	getchar();
}
void lev1()///加载第一关
{
	closegraph();
	bool flag1 = false, flag2 = false;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int temp;

	initgraph(1000, 600);
	rectangle(180, 120, 820, 600);

	sprintf(str1, "剩余步数：%d", step);
	settextstyle(20, 0, str1);
	outtextxy(20, 20, str1);

	settextstyle(20, 0, "目标分数：50");
	outtextxy(20, 60, "目标分数：50");

	sprintf(str2, "分数：%d", score);
	settextstyle(20, 0, str2);
	outtextxy(20, 100, str2);

	settextstyle(20, 0, "规则：");
	outtextxy(840, 10, "规则：");

	settextstyle(15, 0, "拖动交换，分数达到目");
	outtextxy(840, 40, "拖动交换，分数达到目");

	settextstyle(15, 0, "标分数可进入下一关");
	outtextxy(840, 65, "标分数可进入下一关");

	settextstyle(15, 0, "(无解可手动刷新)");
	outtextxy(840, 90, "(无解可手动刷新)");

	settextstyle(20, 0, "Ps:");
	outtextxy(840, 480, "Ps:");

	settextstyle(15, 0, "初始化界面可能有些慢");
	outtextxy(840, 520, "初始化界面可能有些慢");

	settextstyle(15, 0, "请耐心等待");
	outtextxy(840, 545, "请耐心等待");

	settextstyle(30, 0, "重玩本关");
	outtextxy(30, 370, "重玩本关");

	settextstyle(30, 0, "下一关");
	outtextxy(35, 420, "下一关");

	settextstyle(30, 0, "保存");
	outtextxy(42, 470, "保存");

	settextstyle(30, 0, "退出");
	outtextxy(42, 520, "退出");

	settextstyle(30, 0, "刷新");
	outtextxy(850, 310, "刷新");

	print();
	music1();
	MOUSEMSG m;
	while (!_kbhit())///有键盘输入返回1，非键盘输入返回0；
	{
		if (MouseHit())///如果存在鼠标消息，返回 true；否则返回 false
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)///鼠标左键
			{
				if ((m.x >= 30 && m.x <= 150) && (m.y >= 370 && m.y <= 400))///重玩本关
				{
					score = 0;
					step = 20;
					music1();
					renew();
					lev1();
				}
				if ((m.x >= 35 && m.x <= 200) && (m.y >= 420 && m.y <= 450) && score >= 50)///加载下一关
				{
					renew();
					bottom2 = true;
					score = 0;
					step = 40;
					lev2();
				}
				if ((m.x >= 40 && m.x <= 100) && (m.y >= 470 && m.y <= 500))///保存
				{
					save1();
				}
				if ((m.x >= 40 && m.x <= 95) && (m.y >= 520 && m.y <= 550))///回到主界面
				{
					bottom1 = false;
					music1();
					lev0();
				}
				if ((m.x >= 850 && m.x <= 900) && (m.y >= 310 && m.y <= 340))
				{
					clearrectangle(180, 120, 820, 600);
					renew();
					print();
				}
				y1 = (m.x - 180) / 80 + 1;
				x1 = (m.y - 120) / 80 + 1;
				flag1 = true;
			}
			else if (m.uMsg == WM_LBUTTONUP)
			{
				y2 = (m.x - 180) / 80 + 1;
				x2 = (m.y - 120) / 80 + 1;
				if (flag1 && !isout(x1, y1) && !isout(x2, y2) && step > 0)
				{
					if ((m.x >= 180 && m.x <= 820) && (m.y >= 120 && m.y <= 600))
					{
						if (((x1 == x2) && (abs(y1 - y2) <= 1)) || ((y1 == y2) && (abs(x1 - x2) <= 1)))
						{
							clearrectangle(180, 120, 820, 600);
							temp = a[x1][y1];
							a[x1][y1] = a[x2][y2];
							a[x2][y2] = temp;
							print();
							Sleep(300);
							if (!judge_1())
							{
								clearrectangle(180, 120, 820, 600);
								temp = a[x1][y1];
								a[x1][y1] = a[x2][y2];
								a[x2][y2] = temp;
								print();
							}
							else
							{
								if (a[x1][y1] != a[x2][y2])
								{
									clearrectangle(15, 15, 150, 45);
									sprintf(str1, "剩余步数：%d", --step);
									settextstyle(20, 0, str1);
									outtextxy(20, 20, str1);
								}
								clearrectangle(180, 120, 820, 600);
								print_new();
							}
						}
					}
					if (score >= 50)
					{
						settextstyle(50, 0, "恭喜通过本关！！！");
						outtextxy(300, 60, "恭喜通过本关！！！");
					}
					if (step == 0 && score < 50)
					{
						settextstyle(50, 0, "真遗憾，闯关失败");
						outtextxy(300, 60, "真遗憾，闯关失败");
					}
					flag1 = false;
				}
			}
		}
	}
	getchar();
}
void lev2()///加载第二关
{
	closegraph();
	bool flag1 = false, flag2 = false;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int temp;
	initgraph(1000, 600);
	rectangle(180, 120, 820, 600);

	sprintf(str1, "剩余步数：%d", step);
	settextstyle(20, 0, str1);
	outtextxy(20, 20, str1);

	settextstyle(20, 0, "目标分数：300");
	outtextxy(20, 60, "目标分数：300");

	sprintf(str2, "分数：%d", score);
	settextstyle(20, 0, str2);
	outtextxy(20, 100, str2);

	settextstyle(20, 0, "规则：");
	outtextxy(840, 10, "规则：");

	settextstyle(15, 0, "分数达到即可通关");
	outtextxy(840, 40, "分数到达即可通关");

	settextstyle(15, 0, "（可手动刷新）");
	outtextxy(840, 65, "（可手动刷新）");

	settextstyle(20, 0, "Ps:");
	outtextxy(840, 480, "Ps:");

	settextstyle(15, 0, "初始化界面可能有些慢");
	outtextxy(840, 520, "初始化界面可能有些慢");

	settextstyle(15, 0, "请耐心等待");
	outtextxy(840, 545, "请耐心等待");

	settextstyle(30, 0, "上一关");
	outtextxy(40, 370, "上一关");

	settextstyle(30, 0, "重玩本关");
	outtextxy(40, 420, "重玩本关");

	settextstyle(30, 0, "保存");
	outtextxy(42, 470, "保存");

	settextstyle(30, 0, "退出");
	outtextxy(42, 520, "退出");

	settextstyle(30, 0, "刷新");
	outtextxy(850, 310, "刷新");

	print();
	music2();
	MOUSEMSG m;
	while (!_kbhit())///有键盘输入返回1，非键盘输入返回0；
	{
		if (MouseHit())///如果存在鼠标消息，返回 true；否则返回 false
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)///鼠标左键
			{
				if ((m.x >= 40 && m.x <= 120) && (m.y >= 370 && m.y <= 400))///回到上一关
				{
					bottom1 = true;
					renew();
					score = 0;
					step = 20;
					lev1();
					music1();
				}
				if ((m.x >= 30 && m.x <= 150) && (m.y >= 420 && m.y <= 450))///重玩本关
				{
					bottom2 = true;
					step = 40;
					score = 0;
					renew();
					lev2();
					music2();
				}
				if ((m.x >= 40 && m.x <= 100) && (m.y >= 470 && m.y <= 500))///保存
				{
					save2();
				}
				if ((m.x >= 40 && m.x <= 95) && (m.y >= 520 && m.y <= 550))///回到主界面
				{
					bottom2 = false;
					music2();
					lev0();

				}
				if ((m.x >= 850 && m.x <= 900) && (m.y >= 310 && m.y <= 340))///无解刷新
				{
					clearrectangle(180, 120, 820, 600);
					renew();
					print();
				}
				y1 = (m.x - 180) / 80 + 1;
				x1 = (m.y - 120) / 80 + 1;
				flag1 = true;
			}
			else if (m.uMsg == WM_LBUTTONUP)
			{
				y2 = (m.x - 180) / 80 + 1;
				x2 = (m.y - 120) / 80 + 1;
				if (flag1 && !isout(x1, y1) && !isout(x2, y2) && step > 0)
				{
					if ((m.x >= 180 && m.x <= 820) && (m.y >= 120 && m.y <= 600))
					{
						if (((x1 == x2) && (abs(y1 - y2) <= 1)) || ((y1 == y2) && (abs(x1 - x2) <= 1)))
						{							
							clearrectangle(180, 120, 820, 600);
							temp = a[x1][y1];
							a[x1][y1] = a[x2][y2];
							a[x2][y2] = temp;
							print();
							Sleep(300);
							if (!judge_1())
							{
								clearrectangle(180, 120, 820, 600);
								temp = a[x1][y1];
								a[x1][y1] = a[x2][y2];
								a[x2][y2] = temp;
								print();
							}
							else
							{
								if (a[x1][y1] != a[x2][y2])
								{
									clearrectangle(15, 15, 150, 45);
									sprintf(str1, "剩余步数：%d", --step);
									settextstyle(20, 0, str1);
									outtextxy(20, 20, str1);
								}
								clearrectangle(180, 120, 820, 600);
								print_new();
							}
						}
					}
					if (score >= 300)
					{
						settextstyle(50, 0, "恭喜通过本关！！！");
						outtextxy(300, 60, "恭喜通过本关！！！");
					}
					if (step == 0 && score < 300)
					{
						settextstyle(50, 0, "真遗憾，闯关失败");
						outtextxy(300, 60, "真遗憾，闯关失败");
					}
					flag1 = false;
				}
			}
		}
	}
	getchar();
}
void renew()///生成二维数组
{
	srand((unsigned)time(NULL));
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 8; j++)
		{
			a[i][j] = rand() % 6;
			while ((j >= 3 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2]) || (i >= 3 && a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j]))
				a[i][j] = rand() % 6;
		}
}
int judge_1()///单独判断是否有3成串
{
	int k = 0;
	for (int i = 1; i <= 6 && k == 0; i++)
		for (int j = 1; j <= 6 && k == 0; j++)
		{
			if ((a[i][j] == a[i][j + 1]) && (a[i][j] == a[i][j + 2]))
			{
				k = 1;
				break;
			}
		}
	for (int i = 1; i <= 4 && k == 0; i++)
		for (int j = 1; j <= 8 && k == 0; j++)
		{
			if (a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j])
			{
				k = 1;
				break;
			}
		}
	if (k == 1)
		return 1;
	if (k == 0)
		return 0;
}
void print()///输出移动后的图
{
	int x = 0, y = 0;
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 8; j++)
		{
			if (a[i][j] == 0)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x,y,&img[0]);

			}
			if (a[i][j] == 1)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x, y, &img[1]);
			}
			if (a[i][j] == 2)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x, y, &img[2]);
			}
			if (a[i][j] == 3)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x, y, &img[3]);
			}
			if (a[i][j] == 4)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x, y, &img[4]);
			}
			if (a[i][j] == 5)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x, y, &img[5]);
			}
			if (a[i][j] == 6)
			{
				x = 180 + (j - 1) * 80;
				y = 120 + (i - 1) * 80;
				putimage(x, y, &img[6]);
			}
		}
}
void print_new()///输出移动后并消除后的图
{
	while (judge_1())
	{
	here:
		for (int i = 1; i <= 6; i++)///消去横的5个
			for (int j = 1; j <= 6; j++)
			{
				if ((a[i][j] == a[i][j + 1]) && (a[i][j] == a[i][j + 2]) && (a[i][j] == a[i][j + 3]) && (a[i][j] == a[i][j + 4]))
				{
					if (i == 1)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180 + (j - 1) * 80, 120 + (i - 1) * 80, 180 + (j + 4) * 80, i * 80 + 120);
						Sleep(100);
						eliminate_a(j - 1, i - 1, j + 4, i);
						a[i][j] = rand() % 6;
						a[i][j + 1] = rand() % 6;
						a[i][j + 2] = rand() % 6;
						a[i][j + 3] = rand() % 6;
						a[i][j + 4] = rand() % 6;
						score += 5;
						clearrectangle(180, 120, 820, 600);
						print();
						print_score();
						Sleep(100);
						goto here;
					}
					else
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(300);
						clearrectangle(180, 120, 820, 600);
						clearrectangle(180 + (j - 1) * 80, 120 + (i - 1) * 80, 180 + (j + 4) * 80, i * 80 + 120);
						a[i][j] = 6;
						a[i][j + 1] = 6;
						a[i][j + 2] = 6;
						a[i][j + 3] = 6;
						a[i][j + 4] = 6;
						print();
						Sleep(100);
						eliminate_a(j - 1, i - 1, j + 4, i);
						for (int m = i; m >= 2; m--)
						{
							for (int n = 0; n <= 4; n++)
							{
								a[m][j + n] = a[m - 1][j + n];
								a[m - 1][j + n] = 6;
							}
							clearrectangle(180, 120, 820, 600);
							print();
							Sleep(100);
						}
						clearrectangle(180, 120, 820, 600);
						a[1][j] = rand() % 6;
						a[1][j + 1] = rand() % 6;
						a[1][j + 2] = rand() % 6;
						a[1][j + 3] = rand() % 6;
						a[1][j + 4] = rand() % 6;
						print();
						score += 5;
						print_score();
						Sleep(100);
						goto here;
					}

				}
			}
		for (int i = 1; i <= 2; i++)///消去竖的5个
			for (int j = 1; j <= 8; j++)
			{
				if ((a[i][j] == a[i + 1][j]) && (a[i][j] == a[i + 2][j]) && (a[i][j] == a[i + 3][j]) && (a[i][j] == a[i + 4][j]))
				{
					if (i == 1)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 4) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						a[i + 3][j] = 6;
						a[i + 4][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 4);
						Sleep(100);
						for (int m = i; m <= i + 4; m++)
						{
							a[1][j] = rand() % 6;
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i + 1; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							print();
							Sleep(100);
						}
						score += 5;
						print_score();
						goto here;
					}
					if (i == 2)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 4) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						a[i + 3][j] = 6;
						a[i + 4][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 4);
						Sleep(100);
						for (int m = i; m <= i + 4; m++)
						{
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i; n--)
							{
								a[n][j] = a[n - 1][j];
								a[1][j] = rand() % 6;
							}
							print();
							Sleep(100);
						}
						score += 5;
						print_score();
						goto here;
					}
				}
			}
		for (int i = 1; i <= 6; i++)///消去横的4个
			for (int j = 1; j <= 6; j++)
			{
				if ((a[i][j] == a[i][j + 1]) && (a[i][j] == a[i][j + 2]) && (a[i][j] == a[i][j + 3]))
				{
					if (i == 1)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						print();
						eliminate_a(j - 1, i - 1, j + 3, i);
						clearrectangle(180 + (j - 1) * 80, 120 + (i - 1) * 80, 180 + (j + 3) * 80, i * 80 + 120);
						Sleep(100);
						a[i][j] = rand() % 6;
						a[i][j + 1] = rand() % 6;
						a[i][j + 2] = rand() % 6;
						a[i][j + 3] = rand() % 6;
						score += 4;
						clearrectangle(180, 120, 820, 600);
						print();
						print_score();
						Sleep(100);
						goto here;
					}
					else
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle(180 + (j - 1) * 80, 120 + (i - 1) * 80, 180 + (j + 3) * 80, i * 80 + 120);
						a[i][j] = 6;
						a[i][j + 1] = 6;
						a[i][j + 2] = 6;
						a[i][j + 3] = 6;
						print();
						eliminate_a(j - 1, i - 1, j + 3, i);
						Sleep(100);
						for (int m = i; m >= 2; m--)
						{
							for (int n = 0; n <= 3; n++)
							{
								a[m][j + n] = a[m - 1][j + n];
								a[m - 1][j + n] = 6;
							}
							clearrectangle(180, 120, 820, 600);
							print();
							Sleep(100);
						}
						clearrectangle(180, 120, 820, 600);
						a[1][j] = rand() % 6;
						a[1][j + 1] = rand() % 6;
						a[1][j + 2] = rand() % 6;
						a[1][j + 3] = rand() % 6;
						print();
						score += 4;
						print_score();
						Sleep(100);
						goto here;
					}
				}
			}
		for (int i = 1; i <= 3; i++)///消去竖的4个
			for (int j = 1; j <= 8; j++)
			{
				if ((a[i][j] == a[i + 1][j]) && (a[i][j] == a[i + 2][j]) && (a[i][j] == a[i + 3][j]))
				{
					if (i == 1)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 3) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						a[i + 3][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 3);
						Sleep(100);
						for (int m = i; m <= i + 3; m++)
						{
							a[1][j] = rand() % 6;
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i + 1; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							print();
							Sleep(100);
						}
						score += 4;
						print_score();
						goto here;
					}
					if (i == 2)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 3) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						a[i + 3][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 3);
						Sleep(100);
						for (int m = i; m <= i + 3; m++)
						{
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							a[1][j] = rand() % 6;
							print();
							Sleep(100);
						}
						score += 4;
						print_score();
						goto here;
					}
					if (i == 3)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 3) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						a[i + 3][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 3);
						Sleep(100);
						for (int m = i; m <= i + 3; m++)
						{
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i - 1; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							a[1][j] = rand() % 6;
							print();
							Sleep(100);
						}
						score += 4;
						print_score();
						goto here;
					}
				}
			}
		for (int i = 1; i <= 6; i++)///消去横的3个
			for (int j = 1; j <= 6; j++)
			{
				if ((a[i][j] == a[i][j + 1]) && (a[i][j] == a[i][j + 2]))
				{
					if (i == 1)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(300);
						clearrectangle(180, 120, 820, 600);
						clearrectangle(180 + (j - 1) * 80, 120 + (i - 1) * 80, 180 + (j + 2) * 80, i * 80 + 120);
						print();
						eliminate_a(j - 1, i - 1, j + 2, i);
						Sleep(100);
						a[i][j] = rand() % 6;
						a[i][j + 1] = rand() % 6;
						a[i][j + 2] = rand() % 6;
						score += 3;
						clearrectangle(180, 120, 820, 600);
						print();
						print_score();
						Sleep(100);
						goto here;

					}
					else
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle(180 + (j - 1) * 80, 120 + (i - 1) * 80, 180 + (j + 2) * 80, i * 80 + 120);
						a[i][j] = 6;
						a[i][j + 1] = 6;
						a[i][j + 2] = 6;
						print();
						eliminate_a(j - 1, i - 1, j + 2, i);
						Sleep(100);
						for (int m = i; m >= 2; m--)
						{
							for (int n = 0; n <= 2; n++)
							{
								a[m][j + n] = a[m - 1][j + n];
								a[m - 1][j + n] = 6;
							}
							clearrectangle(180, 120, 820, 600);
							print();
							Sleep(100);
						}
						clearrectangle(180, 120, 820, 600);
						a[1][j] = rand() % 6;
						a[1][j + 1] = rand() % 6;
						a[1][j + 2] = rand() % 6;
						print();
						score += 3;
						print_score();
						Sleep(100);
						goto here;
					}
				}
			}
		for (int i = 1; i <= 4; i++)///消去竖的3个
			for (int j = 1; j <= 8; j++)
			{
				if (a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j])
				{
					if (i == 1)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 2) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 2);
						Sleep(100);
						for (int m = i; m <= i + 2; m++)
						{
							a[1][j] = rand() % 6;
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i + 1; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							print();
							Sleep(100);
						}
						score += 3;
						print_score();
						goto here;
					}
					if (i == 2)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 2) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 2);
						print();
						Sleep(100);
						for (int m = i; m <= i + 2; m++)
						{
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							a[1][j] = rand() % 6;
							print();
							Sleep(100);
						}
						score += 3;
						print_score();
						goto here;
					}
					if (i == 3)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 2) * 80 + 120);
						a[i][j] = 6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 2);
						Sleep(100);
						for (int m = i; m <= i + 2; m++)
						{
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i - 1; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							a[1][j] = rand() % 6;
							print();
							Sleep(100);
						}
						score += 3;
						print_score();
						goto here;
					}
					if (i == 4)
					{
						clearrectangle(180, 120, 820, 600);
						print();
						Sleep(100);
						clearrectangle(180, 120, 820, 600);
						clearrectangle((j - 1) * 80 + 180, (i - 1) * 80 + 120, j * 80 + 180, (i + 2) * 80 + 120);
						a[i][j] =6;
						a[i + 1][j] = 6;
						a[i + 2][j] = 6;
						print();
						eliminate_b(j - 1, i - 1, j, i + 2);
						Sleep(100);
						for (int m = i; m <= i + 2; m++)
						{
							clearrectangle(180, 120, 820, 600);
							for (int n = m; n >= i - 2; n--)
							{
								a[n][j] = a[n - 1][j];
							}
							a[1][j] = rand() % 6;
							print();
							Sleep(100);
						}
						score += 3;
						print_score();
						goto here;
					}
				}
			}
	}
	clearrectangle(180, 120, 820, 600);
	print();
	Sleep(300);
}
void print_score()///更新分数
{
	clearrectangle(18, 100, 120, 120);
	sprintf(str2, "分数：%d", score);
	settextstyle(20, 0, str2);
	outtextxy(20, 100, str2);
}
int isout(int x, int y)///判断是否出矩形界
{
	if (x > 6 || x < 1 || y>8 || y < 1)
		return 1;
	else
		return 0;
}
void eliminate_a(int x, int y, int m, int n)///消除行时产生的动画
{

	IMAGE picture[8];
	loadimage(&picture[1], "..\\img\\lightning\\1.png", (m - x) * 80, (n - y) * 80);
	loadimage(&picture[2], "..\\img\\lightning\\2.png", (m - x) * 80, (n - y) * 80);
	loadimage(&picture[3], "..\\img\\lightning\\3.png", (m - x) * 80, (n - y) * 80);
	loadimage(&picture[4], "..\\img\\lightning\\4.png", (m - x) * 80, (n - y) * 80);
	loadimage(&picture[5], "..\\img\\lightning\\5.png", (m - x) * 80, (n - y) * 80);
	loadimage(&picture[6], "..\\img\\lightning\\6.png", (m - x) * 80, (n - y) * 80);
	loadimage(&picture[7], "..\\img\\lightning\\7.png", (m - x) * 80, (n - y) * 80);
	/*for (int i = 0; i <= 16; i++)
	{
		putimage(180 + (x-1) * 80, 120 + (y-1) * 80, (m - x) * 80, (n - y) * 80, &picture, 25, i*128);
		Sleep(100);
	}
	*/
	for (int i = 1; i <= 7; i++)
	{
		putimage(180 + x * 80, 120 + y * 80, &picture[i]);
		Sleep(200);
	}
	Sleep(400);
}
void eliminate_b(int x, int y, int m, int n)///消除列时产生的动画
{
	IMAGE picture;
	loadimage(&picture, "..\\img\\burst\\explosion1.png");
	for (int i = 0; i <= 16; i++)
	{
		putimage(180 + x * 80, 120 + y * 80, (m - x) * 80, (n - y) * 80, &picture, 25, i * 128);
		Sleep(100);
	}
	Sleep(500);
}
void music1()///加载背景音乐bk
{
	mciSendString("open ..\\music\\bk.mp3 alias bk", NULL, 0, NULL);
	if(!bottom1)
		mciSendString("close bk", NULL, 0, NULL);
	else
	{
		mciSendString("close bk1", NULL, 0, NULL);
		mciSendString("stop bk", NULL, 0, NULL);
		mciSendString("play bk ", NULL, 0, NULL);
	}
}
void music2()///加载背景音乐bk1
{
	mciSendString("open ..\\music\\bk1.mp3 alias bk1", NULL, 0, NULL);
	if (!bottom2)
		mciSendString("close bk1", NULL, 0, NULL);
	else
	{
		mciSendString("close bk", NULL, 0, NULL);
		mciSendString("stop bk1 ", NULL, 0, NULL);
		mciSendString("play bk1 ", NULL, 0, NULL);
	}
}
void save1()///保存关卡1的存档
{
	char t[20];
	sprintf_s(t, "del memory1.txt");
	system(t);
	FILE* doc;
	doc = fopen("memory1.txt", "w+");
	for (int i = 1; i <= 6; i++)
			for (int j = 1; j <= 8; j++)
				fwrite(&a[i][j], sizeof(a[i][j]), 1, doc);
		fwrite(&score, sizeof(score), 1, doc);
		fwrite(&step, sizeof(step), 1, doc);
		fclose(doc);
		closegraph();
		exit(0);
}
void readsave1()///读取关卡1的存档
{
	FILE* doc;
	doc = fopen("memory1.txt", "r");
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 8; j++)
			fread(&a[i][j], sizeof(a[i][j]), 1, doc);
	fread(&score, sizeof(score), 1, doc);
	fread(&step, sizeof(step), 1, doc);
	fclose(doc);
}
void save2()///保存关卡2的存档
{
	char t[20];
	sprintf_s(t, "del memory2.txt");
	system(t);
	FILE* doc;
	doc = fopen("memory2.txt", "w+");
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			fwrite(&a[i][j], sizeof(a[i][j]), 1, doc);
		}
	}
	fwrite(&score, sizeof(score), 1, doc);
	fwrite(&step, sizeof(step), 1, doc);
	fclose(doc);
	closegraph();
	exit(0);
}
void readsave2()///读取关卡2的存档
{
	FILE* doc;
	doc = fopen("memory2.txt", "r");
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 8; j++)
			fread(&a[i][j], sizeof(a[i][j]), 1, doc);
	fread(&score, sizeof(score), 1, doc);
	fread(&step, sizeof(step), 1, doc);
	fclose(doc);
}