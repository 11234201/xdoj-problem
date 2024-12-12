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
        edge.resize(m*2+1);

        ans.resize(n,0x3fffffff);
        vis.resize(n);
        pre.resize(n,-1);
    }


    void mkEdge(int f,int to,int w){
        edge[edgeCnt]={to,head[f],w};
        head[f]=edgeCnt;
        ++edgeCnt;
//给无向图建造边
        edge[edgeCnt]={f,head[to],w};
        head[to]=edgeCnt;
        ++edgeCnt;
    }

    void Dijkstra(int from,int maxDis){
        priority_queue<QueueStruct>q;
        ans[from]=0;
        q.push({0,from,0});
        while(!q.empty()){
            auto top=q.top();  q.pop();
            int v=top.v;

            if(vis[v])
                continue;

            //提前退出
            if(top.w==maxDis)
                continue;
            pre[v]=top.father;
            vis[v]=1;


            for(int u=head[v];u;u=edge[u].next) {
                int t=edge[u].to;
                if(ans[t]>ans[v]+edge[u].w){
                    ans[t]=ans[v]+edge[u].w;
                    q.push({ans[t],t,v});
                }
            }
        }
        int cnt=0;
        for(auto &i:ans)
            if(i<0x3fffffff)
                ++cnt;
        cout<<100.0*cnt/n<<'%'<<endl;


        ans.assign(n,0x3fffffff);
        vis.assign(n,0);
        pre.assign(n,-1);
    }

};


int main()
{
    int n,m;
    cout<<fixed<<setprecision(2);
    while(true) {
        cin >> n >> m;
        if(n==m&&n==0)
            break;
        //字母到编号的映射
        Graph graph(n, m);
        int tmpF, tmpT;
        int w;

        while(m--){
            cin>>tmpF>>tmpT;
            graph.mkEdge(tmpF-1,tmpT-1,1);
        }
        for(int i=0;i<n;++i){
            cout<<i+1<<':';
            graph.Dijkstra(i,6);
        }
    }
    return 0;
}