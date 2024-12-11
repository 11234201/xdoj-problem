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

class Stock{
private:
    int cash;
    int quantity;
    int price;
public:
    Stock(int num,int p)
    :quantity(num),price(p),cash(0){}

    void change(int num,int p){
        quantity+=num;
        price=p;
        cash-=p*num;
    }
    void cnt(){
        cout<<price*quantity+cash<<endl;
    }
};

int main()
{
    int m,p,n;
    cin>>m>>p>>n;
    Stock stock(m,p);
    while(n--){
        cin>>m>>p;
        stock.change(m,p);
    }
    stock.cnt();
    return 0;
}