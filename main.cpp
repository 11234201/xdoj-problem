// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Stu{
    int id,time;
    bool operator < (const Stu &other) const{
        if(time==other.time)
            return id<other.id;
        return time>other.time;
    }
};

class AttendanceSystem{
private:
    //id,time
    unordered_map<int,int> stuList;
public:
    void update(int id,int time){
        stuList[id]+=time;
    }
    void Output(){
        vector<Stu> stu;
        stu.reserve(stuList.size());
        for(auto &s: stuList)
            stu.push_back({s.first,s.second});

        sort(stu.begin(),stu.end());
        for(auto &s:stu)
            cout<<s.id<<' '<<s.time<<endl;

    }
};

//input xx:xx string time,
int translateTime(string &time){
    int ans;
    ans=(time[0]-'0')*10+time[1]-'0';
    ans*=60;
    ans+=(time[3]-'0')*10+time[4]-'0';
    return ans;
}

int main()
{
    int n;
    cin>>n;
    int id;
    AttendanceSystem sys;
    string tmpS;
    while(n--){
        cin>>id>>tmpS;
        int start= translateTime(tmpS);
        cin>>tmpS;
        int end  = translateTime(tmpS);
        sys.update(id,end-start);
    }

    sys.Output();
    return 0;
}