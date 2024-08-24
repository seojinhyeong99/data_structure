#include<bits/stdc++.h>
using namespace std;
class Seg{
    int N;
    vector<int>st;
    void init(int n,int s,int e,vector<int>&v){
        if(s==e){
            st[n]=v[s];
            return;
        }
        int m=s+e>>1;
        init(n*2,s,m,v);
        init(n*2+1,m+1,e,v);
    }
    //not stable
    int kth_num(int n,int s,int e,int k){
        if(s==e) return s;
        int m=s+e>>1;
        if(st[n*2]<=k){
            return kth_num(n*2,s,m,k);
        }
        else{
            return kth_num(n*2+1,m+1,e,k-st[n*2]);
        }
    }
    //moderation
    int query(int n,int s,int e,int l,int r){
        if(l<=s and e<=r) return st[n];
        if(e<l or r<s) return 0;
        int m=s+e>>1;
        int l_segment=query(n*2,s,m,l,r);
        int r_segment=query(n*2+1,m+1,e,l,r);
        //sum
        return l_segment+r_segment;
        //max
        //return max(l_segment,r_segment);
    }
    void update(int n,int s,int e,int l,int r,int diff){
        //assert(l==r);
        //l!=r case need lazysegment
        if(e<l or r<s) return;
        st[n]+=diff;
        int m=s+e>>1;
        update(n*2,s,m,l,r,diff);
        update(n*2+1,m+1,e,l,r,diff);
    }
    void change(int n,int s,int e,int idx,int val){
        if(e<idx or idx<s) return;
        if(s==e){
            st[idx]=val;
            return;
        }
        int m=s+e>>1;
        change(n*2,s,m,idx,val);
        change(n*2+1,m+1,e,idx,val);
        //sum
        st[n]=st[n*2]+st[n*2+1];
        //max
        //st[n]=max(st[n*2],st[n*2+1]);
    }
    public:
    Seg(int n):N(n){
        st=vector<int>(N*4);
    }
    Seg(int n,vector<int>&v):N(n){
        st=vector<int>(N*4);
        init(1,0,N-1,v);
    }
};