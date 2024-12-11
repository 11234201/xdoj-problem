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

struct Line{
    int id;
    int cap;
};

class System{
private:
    vector<Line> seats;
    int numLine;
public:
    explicit System():numLine(20){
        seats.resize(numLine);
        for(int i=0;i<numLine;++i)
            seats[i].id=i, seats[i].cap=5;
    }

    //找到连号的最小座位排号
    int find(int n){
        int x=-1;
        for(int i=0;i<numLine;++i)
            if(seats[i].cap>=n){
                x=i;
                break;
            }
        return x;
    }

    void output(int lineI,int n){
        int start=lineI*5+(5-seats[lineI].cap)+1;
        seats[lineI].cap-=n;
        for(int i=0;i<n;++i)
            cout<<start+i<<' ';
    }

    void buy(int n){
        int lineI= find(n);
        //如果没有连号的
        if(lineI==-1){
            for(int i=0;i<numLine;++i){
                if(!seats[i].cap)
                    continue;
                if(seats[i].cap<n){
                    n-=seats[i].cap;
                    output(i,seats[i].cap);
                }
                else {
                    output(i, n);
                    n=0;
                    break;
                }
            }
            if(n){
                cerr<<"Error!!!!"<<endl;
            }
        }
        //有连号
        else
            output(lineI,n);

        cout<<endl;
    }
};

int main()
{
    int n,num;
    cin>>n;
    System sys;
    while(n--){
        cin>>num;
        sys.buy(num);
    }
    return 0;
}