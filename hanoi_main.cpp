#include <iostream>
#include <time.h>
#include <conio.h>
#include "cmd_console_tools.h"
#include "hanoi.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

     本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{


	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);

	int menu=0,times=-1,n=0;
	char src='0', dst='0', tmp='0';
	while (1)
	{
		menu = hanoi_menu();//用菜单函数获得menu的值
		if (menu == 0)
			return 0;
		else if (menu == 5)
		{
			cct_cls();
			draw();
		}
		else
		{
			cct_setcursor(2);//光标回到缺省状态
			readln(&src, &dst, &n, &times, menu);
			tmp = 3 * 'B' - dst - src;
		}//完成参数的输入
		if (menu == 1 || menu == 2 || menu == 3 || menu == 4)
		{
			init(n, src);//初始化
			if (menu == 4)
			{
				cct_cls();
				cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << times << endl;
				printinit(n, src, dst, menu);
			}
			hanoi(n, src, tmp, dst, menu, times);//共用一个递归函数
		}
		else if (menu == 6)
		{
			init(n, src);
			inittower(src, dst, n);
		}
		else if (menu == 7)
			first(n, src, tmp, dst);
		else if (menu == 8)
		{
			init(n, src);
			inittower(src, dst, n);
			printinit(n, src, dst, menu);
			hanoi(n, src, tmp, dst, menu, times);
		}
		else if (menu==9)
		{
			init(n, src);
			inittower(src, dst, n);
			printinit(n, src, dst, menu);
			game(n, src, dst);
		}
		cct_setcolor(0, 15);//菜单完成重置颜色
		cct_setcursor(2);//光标回到缺省方式
		if (menu>=4)
			cct_gotoxy(0, 35);
		cout << "\n\n按回车键继续";
		while (_getch() != '\r')
			;
		cct_cls();
		clean();
	}
	return 0;
}
