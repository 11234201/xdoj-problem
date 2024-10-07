// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

class MyComp{
public:
    bool operator()(pair<int,int> p1,pair<int ,int>p2){
        return p1.second<p2.second;
    }
};

struct Polynomial{
    typedef  map<int,int> myType;
    //第一项是指数，第二项是系数
    myType body;

    Polynomial operator+(const Polynomial& other)const{
        Polynomial temp=*this;

        for(auto &it:other.body){
            temp.body[it.first]+=it.second;
            if(temp.body[it.first]==0)
                temp.body.erase(it.first);
        }
        return temp;
    }

    Polynomial operator-(const Polynomial& other)const{
        Polynomial temp= *this;

        for(auto &it:other.body){
            temp.body[it.first]-=it.second;
            if(temp.body[it.first]==0)
                temp.body.erase(it.first);
        }
        return temp;
    }

    friend ostream& operator<<(ostream& os,const Polynomial &sub){
        bool first= true;
        if(sub.body.empty())
            return os<<'0';
        for(const auto &it:sub.body){
            if(!first){
                if(it.second>0)
                    os<<'+';
                else
                    os<<'-';
            }
            first= false;
            if(it.first==0)
                os<<it.second;
            else {
                if(it.second!=1&&it.second!=-1)
                    os<<abs(it.second);
                os << "x" ;
                if(it.first!=1)
                    os<<'^'<<it.first;
            }
        }
        return os;
    }
};

int main()
{
    int n,m,operate;
    int temp1,temp2;
    Polynomial p1,p2;
    cin>>n>>m>>operate;
    while(n--){
        cin>>temp1>>temp2;
        p1.body.insert({temp2,temp1});
    }
    while(m--){
        cin>>temp1>>temp2;
        p2.body.insert({temp2,temp1});
    }
    if(operate)
        cout<<p1-p2;
    else
        cout<<p1+p2;
    return 0;
}