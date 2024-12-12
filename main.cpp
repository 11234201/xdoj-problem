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
    int cFreq=0;
    int lChild=-1,rChild=-1;
    int father=-1;
    char c='\0';
//
//    TNode(): cFreq(0), lChild(-1), rChild(-1){}
//    explicit TNode(int c): cFreq(c), lChild(-1), rChild(-1){}
//    TNode(int c,int l,int r): cFreq(c), lChild(l), rChild(r){}
    bool operator < (const TNode other)const{
        return cFreq>other.cFreq;
    }
};


class huffmanTree{
private:
    int n;
    int index=0;
    vector<TNode> tree;
    priority_queue<TNode> minHeap;
    map<char,string> codeMap;
public:
    huffmanTree(int num, vector<pair<char,int> >& f):n(num){
        //tree.resize(2*n-1);
        TNode tmpNode;
        for(auto k:f){
            tmpNode.cFreq=k.second;
            tmpNode.c=k.first;
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

        //从顶部下来，找父节点
        //now, father
        queue<pair<int,int> > q;
        q.emplace(index,-1);
        while(!q.empty()){
            auto front=q.front();
            q.pop();
            if(front.first==-1)
                continue;
            auto &root=tree[front.first];
            root.father= front.second;
            q.emplace(root.lChild,front.first);
            q.emplace(root.rChild,front.first);
        }
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

    void encoding(){
        //node,code
        queue<pair<int,string> > q;
        q.emplace(index,"");
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            if(front.first==-1)
                continue;
            auto &root=tree[front.first];
            if(root.c)
                codeMap[root.c]=front.second;
            q.emplace(root.lChild,front.second+'0');
            q.emplace(root.rChild,front.second+'1');
        }
        for(auto &subN:codeMap){
            cout<<subN.first<<':'<<subN.second<<' ';
        }
        cout<<endl;
    }
    void outputTree(){
        for(int i=0;i<=index;++i)
            cout<<i+1<<' '<<tree[i].cFreq<<' '<<tree[i].father+1<<' '
                <<tree[i].lChild+1<<' '<<tree[i].rChild+1<<endl;
    }

    void outputCoding(string &input){
        for(auto &c:input)
            cout<<codeMap[c];
        cout<<endl;
    }

};

int main()
{
    string input;
    while(true) {
        cin>>input;
        if(input=="0")
            break;

        int n=0;
        vector<pair<char,int> > freq;
        int cnt[26]={0};
        for(auto &subC:input)
            ++cnt[subC-'a'];
        for(int i=0;i<26;++i)
            if(cnt[i]){
                ++n;
                freq.emplace_back(i+'a',cnt[i]);
                cout<<char('a'+i)<<':'<<cnt[i]<<' ';
            }
        cout<<endl;

        huffmanTree HTree(n, freq);
        HTree.BuildTree();
        HTree.outputTree();
        HTree.encoding();
        HTree.outputCoding(input);
    }
    return 0;
}