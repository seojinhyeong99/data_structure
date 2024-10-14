#include<bits/stdc++.h>
using namespace std;
class B_match{
    //n->m
    int N,M;
    vector<bool>c;
    vector<int>it;
    vector<vector<int>>g;
    bool dfs(int x){
        for(const auto &i:g[x]){
            if(c[i]) continue;
            c[i]=true;
            if(it[i]==-1 or dfs(it[i])){
                it[i]=x;
                return true;
            }
        }
        return false;
    }
    public:
    B_match(int n,int m):N(n),M(m){
        c=vector<bool>(M+1);
        it=vector<int>(M+1,-1);
        g=vector<vector<int>>(N+1);
    }
    //x->y
    void add_edge(int x,int y){
        g[x].push_back(y);
    }
    bool try_match(int x){
        fill(c.begin(),c.end(),false);
        return dfs(x);
    }
};