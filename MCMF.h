#include<bits/stdc++.h>
using namespace std;
using ll=long long;
class MCMF{
    int N;
    const ll INF=1e18;
    vector<vector<ll>>f,d,c;
    vector<vector<ll>>g;
    public:
    MCMF(int n):N(n){
        f=vector<vector<ll>>(n+1,vector<ll>(n+1));
        d=vector<vector<ll>>(n+1,vector<ll>(n+1));
        c=vector<vector<ll>>(n+1,vector<ll>(n+1));
        g=vector<vector<ll>>(n+1);
    }
    void add_eg(int u,int v,ll x,ll y=0){
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v]=x;
        d[u][v]=y;
        d[v][u]=-y;
    }
    //flow,cost
    pair<ll,ll> mcmf(int s,int e){
        pair<ll,ll>ret;
        vector<int>it(N+1,-1);
        while(1){
            it[e]=-1;
            vector<ll>dist(N+1,INF);
            vector<bool>inq(N+1);
            queue<int>q;
            q.push(s);
            inq[s]=true;
            dist[s]=0;
            while(q.size()){
                int cur=q.front();q.pop();
                inq[cur]=false;
                for(auto nxt:g[cur]){
                    if(c[cur][nxt]-f[cur][nxt]>0&&dist[nxt]>dist[cur]+d[cur][nxt]){
                        it[nxt]=cur;
                        dist[nxt]=dist[cur]+d[cur][nxt];
                        if(!inq[nxt]){
                            q.push(nxt);
                            inq[nxt]=true;
                        }
                    }
                }
            }
            if(it[e]==-1) break;
            ll flow=INF;
            for(int i=e;i!=s;i=it[i]){
                flow=min(flow,c[it[i]][i]-f[it[i]][i]);
            }
            ret.first+=flow;
            ret.second+=flow*dist[e];
            for(int i=e;i!=s;i=it[i]){
                f[it[i]][i]+=flow;
                f[i][it[i]]-=flow;
            }
        }
        return ret;
    }
};