#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int solve(int i,vector<int>& dp){
    if(i==0) return 1;
    if(dp[i]!=-1) return dp[i];
    int res = 0;
    for(int pos=1;pos<=6;pos++){
        if(i-pos>=0){
            res=(res+solve(i-pos,dp))%mod;
        }
    }
    return dp[i] = res;
}
int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<int> dp(n+2,-1);
    cout<<solve(n,dp);
    return 0;
}
