#include <bits/stdc++.h>
using namespace std;
const int MOD = (int)1e9 + 7;
// using tabular solution 

int main(){
    long long n,k; 
    cin>>n>>k;

    vector<long long> coins(n);
    vector<long long> dp(k+1,0);
    dp[0] = 1;
    for(int i = 0;i<n;i++) cin>>coins[i];
    //  tabular solution
    for (auto c : coins) {
			for(long long x = 1;x<=k;x++) {
				if (x-c >= 0) {
					dp[x]+= (dp[x-c]);
                     dp[x] %=MOD; 
				}
               
            }
		}

    
    
    cout<<dp[k];
}
// #include <bits/stdc++.h>
// using namespace std;

// const long long mod = 1e9+7;

// int dfs(long long sum, vector<long long>& coins, long long amount, long long index, vector<vector<long long>>& memo) {
//     if (sum == amount) return 1; // Found a valid combination
//     if (sum > amount || index >= static_cast<long long>(coins.size())) return 0; // Out of bounds

//     // Check if the result is already computed
//     if (memo[sum][index] != -1) {
//         return memo[sum][index];
//     }

//     // Option 1: Include the current coin
//     int include = dfs(sum + coins[index], coins, amount, index, memo);

//     // Option 2: Exclude the current coin
//     int exclude = dfs(sum, coins, amount, index + 1, memo);

//     // Store result in memo table and return
//     memo[sum][index] = (include + exclude) % mod;
//     return memo[sum][index];
// }

// int main() {
//     long long n, m;
//     cin >> n >> m;
//     vector<long long> coins(n);
//     for (int i = 0; i < n; i++) {
//         cin >> coins[i];
//     }

//     // Memoization table
//     vector<vector<long long>> memo(m + 1, vector<long long>(n, -1));

//     // Solve using the dfs function
//     cout << dfs(0, coins, m, 0, memo) << endl;

//     return 0;
// }
