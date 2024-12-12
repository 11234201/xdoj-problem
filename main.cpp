// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
#include <iomanip>
using namespace std;


stack<double> nums;
string postfix;
stack<char> operate;

bool isNum(char c){
    if(c>='0'&&c<='9'||c=='.') return true;
    return false;
}

bool isOp(char c){
    return c=='+'||c=='-'||c=='*'||c=='/';
}

int level(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    return 0;
}

int cal(char op,int a,int b){
    switch (op) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': if (b == 0) {
                cerr << "Error: Division by zero" << endl;
                exit(1);
            }
            return a / b;
        default: cerr << "Error: Invalid operator" << endl;
            exit(1);
    }
}


void translate(string &s){
    for(auto &subC:s){
        if(subC=='='){
            break;
        }
        if(subC==' ')
            continue;

        if(isNum(subC)){
            postfix+=subC;
            continue;
        }
        if(isOp(subC)){
            if(!operate.empty()){
                char top=operate.top();
                while(level(top)>= level(subC)){
                    postfix+=top;
                    operate.pop();
                    if(operate.empty())
                        break;
                    top=operate.top();
                }
            }
            operate.push(subC);
            continue;
        }

        if(subC=='('){
            operate.push(subC);
            continue;
        }

        if(subC==')'){
            char top=operate.top();
            while(top!='('){
                postfix+= top;
                operate.pop();
                top=operate.top();
            }
            operate.pop();
        }
    }
    while(!operate.empty()){
        postfix+=operate.top();
        operate.pop();
    }

}

int calculate(){
    stack<int> ans;
    for(auto &subC:postfix){
        if(isNum(subC))
            ans.push(subC-'0');
        else{
            int numb = ans.top();  ans.pop();
            int numa = ans.top();  ans.pop();
            ans.push(cal(subC,numa,numb));
        }
    }
    return ans.top();
}

int main()
{
    string input;
    cout<<fixed<<setprecision(0);
    while(true){
        cin>>input;
        if(input=="=")
            break;
        translate(input);
        cout<<postfix<<endl<<calculate()<<endl;
        postfix.clear();
    }
    return 0;
}