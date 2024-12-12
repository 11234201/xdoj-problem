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

struct snVal{
    string name;
    double price;
};
struct nameVal{
    string sn;
    double price;
};

class LibrarySystem{
private:
    map<string,snVal> snList;
    multimap<string,nameVal> nameList;
    vector<pair<string ,snVal>> store;
    double totalPrice=0;
public:
    //以0 0 0 结尾的输入
    void basicInput(){
        string key;
        string name;
        double p;
        while(true) {
            cin >> key >> name >> p;
            if(key=="0"&&name=="0")
                break;
            insert(key,name,p);
            store.push_back({key,{name,p}});
            totalPrice+=p;
        }
        cout<<endl;
    }
    //其他输入
    void basicInput(int n){
        string key;
        string name;
        double p;
        while(n--){
            cin >> key >> name >> p;
            insert(key,name,p);
            store.push_back({key,{name,p}});
        }
        cout<<endl;

    }
    //插入新元素
    void insert(string &key, string &name, double p){
        nameList.insert({name,{key,p}});
    }

    void output(){
        for(auto & sub: store)
            cout<<sub.first<<' '<<sub.second.name<<' '<<sub.second.price<<endl;
    }

    //返回不重复元素个数
    size_t returnSize(){
        return store.size();
    }
    //Q3重新编排价格
    void rePrice(){
        double average=totalPrice/store.size();
        for(auto & sub: store)
            if(sub.second.price<average)
                sub.second.price*=1.2;
            else
                sub.second.price*=1.1;
        output();
    }

    static int cmp1(const pair<string ,snVal>& a, const pair<string ,snVal>& b){
        return a.second.price>b.second.price;
    }
    static int cmp2(const pair<string ,snVal>& a, const pair<string ,snVal>& b){
        return a.second.price<b.second.price;
    }
    void Sort(int n){
        if(n==1)
            sort(store.begin(),store.end(),cmp1);
        else
            sort(store.begin(),store.end(),cmp2);
    }

    //Q5
    void findMaxPrice(){
        double maxPrice;
        int flag=1;
        for(auto &sub:store){
            if(flag){
                maxPrice=sub.second.price;
                flag=0;
            }
            if(abs(maxPrice-sub.second.price)<1e-6)
                cout<<sub.first<<' '<<sub.second.name<<' '<<sub.second.price<<endl;
            else
                break;
        }
    }
    //Q6
    void findName(string &name){
        auto range=nameList.equal_range(name);
        auto count=distance(range.first,range.second);
        if(!count) {
            cout << "Sorry, system don't have your favorite!" << endl;
            return;
        }
        for(auto it=range.first;it!=range.second;++it)
            cout<<it->second.sn<<' '<<it->first<<' '<<it->second.price<<endl;
    }
    //Q7
    void findBook(int index){
        if(!index||index>store.size()){
            cout<<"Sorry, the book in the best position does not exist!"<<endl;
            return;
        }
        auto &sub=store[index-1];
        cout<<sub.first<<' '<<sub.second.name<<' '<<sub.second.price<<endl;
    }
    //Q8
    void insertNew(){
        int pos;
        string sn,name;
        double p;
        cin>>pos>>sn>>name>>p;
        if(!pos||pos>store.size()+1){
            cerr<<"Error!!!"<<endl;
            return;
        }
        store.insert(store.begin()+pos-1,{sn,{name,p}});
    }
    //Q9
    void erase(){
        int pos;
        cin>>pos;
        if(!pos||pos>store.size()){
            cerr<<"Error!!!"<<endl;
            return;
        }
        store.erase(store.begin()+pos-1);
    }
    //Q10
    void removeDup(){
        snList.clear();
        int i=-1;
        vector<int> era;
        for(auto sub=store.begin();sub!=store.end();++sub){
            ++i;
            auto it=snList.find(sub->first);
            if(it==snList.end())
                snList[sub->first]=sub->second;
            else
                era.push_back(i);
        }
        for(auto ii=era.rbegin();ii!=era.rend();++ii)
            store.erase(store.begin()+ *ii);
    }
};


int main()
{
    cout<<"input your operation, limited in num 1~10:"<<endl
        <<"1: Book information table creation and output"<<endl
        <<"2: Sort the book information table"<<endl
        <<"3: Book information table modification"<<endl
        <<"4: Reverse storage of the book information table"<<endl
        <<"5: Book information table for finding the most expensive books"<<endl
        <<"6: Book information table for finding favorite books"<<endl
        <<"7: Book information table the best place to find books"<<endl
        <<"8: The entry of new books into the library of the book information sheet"<<endl
        <<"9: Book information table for old books out of storage"<<endl
        <<"10: The book information table removes the weight of the book"<<endl
        <<"please input Question NUM: ";

    int op;
    cin>>op;
    cout<<"you choose Q "<<op<<" !"<<endl;
    LibrarySystem sys;
    cout<<fixed<<setprecision(2);

    switch (op) {
        case 1:{
            sys.basicInput();
            cout<<sys.returnSize()<<endl;
            sys.output();
            break;
        }
        case 2:{
            sys.basicInput();
            sys.Sort(1);
            sys.output();
            break;
        }
        case 3:{
            sys.basicInput();
            sys.rePrice();
            break;
        }
        case 4:{
            int n;
            cin>>n;
            sys.basicInput(n);
            sys.Sort(2);
            sys.output();
            break;
        }
        case 5:{
            int n;
            cin>>n;
            sys.basicInput(n);
            sys.Sort(1);
            sys.findMaxPrice();
            break;
        }
        case 6:{
            int n,m;
            cin>>n;
            sys.basicInput(n);
            cin>>m;
            string tmpS;
            while(m--){
                cin>>tmpS;
                sys.findName(tmpS);
            }
            break;
        }
        case 7:{
            int n,m;
            cin>>n;
            sys.basicInput(n);
            cin>>m;
            int tmpInt;
            while(m--){
                cin>>tmpInt;
                sys.findBook(tmpInt);
            }
            break;
        }
        case 8:{
            int n;
            cin>>n;
            sys.basicInput(n);
            sys.insertNew();
            sys.output();
            break;
        }
        case 9:{
            int n;
            cin>>n;
            sys.basicInput(n);
            sys.erase();
            sys.output();
            break;
        }
        case 10:{
            int n;
            cin>>n;
            sys.basicInput(n);
            sys.removeDup();
            sys.output();
            break;
        }
        default:{cerr<<"Error!!!!"<<endl;}
    }

    return 0;
}