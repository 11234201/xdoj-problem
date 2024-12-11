// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;


int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int> >a;
    vector<int> tmp(m);
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j)
            cin>>tmp[j];
        a.push_back(tmp);
    }
    int cnt=0,tmpIn;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j) {
            cin >> tmpIn;
            if(tmpIn==a[i][j])
                ++cnt;
        }
    }
    cout<<fixed<<setprecision(2)<<100.0*cnt/n/m<<endl;
    return 0;
}