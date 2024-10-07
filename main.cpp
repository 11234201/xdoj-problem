// main.cpp文件

#include <iostream>
#include <string>
#include <list>
using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    list<pair<int,int> > list1;
    int temp;
    for(int i=0;i<n;i++){
        cin>>temp;
        list1.emplace_back(i,temp);
    }
    int left=m,cnt=n;
    while(cnt){
        left=(left-1)%cnt+1;
        auto it=list1.begin();
        advance(it,left-1);
        left+=it->second;
        if(cnt==n)
            cout<<it->first+1;
        else {
            cout<<' '<<it->first+1;
        }
        list1.erase(it);
        --cnt;
        --left;
    }

    return 0;
}