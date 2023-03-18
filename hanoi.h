#pragma once

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
int hanoi_menu();//获取menu值并返回
void readln(char* p1, char* p2, int* p3, int* p4,int menu);//获取src，dst，等参数
void hanoi(int n, char src, char tmp, char dst, int menu,int times);//1,2,3,4,8共用一个递归函数
void init(int n, char src);//数组内部初始化
void clean();//一次完整菜单执行完后，重置数组等参数
void inittower(char src, char dst, int n);//画出柱子及初始状态
void printinit(int n, char src, char dst, int menu);
void draw();
void first(int n, char src, char tmp, char dst);
void game(int n, char src, char dst);
