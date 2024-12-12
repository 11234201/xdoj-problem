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
    int to,next,w;
};

struct QueueStruct{
    int w,v,father;
    bool operator <(const QueueStruct& other)const{
        return w>other.w;
    }
};

class Graph{
private:
    vector<int> head;
    vector<Edge> edge;
    //访问数组
    vector<int> vis;
    //记录距离dis
    vector<int> ans;
    //记录路径上该点的上一个点
    vector<int> pre;

    map<int,char> unNameMap;
    int n,m;
    int edgeCnt=1;
public:
    Graph(int nn,int mm):n(nn), m(mm), edgeCnt(1){
        head.resize(n);
        edge.resize(m+1);

        ans.resize(n,0x3fffffff);
        vis.resize(n);
        pre.resize(n,-1);
    }


    void mkEdge(int f,int to,int w){
        edge[edgeCnt]={to,head[f],w};
        head[f]=edgeCnt;
        ++edgeCnt;
//给无向图建造边
//        edge[edgeCnt]={f,head[to]};
//        head[to]=edgeCnt;
//        ++edgeCnt;
    }

    void Dijkstra(int from,int to){
        priority_queue<QueueStruct>q;
        ans[from]=0;
        q.push({0,0,0});
        while(!q.empty()){
            auto top=q.top();  q.pop();
            int v=top.v;

            if(vis[v])
                continue;

            pre[v]=top.father;
            vis[v]=1;

            //提前退出
            if(v==to)
                break;

            for(int u=head[v];u;u=edge[u].next) {
                int t=edge[u].to;
                if(ans[t]>ans[v]+edge[u].w){
                    ans[t]=ans[v]+edge[u].w;
                    q.push({ans[t],t,v});
                }
            }
        }
        //输出结果与路径
        cout<<endl<<ans[to]<<endl;
        recurveOutput(to);
        cout<<endl;
    }

    //递归输出路径
    void recurveOutput(int n){
        if(pre[n]==n){
            cout<<unNameMap[n]<<' ';
            return;
        }
        recurveOutput(pre[n]);
        cout<<unNameMap[n]<<' ';
    }
    //编号到字母的映射，方便在类里面直接输出回溯
    void mkUnNameMap(map<char,int> &nameMap){
        for(auto &sub:nameMap){
            unNameMap[sub.second]=sub.first;
        }
    }
};


int main()
{
    while(true) {
        cin >> n >> m;
        if(n==m&&n==0)
            break;
        map<char,int> nameMap;
        //字母到编号的映射
        Graph graph(n, m);
        char tmpF, tmpT;
        int w;
        for(int i=0;i<n;++i){
            cin>>tmpF;
            nameMap[tmpF]=i;
        }
        graph.mkUnNameMap(nameMap);

        while(m--){
            cin>>tmpF>>tmpT>>w;
            graph.mkEdge(nameMap[tmpF],nameMap[tmpT],w);
        }
        cin>>tmpF>>tmpT;
        graph.Dijkstra(nameMap[tmpF],nameMap[tmpT]);
    }
    return 0;
}