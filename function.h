#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
using a3=array<int,3>;
using a4=array<int,4>;
using a5=array<int,5>;
using vvi=vector<vector<int>>;
constexpr ll mod=1e9+7;
//condinate compression
function<vector<int>(vector<int>)>condinate_compression=[](vector<int>v){
    vector<int>ret(v);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(auto &x:ret){
        x=lower_bound(v.begin(),v.end(),x)-v.begin();
    }
    return ret;
};
//first : data, second mapping
function<pair<vector<int>,vector<int>>(vector<int>)>condinate_compression_2=[](vector<int>v){
    pair<vector<int>,vector<int>>ret;
    ret.first=v;
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    ret.second=v;
    for(auto &x:ret.first){
        x=lower_bound(v.begin(),v.end(),x)-v.begin();
    }
    return ret;
};
//matrix mul
vvi operator*(vvi& a,vvi& b){
    int n=a.size();
    vvi ret(n,vector<int>(n,0));
    for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++) ret[i][j]=((ll)ret[i][j]+(ll)a[i][k]*(ll)b[k][j])%mod;
    return ret;
}
//matrix add
vvi operator+(vvi& a,vvi &b){
    int n=a.size();
    vvi ret=vvi(n,vector<int>(n,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) ret[i][j]=(a[i][j]+b[i][j])%mod;
    return ret;
}
//matrix power
function<vvi(vvi,int)>Matrix_Pow=[](vvi v,int k){
    int n=v.size();
    vvi ret(n,vector<int>(n,0));
    for(int i=0;i<n;i++) ret[i][i]=1;
    vvi a=v;
    while(k){
        if(k&1){
            ret=ret*a;
        }
        a=a*a;
        k>>=1;
    }
    return ret;
};
//matrix power psum
function<vvi(vvi,int)>Matrix_Pow_Sum=[](vvi v,int k){
    int n=v.size();
    int K=k;
    vvi y(n,vector<int>(n,0));
    vvi ret(n,vector<int>(n,0));
    for(int i=0;i<n;i++) y[i][i]=1;
    vector<vvi>dp;
    vector<vvi>p_sum;
    vvi a=v;
    p_sum.push_back(a);
    dp.push_back(a);
    int cnt=0;
    while(k){
        vvi temp=p_sum.back()*a;
        p_sum.push_back(temp+p_sum.back());
        a=a*a;
        dp.push_back(a);
        k>>=1;
        cnt++;
    }
    for(int i=cnt;i>=0;i--){
        if(K&(1<<i)){
            vvi temp=y*p_sum[i];
            ret=ret+temp;
            y=y*dp[i];
        }
    }
    return ret;
};