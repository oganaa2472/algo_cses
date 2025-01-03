#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9+7;
int solve(long long m,vector<long long>& dp,vector<long long>& coins){
    if (m == 0) return 1; 
    if (m < 0) return 0; 

    if (dp[m] != -1) return dp[m];

    long long res = 0;
    for (long long coin : coins) {
        res+=solve(m - coin, dp,coins);
    }

    return dp[m] = res%mod;
}
int main() {
	// your code goes here
	long long n,m;
	cin>>n>>m;
	vector<long long> coins(n);
	vector<long long> dp(m+1,-1);
	for(int i=0;i<n;i++){
	    cin>>coins[i];
	}
	int answer = solve(m,dp,coins);
	cout<<answer<<endl;
	

}
