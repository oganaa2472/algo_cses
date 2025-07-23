#include <bits/stdc++.h>
using namespace std;
int mod = 1e9+7;
long long solve(int n, vector<long long>& dp){
    if(n==0) return 1;
    if(dp[n]!=-1) return dp[n];
    long long answer = 0;
    for(int i = 1;i<=6;i++){
        if(n-i>=0){
            answer=(answer + solve(n-i,dp))%mod;  
        }
    }
    return dp[n] = answer;
}
int main() {
	// your code goes here
    int n ;
    cin>>n;
    vector<long long> dp(n+1,0);
    dp[0] = 1;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=6;j++){
            if(i-j>=0){
                dp[i]=(dp[i]+dp[i-j])%mod;
            }
        }
    }
    cout<<dp[n];
}
