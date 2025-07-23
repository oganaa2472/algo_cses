#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int M = 1000000007;

int solve(int n,vector<int>& dp){
    if (n == 0) return 0;
    if (dp[n] != -1) return dp[n];

    int ans = INT_MAX;
    int temp = n;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit > 0) {
            ans = min(ans, 1 + solve(n - digit,dp));
        }
        temp /= 10;
    }
    return dp[n] = ans;
}
int main() {
    int n;
    cin >> n;

    vector<int> dp(n+1,-1);

    cout << solve(n,dp) << "\n";
}