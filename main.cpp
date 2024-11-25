// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int fib(int n){
    if(n==0)
        return 7;
    if(n==1)
        return 11;
    return fib(n - 1) + fib(n - 2);
}

int main()
{

    int n;
    cin>>n;
    cout << fib(n);
    return 0;
}