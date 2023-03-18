#pragma once

/* ------------------------------------------------------------------------------------------------------

     ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */
int hanoi_menu();//��ȡmenuֵ������
void readln(char* p1, char* p2, int* p3, int* p4,int menu);//��ȡsrc��dst���Ȳ���
void hanoi(int n, char src, char tmp, char dst, int menu,int times);//1,2,3,4,8����һ���ݹ麯��
void init(int n, char src);//�����ڲ���ʼ��
void clean();//һ�������˵�ִ�������������Ȳ���
void inittower(char src, char dst, int n);//�������Ӽ���ʼ״̬
void printinit(int n, char src, char dst, int menu);
void draw();
void first(int n, char src, char tmp, char dst);
void game(int n, char src, char dst);
