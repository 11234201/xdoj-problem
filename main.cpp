// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
using namespace std;

struct TNode{
    int cFreq;
    int lChild,rChild;

    TNode(): cFreq(0), lChild(-1), rChild(-1){}
    explicit TNode(int c): cFreq(c), lChild(-1), rChild(-1){}
    TNode(int c,int l,int r): cFreq(c), lChild(l), rChild(r){}
    bool operator < (const TNode other)const{
        return cFreq>other.cFreq;
    }
};


class huffmanTree{
private:
    int n;
    int index;
    vector<TNode> tree;
    priority_queue<TNode> minHeap;
public:
    huffmanTree(int num, vector<int> f):n(num){
        //tree.resize(2*n-1);
        TNode tmpNode;
        for(int i=0;i<n;i++){
            tmpNode.cFreq=f[i];
            minHeap.push(tmpNode);
        }
    }
    void BuildTree(){
        index=0;
        while(minHeap.size()>1){
            TNode left =minHeap.top();minHeap.pop();
            TNode right=minHeap.top();minHeap.pop();
            TNode newNode={right.cFreq+left.cFreq,index,index+1};
            tree.push_back(left);
            tree.push_back(right);
            minHeap.push(newNode);
            index+=2;
        }
        tree.push_back(minHeap.top());
//        ++index;
    };


    int calWPL(int i,int deep){
        if(tree[i].lChild==-1&&tree[i].rChild==-1)
            return deep*tree[i].cFreq;
        return calWPL(tree[i].lChild,deep+1)
               + calWPL(tree[i].rChild,deep+1);
    }

    int solve(){
        return calWPL(index,0);
    }
};

int main()
{
    int n;
    vector<int> freq;
    cin>>n;
    freq.resize(n);
    for(int i=0;i<n;++i)
        cin>>freq[i];
    huffmanTree HTree(n,freq);
    HTree.BuildTree();
    cout<<HTree.solve()<<endl;
    return 0;
}