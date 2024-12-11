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
};

class Graph{
private:
    vector<int> head;
    vector<Edge> edge;
    vector<int> vis;
    vector<int> ans;
    int n,m;
    int edgeCnt=1;
    int stop;
public:
    Graph(int nn,int mm):n(nn), m(mm), edgeCnt(1),stop(0){
        head.resize(n);
        edge.resize(m*2+1);

        vis.resize(n);
    }

    //给无向图建造边
    void mkEdge(int f,int to){
        edge[edgeCnt]={to,head[f]};
        head[f]=edgeCnt;
        ++edgeCnt;

//        edge[edgeCnt]={f,head[to]};
//        head[to]=edgeCnt;
//        ++edgeCnt;
    }

    void dfs(int v){
        if(v==n-1){
            ans.push_back(v);
            stop=1;
            return;
        }
        for(int u=head[v];u;u=edge[u].next){
            int to=edge[u].to;
            if(vis[to])
                continue;

            vis[to]=1;
            dfs(to);
            vis[to]=0;

            if(stop) {
                ans.push_back(v);
                break;
            }
        }
    }

    void bfs(){
        queue<int > q;
        q.push(0);
        vis[0]=1;
        vector<int> pre;
        while(!q.empty()){
            int v=q.front();
            ans.push_back(v);
            q.pop();
            if(v==n-1) {
                stop=1;
            }
            for(int u=head[v];u;u=edge[u].next){
                int to=edge[u].to;
                if(vis[to])
                    continue;
                q.push(to);
                vis[to]=1;
            }
        }
        if(!stop){
            cout<<"NO"<<endl;
            return;
        }
        cout<<"YES"<<endl;
        for(int & an : ans)
            cout<<1+an<<' ';
    }

    void solve(){
        vis[0]=1;
        ans.clear();
        dfs(0);
//        bfs();
        if(stop){
            cout<<"NO"<<endl;
            return;
        }
        cout<<"YES"<<endl;
        for(auto i=ans.rbegin();i!=ans.rend();++i)
            cout<<1+*i<<' ';
    }

};

int cmp(pair<int,int>a, pair<int,int >b){
    if(a.first==b.first)
        return a.second>b.second;
    return a.first>b.first;
}

int main()
{

    cin>>n>>m;
    Graph graph(n,m);
    int tmpF,tmpT;
    vector<pair<int,int> > store;
    for(int i=0;i<m;++i){
        cin>>tmpF>>tmpT;
        store.emplace_back(tmpF,tmpT);
        store.emplace_back(tmpT,tmpF);
    }
    sort(store.begin(),store.end(), cmp);
    for(auto & e:store){
        graph.mkEdge(e.first-1,e.second-1);
    }
    //以上存储排序操作为了保证遍历时候编号小的在前
//    graph.solve();
    graph.bfs();
    return 0;
}