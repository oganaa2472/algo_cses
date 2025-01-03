#include <bits/stdc++.h>
using namespace std;
int mod = 1e9+7;
int solve(int n,vector<int> dp){
    if(n<0) return 0;
    if(n==0) return 1;
    if(dp[n]!=-1) return dp[n];
    
    int ans = 0;
    for(int i = 1;i<=6;i++){
        if(n-i>=0){
            ans += solve(n-i,dp);
        }
        
    }
    return dp[n] = ans%mod;   
}
int main() {
	// your code goes here
	int n;
	cin>>n;
	vector<int> dp(n+1,-1);
	int answer = solve(n,dp);
	cout<<answer<<endl;
	

}
