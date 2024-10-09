// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

class explainDemonL{
public:
static void run(string& inputS){
    inputS= raw3(inputS);
    inputS= rawB(inputS);
    inputS= rawA(inputS);
}
//将所有B转换成tAdA
static string rawB(string s){
    string tmpS;
    for(auto &tmpC:s){
        if(tmpC=='B')
            tmpS+="tAdA";
        else
            tmpS+=tmpC;
    }
    return tmpS;
}

//将所有A转换成sae
static string rawA(string s){
    string tmpS;
    for(auto &tmpC:s){
        if(tmpC=='A')
            tmpS+="sae";
        else
            tmpS+=tmpC;
    }
    return tmpS;
}

//将所有（？x1 x2...xn）转化为 ?xn?...?x2?x1?
//?可以是任意字符
static string raw3(string s){
    string tmpS;
    size_t left=s.find('('),right;
    //如果有括号
    if(left!=string::npos){
        right=s.rfind(')');
        tmpS=s.substr(left+2,right-left-2);//tmpS这时已成为括号里除了第一个字符之外的串

        char theta= s[left+1];//？对应的字符

        //递归调用
        tmpS=raw3(tmpS);

        string changedS;
        changedS=theta;
        //规则3
        for(auto it=tmpS.rbegin();it!=tmpS.rend();it++){
            changedS += *it;
            changedS += theta;
        }
        tmpS=changedS;
        if(left){
            tmpS=s.substr(0,left)+tmpS;
        }
        if(right!=s.size()){
            tmpS=tmpS+s.substr(right+1,s.size()-right-1);
        }
    }
    //如果没有括号
    else
        tmpS=s;
    return tmpS;
}
};

int main()
{
    string inputS;
    cin>>inputS;
    explainDemonL::run(inputS);
    cout<<inputS;
    return 0;
}