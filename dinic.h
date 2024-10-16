#include<bits/stdc++.h>
using namespace std;
using vvi=vector<vector<int>>;
//O(V^2*E)
class Dinic{
    int S,E,N;
    const int INF=1e9;
    vvi g,c,f;
    vector<int>lv,it;
    bool bfs(){
        lv=vector<int>(N+1,-1);
        lv[S]=0;
        queue<int>q;
        q.push(S);
        while(q.size()){
            int cur=q.front();q.pop();
            for(const auto &nxt:g[cur]){
                if(lv[nxt]==-1 and c[cur][nxt]-f[cur][nxt]>0){
                    lv[nxt]=lv[cur]+1;
                    q.push(nxt);
                }
            }
        }
        return lv[E]!=-1;
    }
    int dfs(int cur,int flow){
        if(cur==E) return flow;
        for(int i=it[cur];i<g[cur].size();i++){
            int nxt=g[cur][i];
            if(lv[nxt]-1==lv[cur] and c[cur][nxt]-f[cur][nxt]>0){
                int k=dfs(nxt,min(flow,c[cur][nxt]-f[cur][nxt]));
                if(k){
                    f[cur][nxt]+=k;
                    f[nxt][cur]-=k;
                    it[cur]=i;
                    return k;
                }
            }
        }
        it[cur]=g[cur].size();
        return 0;
    }
    public:
    //ex) N+1 Source N+2 Sink
    Dinic(int n):N(n){
        g=vvi(N+1);
        c=vvi(N+1,vector<int>(N+1));
        f=vvi(N+1,vector<int>(N+1));
    }
    int solve(int s,int e){
        S=s;
        E=e;
        int ret=0;
        while(bfs()){
            it=vector<int>(N+1);
            while(1){
                int flow=dfs(S,INF);
                if(flow) ret+=flow;
                else break;
            }
        }
        return ret;
    }
    void add_edge(int x,int y,int cs=0){
        //custom
        g[x].push_back(y);
        g[y].push_back(x);
        c[x][y]=(cs==0?INF:cs);
    }
};