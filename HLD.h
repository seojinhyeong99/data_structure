#include<bits/stdc++.h>
using namespace std;
using ll = long long;
class Lazy_Seg{
    int N;
    public:
    Lazy_Seg(int n):N(n){}
};
class HLD{
    vector<int>sz,dep,par,top,in;
    vector<vector<int>>g;
    int cnt=0,N;
    //need segmenttree
    Lazy_Seg seg;
    void init(){
        sz=vector<int>(N+1);
        dep=vector<int>(N+1);
        par=vector<int>(N+1);
        top=vector<int>(N+1);
        top[1]=1;
        in=vector<int>(N+1);
    }
    //g2 is (idx,val) or (idx)
    void set_tree(int x,int p,vector<vector<int>>&g2){
        for(const auto& i:g2[x]){
            if(i==p) continue;
            g[x].push_back(i);
            set_tree(i,x,g2);
        }
    }
    void dfs1(int x){
        sz[x]=1;
        for(auto& i:g[x]){
            par[i]=x;
            dep[i]=dep[x]+1;
            dfs1(i);
            sz[x]+=sz[i];
            if(sz[g[x][0]]<sz[i]) swap(g[x][0],i);
        }
    }
    void dfs2(int x){
        //ett
        in[x]=++cnt;
        for(const auto &i:g[x]){
            top[i]=(i==g[x][0]?top[x]:i);
            dfs2(i);
        }
    }
    //idx,depth
    pair<int,int> find_LCA(int a,int b){
        //Small to Lage
        while(top[a]!=top[b]){
            if(dep[top[a]]<dep[top[b]]) swap(a,b);
            a=par[top[a]];
        }
        if(dep[a]==dep[b]) return {a,dep[a]};
        if(dep[a]<dep[b]) swap(a,b);
        return {b,dep[b]};
    }
    public:
    //exist tree case
    HLD(int n):N(n),seg(Lazy_Seg(n)){}
    HLD(int n,vector<vector<int>>&g2):N(n),seg(Lazy_Seg(n)){
        init();
        g=vector<vector<int>>(N+1);
        set_tree(1,0,g2);
        dfs1(1);
        dfs2(1);
    }
    void seg_graph(vector<vector<int>>&g2){
        g=g2;
        init();
        dfs1(1);
        dfs2(1);
    }
};