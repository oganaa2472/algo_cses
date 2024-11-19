#include <bits/stdc++.h>
const int MOD = 1e9+7;
using namespace std;
long long solve(vector<long long>& dp,vector<long long>& coins,long long x){
	if(x<0) return 0;
	if(x==0) return 1;
	if(dp[x]!=-1) return dp[x];
	long long ans=0;
	for(auto coin:coins){
		ans=(ans+solve(dp,coins,x-coin))%MOD;
	}
	
	return dp[x] = ans%MOD;
}
int main() {
	// your code goes here
	long long n,x;
	cin>>n>>x;
	vector<long long> coins(n);
	vector<long long> dp(x+1,-1);
	for(int i = 0;i<n;i++) cin>>coins[i];
	
	int ans = solve(dp,coins,x);
	cout<<ans<<endl;
	return 0;
}