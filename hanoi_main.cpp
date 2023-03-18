#include <iostream>
#include <time.h>
#include <conio.h>
#include "cmd_console_tools.h"
#include "hanoi.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

     ���ļ�Ҫ��
	1����������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ�֣�const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{


	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);

	int menu=0,times=-1,n=0;
	char src='0', dst='0', tmp='0';
	while (1)
	{
		menu = hanoi_menu();//�ò˵��������menu��ֵ
		if (menu == 0)
			return 0;
		else if (menu == 5)
		{
			cct_cls();
			draw();
		}
		else
		{
			cct_setcursor(2);//���ص�ȱʡ״̬
			readln(&src, &dst, &n, &times, menu);
			tmp = 3 * 'B' - dst - src;
		}//��ɲ���������
		if (menu == 1 || menu == 2 || menu == 3 || menu == 4)
		{
			init(n, src);//��ʼ��
			if (menu == 4)
			{
				cct_cls();
				cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �㣬��ʱ����Ϊ " << times << endl;
				printinit(n, src, dst, menu);
			}
			hanoi(n, src, tmp, dst, menu, times);//����һ���ݹ麯��
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
		cct_setcolor(0, 15);//�˵����������ɫ
		cct_setcursor(2);//���ص�ȱʡ��ʽ
		if (menu>=4)
			cct_gotoxy(0, 35);
		cout << "\n\n���س�������";
		while (_getch() != '\r')
			;
		cct_cls();
		clean();
	}
	return 0;
}
