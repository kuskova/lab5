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

int main(){
    return 0;
}
