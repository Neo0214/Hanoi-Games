#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
const int portx = 11, porty = 12;//纵向输出的A中心底坐标  y+15
const int bg_color = 15, fg_color = 7, rpt=23;
const int basex = 12, basey = 15;//柱子A的中心底坐标
int sum = 0;
int a[11] = { 0 }, b[11] = { 0 }, c[11] = { 0 };
int topa = 0, topb = 0, topc = 0;

void anime(int n, char src, char dst,int times);//函数声明
/***************************************************************************
  函数名称：
  功    能：输入各参数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void readln(char* p1, char* p2, int* p3, int* p4,int menu) 
{
	char src, dst;
	int times,n;
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> n;
        if (n >= 1 && n <= 10 && cin.good())//输入正确，清空缓存区
        {
            cin.ignore(1024, '\n');
            break;
        }
        else//输入错误，清空缓存区，重新输入
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }
    *p3 = n;
    while (1)
    {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> src;
        if ((src == 'A' || src == 'B' || src == 'C' || src == 'a' || src == 'b' || src == 'c') && cin.good())//输入正确，清空缓存区
        {
            cin.ignore(1024, '\n');
            break;
        }
        else//输入错误，清空缓存区，重新输入
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }
    if (src != 'A' && src != 'B' && src != 'C')//将起始柱改为大写字母
        src = src + 'A' - 'a';
    *p1 = src;
    while (1)
    {
        cout << "请输入目标柱(A-C)" << endl;
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
            if (dst != 'A' && dst != 'B' && dst != 'C')//将目标柱改为大写字母
                dst = dst + 'A' - 'a';
            cout << "目标柱(" << dst << ")不能与起始柱(" << src << ")相同" << endl;
        }
    }
    if (dst != 'A' && dst != 'B' && dst != 'C')//将目标柱改为大写字母
        dst = dst + 'A' - 'a';
    *p2 = dst;
    while (menu==4 || menu==8)
    {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)";
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
  函数名称：
  功    能：基本解输出
  输入参数：
  返 回 值：
  说    明：1,2共用
***************************************************************************/
void basic(int n, char src, char dst, int menu)
{
    if (menu==1)
        cout << n << "# " << src << "---->" << dst<<endl;
    else
        cout << "第" << setw(4) << sum << " 步" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
}
/***************************************************************************
  函数名称：
  功    能：将数组初始化
  输入参数：
  返 回 值：
  说    明：0为无盘
***************************************************************************/
void init(int n, char src)
{
    int i;
    for (i = 1; i <= n; i++)//将初始盘挪到初始塔上
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
  函数名称：
  功    能：挪动数组内部值
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：
  功    能：横向输出数组
  输入参数：
  返 回 值：
  说    明：3,4,8共用，包含挪动数组值
***************************************************************************/
void trans(int n, char src, char dst, bool k)
{
    int i;
    cct_setcursor(3);//不显示光标
    cct_setcolor(0, 7);//重置为标准颜色
    if (k)//初始显示时不显示该句
    {
        cout << "第" << setw(4) << sum << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")  ";
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
  函数名称：
  功    能：初始化屏幕输出,包含横向与纵向
  输入参数：
  返 回 值：
  说    明：
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
    cout << "初始:  ";
    trans(n, src, dst, 0);//k=0不会显示第n步
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
  函数名称：
  功    能：纵向输出数组
  输入参数：
  返 回 值：
  说    明：4,8共用,包含时间控制
***************************************************************************/
void portrait(int n, char src, char dst, int times, int menu)
{
    cct_setcursor(3);//不显示光标
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
  函数名称：
  功    能：实现menu8功能
  输入参数：
  返 回 值：
  说    明：menu8
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
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层"<<endl;
    draw();
    cct_setcursor(3);//不显示光标
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
    }//往上挪
    if (src < dst && times!=-1)//往右挪
    {
        for (i = basex + (src - 'A') * 31; i < basex + (dst - 'A') * 31; i++)
        {
            Sleep(cut1);
            cct_showch(i - n, 1, ' ', 0, fg_color, length);
            Sleep(cut2);
            cct_showch(i - n + 1, 1, ' ', n, fg_color, length);
        }
    }
    else if (times!=-1)//往左挪
    {
        for (i = basex + (src - 'A') * 31; i > basex + (dst - 'A') * 31; i--)
        {
            Sleep(cut1);
            cct_showch(i - n, 1, ' ', 0, fg_color, length);
            Sleep(cut2);
            cct_showch(i - n - 1, 1, ' ', n, fg_color, length);
        }
    }
    //左右平移完成
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
    anime(1, src, realdst,4);//默认按times=4延时
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
    int plate;//plate为源柱顶部的盘号
    if (src == 'A')
        plate = a[topa - 1];
    else if (src == 'B')
        plate = b[topb - 1];
    else
        plate = c[topc - 1];

    if (plate == 0)
        return 0;//源柱为空
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
    char tmp[12] = {'\0'},realdst=dst;//记下最终目标
    cct_setcursor(2);//光标回到缺省状态
    cct_gotoxy(0, 34);
    cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
    while (1)
    {
        cct_setcolor(0, 7);
        cct_gotoxy(60, 34);
        cct_setcursor(2);
        reset(tmp);
        for (i = 0; i < 15; i++)//最多输入15个字符就自动清空
        {
                tmp[i] = _getch();//输入
            if (tmp[i] == '\r')//遇到回车结束输入
                break;
            else if (tmp[i] >= 33 && tmp[i] <= 126)//其余若在键盘字符上则输出该字符，使其显示在屏幕上
                cout << tmp[i];
            else
                i--;
        }
        if (tmp[2] == '\r')//如果只输入了两个字符就回车，可能为正确输入，赋值给src，dst
        {
            src = tmp[0];
            dst = tmp[1];
        }
        else if ((tmp[0] == 'q' || tmp[0] == 'Q') && tmp[1]=='\r')//只输入了一个q
        {
            cout << "\n游戏中止!!!!!";
            return;
        }
        else//其余情况均需要重新输入，直接给src错误值
            src = '0';
        if (((src >= 'A' && src <= 'C') || (src >= 'a' && src <= 'c')) && ((dst >= 'A' && dst <= 'C') || (dst >= 'a' && dst <= 'c')))
        {//输入均为正确字母
            src = src <= 'c' ? src - 'a' + 'A' : src;
            dst = dst <= 'c' ? dst - 'a' + 'A' : dst;//均转换为大写
            if (src == dst)//两个盘子一样，什么也不做
                ;
            else if (judge(src, dst)==0)
            {
                cout << "\n源柱为空!";
                Sleep(300);
            }
            else if (judge(src, dst) == 2)
            {
                cout << "\n大盘压小盘，非法输入！";
                Sleep(300);
            }
            else//正确挪动，步数+1，挪盘输出
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
        cout << "                                  ";//无论有没有输出错误提示句，该行均用空格清理
        cct_gotoxy(60, 34);//输入提示语句冒号后
        cout << "                                                       ";//完成一次输入，空格清理屏幕
        if (win(realdst, n))
        {
            cout << "\n游戏结束!!!!!\n\n";
        }
    }
}