#include<bits/stdc++.h>


using namespace std;    
string s = "";
long long solver(int idx, int isSmall, vector<vector<int>> &dp){


    if(idx==s.size()) return 1;
    if(dp[idx][isSmall]!=-1 ) return dp[idx][isSmall];

    long long ans = 0;
    int limit = isSmall?(s[idx]-'0'):9;
    for(int digit=0;digit<=limit;digit++){
        if(digit==3) continue;
        bool new_tight = isSmall | (digit<limit);
        ans+=solver(idx+1,new_tight);
    }
    return dp[idx][isSmall] = ans;
}
long long solve(long long n){
    if(n<0) return 0;
    if(n==0) return 1;

    s = to_string(n);
    int len = s.size();
    vector<vector<int>> dp(len,vector<vector<int>>(2));
    return solver(0,1,dp)-1;
}
int main() {

    long long a,b;

    cin>>a>>b;
    long long countB = solve(b);
    long long countB = solve(a-1);
    cout<<countB - countA<<endl;
    return 0;
}