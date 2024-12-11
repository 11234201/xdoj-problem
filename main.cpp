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
#include <cmath>

using namespace std;

struct stu{
    string id;
    string name;
    double score;
    bool operator <(const stu& other)const{
        return score>other.score;
    }
    friend ostream& operator<<(ostream& os, const stu& obj);
};

ostream& operator<<(ostream& os, const stu& obj){
    os<<obj.id<<' '<<obj.name<<' '<< fixed<< setprecision(3)<<obj.score<<endl;
    return os;
}

int main()
{
    int n,m;
    double ratio;
    cin>>n>>m>>ratio;
    vector<stu> list;
    string id;
    string name;
    for(int i=0;i<n;++i){
        double total=0,score,tmpCredit,credit=0;
        int flag=0;
        cin>>id>>name;
        for(int j=0;j<m;++j){
            cin>>score>>tmpCredit;
            total+=score*tmpCredit;
            credit+=tmpCredit;
            if(score<60)
                flag=1;
        }
        double attach;
        cin>>attach;

        if(flag)
            continue;
        list.push_back({id,name,total/credit+attach});
    }
    sort(list.begin(),list.end());
    int limit=ceil(ratio*n);
    limit=max(1,limit);
    for(int i=0;i<limit&&!list.empty();++i)
        if(list[i].score>0)
            cout<<list[i];
    return 0;
}