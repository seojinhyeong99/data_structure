#include<bits/stdc++.h>
using namespace std;
using vvi=vector<vector<int>>;
class SCC{
    stack<int>s;
    int id,N;
    vector<int>d,it,in_degree;
    vector<bool>c;
    vvi g,scc;
    int dfs(int x){
        s.push(x);
        d[x]=++id;
        int p=d[x];
        for(const auto &y:g[x]){
            if(!d[y]) p=min(p,dfs(y));
            else if(!c[y]) p=min(p,d[y]);
        }
        if(d[x]==p){
            vector<int>v;
            while(1){
                int y=s.top();s.pop();
                it[y]=scc.size();
                c[y]=true;
                v.push_back(y);
                if(x==y) break;
            }
            scc.push_back(v);
        }
        return p;
    }
    public:
    SCC(int n):N(n){
        id=0;
        d=vector<int>(N+1);
        it=vector<int>(N+1);
        c=vector<bool>(N+1);
        scc.clear();
        g=vvi(N+1);
    }
    void add_edge(int x,int y){
        g[x].push_back(y);
    }
    void solve_scc(){
        for(int i=1;i<=N;i++){
            if(!d[i]) dfs(i);
        }
    }
    vvi get_scc(){
        return scc;
    }
    //idx is [0~scc.size())
    vvi new_graph(){
        vvi G(scc.size());
        in_degree=vector<int>(scc.size());
        for(int i=1;i<=N;i++){
            for(const auto &j:g[i]){
                if(it[i]==it[j]) continue;
                in_degree[it[j]]++;
                G[it[i]].push_back(it[j]);
            }
        }
        return G;
    }
    vector<int> get_degree(){
        return in_degree;
    }
    int find_group(int x){
        return it[x];
    }
};