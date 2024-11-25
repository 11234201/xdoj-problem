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

int n,m;

struct Edge{
    int to,next;
    int w;

    Edge():to(0),next(0),w(0){}
    Edge(int a,int b):to(a),next(b),w(0){}
    Edge(int a,int b,int c):to(a),next(b),w(c){}

    bool operator < (const Edge& other) const{
        if(w==other.w) {
            if (to == other.to)
                return next < other.next;
            else
                return to < other.to;
        }
        return w<other.w;
    }
};

class Graph{
private:
    vector<int> head;
    vector<Edge> edge;
    vector<Edge> store;
    vector<int> fa;
    vector<Edge> ans;
    int n,m;
    int edgeCnt=1;
public:
    Graph(int nn,int mm):n(nn), m(mm), edgeCnt(1){
        head.resize(n);
        edge.resize(m*2+1);

        fa.resize(n);
        for(int i=0;i<n;++i)
            fa[i]=i;
    }

    void storeEdge(int f,int to,int w){
        //保证f小于to
        if(f>to){
            f=f^to;
            to=f^to;
            f=f^to;
        }
        store.emplace_back(f,to,w);
    }

    int Fa(int a){
        if(fa[a]==a)
            return a;
        return fa[a]=Fa(fa[a]);
    }

    void Kruskal(){
        sort(store.begin(),store.end());
        int cnt=1;
        for(auto &subEdge: store){
            int lfa=Fa(subEdge.to), rfa=Fa(subEdge.next);
            if(lfa!=rfa){
                fa[rfa]=lfa;
                ans.push_back(subEdge);
                ++cnt;
                if(cnt==n)
                    break;
            }
        }
    }

    friend ostream& operator << (ostream& s, const Graph & g){
        for(auto &subEdge: g.ans){
            printf("%d %d %d\n",subEdge.to+1,subEdge.next+1,subEdge.w);
        }
        return s;
    }

};

int main()
{

    cin>>n>>m;
    Graph graph(n,m);
    int tmpF,tmpT,tmpW;
    for(int i=0;i<m;++i){
        cin>>tmpF>>tmpT>>tmpW;
        graph.storeEdge(tmpF-1,tmpT-1,tmpW);
    }
    graph.Kruskal();
    cout<<graph;

    return 0;
}