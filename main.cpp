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
public:
    Graph(int nn,int mm):n(nn), m(mm), edgeCnt(1){
        head.resize(n);
        edge.resize(m*2+1);

        vis.resize(n);
    }

    //给无向图建造边
    void mkEdge(int f,int to){
        edge[edgeCnt]={to,head[f]};
        head[f]=edgeCnt;
        ++edgeCnt;

        edge[edgeCnt]={f,head[to]};
        head[to]=edgeCnt;
        ++edgeCnt;
    }

    //从某一个点start开始遍历所有能到的点，并标记为num
    void Traversal(int start,int num){
        queue<int> q;
        q.push(start);
        vis[start]=num;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v=head[u];v;v=edge[v].next) {
                int& to = edge[v].to;
                if (!vis[to]) {
                    q.push(to);
                    vis[to] = num;
                }
            }
        }
    }

    void Find(){
        int subGraphNum=0;
        for(int i=0;i<n;++i){
            if(vis[i])
                continue;
            ++subGraphNum;
            Traversal(i,subGraphNum);
        }

        ans.resize(subGraphNum);
        //统计答案，因为num是从1开始的，所以--后再统计
        for(int i=0;i<n;++i)
            ++ans[--vis[i]];

        sort(ans.begin(),ans.end());
    }

    friend ostream& operator << (ostream& s, const Graph & g){
        s << g.ans.size() << endl;
        for(auto & i : g.ans)
            s<<i<<' ';
        return s;
    }

};

int main()
{

    cin>>n>>m;
    Graph graph(n,m);
    int tmpF,tmpT;
    for(int i=0;i<m;++i){
        cin>>tmpF>>tmpT;
        graph.mkEdge(tmpF-1,tmpT-1);
    }
    graph.Find();
    cout<<graph;

    return 0;
}