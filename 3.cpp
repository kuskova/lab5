#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

double operations(char string[])
{
	char stackdigs[100] = "";
	char* stackop = new char [strlen(string)];
	int finish = -1, finishop = -1;
	for (int i = 0;i < strlen(string);i++)
	{
		if (isdigit(*(string + i))) //пока это числа мы записываем их в строку другого char-массива
		{
			finish++;
			*(stackdigs + finish) = *(string + i);
		}
		else if (*(string + i) != ')') //пока мы не встретили ')',то мы заносим + - * / в другой char-массив
		{
			if ((*(string + i) == '*' || *(string + i) == '/') && isdigit(*(string + i + 1))) // описание приоритета * / между чиcлами и )* )/
			{
				finish++;
				*(stackdigs + finish) = '.';
				int k = i;
				while (isdigit(*(string + k + 1)))
				{
					finish++;
					*(stackdigs + finish) = *(string + k + 1);
					k++;
				}
				finish++;
				*(stackdigs + finish) = *(string + i);
				i = k;
			}
			else if (*(string + i + 1) == '-' && *(string + i) == '(')
			{
				int k = i;
				while (isdigit(*(string + k + 2)))
				{
					k++;
				}
				if (*(string + k + 2) == ')')// специально для (-х)
				{
					finishop++;
					*(stackop + finishop) = '(';
					finish++;
					*(stackdigs + finish) = '0';
					finish++;
					*(stackdigs + finish) = '.';
				}
			}
			else if (*(string + i) == '-' && i == 0)
			{
				finish++;
				*(stackdigs + finish) = '0';
				finish++;
				*(stackdigs + finish) = '.';
				int k = i;
				while (isdigit(*(string + k + 1)))
				{
					finish++;
					*(stackdigs + finish) = *(string + k + 1);
					k++;
				}
				i = k;
				finish++;
				*(stackdigs + finish) = '-';
			}
			else // заносим + - ( и отделяем числа '.'
			{
				finishop++;
				*(stackop + finishop) = *(string + i);
				if (*(stackdigs + finish) != '.' || *(string + i) != '(' && i == 0)
					finish++;
				*(stackdigs + finish) = '.';
			}
		}

		else
		{
			int h = finishop;
			while (*(stackop + h) != '(')
			{
				if (*(stackop + h) == '-' && *(stackop + h + 1) == '-')
				{
					*(stackop + h + 1) = '+';
					while (*(stackop + h) != '+' && *(stackop + h) != '(')
					{
						*(stackop + h) = '+';
						h--;
					}
					*(stackop + h + 1) = '-';
					h++;
				}
				else if (*(stackop + h) == '-' && *(stackop + h + 1) == '+')
				{
					*(stackop + h + 1) = '-';
					while (*(stackop + h) != '+' && *(stackop + h) != '(')
					{
						*(stackop + h) = '+';
						h--;
					}
					*(stackop + h + 1) = '-';
					h++;
				}
				h--;
			}
			while (*(stackop + finishop) != '(')
			{
				finish++;
				*(stackdigs + finish) = *(stackop + finishop);
				finishop--;
			}
			finishop--;
			if (*(stackop + finishop) == '*' || *(stackop + finishop) == '/')
			{
				finish++;
				*(stackdigs + finish) = *(stackop + finishop);
				finishop--;
			}
		}
		if (i == strlen(string) - 1)// вывод оставшихся символов + -
		{
			for (int konec_yeah = finishop;konec_yeah >= 0;konec_yeah--)
			{
				if (*(stackop + konec_yeah) == '-' && *(stackop + konec_yeah + 1) == '-')
				{
					*(stackop + konec_yeah + 1) = '+';
					while (*(stackop + konec_yeah) != '+' && konec_yeah >= 0)
					{
						*(stackop + konec_yeah) = '+';
						konec_yeah--;
					}
					*(stackop + konec_yeah + 1) = '-';
					konec_yeah++;
				}
				else if (*(stackop + konec_yeah) == '-' && *(stackop + konec_yeah + 1) == '+')
				{
					*(stackop + konec_yeah + 1) = '-';
					while (*(stackop + konec_yeah) != '+' && konec_yeah >= 0)
					{
						*(stackop + konec_yeah) = '+';
						konec_yeah--;
					}
					*(stackop + konec_yeah + 1) = '-';
					konec_yeah++;
				}
			}
			for (int j = finishop + 1;j != 0;j--)
			{
				finish++;
				*(stackdigs + finish) = *(stackop + finishop);
				finishop--;
			}
		}
	}
	for (int i = 0;i <= finish;i++)
	{
		cout << stackdigs[i];
	}
	cout << endl;
	double digs[100] = {0};//начало операций
	int number = 0;
	int finish2 = -1;
	for (int i = 0;i < static_cast<int>(strlen(stackdigs));i++)
	{
		if (isdigit(*(stackdigs + i)))
		{
			number = number * 10 + (*(stackdigs + i) - '0');
		}
		else if (*(stackdigs + i) == '.')
		{
			if (i != 0 && isdigit(*(stackdigs + i - 1)))
			{
				finish2++;
				digs[finish2] = number;
				number = 0;
			}
		}

		else
		{
			switch (*(stackdigs + i))
			{
			case '+':
				if (number != 0)
				{
					digs[finish2] = digs[finish2] + number;
					number = 0;
				}
				else
				{
					digs[finish2 - 1] = digs[finish2] + digs[finish2 - 1];
					digs[finish2] = 0;
					finish2--;
				}
				break;
			case '-':
				if (number != 0)
				{
					digs[finish2] = digs[finish2] - number;
					number = 0;
				}
				else
				{
					digs[finish2 - 1] = digs[finish2 - 1] - digs[finish2];
					digs[finish2] = 0;
					finish2--;
				}
				break;
			case '*':
				if (number != 0)
				{
					digs[finish2] = digs[finish2] * number;
					number = 0;
				}
				else
				{
					digs[finish2 - 1] = digs[finish2] * digs[finish2 - 1];
					digs[finish2] = 0;
					finish2--;
				}
				break;
			case '/':
				if (number != 0)
				{
					digs[finish2] = static_cast<double>(digs[finish2] / number);
					number = 0;
				}
				else
				{
					digs[finish2 - 1] = static_cast<double>(digs[finish2 - 1] / digs[finish2]);
					digs[finish2] = 0;
					finish2--;
				}
				break;
			}
		}
	}
	cout << digs[0] << endl;
	return digs[0];
}

inline void assert(char s[], double ans){
    const double EPS = 1e-5;
    double res = operations(s);
    if (fabs(res - ans) <= EPS)
        puts("OK");
    else
        puts("FAIL");
}

int main()
{
    char s1[] = "-2*((3+5)/4-7*9+3*(4+5))+1";
    char s2[] = "((((1+2)+3)+4)*5)/2-3*(1+4)-1";
    char s3[] = "(2+3)/2+(1-4)/7";
    assert(s1, 69);
    assert(s2, 9);
    assert(s3, 2.0714285714);
}
