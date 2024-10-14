#include<bits/stdc++.h>
using namespace std;
class Lazy_Seg{
    int N;
    vector<int>st,prop;
    void init(int n,int s,int e,vector<int>&v){
        if(s==e){
            st[n]=v[s];
            return;
        }
        int m=s+e>>1;
        init(n*2,s,m,v);
        init(n*2+1,m+1,e,v);
        st[n]=st[n*2]+st[n*2+1];
    }
    void push(int n,int s,int e){
        st[n]+=prop[n];
        if(s!=e){
            for(auto i:{n*2,n*2+1}){
                prop[i]+=prop[n];
            }
        }
        prop[n]=0;
    }
    int query(int n,int s,int e,int l,int r){
        if(r<s or e<l) return 0;
        push(n,s,e);
        if(l<=s and e<=r) return st[n];
        int m=s+e>>1;
        return query(n*2,s,m,l,r)+query(n*2+1,m+1,e,l,r);
    }
    void update(int n,int s,int e,int l,int r,int diff){
        push(n,s,e);
        if(r<s or e<l) return;
        if(l<=s and e<=r){
            prop[n]+=diff;
            push(n,s,e);
            return;
        }
        int m=s+e>>1;
        update(n*2,s,m,l,r,diff);
        update(n*2+1,m+1,e,l,r,diff);
        st[n]=st[n*2]+st[n*2+1];
    }
    public:
    Lazy_Seg(int n):N(n){
        st=vector<int>(N*4);
        prop=vector<int>(N*4);
    }
    Lazy_Seg(int n,vector<int>&v):N(n){
        st=vector<int>(N*4);
        prop=vector<int>(N*4);
        init(1,0,N-1,v);
    }
};