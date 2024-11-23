// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
using namespace std;

string s;

int left(char c){
    if(c=='(')
        return 1;
    if(c=='[')
        return 2;
    if(c=='{')
        return 3;
    return 0;
}

int right(char c){
    if(c==')')
        return 1;
    if(c==']')
        return 2;
    if(c=='}')
        return 3;
    return 0;
}

int main()
{
    cin>>s;
    stack<int> myStack;
    int match=0;
    int result=1;
    for(auto &tmpC:s){
        if(!myStack.empty())
            match=myStack.top();
        int tmpMatch= left(tmpC);
        //如果是左括号就入栈
        if(tmpMatch){
            myStack.push(tmpMatch);
            continue;
        }

        tmpMatch= right(tmpC);
        //是非括号就下一个字符
        if(!tmpMatch)
            continue;
        //检测是否匹配
        if(tmpMatch!=match){
            result=0;
            break;
        }
        myStack.pop();
    }
    //如果字符串检测结束了栈还有元素也是没匹配
    if(!myStack.empty())
        result=0;

    if(result)
        cout<<"yes";
    else
        cout<<"no";
    return 0;
}