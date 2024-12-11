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

class QSort{
private:
    vector<int> list;
    int length;
public:
    explicit QSort(int n):length(n){
        list.assign(n,0);
        for(int i=0;i<n;i++)
            cin>>list[i];
    }

    int Partition(int left,int right){
        int core=list[left];
        while(left<right){
            while(left<right && list[right]>=core) --right;
            list[left]=list[right];
//            corePlace=right;
            while(left<right && list[left]<=core) ++left;
            list[right]=list[left];
        }
        list[left]=core;
        return left;
    }

    void sort(int left,int right){
        int corePlace=0;
        if(left>=length||right<0)
            return;
        if(left<right){
            corePlace= Partition(left,right);
            sort(left,corePlace-1);
            sort(corePlace+1,right);
            cout<<list[corePlace]<<' ';
        }
        if(left==right)
            cout<<list[left]<<' ';
    }
};

int main()
{
    int n;
    cin>>n;
    QSort qSort(n);
    qSort.sort(0,n-1);

    return 0;
}