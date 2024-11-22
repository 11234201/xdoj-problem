// main.cpp文件

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
using namespace std;


class MazeFather{
public:
    virtual void inputData()=0;
    virtual void findPath()=0;
    virtual void outputPath()=0;
    virtual ~MazeFather() = default;
};

class Maze: public MazeFather{
private:
    int n,m,startX,startY,endX,endY;
    int dfsStopFlag;
    vector<vector<int> > mazeMatrix;
    vector<vector<int> > dis;

    struct Node{
        Node(int xx, int yy)
        : x(xx),y(yy),cost(0),f(0),direction(-1){}
        Node(int xx, int yy, int c,int f)
        : x(xx),y(yy),cost(c),f(f),direction(-1){}
        Node(int xx, int yy, int c,int f, int d)
        : x(xx),y(yy),cost(c),f(f),direction(d){}
        int x,y;
        int cost=0;
        int f=0;
        int direction=-1;
        bool operator < (const Node other)const{
            return f < other.f;
        }
        bool operator == (const Node other)const{
            return x==other.x&&y==other.y;
        }
    };
    vector<vector<Node> > pre;
    Node direction[4]={{0,1},  {1,0},
                       {0,-1},  {-1,0}};

    //判断越界
    bool beyondBoundary(int x, int y) const{
        if(x<0||y<0||x>=n||y>=m)
            return true;
        return false;
    }
    //计算曼哈顿距离
    static int manhattanDis(int ax,int ay, int bx,int by){
        return abs(ax-bx)+ abs(ay-by);
    }

//A* algorithm ,题目要求的是用深度优先搜索
    void AStar(){
        priority_queue<Node> q;
        int manhattan= manhattanDis(startX,startY,endX,endY);
        q.push({startX,startY,0,manhattan});
        dis[startX][startY]=0;
        while(!q.empty()){
            Node curNode=q.top();
            q.pop();
            for(int i=0;i<4;i++){
                int newX=curNode.x+direction[i].x;
                int newY=curNode.y+direction[i].y;
                int newCost=curNode.cost+1;
                //判断越界
                if(beyondBoundary(newX,newY))
                    continue;
                if(mazeMatrix[newX][newY])
                    continue;
                if(dis[newX][newY]>newCost){
                    dis[newX][newY]=newCost;
                    curNode.direction=i;
                    pre[newX][newY]=curNode;

                    int f=newCost + manhattanDis(newX,newY,
                                                 endX,endY);
                    q.push({newX,newY,newCost,f});
                }
            }
        }
    }



    void dfs(int x,int y, int cost){
        if(x==endX&&y==endY){
            dfsStopFlag=1;

            return;
        }
        if(dfsStopFlag)
            return;
        if(!dis[x][y])
            return;
        for(int i=0;i<4;i++){
            int newX=x+direction[i].x;
            int newY=y+direction[i].y;
            int newCost=cost+1;
            //判断越界
            if(beyondBoundary(newX,newY))
                continue;
            if(!dis[newX][newY])
                continue;
            if(mazeMatrix[newX][newY])
                continue;
            pre[newX][newY]=Node({x,y,cost,0,i});
            dis[x][y]=0;
            dfs(newX,newY,newCost);
            //dis[newX][newY]=1;
            if(dfsStopFlag)
                break;
        }
    }

    void dfsStart(){
        //dis[startX][startY]=0;
        dfs(startX,startY,0);
    }

    //递归调用输出
    void recursionOutput(int x,int y,int d){
        Node &preNode=pre[x][y];
        if(preNode==Node({-1,-1})){
            cout<<'('<<x+1<<','<<y+1<<','<<d+1 <<')';
            return;
        }
        recursionOutput(preNode.x,preNode.y,preNode.direction);

        cout<<",("<<x+1<<','<<y+1<<','<<d+1 <<')';
    }
public:
    Maze(){    }

    //输入数据和初始化
    void inputData() override{
        cin>>n>>m>>startX>>startY>>endX>>endY;
        vector<int> tmp;
        tmp.resize(m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cin >> tmp[j];
            mazeMatrix.push_back(tmp);
        }
        --startX,--startY,--endX,--endY;
        //初始化dis
        tmp.assign(m,0x3fffffff);
        for(int i=0;i<n;i++)
            dis.push_back(tmp);
        //初始化pre，pre表示路径上某个点的上一个点数据
        vector<Node> tmpNode;
        tmpNode.assign(m,{-1,-1});
        for(int i=0;i<n;i++)
            pre.push_back(tmpNode);
        dfsStopFlag=0;

    }

    //path finding algorithm
    void findPath() override{
        dfsStart();
    }

    void outputPath() override{
        if(pre[endX][endY].direction!=-1)
            recursionOutput(endX,endY,0);
        else
            cout<<"no";
    }
};

int main()
{
    MazeFather* solveP = new Maze();
    solveP->inputData();
    solveP->findPath();
    solveP->outputPath();
    delete(solveP);
    return 0;
}