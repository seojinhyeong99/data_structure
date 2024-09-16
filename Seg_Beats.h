#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>pi;
class SegBeats{
    //mx,mn
    vector<pi>st;
    vector<int>prop;
    int N;
    void init(int n,int s,int e,vector<int>&v){
        if(s==e){
            st[n]={v[s],v[s]};
            return;
        }
        int m=s+e>>1;
        init(n*2,s,m,v);
        init(n*2+1,m+1,e,v);
        pull(n,s,e);
    }
    void push(int n,int s,int e){
        if(prop[n]==0) return;
        st[n]={st[n].first+prop[n],st[n].second+prop[n]};
        if(s!=e){
            for(auto i:{n*2,n*2+1}) prop[i]+=prop[n];
        }
        prop[n]=0;
    }
    void pull(int n,int s,int e){
        st[n].first=max(st[n*2].first,st[n*2+1].first);
        st[n].second=min(st[n*2].second,st[n*2+1].second);
    }
    bool tag_conditoin(int mx,int mn,int val){
        if(mx==mn) return true;
        if(mx==mn+1 and mx/val==mn/val+1) return true;
        return false;
    }
    int get_mx(int n,int s,int e,int l,int r){
        push(n,s,e);
        if(r<s or e<l) return 0;
        if(l<=s and e<=r) return st[n].first;
        int m=s+e>>1;
        return max(get_mx(n*2,s,m,l,r),get_mx(n*2+1,m+1,e,l,r));
    }
    void add(int n,int s,int e,int l,int r,int val){
        push(n,s,e);
        if(r<s or e<l) return;
        if(l<=s and e<=r){
            prop[n]+=val;
            push(n,s,e);
            return;
        }
        int m=s+e>>1;
        add(n*2,s,m,l,r,val);
        add(n*2+1,m+1,e,l,r,val);
        pull(n,s,e);
    }
    void div(int n,int s,int e,int l,int r,int val){
        push(n,s,e);
        if(r<s or e<l) return;
        if(l<=s and e<=r and tag_conditoin(st[n].first,st[n].second,val)){
            prop[n]-=st[n].first-(st[n].first/val);
            push(n,s,e);
            return;
        }
        int m=s+e>>1;
        div(n*2,s,m,l,r,val);
        div(n*2+1,m+1,e,l,r,val);
        pull(n,s,e);
    }
    public:
    SegBeats(int n,vector<int>&v):N(n){
        st=vector<pi>(N*4,{0,2e9});
        prop=vector<int>(N*4);
        init(1,0,N-1,v);
    }
    void query(int t,int l,int r,int x){
        switch (t)
        {
        case 0:
            add(1,0,N-1,l,r,x);
            break;
        case 1:
            div(1,0,N-1,l,r,x);
            break;
        default:
            cout<<get_mx(1,0,N-1,l,r)<<"\n";
            break;
        }
    }
};