// #include <bits/stdc++.h>
// using namespace std;
// const int MOD = (int)1e9 + 7;
// // using tabular solution 

// int main(){
//     long long n,k; 
//     cin>>n>>k;

//     vector<long long> coins(n);
//     vector<long long> dp(k+1,0);
//     dp[0] = 1;
//     for(int i = 0;i<n;i++) cin>>coins[i];
//     //  tabular solution
//     for (auto c : coins) {
// 			for(long long x = 1;x<=k;x++) {
//                 cout<<dp[x]<<" ";
// 				if (x-c >= 0) {
// 					dp[x]+= (dp[x-c]);
//                      dp[x] %=MOD; 
// 				}
               
//             }
// 		}

    
    
//     cout<<dp[k];
// }

#include <bits/stdc++.h>
using namespace std;

const int MOD = (int)1e9 + 7;

long long countWays(int k, const vector<long long>& coins, vector<long long>& memo) {
    if (k == 0) return 1; // Base case: one way to make sum 0
    if (k < 0) return 0;  // Base case: no way to make a negative sum
    if (memo[k] != -1) return memo[k]; // Return cached result

    long long ways = 0;
    for (auto c : coins) {
        if (k - c >= 0) {
            ways += countWays(k - c, coins, memo);
            ways %= MOD; // Modulo operation to avoid overflow
        }
    }

    return memo[k] = ways; // Cache and return result
}

int main() {
    long long n, k;
    cin >> n >> k;

    vector<long long> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    vector<long long> memo(k + 1, -1); // Initialize memoization table with -1
    cout << countWays(k, coins, memo) << endl;

    return 0;
}
