// #include <iostream>
// #include <vector>
// #include <climits>
// using namespace std;

// long long MOD = 1e9 + 7;

// int main() {
//     long long n,x;
//     cin >> n>>x;
//     vector<long long> dp(x+1,INT_MAX);
//     vector<long long> coins(n);
//     for(int i =0;i<n;i++) cin>>coins[i];
// 	dp[0] = 0;
//     for(int i = 1;i<=x;i++){
//         for(auto coin:coins){
//             if(i-coin>=0){
//                 dp[i] = min(dp[i], dp[i-coin]+1);
//             }
//         }
//     }
//    if(dp[x]==INT_MAX) cout<<-1<<endl;
//    else cout<<dp[x]<<endl;
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
int mod = 1e9+7;
int solve(int m,vector<int>& dp,vector<int>& coins){
    if (m == 0) return 0; 
    if (m < 0) return INT_MAX; 

    if (dp[m] != -1) return dp[m];

    int ans = INT_MAX;
    for (int coin : coins) {
        int res = solve(m - coin, dp,coins);
        if (res != INT_MAX) { 
            ans = min(ans, res + 1);
        }
    }

    return dp[m] = ans;
}
int main() {
	// your code goes here
	int n,m;
	cin>>n>>m;
	vector<int> coins(n);
	vector<int> dp(m+1,-1);
	for(int i=0;i<n;i++){
	    cin>>coins[i];
	}
	int answer = solve(m,dp,coins);
	if(answer==INT_MAX) cout<<-1<<endl;
	else cout<<answer<<endl;
	

}
