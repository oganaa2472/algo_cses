#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int solve(int amount,vector<int>& dp,vector<int>& coins){
    if(amount==0) return 1;
    if(amount<0) return 0;
    if(dp[amount]!=-1) return dp[amount];
    int res = 0;
    for(int pos=0;pos<coins.size();pos++){
        if(amount-coins[pos]>=0){
             res =(res+solve(amount-coins[pos],dp,coins))%mod;
        }
    }
    return dp[amount] = res;
}
int main() {
	// your code goes here
    int n,m;
    cin>>n>>m;
    vector<int> dp(m+1,-1);
    vector<int> coins(n);
    for(int i=0;i<n;i++)  cin>>coins[i];
    int res = solve(m,dp,coins);
    if(res==INT_MAX) cout<<-1<<endl;
    else cout<<res<<endl;
    return 0;
}
