// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
using namespace std;


int main()
{
    string s;
    cin>>s;
    for(auto &tmpC:s){
        tmpC+=4;
        if((tmpC>'z') || (tmpC<'a'&&tmpC>'Z'))
            tmpC-=26;
    }
    cout<<s;
    return 0;
}