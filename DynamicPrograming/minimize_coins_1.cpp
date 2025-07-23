#include <bits/stdc++.h>
using namespace std;
int mod = 1e9+7;
long long solve(int n, vector<long long>& dp, vector<int>& coins){
    if(n==0) return 1;
    if(n<0) return 0;
    if(dp[n]!=-1) return dp[n];
    long long answer = 0;
    for(auto c:coins){
        if(n-c>=0){
            answer += (answer+solve(n-c,dp,coins))%mod;
        }
    }
    return dp[n] = answer;
}
int main() {
	// your code goes here
    int n,k;
    cin>>n>>k;
    vector<int> coins(n);
    for(int i = 0;i<n;i++){
        cin>>coins[i];
    }

    vector<long long> dp(k+1,-1);

    
    long long result = solve(k, dp, coins);

    int ans = (result == INT_MAX) ? -1 : result;
    cout << ans << endl;
}
