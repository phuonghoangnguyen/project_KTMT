#include "Menu.h"

BUTTON key(int a) //tra ve thao tac dieu khien
{
	if (a == 224)
	{
		char c;
		c = _getch();
		if (c == 72)
		{
			return up; //mui ten len
		}
		if (c == 80)
		{
			return down; // mui ten xuong
		}
	}
	else if (a == 13)
	{
		return enter; //nut enter
	}
}

int menu(string Menu[7], int n)
{
	int tt = 1;
	int *color = new int[n];
	for (int i = 1; i <= n; i++)
	{
		color[i] = TEXTCOLOR;
	}
	color[1] = BACKGROUND;
	while (1)
	{
		clrscr();
		TextColor(12);
		cout << Menu[0] << endl;
		for (int i = 1; i < n; i++)
		{
			TextColor(color[i]);
			cout << Menu[i] << endl;
		}
		int a = _getch();
		BUTTON TT = key(a);
		switch (TT)
		{
		case(up) :
		{
			if (tt == 1)
			{
				tt = n - 1;
			}
			else
			{
				tt--;
			}
			break;
		}
		case(down) :
		{
			if (tt == n - 1)
			{
				tt = 1;
			}
			else
			{
				tt++;
			}
			break;
		}
		case(enter) :
		{
			return tt;
			break;
			free(color);
		}
		case(esc) :
		{
			return 0;
		}
		}
		for (int i = 1; i < n; i++)
		{
			color[i] = TEXTCOLOR;
		}
		color[tt] = BACKGROUND;
	}
}

QInt Calculator(const QInt &oper1, const QInt &oper2, char oprtor)
{
	switch (oprtor)
	{
	case '+': return oper1 + oper2;
	case '-': return oper1 - oper2;
	case '*': return oper1 * oper2;
	case '/': return oper1 / oper2;
	default: throw::logic_error("unsupported error!");
	}
}

int StoN(const string &s)
{
	stringstream str(s);
	int number;
	str >> number;
	return number;
}