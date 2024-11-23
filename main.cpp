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
    int n,sum=0,tmpNum;
    cin>>n;
    while(n--){
        cin>>tmpNum;
        int bit;
        while(tmpNum){
            bit=tmpNum%10;
            tmpNum/=10;
            sum=(sum+bit)%10;
        }
    }
    cout<<sum;
    return 0;
}