#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

     ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
const int portx = 11, porty = 12;//���������A���ĵ�����  y+15
const int bg_color = 15, fg_color = 7, rpt=23;
const int basex = 12, basey = 15;//����A�����ĵ�����
int sum = 0;
int a[11] = { 0 }, b[11] = { 0 }, c[11] = { 0 };
int topa = 0, topb = 0, topc = 0;

void anime(int n, char src, char dst,int times);//��������
/***************************************************************************
  �������ƣ�
  ��    �ܣ����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void readln(char* p1, char* p2, int* p3, int* p4,int menu) 
{
	char src, dst;
	int times,n;
    while (1)
    {
        cout << "�����뺺ŵ���Ĳ���(1-10)" << endl;
        cin >> n;
        if (n >= 1 && n <= 10 && cin.good())//������ȷ����ջ�����
        {
            cin.ignore(1024, '\n');
            break;
        }
        else//���������ջ���������������
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }
    *p3 = n;
    while (1)
    {
        cout << "��������ʼ��(A-C)" << endl;
        cin >> src;
        if ((src == 'A' || src == 'B' || src == 'C' || src == 'a' || src == 'b' || src == 'c') && cin.good())//������ȷ����ջ�����
        {
            cin.ignore(1024, '\n');
            break;
        }
        else//���������ջ���������������
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }
    if (src != 'A' && src != 'B' && src != 'C')//����ʼ����Ϊ��д��ĸ
        src = src + 'A' - 'a';
    *p1 = src;
    while (1)
    {
        cout << "������Ŀ����(A-C)" << endl;
        cin >> dst;
        if ((dst == 'A' || dst == 'B' || dst == 'C' || dst == 'a' || dst == 'b' || dst == 'c') && dst != src && dst + 'A' - 'a' != src && cin.good())
        {
            cin.ignore(1024, '\n');
            break;
        }
        else if ((cin.good() == 0) || (dst != 'A' && dst != 'B' && dst != 'C' && dst != 'a' && dst != 'b' && dst != 'c'))
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(1024, '\n');
            if (dst != 'A' && dst != 'B' && dst != 'C')//��Ŀ������Ϊ��д��ĸ
                dst = dst + 'A' - 'a';
            cout << "Ŀ����(" << dst << ")��������ʼ��(" << src << ")��ͬ" << endl;
        }
    }
    if (dst != 'A' && dst != 'B' && dst != 'C')//��Ŀ������Ϊ��д��ĸ
        dst = dst + 'A' - 'a';
    *p2 = dst;
    while (menu==4 || menu==8)
    {
        cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)";
        cin >> times;
        if (times >= 0 && times <= 5 && cin.good())
        {
            *p4 = times;
            break;
        }
        else if (!cin.good())
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    } 
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ����������
  ���������
  �� �� ֵ��
  ˵    ����1,2����
***************************************************************************/
void basic(int n, char src, char dst, int menu)
{
    if (menu==1)
        cout << n << "# " << src << "---->" << dst<<endl;
    else
        cout << "��" << setw(4) << sum << " ��" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ��������ʼ��
  ���������
  �� �� ֵ��
  ˵    ����0Ϊ����
***************************************************************************/
void init(int n, char src)
{
    int i;
    for (i = 1; i <= n; i++)//����ʼ��Ų����ʼ����
    {
        if (src == 'A')
        {
            a[i - 1] = n - i + 1;
            topa = n;
        }
        else if (src == 'B')
        {
            b[i - 1] = n - i + 1;
            topb = n;
        }
        else
        {
            c[i - 1] = n - i + 1;
            topc = n;
        }
    }
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�Ų�������ڲ�ֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void movet(int n, char src, char dst)
{
    if (src == 'A')
        a[--topa] = 0;
    else if (src == 'B')
        b[--topb] = 0;
    else
        c[--topc] = 0;
    if (dst == 'A')
        a[topa++] = n;
    else if (dst == 'B')
        b[topb++] = n;
    else
        c[topc++] = n;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ������������
  ���������
  �� �� ֵ��
  ˵    ����3,4,8���ã�����Ų������ֵ
***************************************************************************/
void trans(int n, char src, char dst, bool k)
{
    int i;
    cct_setcursor(3);//����ʾ���
    cct_setcolor(0, 7);//����Ϊ��׼��ɫ
    if (k)//��ʼ��ʾʱ����ʾ�þ�
    {
        cout << "��" << setw(4) << sum << " ��(" << setw(2) << n << "#: " << src << "-->" << dst << ")  ";
    }
    cout << "A:";
    for (i = 0; i < 10; i++)
    {
        if (a[i] != 0)
            cout << setw(2) << a[i];
        else
            cout << setw(2) << " ";
    }
    cout << " B:";
    for (i = 0; i < 10; i++)
    {
        if (b[i] != 0)
            cout << setw(2) << b[i];
        else
            cout << setw(2) << " ";
    }
    cout << " C:";
    for (i = 0; i < 10; i++)
    {
        if (c[i] != 0)
            cout << setw(2) << c[i];
        else
            cout << setw(2) << " ";
    }
    cout << endl;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ����Ļ���,��������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void printinit(int n, char src, char dst, int menu)
{
    int i,tmpporty;
    if (menu == 6)
        return;
    cct_setcolor(0, 7);
    tmpporty = porty + menu / 8 * 15;
    cct_gotoxy(portx - 2, tmpporty);
    cout << "=========================";
    cct_gotoxy(portx, tmpporty + 1);
    cout << "A         B         C";
    cct_gotoxy(0, tmpporty + 5);
    cout << "��ʼ:  ";
    trans(n, src, dst, 0);//k=0������ʾ��n��
    if (src == 'A')
    {
        for (i = topa; i > 0; i--)
        {
            cct_gotoxy(portx - 1, tmpporty + i - topa - 1);
            cout << setw(2) << i;
        }
    }
    if (src == 'B')
    {
        for (i = topb; i > 0; i--)
        {
            cct_gotoxy(portx + 9, tmpporty + i - topb - 1);
            cout << setw(2) << i;
        }
    }
    if (src == 'C')
    {
        for (i = topc; i > 0; i--)
        {
            cct_gotoxy(portx + 19, tmpporty + i - topc - 1);
            cout << setw(2) << i;
        }
    }

}
/***************************************************************************
  �������ƣ�
  ��    �ܣ������������
  ���������
  �� �� ֵ��
  ˵    ����4,8����,����ʱ�����
***************************************************************************/
void portrait(int n, char src, char dst, int times, int menu)
{
    cct_setcursor(3);//����ʾ���
    cct_setcolor(0, 7);
    int diff = menu / 8 * 15;
    if (times > 0)
        Sleep(300 - 58 * times);
    else if (times==0)
        while (_getch() != '\r')
            ;
    if (src == 'A')
        cct_gotoxy(portx - 1, porty - topa - 1 + diff);
    else if (src == 'B')
        cct_gotoxy(portx + 9, porty - topb - 1 + diff);
    else
        cct_gotoxy(portx + 19, porty - topc - 1 + diff);
    cout << "  ";
    if (dst == 'A')
        cct_gotoxy(portx - 1, porty - topa + diff);
    else if (dst == 'B')
        cct_gotoxy(portx + 9, porty - topb + diff);
    else
        cct_gotoxy(portx + 19, porty - topc + diff);
    cout << setw(2) << n;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�ʵ��menu8����
  ���������
  �� �� ֵ��
  ˵    ����menu8
***************************************************************************/
void clean()
{
    sum = 0;
    for (int i = 0; i < 11; i++)
    {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    topa = 0;
    topb = 0;
    topc = 0;
}
void draw()
{
    int i, j;
    cct_setcursor(3);
    for (i = 0; i < 3; Sleep(20), i++)
        cct_showch(basex + i * 31 - 11, basey, ' ', bg_color, fg_color, rpt);
    for (j = 0; j < 12; j++)
    {
        for (i = 0; i < 3; i++)
        {
            Sleep(20);
            cct_showch(basex + 31 * i, basey - 1 - j, ' ', bg_color, fg_color, 1);
        }
    }
}
void inittower(char src, char dst, int n)
{
    int j;
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��"<<endl;
    draw();
    cct_setcursor(3);//����ʾ���
    if (src == 'A')
    {
        for (j = n; j > 0; j--)
        {
            Sleep(100);
            cct_showch(basex - j, basey - n + j - 1, ' ', j, fg_color, 2 * j + 1);
        }
    }
    if (src == 'B')
    {
        for (j = n; j > 0; j--)
        {
            Sleep(100);
            cct_showch(basex + 31 - j, basey - n + j - 1, ' ', j, fg_color, 2 * j + 1);
        }
    }
    if (src == 'C')
    {
        for (j = n; j > 0; j--)
        {
            Sleep(100);
            cct_showch(basex + 62 - j, basey - n + j - 1, ' ', j, fg_color, 2 * j + 1);
        }
    }
}
void anime(int n, char src, char dst, int times)
{
    int i, j, length = 2 * n + 1;
    int cut1 = 310 - 50 * times, cut2 = cut1 + 1;
    cct_setcursor(3);
    if (src == 'A')
        i = basey - topa-1;
    else if (src == 'B')
        i = basey - topb-1;
    else
        i = basey - topc-1;
    for (; i >= 2; i--)
    {
        Sleep(cut1+30);
        cct_showch(basex + (src - 'A') * 31 - n, i, ' ', 0, fg_color, length);
        if (i>2)
            cct_showch(basex + (src - 'A') * 31, i, ' ', bg_color, fg_color, 1);
        Sleep(cut2+30);
        if (times!=-1)
            cct_showch(basex + (src - 'A') * 31 - n, i - 1, ' ', n, fg_color, length);
    }//����Ų
    if (src < dst && times!=-1)//����Ų
    {
        for (i = basex + (src - 'A') * 31; i < basex + (dst - 'A') * 31; i++)
        {
            Sleep(cut1);
            cct_showch(i - n, 1, ' ', 0, fg_color, length);
            Sleep(cut2);
            cct_showch(i - n + 1, 1, ' ', n, fg_color, length);
        }
    }
    else if (times!=-1)//����Ų
    {
        for (i = basex + (src - 'A') * 31; i > basex + (dst - 'A') * 31; i--)
        {
            Sleep(cut1);
            cct_showch(i - n, 1, ' ', 0, fg_color, length);
            Sleep(cut2);
            cct_showch(i - n - 1, 1, ' ', n, fg_color, length);
        }
    }
    //����ƽ�����
    if (dst == 'A')
        i = basey - topa;
    else if (dst == 'B')
        i = basey - topb;
    else
        i = basey - topc;
    for (j = 1; j < i; j++)
    {
        Sleep(cut1);
        cct_showch(basex + (dst - 'A') * 31 - n, j, ' ', 0, fg_color, length);
        if (j >= 3)
            cct_showch(basex + (dst - 'A') * 31, j, ' ', bg_color, fg_color, 1);
        Sleep(cut2);
        cct_showch(basex + (dst - 'A') * 31 - n, j + 1, ' ', n, fg_color, length);
    }
}
void first(int n, char src, char tmp, char dst)
{
    init(n, src);
    inittower(src, dst, n);
    char realdst = n % 2 == 0 ? tmp : dst;
    movet(1, src, realdst);
    Sleep(300);
    anime(1, src, realdst,4);//Ĭ�ϰ�times=4��ʱ
}
void menu3(int n, char src, char dst)
{
    movet(n, src, dst);
    trans(n, src, dst, 1);
}
void menu4(int n, char src, char dst, int times)
{
    movet(n, src, dst);
    portrait(n, src, dst, times,4);
    cct_gotoxy(0, porty + 5);
    trans(n, src, dst, 1);
}
void menu8(int n, char src, char dst, int times)
{
    movet(n, src, dst);
    portrait(n, src, dst, times, 8);
    cct_gotoxy(0, basey + 17);
    trans(n, src, dst, 1);
    anime(n, src, dst, times);
}
void choosemenu(int n, char src, char dst,int menu, int times)
{
    if (menu == 1 || menu == 2)
        basic(n, src, dst, menu);
    else if (menu == 3)
        menu3(n, src, dst);
    else if (menu == 4)
        menu4(n, src, dst, times);
    else
        menu8(n, src, dst, times);
}
void hanoi(int n, char src, char tmp, char dst,int menu,int times)
{
    if (n > 0)
    {
        hanoi(n - 1, src, dst, tmp,menu,times);
        sum++;
        choosemenu(n, src, dst, menu, times); 
        hanoi(n - 1, tmp, src, dst,menu,times);   
    }
}
int judge(char src, char dst)
{
    int plate;//plateΪԴ���������̺�
    if (src == 'A')
        plate = a[topa - 1];
    else if (src == 'B')
        plate = b[topb - 1];
    else
        plate = c[topc - 1];

    if (plate == 0)
        return 0;//Դ��Ϊ��
    if (dst == 'A' && topa!=0 && plate > a[topa - 1] && a[topa-1]!=0)
        return 2;
    else if (dst == 'B' && topb!=0 && plate > b[topb - 1] && b[topb - 1] != 0)
        return 2;
    else if (dst == 'C' && topc!=0 && plate > c[topc - 1] && c[topc - 1] != 0)
        return 2;
    return 1;
}
int findpan(char src)
{
    if (src == 'A')
        return a[topa - 1];
    else if (src == 'B')
        return b[topb - 1];
    else
        return c[topc - 1];
}
int win(char realdst, int n)
{
    if (realdst == 'A')
    {
        if (topa == n)
            return 1;
    }
    else if (realdst == 'B')
    {
        if (topb == n)
            return 1;
    }
    else
    {
        if (topc == n)
            return 1;
    }
    return 0;
}
void reset(char tmp[12])
{
    for (int i = 0; i < 12; i++)
        tmp[i] = '\0';
}
void game(int n, char src, char dst)
{
    int pan,i;
    char tmp[12] = {'\0'},realdst=dst;//��������Ŀ��
    cct_setcursor(2);//���ص�ȱʡ״̬
    cct_gotoxy(0, 34);
    cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
    while (1)
    {
        cct_setcolor(0, 7);
        cct_gotoxy(60, 34);
        cct_setcursor(2);
        reset(tmp);
        for (i = 0; i < 15; i++)//�������15���ַ����Զ����
        {
                tmp[i] = _getch();//����
            if (tmp[i] == '\r')//�����س���������
                break;
            else if (tmp[i] >= 33 && tmp[i] <= 126)//�������ڼ����ַ�����������ַ���ʹ����ʾ����Ļ��
                cout << tmp[i];
            else
                i--;
        }
        if (tmp[2] == '\r')//���ֻ�����������ַ��ͻس�������Ϊ��ȷ���룬��ֵ��src��dst
        {
            src = tmp[0];
            dst = tmp[1];
        }
        else if ((tmp[0] == 'q' || tmp[0] == 'Q') && tmp[1]=='\r')//ֻ������һ��q
        {
            cout << "\n��Ϸ��ֹ!!!!!";
            return;
        }
        else//�����������Ҫ�������룬ֱ�Ӹ�src����ֵ
            src = '0';
        if (((src >= 'A' && src <= 'C') || (src >= 'a' && src <= 'c')) && ((dst >= 'A' && dst <= 'C') || (dst >= 'a' && dst <= 'c')))
        {//�����Ϊ��ȷ��ĸ
            src = src <= 'c' ? src - 'a' + 'A' : src;
            dst = dst <= 'c' ? dst - 'a' + 'A' : dst;//��ת��Ϊ��д
            if (src == dst)//��������һ����ʲôҲ����
                ;
            else if (judge(src, dst)==0)
            {
                cout << "\nԴ��Ϊ��!";
                Sleep(300);
            }
            else if (judge(src, dst) == 2)
            {
                cout << "\n����ѹС�̣��Ƿ����룡";
                Sleep(300);
            }
            else//��ȷŲ��������+1��Ų�����
            {
                sum++;
                pan = findpan(src);
                movet(pan, src, dst);
                portrait(pan, src, dst, -1, 8);
                cct_gotoxy(0, basey + 17);
                trans(pan, src, dst, 1);
                anime(pan, src, dst, 6);
            }      
        }
        cct_setcolor(0, 7);
        cct_setcursor(3);
        cct_gotoxy(0, 35);
        cout << "                                  ";//������û�����������ʾ�䣬���о��ÿո�����
        cct_gotoxy(60, 34);//������ʾ���ð�ź�
        cout << "                                                       ";//���һ�����룬�ո�������Ļ
        if (win(realdst, n))
        {
            cout << "\n��Ϸ����!!!!!\n\n";
        }
    }
}