#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef pair<int, int> pi;
typedef long long ll;
using pll=pair<ll,ll>;
class GreedyMove{
    bool cmp(const pll& a,const pll& b){
        //return a>=b?
        //ax/ay>=bx/by equl ax*by>=bx*ay
        return a.first*b.second>=b.first*a.second;
    }
    vector<ll>r,c;
    stack<pll>r_st,c_st;
    pll c_sum;
    ll ans;
    public:
    GreedyMove(vector<ll>&row,vector<ll>&column):c_sum({0,0}){
        for(int i=0;i+1<row.size();i++){
            r.push_back(row[i]-row[i+1]);
        }
        for(int i=0;i+1<column.size();i++){
            c.push_back(column[i+1]-column[i]);
        }
        ans=column[0]*ll(row.size()-1)+row.back()*ll(column.size()-1);
    }
    ll solve(){
        for(int i=r.size()-1;i>=0;i--){
            pll cur={r[i],1};
            while(r_st.size() and cmp(r_st.top(),cur)){
                cur.first+=r_st.top().first;
                cur.second+=r_st.top().second;
                r_st.pop();
            }
            r_st.push(cur);
        }
        for(int i=0;i<c.size();i++){
            pll cur={c[i],1};
            c_sum.first+=cur.first;
            c_sum.second+=cur.second;
            while(c_st.size() and cmp(c_st.top(),cur)){
                cur.first+=c_st.top().first;
                cur.second+=c_st.top().second;
                c_st.pop();
            }
            c_st.push(cur);
        }
        vector<pll>v(r_st.size());
        while(r_st.size()){
            v[r_st.size()-1]=r_st.top();
            r_st.pop();
        }
        for(const auto &[x,y]:v){
            while(c_st.size() and c_st.top().first*y+x*c_st.top().second>=0){
                c_sum.first-=c_st.top().first;
                c_sum.second-=c_st.top().second;
                c_st.pop();
            }
            ans+=x*c_sum.second+c_sum.first*y;
        }
        return ans;
    }
};