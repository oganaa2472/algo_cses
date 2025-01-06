#include <bits/stdc++.h>
using namespace std;

int mod = 1e9+7;
int main() {
	// your code goes here
	
	int n;
	cin>>n;
	vector<vector<char>> ch(n,vector<char>(n));
	
	for(int i = 0;i<n;i++){
	    for(int j=0;j<n;j++){
	       cin>>ch[i][j];
	    }
	}
	
	vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    dp[0][0] = ch[0][0]=='.'?1:0;
    for(int i =0;i<n;i++){
		for(int j = 0 ;j<n;j++){
			if(ch[i][j]=='.'){
				if(i-1>=0&&ch[i-1][j]!='*'){
					dp[i][j] = (dp[i][j]+dp[i-1][j])%mod;
				}
				if(j-1>=0&&ch[i][j-1]!='*'){
					dp[i][j] = (dp[i][j]+dp[i][j-1])%mod;
				}
			}
		}
    }
	cout<<dp[n-1][n-1]; 
}
