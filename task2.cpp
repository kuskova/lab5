#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

inline int calc(char s[]){
    int len = strlen(s);
    stack <int> op, num;
    for (int i = 0; i < len; ++i)
        if (isdigit(s[i]))
            num.push(s[i]-'0');
        else
            if (s[i] == 'x')
                op.push(0);
            else
                if (s[i] == 'n')
                    op.push(1);
                else
                    if (s[i] == ')'){
                        int t = num.top();
                        num.pop();
                        if (op.top())
                            num.top() = min(num.top(), t);
                        else
                            num.top() = max(num.top(), t);
                        op.pop();
                    }
    return num.top();
}

void assert(char s[], int right)
{
	if (calc(s)==right)
	{
		cout << "OK" << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}
}
int main(){
	char s[100]="max(min(max(2,3),min(6,5)),min(9,max(3,5)))";
	assert(s,5);
	char q[100]="max(4, min(3,5))";
	assert(q,4);
	char z[100]="min(min(3,5), max(2,max(3,4)))";
	assert(z,3);
    return 0;
}
