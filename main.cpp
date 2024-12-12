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

double cal(char op,double a,double b){
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

void calTop(){
    char topOp=operate.top();
    double numb = nums.top();  nums.pop();
    double numa = nums.top();  nums.pop();
    double newNum = cal(topOp, numa, numb);
    nums.push(newNum);
    operate.pop();
}

double calculate(string &s){
    string tmpNum;
    for(auto &subC:s){
        if(subC=='=') {
            if(!tmpNum.empty()){
                nums.push(stod(tmpNum));
                tmpNum.clear();
            }
            break;
        }
        if(subC==' ')
            continue;
        //如果是数字就加到字符串里
        if(isNum(subC)){
             tmpNum+= subC;
             continue;
        }
         //如果是操作符
        if(isOp(subC)){
            //将操作符前一个数字解析入栈
            if(!tmpNum.empty()){
                nums.push(stod(tmpNum));
                tmpNum.clear();
            }
            //如果操作符栈空，直接入栈
            if(operate.empty()) {
                operate.push(subC);
                continue;
            }
            char topOp=operate.top();
            //如果操作符等级不高于栈顶，则计算再入栈新操作符
            if(level(topOp)>= level((subC))){
                calTop();
            }
            //否则就入栈新操作符
            operate.push(subC);
            continue;
        }
        //如果是括号
        if(subC==')'){
            //将操作符前一个数字解析入栈
            if(!tmpNum.empty()){
                nums.push(stod(tmpNum));
                tmpNum.clear();
            }

            char topOp=operate.top();
            while(topOp!='(') {
                calTop();
                topOp=operate.top();
            }
            operate.pop();
            continue;
         }
         operate.push(subC);
    }

    while(!operate.empty())
        calTop();

    return nums.top();
}

int main()
{
    string input;
    cout<<fixed<<setprecision(2);
    while(true){
        cin>>input;
        if(input=="=")
            break;
        cout<<calculate(input)<<endl;
    }

    return 0;
}