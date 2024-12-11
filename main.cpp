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

class HashTable{
private:
    vector<int> table;
    int tableCap,p;
    int capUse;
public:
    HashTable(int m,int p)
    :tableCap(m),p(p),capUse(0)
    {
        table.assign(m,-1);
    }

    int insert(int inNum){
        //程序退出
        if(inNum==-1)
            return 0;

        int have=0;
        //插入部分
        int place=inNum % p;
        if(table[place]==inNum)
            have=1;
        //冲突处理
        else if(table[place]!=-1)//如果已经有数字了且不是inNum
            while(table[place]!=-1){
                if(table[place]==inNum){
                    have=1;
                    break;
                }
                place=(place+1) % tableCap;
            }

        //记录和输出
        //如果表里没有就记录
        if(!have) {
            table[place] = inNum;
            ++capUse;
        }

        //判断是否满了
        if(capUse==tableCap) {
            cout << "Table full" << endl;
            return 0;
        }

        //不满就输出位置并返回继续
        cout << place << endl;
        return 1;
    }
};

int main()
{
    int m,p;
    cin>>m>>p;
    HashTable hashTable(m,p);
    while(true){
        int tmpNum;
        cin>>tmpNum;

        if(hashTable.insert(tmpNum))
            continue;
        break;
    }

    return 0;
}