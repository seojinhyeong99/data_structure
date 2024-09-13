#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
using a3=array<int,3>;
using a4=array<int,4>;
using a5=array<int,5>;
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