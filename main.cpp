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


int main()
{
    int n;
    vector<int> tmp;
    vector<vector<int> > x;
    vector<vector<double> > y;
    cin>>n;
    tmp.resize(n,0);

    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)
            cin>>tmp[j];
        x.push_back(tmp);
    }
    vector<double> tmpD;
    tmpD.resize(n,0);
    y.resize(n,tmpD);

    for(int i=0;i<n;++i)
        for (int j=0; j<n;++j)
            for(int k1=-1;k1<=1;++k1){
                int ni=i+k1;
                if(ni<0||ni>=n)
                    continue;
                for(int k2=-1;k2<=1;++k2){
                    int nj=j+k2;
                    if(nj<0||nj>=n)
                        continue;
                    y[i][j]+=x[ni][nj];
                }
            }
    for(int i=0;i<n;++i) {
        for (int j = 0; j < n; ++j)
            cout<<int(y[i][j]/9+0.5)<<' ';
        cout<<endl;
    }
    return 0;
}