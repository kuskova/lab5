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

int main(){
    char s1[] = "(()){[][]}";
    char s2[] = "([]]";

    assert(s1, true);
    assert(s2, false);
    return 0;
}
