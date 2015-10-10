#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct item{
    char key;
    item* prev;
};

inline bool solve1(char s[]){
}

inline bool solve2(char s[]){
    int len = strlen(s);
    item* top = new item;
    top->key = 0, top->prev=NULL;
    for (int i = 0; i < len; ++i)
        if (s[i] == '(' || s[i] == '[' || s[i] == '{'){
            item* cur = new item;
            cur->key = s[i];
            cur->prev = top;
            top = cur;
        }
        else{
            if (s[i] == ')' && top->key != '(' || s[i] == ']' && top->key != '[' || s[i] == '}' && top->key != '{')
                return false;
            top = top->prev;
        }
    return top->key == 0;
}

inline void assert(char s[], bool ans){
    bool res1 = solve1(s);
    bool res2 = solve2(s);
    if (res1 == ans)
        printf("OK ");
    else
        printf("WA ");
    if (res2 == ans)
        puts("OK");
    else
        puts("WA");
}

bool testskobki(char string[])
{
	char* ctec = new char [strlen(string)];
	int finish = -1;
	for (int k = 0; k < strlen(string); k++)
	{
		char simvol = *( string + k );
		if (simvol == '(' || simvol == '{' || simvol == '[')
		{
			finish++;
			ctec[finish] = simvol;
		}
		else
		{
			int skoba = static_cast<int>(*( string + k ));
			int zadnyaa = static_cast<int>(*( ctec + finish ));
			if (skoba - zadnyaa <= 2 && skoba - zadnyaa > 0)
			{
				finish--;
			}
			else
			{
				return false;
			}
		}
	}
	if (finish == -1)
	{
		return true;
	}
	return false;
}

void assert1(bool test, char string[])
{
	if (test == testskobki(string))
	{
		cout << "OK" << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}
}
int main(){
    char s1[] = "(()){[][]}";
    char s2[] = "([]]";

    assert(s1, true);
    assert(s2, false);
    char a[5] = "(())";
	assert1(true,a);
	char b[100] = "(()){[{]]}";
	assert1(false,b);
    return 0;
}
